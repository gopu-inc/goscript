/*
** GoScript (GJS) Interpreter
** Derived from fe, restructured for Rust-like syntax.
** GOPU INC - 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include "gsc.h"

/* --- Macros & Types --- */

#define unused(x)     ( (void) (x) )
#define car(x)        ( (x)->car.o )
#define cdr(x)        ( (x)->cdr.o )
#define tag(x)        ( (x)->car.c )
#define strbuf(x)     ( &(x)->car.c + 1 )
#define rbuf(x)       ( (unsigned char*) &(x)->car.c + 1 )
#define prim(x)       ( (x)->cdr.i )
#define number(x)     ( (x)->v.n )
#define cfunc(x)      ( (x)->v.f )
#define ptr(x)        ( (x)->v.p )
#define settype(x, t) ( (x)->car.c = (t) )

typedef struct { gs_CFunc f; gs_Number n; void *p; char c; } Value;

struct gs_Object {
  union { gs_Object *o; char c; int i; } car;
  union { gs_Object *o; int i; } cdr;
  Value v;
};

struct gs_Context {
  gs_Handlers handlers;
  gs_Object *objects;
  int object_count;
  gs_Object **gcstack;
  int gcstack_size;
  int gcstack_idx;
  gs_Object *symlist;
  gs_Object *t;
  gs_Object *nil;
  gs_ReadFn readfp;
  gs_WriteFn writefp;
  void *udata;
  char next_char;
  int line;
  jmp_buf *jmp;
};

/* --- Garbage Collector --- */

static void mark(gs_Context *ctx, gs_Object *obj) {
  gs_Object *nil = ctx->nil;
  if (obj == nil || (tag(obj) & 0x80)) return;
  int t = tag(obj);
  settype(obj, t | 0x80);
  if (t == GS_TPAIR) {
    mark(ctx, car(obj));
    mark(ctx, cdr(obj));
  }
}

static void collectgarbage(gs_Context *ctx) {
  int i;
  /* Mark */
  mark(ctx, ctx->symlist);
  for (i = 0; i < ctx->gcstack_idx; i++) mark(ctx, ctx->gcstack[i]);
  if (ctx->handlers.mark) ctx->handlers.mark(ctx, NULL);
  /* Sweep */
  for (i = 0; i < ctx->object_count; i++) {
    gs_Object *obj = &ctx->objects[i];
    if (tag(obj) & 0x80) {
      settype(obj, tag(obj) & ~0x80);
    } else if (tag(obj) != GS_TFREE) {
      settype(obj, GS_TFREE);
      cdr(obj) = (gs_Object*) ctx->nil; /* simple free link */
    }
  }
}

/* --- Core Internal Functions --- */


static gs_Object* object(gs_Context *ctx) {
  gs_Object *obj = NULL;
  
  /* 1. Cherche un objet libre */
  for (int i = 0; i < ctx->object_count; i++) {
    if (tag(&ctx->objects[i]) == GS_TFREE) {
      obj = &ctx->objects[i];
      break;
    }
  }
  
  /* 2. Si aucun objet n'est libre, on lance le GC et on RETENTE */
  if (!obj) {
    collectgarbage(ctx);
    
    for (int i = 0; i < ctx->object_count; i++) {
      if (tag(&ctx->objects[i]) == GS_TFREE) {
        obj = &ctx->objects[i];
        break;
      }
    }
    
    /* 3. Si c'est toujours plein après le GC, là on crash vraiment */
    if (!obj) {
      gs_error(ctx, "out of memory");
    }
  }
  
  gs_pushgc(ctx, obj);
  return obj;
}

gs_Object* gs_cons(gs_Context *ctx, gs_Object *car, gs_Object *cdr) {
  gs_Object *obj = object(ctx);
  settype(obj, GS_TPAIR);
  car(obj) = car;
  cdr(obj) = cdr;
  return obj;
}

gs_Object* gs_symbol(gs_Context *ctx, const char *name) {
  gs_Object *obj;
  for (obj = ctx->symlist; obj != ctx->nil; obj = cdr(obj)) {
    if (!strcmp(strbuf(car(obj)), name)) return car(obj);
  }
  obj = object(ctx);
  settype(obj, GS_TSYMBOL);
  strcpy(strbuf(obj), name);
  ctx->symlist = gs_cons(ctx, obj, ctx->symlist);
  return obj;
}

gs_Object* gs_number(gs_Context *ctx, gs_Number n) {
  gs_Object *obj = object(ctx);
  settype(obj, GS_TNUMBER);
  number(obj) = n;
  return obj;
}

gs_Object* gs_string(gs_Context *ctx, const char *str) {
  gs_Object *obj = object(ctx);
  settype(obj, GS_TSTRING);
  strcpy(strbuf(obj), str);
  return obj;
}

gs_Object* gs_bool(gs_Context *ctx, int b) {
  return b ? ctx->t : ctx->nil;
}

gs_Object* gs_cfunc(gs_Context *ctx, gs_CFunc fn) {
  gs_Object *obj = object(ctx);
  settype(obj, GS_TCFUNC);
  cfunc(obj) = fn;
  return obj;
}

gs_Object* gs_ptr(gs_Context *ctx, void *p) {
  gs_Object *obj = object(ctx);
  settype(obj, GS_TPTR);
  ptr(obj) = p;
  return obj;
}

gs_Object* gs_list(gs_Context *ctx, gs_Object **objs, int n) {
  gs_Object *list = ctx->nil;
  for (int i = n - 1; i >= 0; i--) {
    list = gs_cons(ctx, objs[i], list);
  }
  return list;
}

/* --- Lexer & Parser (Rust-like Syntax) --- */

typedef enum {
  TK_EOF, TK_ERROR, TK_LET, TK_FN, TK_IF, TK_ELSE, TK_WHILE,
  TK_SYM, TK_NUM, TK_STR, TK_LPAREN, TK_RPAREN, TK_LBRACE, TK_RBRACE,
  TK_EQ, TK_COMMA, TK_COLON, TK_SEMICOLON, TK_DBLCOLON
} Token;

static char next(gs_Context *ctx) {
  char c = ctx->next_char;
  ctx->next_char = ctx->readfp(ctx, ctx->udata);
  if (c == '\n') ctx->line++;
  return c;
}

static char peek(gs_Context *ctx) {
  return ctx->next_char;
}

static Token get_token(gs_Context *ctx, char *buf) {
  while (isspace(peek(ctx))) next(ctx);

  char c = next(ctx);
  if (c == '\0' || c == EOF) return TK_EOF;

  if (isdigit(c)) {
    int i = 0; buf[i++] = c;
    while (isdigit(peek(ctx)) || peek(ctx) == '.') buf[i++] = next(ctx);
    buf[i] = '\0';
    return TK_NUM;
  }

  if (isalpha(c) || c == '_') {
    int i = 0; buf[i++] = c;
    while (isalnum(peek(ctx)) || peek(ctx) == '_' || peek(ctx) == '-') buf[i++] = next(ctx);
    buf[i] = '\0';
    if (!strcmp(buf, "let")) return TK_LET;
    if (!strcmp(buf, "fn")) return TK_FN;
    if (!strcmp(buf, "if")) return TK_IF;
    if (!strcmp(buf, "else")) return TK_ELSE;
    if (!strcmp(buf, "while")) return TK_WHILE;
    return TK_SYM;
  }

  if (c == '"') {
    int i = 0;
    while (peek(ctx) != '"' && peek(ctx) != '\0' && peek(ctx) != EOF) 
      buf[i++] = next(ctx);
    next(ctx); // consume closing "
    buf[i] = '\0';
    return TK_STR;
  }

  if (c == '(') return TK_LPAREN;
  if (c == ')') return TK_RPAREN;
  if (c == '{') return TK_LBRACE;
  if (c == '}') return TK_RBRACE;
  if (c == ',') return TK_COMMA;
  if (c == ';') return TK_SEMICOLON;
  if (c == '=') return TK_EQ;
  if (c == ':') {
    if (peek(ctx) == ':') { next(ctx); return TK_DBLCOLON; }
    return TK_COLON;
  }

  return TK_ERROR;
}

/* Forward declarations for Parser */
static gs_Object* parse_expr(gs_Context *ctx);

static gs_Object* parse_block(gs_Context *ctx) {
  char buf[256];
  gs_Object *res = ctx->nil;
  gs_Object **tail = &res;
  
  while (1) {
    Token t = get_token(ctx, buf);
    if (t == TK_RBRACE || t == TK_EOF) break;
    
    *tail = gs_cons(ctx, parse_expr(ctx), ctx->nil);
    tail = &cdr(*tail);
  }
  return gs_cons(ctx, gs_symbol(ctx, "do"), res);
}

static gs_Object* parse_expr(gs_Context *ctx) {
  char buf[256];
  Token t = get_token(ctx, buf);

  if (t == TK_NUM) return gs_number(ctx, atof(buf));
  if (t == TK_STR) return gs_string(ctx, buf);
  
  if (t == TK_SYM) {
    gs_Object *s = gs_symbol(ctx, buf);
    if (peek(ctx) == '(') { /* Function call: print(x) -> (print x) */
      next(ctx); // (
      gs_Object *args = ctx->nil;
      gs_Object **tail = &args;
      while (peek(ctx) != ')') {
        *tail = gs_cons(ctx, parse_expr(ctx), ctx->nil);
        tail = &cdr(*tail);
        if (peek(ctx) == ',') next(ctx);
      }
      next(ctx); // )
      return gs_cons(ctx, s, args);
    }
    return s;
  }

  if (t == TK_LET) { /* let x = 10 -> (= x 10) */
    get_token(ctx, buf);
    gs_Object *var = gs_symbol(ctx, buf);
    get_token(ctx, buf); // assume =
    gs_Object *val = parse_expr(ctx);
    return gs_list(ctx, (gs_Object*[]){ gs_symbol(ctx, "="), var, val }, 3);
  }

  if (t == TK_FN) { /* fn name(a, b) { ... } */
    get_token(ctx, buf);
    gs_Object *name = gs_symbol(ctx, buf);
    get_token(ctx, buf); // (
    gs_Object *args = ctx->nil;
    gs_Object **tail = &args;
    while (peek(ctx) != ')') {
      get_token(ctx, buf);
      *tail = gs_cons(ctx, gs_symbol(ctx, buf), ctx->nil);
      tail = &cdr(*tail);
      if (peek(ctx) == ',') next(ctx);
    }
    next(ctx); // )
    get_token(ctx, buf); // {
    gs_Object *body = parse_block(ctx);
    gs_Object *lambda = gs_list(ctx, (gs_Object*[]){ gs_symbol(ctx, "fn"), args, body }, 3);
    return gs_list(ctx, (gs_Object*[]){ gs_symbol(ctx, "="), name, lambda }, 3);
  }

  if (t == TK_IF) { /* if (cond) { ... } else { ... } */
    gs_Object *cond = parse_expr(ctx);
    get_token(ctx, buf); // {
    gs_Object *then_b = parse_block(ctx);
    gs_Object *else_b = ctx->nil;
    if (peek(ctx) == 'e') { /* Simplified else detection */
      get_token(ctx, buf); // else
      get_token(ctx, buf); // {
      else_b = parse_block(ctx);
    }
    return gs_list(ctx, (gs_Object*[]){ gs_symbol(ctx, "if"), cond, then_b, else_b }, 4);
  }

  if (t == TK_WHILE) { /* while (cond) { ... } */
    gs_Object *cond = parse_expr(ctx);
    get_token(ctx, buf); // {
    gs_Object *body = parse_block(ctx);
    return gs_list(ctx, (gs_Object*[]){ gs_symbol(ctx, "while"), cond, body }, 3);
  }

  return ctx->nil;
}

/* --- Evaluator & Primitives --- */

enum {
  P_EVAL, P_SET, P_IF, P_FN, P_MACRO, P_WHILE, P_QUOTE, P_AND, P_OR, P_DO, P_CONS, 
  P_CAR, P_CDR, P_SETCAR, P_SETCDR, P_LIST, P_NOT, P_IS, P_ATOM, P_PRINT, P_LT, 
  P_LTE, P_ADD, P_SUB, P_MUL, P_DIV, P_MAX
};

static const char *primnames[] = {
  "eval", "=", "if", "fn", "macro", "while", "quote", "and", "or", "do", "cons",
  "car", "cdr", "setcar", "setcdr", "list", "not", "is", "atom", "print", "<",
  "<=", "+", "-", "*", "/"
};

static gs_Object* eval(gs_Context *ctx, gs_Object *obj, gs_Object *env);

static gs_Object* evlist(gs_Context *ctx, gs_Object *obj, gs_Object *env) {
  gs_Object *res = ctx->nil;
  gs_Object **tail = &res;
  while (obj != ctx->nil) {
    *tail = gs_cons(ctx, eval(ctx, gs_nextarg(ctx, &obj), env), ctx->nil);
    tail = &cdr(*tail);
  }
  return res;
}

/* Error handling */
void gs_error(gs_Context *ctx, const char *msg) {
  if (ctx->handlers.error) {
    ctx->handlers.error(ctx, msg, NULL);
  }
  if (ctx->jmp) {
    longjmp(*ctx->jmp, 1);
  }
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

/* GC Functions */
void gs_pushgc(gs_Context *ctx, gs_Object *obj) {
  if (ctx->gcstack_idx >= ctx->gcstack_size) {
    gs_error(ctx, "GC stack overflow");
  }
  ctx->gcstack[ctx->gcstack_idx++] = obj;
}

void gs_restoregc(gs_Context *ctx, int idx) {
  ctx->gcstack_idx = idx;
}

int gs_savegc(gs_Context *ctx) {
  return ctx->gcstack_idx;
}

void gs_mark(gs_Context *ctx, gs_Object *obj) {
  mark(ctx, obj);
}

/* Accessors */
gs_Object* gs_car(gs_Context *ctx, gs_Object *obj) {
  unused(ctx);
  if (tag(obj) != GS_TPAIR) return ctx->nil;
  return car(obj);
}

gs_Object* gs_cdr(gs_Context *ctx, gs_Object *obj) {
  unused(ctx);
  if (tag(obj) != GS_TPAIR) return ctx->nil;
  return cdr(obj);
}

gs_Object* gs_nextarg(gs_Context *ctx, gs_Object **arg) {
  gs_Object *obj = car(*arg);
  *arg = cdr(*arg);
  return obj;
}

int gs_type(gs_Context *ctx, gs_Object *obj) {
  unused(ctx);
  return tag(obj) & 0x7F; /* Remove GC mark bit */
}

int gs_isnil(gs_Context *ctx, gs_Object *obj) {
  return obj == ctx->nil;
}

gs_Number gs_tonumber(gs_Context *ctx, gs_Object *obj) {
  if (tag(obj) == GS_TNUMBER) return number(obj);
  gs_error(ctx, "not a number");
  return 0;
}

void gs_tostring(gs_Context *ctx, gs_Object *obj, char *dst, int size) {
  if (tag(obj) == GS_TSTRING) {
    strncpy(dst, strbuf(obj), size - 1);
    dst[size - 1] = '\0';
  } else if (tag(obj) == GS_TSYMBOL) {
    strncpy(dst, strbuf(obj), size - 1);
    dst[size - 1] = '\0';
  } else if (tag(obj) == GS_TNUMBER) {
    snprintf(dst, size, "%g", number(obj));
  } else {
    snprintf(dst, size, "#<object:%d>", tag(obj));
  }
}

void* gs_toptr(gs_Context *ctx, gs_Object *obj) {
  if (tag(obj) == GS_TPTR) return ptr(obj);
  gs_error(ctx, "not a pointer");
  return NULL;
}

/* I/O */
static char file_reader(gs_Context *ctx, void *udata) {
  return fgetc((FILE*) udata);
}

gs_Object* gs_readfp(gs_Context *ctx, FILE *fp) {
  gs_ReadFn old_read = ctx->readfp;
  void *old_udata = ctx->udata;
  
  ctx->readfp = file_reader;
  ctx->udata = fp;
  
  gs_Object *obj = parse_expr(ctx);
  
  ctx->readfp = old_read;
  ctx->udata = old_udata;
  
  return obj;
}

gs_Object* gs_read(gs_Context *ctx, gs_ReadFn fn, void *udata) {
  gs_ReadFn old_read = ctx->readfp;
  void *old_udata = ctx->udata;
  
  ctx->readfp = fn;
  ctx->udata = udata;
  
  gs_Object *obj = parse_expr(ctx);
  
  ctx->readfp = old_read;
  ctx->udata = old_udata;
  
  return obj;
}

static void stdout_writer(gs_Context *ctx, void *udata, char chr) {
  unused(ctx);
  unused(udata);
  putchar(chr);
}

void gs_write(gs_Context *ctx, gs_Object *obj, gs_WriteFn fn, void *udata, int quoted) {
  if (!fn) fn = stdout_writer;
  
  switch (tag(obj) & 0x7F) {
    case GS_TNIL:
      fn(ctx, udata, 'n');
      fn(ctx, udata, 'i');
      fn(ctx, udata, 'l');
      break;
    case GS_TNUMBER: {
      char buf[32];
      sprintf(buf, "%g", number(obj));
      for (char *p = buf; *p; p++) fn(ctx, udata, *p);
      break;
    }
    case GS_TSTRING:
      if (quoted) fn(ctx, udata, '"');
      for (char *p = strbuf(obj); *p; p++) fn(ctx, udata, *p);
      if (quoted) fn(ctx, udata, '"');
      break;
    case GS_TSYMBOL:
      for (char *p = strbuf(obj); *p; p++) fn(ctx, udata, *p);
      break;
    case GS_TPAIR:
      fn(ctx, udata, '(');
      while (obj != ctx->nil && tag(obj) == GS_TPAIR) {
        gs_write(ctx, car(obj), fn, udata, quoted);
        obj = cdr(obj);
        if (obj != ctx->nil) fn(ctx, udata, ' ');
      }
      if (obj != ctx->nil) {
        fn(ctx, udata, '.');
        fn(ctx, udata, ' ');
        gs_write(ctx, obj, fn, udata, quoted);
      }
      fn(ctx, udata, ')');
      break;
    default:
      fn(ctx, udata, '#');
      fn(ctx, udata, '<');
      fn(ctx, udata, '0' + (tag(obj) & 0x7F));
      fn(ctx, udata, '>');
      break;
  }
}

/* Set global variable */
void gs_set(gs_Context *ctx, gs_Object *sym, gs_Object *v) {
  gs_Object *pair = gs_cons(ctx, sym, v);
  ctx->symlist = gs_cons(ctx, pair, ctx->symlist);
}

/* Eval public */
gs_Object* gs_eval(gs_Context *ctx, gs_Object *obj) {
  jmp_buf jmp;
  jmp_buf *old = ctx->jmp;
  ctx->jmp = &jmp;
  
  if (setjmp(jmp)) {
    ctx->jmp = old;
    return ctx->nil;
  }
  
  gs_Object *result = eval(ctx, obj, ctx->nil);
  ctx->jmp = old;
  return result;
}

/* Core eval implementation */
static gs_Object* eval(gs_Context *ctx, gs_Object *obj, gs_Object *env) {
  if (obj == ctx->nil) return ctx->nil;
  
  int t = tag(obj) & 0x7F;
  
  if (t == GS_TNUMBER || t == GS_TSTRING || t == GS_TCFUNC || t == GS_TPTR) 
    return obj;
    
  if (t == GS_TSYMBOL) {
    /* lookup env */
    while (env != ctx->nil) {
      gs_Object *bind = car(env);
      if (car(bind) == obj) return cdr(bind);
      env = cdr(env);
    }
    gs_error(ctx, "unbound variable");
  }
  
  if (t == GS_TPAIR) {
    gs_Object *fn = eval(ctx, car(obj), env);
    gs_Object *args = cdr(obj);
    
    t = tag(fn) & 0x7F;
    
    if (t == GS_TPRIM) {
      /* Primitives execution logic */
      switch (prim(fn)) {
        case P_ADD: {
          gs_Number n = 0;
          while (args != ctx->nil) 
            n += gs_tonumber(ctx, eval(ctx, gs_nextarg(ctx, &args), env));
          return gs_number(ctx, n);
        }
        case P_SUB: {
          gs_Object *first = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Number n = gs_tonumber(ctx, first);
          if (args == ctx->nil) return gs_number(ctx, -n);
          while (args != ctx->nil) 
            n -= gs_tonumber(ctx, eval(ctx, gs_nextarg(ctx, &args), env));
          return gs_number(ctx, n);
        }
        case P_MUL: {
          gs_Number n = 1;
          while (args != ctx->nil) 
            n *= gs_tonumber(ctx, eval(ctx, gs_nextarg(ctx, &args), env));
          return gs_number(ctx, n);
        }
        case P_DIV: {
          gs_Object *first = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Number n = gs_tonumber(ctx, first);
          while (args != ctx->nil) 
            n /= gs_tonumber(ctx, eval(ctx, gs_nextarg(ctx, &args), env));
          return gs_number(ctx, n);
        }
        case P_LT: {
          gs_Object *first = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Number a = gs_tonumber(ctx, first);
          gs_Object *second = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Number b = gs_tonumber(ctx, second);
          return gs_bool(ctx, a < b);
        }
        case P_LTE: {
          gs_Object *first = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Number a = gs_tonumber(ctx, first);
          gs_Object *second = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Number b = gs_tonumber(ctx, second);
          return gs_bool(ctx, a <= b);
        }
        case P_CONS: {
          gs_Object *a = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Object *b = eval(ctx, gs_nextarg(ctx, &args), env);
          return gs_cons(ctx, a, b);
        }
        case P_CAR:
          return gs_car(ctx, eval(ctx, gs_nextarg(ctx, &args), env));
        case P_CDR:
          return gs_cdr(ctx, eval(ctx, gs_nextarg(ctx, &args), env));
        case P_ATOM: {
          gs_Object *v = eval(ctx, gs_nextarg(ctx, &args), env);
          return gs_bool(ctx, (tag(v) & 0x7F) != GS_TPAIR);
        }
        case P_NOT: {
          gs_Object *v = eval(ctx, gs_nextarg(ctx, &args), env);
          return gs_bool(ctx, v == ctx->nil);
        }
        case P_IS: {
          gs_Object *a = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Object *b = eval(ctx, gs_nextarg(ctx, &args), env);
          return gs_bool(ctx, a == b);
        }
        case P_PRINT: {
          while (args != ctx->nil) {
            gs_Object *v = eval(ctx, gs_nextarg(ctx, &args), env);
            gs_write(ctx, v, NULL, NULL, 1);
            if (args != ctx->nil) printf(" ");
          }
          printf("\n");
          return ctx->nil;
        }
        case P_SET: {
          gs_Object *sym = gs_nextarg(ctx, &args);
          if ((tag(sym) & 0x7F) != GS_TSYMBOL) 
            gs_error(ctx, "set: first argument must be a symbol");
          gs_Object *val = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_set(ctx, sym, val);
          return val;
        }
        case P_IF: {
          gs_Object *cond = eval(ctx, gs_nextarg(ctx, &args), env);
          gs_Object *then_expr = gs_nextarg(ctx, &args);
          gs_Object *else_expr = args != ctx->nil ? gs_nextarg(ctx, &args) : ctx->nil;
          
          if (cond != ctx->nil) 
            return eval(ctx, then_expr, env);
          else if (else_expr != ctx->nil)
            return eval(ctx, else_expr, env);
          else
            return ctx->nil;
        }
        case P_WHILE: {
          gs_Object *cond_expr = gs_nextarg(ctx, &args);
          gs_Object *body_expr = gs_nextarg(ctx, &args);
          gs_Object *result = ctx->nil;
          
          while (1) {
            gs_Object *cond = eval(ctx, cond_expr, env);
            if (cond == ctx->nil) break;
            result = eval(ctx, body_expr, env);
          }
          return result;
        }
        case P_DO: {
          gs_Object *result = ctx->nil;
          while (args != ctx->nil) {
            result = eval(ctx, gs_nextarg(ctx, &args), env);
          }
          return result;
        }
        case P_FN: {
          gs_Object *params = gs_nextarg(ctx, &args);
          gs_Object *body = gs_nextarg(ctx, &args);
          gs_Object *func = object(ctx);
          settype(func, GS_TFUNC);
          car(func) = env; /* closure environment */
          cdr(func) = gs_cons(ctx, params, body);
          return func;
        }
        case P_LIST: {
          gs_Object *result = ctx->nil;
          gs_Object **tail = &result;
          while (args != ctx->nil) {
            *tail = gs_cons(ctx, eval(ctx, gs_nextarg(ctx, &args), env), ctx->nil);
            tail = &cdr(*tail);
          }
          return result;
        }
        default:
          gs_error(ctx, "unknown primitive");
      }
    }
    
    if (t == GS_TFUNC) {
      gs_Object *params = car(cdr(fn));
      gs_Object *body = cdr(cdr(fn));
      gs_Object *closure_env = car(fn);
      
      /* Evaluate arguments */
      gs_Object *ev_args = evlist(ctx, args, env);
      
      /* Create new environment with params bound to args */
      gs_Object *new_env = closure_env;
      while (params != ctx->nil && ev_args != ctx->nil) {
        new_env = gs_cons(ctx, 
                         gs_cons(ctx, car(params), car(ev_args)), 
                         new_env);
        params = cdr(params);
        ev_args = cdr(ev_args);
      }
      
      return eval(ctx, body, new_env);
    }
    
    if (t == GS_TCFUNC) {
      return cfunc(fn)(ctx, args);
    }
  }
  
  return obj;
}

/* Context management */
gs_Context* gs_open(void *ptr, int size) {
  gs_Context *ctx = (gs_Context*)ptr;
  memset(ctx, 0, sizeof(gs_Context));
  
  /* Calculate object pool */
  ctx->objects = (gs_Object*)((char*)ptr + sizeof(gs_Context));
  ctx->object_count = (size - sizeof(gs_Context)) / sizeof(gs_Object);
  
  /* Setup GC stack */
  ctx->gcstack = (gs_Object**)&ctx->objects[ctx->object_count];
  ctx->gcstack_size = (size - (sizeof(gs_Context) + ctx->object_count * sizeof(gs_Object))) / sizeof(gs_Object*);
  ctx->gcstack_idx = 0;
  
/* Initialize nil and t */
  static gs_Object nil_obj;
  memset(&nil_obj, 0, sizeof(gs_Object));
  nil_obj.car.c = GS_TNIL;
  nil_obj.cdr.o = NULL;
  ctx->nil = &nil_obj;
  
  static gs_Object t_obj;
  memset(&t_obj, 0, sizeof(gs_Object));
  t_obj.car.c = GS_TSYMBOL;
  t_obj.cdr.o = NULL;
  strcpy(strbuf(&t_obj), "t");
  ctx->t = &t_obj;  
  
  ctx->symlist = ctx->nil;
  ctx->line = 1;
  
  /* Register primitives */
  for (int i = 0; i < P_MAX; i++) {
    gs_Object *p = object(ctx);
    settype(p, GS_TPRIM);
    prim(p) = i;
    gs_set(ctx, gs_symbol(ctx, primnames[i]), p);
  }
  
  /* Initialize modules if available */
  #ifdef GS_HAVE_FS
  fs_init(ctx);
  #endif
  
  return ctx;
}

void gs_close(gs_Context *ctx) {
  /* Nothing to do for now */
  unused(ctx);
}

gs_Handlers* gs_handlers(gs_Context *ctx) {
  return &ctx->handlers;
}

/* --- REPL / Main --- */

#ifdef GS_STANDALONE

static char file_read(gs_Context *ctx, void *udata) {
  unused(ctx);
  return fgetc((FILE*) udata);
}

static char stdin_read(gs_Context *ctx, void *udata) {
  unused(ctx);
  unused(udata);
  int c = getchar();
  return (c == EOF) ? '\0' : c;
}

int main(int argc, char **argv) {
  char memory[1024 * 1024]; // 1MB for GoScript
  gs_Context *ctx = gs_open(memory, sizeof(memory));
  ctx->readfp = stdin_read;

  if (argc > 1) {
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
      fprintf(stderr, "Cannot open file: %s\n", argv[1]);
      return 1;
    }
    
    ctx->readfp = file_read;
    ctx->udata = f;
    
    while (peek(ctx) != EOF && peek(ctx) != '\0') {
      gs_Object *obj = parse_expr(ctx);
      if (obj != ctx->nil) {
        gs_eval(ctx, obj);
      }
    }
    
    fclose(f);
  } else {
    printf("GoScript GJS 1.0 (Syntax: Rust-like)\n");
    printf("Type 'exit' to quit\n");
    
    while (1) {
      printf("> ");
      fflush(stdout);
      
      gs_Object *obj = parse_expr(ctx);
      if (obj != ctx->nil) {
        gs_Object *res = gs_eval(ctx, obj);
        if (res != ctx->nil) {
          gs_write(ctx, res, NULL, NULL, 1);
          printf("\n");
        }
      }
    }
  }
  
  return 0;
}

#endif
