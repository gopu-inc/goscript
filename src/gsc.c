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

typedef struct { _CFunc f; fe_Number n; void *p; char c; } Value;

struct fe_Object {
  union { fe_Object *o; char c; int i; } car;
  union { fe_Object *o; int i; } cdr;
  Value v;
};

struct fe_Context {
  fe_Handlers handlers;
  fe_Object *objects;
  int object_count;
  fe_Object **gcstack;
  int gcstack_size;
  int gcstack_idx;
  fe_Object *symlist;
  fe_Object *t;
  fe_Object *nil;
  fe_ReadFn readfp;
  fe_WriteFn writefp;
  void *udata;
  char next_char;
  int line;
};
// Remplacer la ligne 28:
typedef struct { fe_CFunc f; fe_Number n; void *p; char c; } Value;
// Note: fe_CFunc est déjà défini dans gsc.h

// Ajouter ces fonctions après eval() ou avant leur utilisation:

/* Lecture depuis un FILE* */
fe_Object* fe_readfp(fe_Context *ctx, FILE *fp) {
    // Sauvegarder l'ancien readfp
    fe_ReadFn old_read = ctx->readfp;
    void *old_udata = ctx->udata;
    
    // Configurer pour lire depuis le fichier
    ctx->readfp = (fe_ReadFn)fgetc;
    ctx->udata = fp;
    
    // Lire une expression
    fe_Object *obj = parse_expr(ctx);
    
    // Restaurer l'ancienne configuration
    ctx->readfp = old_read;
    ctx->udata = old_udata;
    
    return obj;
}

/* Évaluation simplifiée */
fe_Object* fe_eval(fe_Context *ctx, fe_Object *obj) {
    return eval(ctx, obj, ctx->nil);
}
/* --- Garbage Collector --- */

static void mark(fe_Context *ctx, fe_Object *obj) {
  fe_Object *nil = ctx->nil;
  if (obj == nil || (tag(obj) & 0x80)) return;
  int t = tag(obj);
  settype(obj, t | 0x80);
  if (t == FE_TPAIR) {
    mark(ctx, car(obj));
    mark(ctx, cdr(obj));
  }
}

static void collectgarbage(fe_Context *ctx) {
  int i;
  /* Mark */
  mark(ctx, ctx->symlist);
  for (i = 0; i < ctx->gcstack_idx; i++) mark(ctx, ctx->gcstack[i]);
  if (ctx->handlers.mark) ctx->handlers.mark(ctx, NULL);
  /* Sweep */
  for (i = 0; i < ctx->object_count; i++) {
    fe_Object *obj = &ctx->objects[i];
    if (tag(obj) & 0x80) {
      settype(obj, tag(obj) & ~0x80);
    } else if (tag(obj) != FE_TFREE) {
      settype(obj, FE_TFREE);
      cdr(obj) = (fe_Object*) ctx->nil; /* simple free link */
    }
  }
}

/* --- Core Internal Functions --- */

static fe_Object* object(fe_Context *ctx) {
  fe_Object *obj = NULL;
  /* find free object */
  for (int i = 0; i < ctx->object_count; i++) {
    if (tag(&ctx->objects[i]) == FE_TFREE) {
      obj = &ctx->objects[i];
      break;
    }
  }
  if (!obj) {
    collectgarbage(ctx);
    fe_error(ctx, "out of memory");
  }
  fe_pushgc(ctx, obj);
  return obj;
}

fe_Object* fe_cons(fe_Context *ctx, fe_Object *car, fe_Object *cdr) {
  fe_Object *obj = object(ctx);
  settype(obj, FE_TPAIR);
  car(obj) = car;
  cdr(obj) = cdr;
  return obj;
}

fe_Object* fe_symbol(fe_Context *ctx, const char *name) {
  fe_Object *obj;
  for (obj = ctx->symlist; obj != ctx->nil; obj = cdr(obj)) {
    if (!strcmp(strbuf(car(obj)), name)) return car(obj);
  }
  obj = object(ctx);
  settype(obj, FE_TSYMBOL);
  strcpy(strbuf(obj), name);
  ctx->symlist = fe_cons(ctx, obj, ctx->symlist);
  return obj;
}

fe_Object* fe_number(fe_Context *ctx, fe_Number n) {
  fe_Object *obj = object(ctx);
  settype(obj, FE_TNUMBER);
  number(obj) = n;
  return obj;
}

fe_Object* fe_string(fe_Context *ctx, const char *str) {
  fe_Object *obj = object(ctx);
  settype(obj, FE_TSTRING);
  strcpy(strbuf(obj), str);
  return obj;
}

/* --- Lexer & Parser (Rust-like Syntax) --- */

typedef enum {
  TK_EOF, TK_ERROR, TK_LET, TK_FN, TK_IF, TK_ELSE, TK_WHILE,
  TK_SYM, TK_NUM, TK_STR, TK_LPAREN, TK_RPAREN, TK_LBRACE, TK_RBRACE,
  TK_EQ, TK_COMMA, TK_COLON, TK_SEMICOLON, TK_DBLCOLON
} Token;

static char next(fe_Context *ctx) {
  char c = ctx->next_char;
  ctx->next_char = ctx->readfp(ctx, ctx->udata);
  if (c == '\n') ctx->line++;
  return c;
}

static char peek(fe_Context *ctx) {
  return ctx->next_char;
}

static Token get_token(fe_Context *ctx, char *buf) {
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
    while (isalnum(peek(ctx)) || peek(ctx) == '_' || peek(ctx) == '-' || peek(ctx) == '/') buf[i++] = next(ctx);
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
    while (peek(ctx) != '"' && peek(ctx) != '\0') buf[i++] = next(ctx);
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
static fe_Object* parse_expr(fe_Context *ctx);

static fe_Object* parse_block(fe_Context *ctx) {
  char buf[256];
  fe_Object *res = ctx->nil;
  fe_Object **tail = &res;
  while (1) {
    Token t = get_token(ctx, buf);
    if (t == TK_RBRACE || t == TK_EOF) break;
    /* On "repousse" le token pour parse_expr */
    /* Note: Dans un vrai interpréteur, on utilise un unget_token. 
       Ici on simplifie la logique de boucle */
    *tail = fe_cons(ctx, parse_expr(ctx), ctx->nil);
    tail = &cdr(*tail);
  }
  return fe_cons(ctx, fe_symbol(ctx, "do"), res);
}

static fe_Object* parse_expr(fe_Context *ctx) {
  char buf[256];
  Token t = get_token(ctx, buf);

  if (t == TK_NUM) return fe_number(ctx, atof(buf));
  if (t == TK_STR) return fe_string(ctx, buf);
  if (t == TK_SYM) {
    fe_Object *s = fe_symbol(ctx, buf);
    if (peek(ctx) == '(') { /* Appel de fonction : print(x) -> (print x) */
      next(ctx); // (
      fe_Object *args = ctx->nil;
      fe_Object **tail = &args;
      while (peek(ctx) != ')') {
        *tail = fe_cons(ctx, parse_expr(ctx), ctx->nil);
        tail = &cdr(*tail);
        if (peek(ctx) == ',') next(ctx);
      }
      next(ctx); // )
      return fe_cons(ctx, s, args);
    }
    return s;
  }

  if (t == TK_LET) { /* let x = 10 -> (= x 10) */
    get_token(ctx, buf);
    fe_Object *var = fe_symbol(ctx, buf);
    get_token(ctx, buf); // assume =
    fe_Object *val = parse_expr(ctx);
    return fe_list(ctx, (fe_Object*[]){ fe_symbol(ctx, "="), var, val }, 3);
  }

  if (t == TK_FN) { /* fn name(a, b) { ... } */
    get_token(ctx, buf);
    fe_Object *name = fe_symbol(ctx, buf);
    get_token(ctx, buf); // (
    fe_Object *args = ctx->nil;
    fe_Object **tail = &args;
    while (peek(ctx) != ')') {
      get_token(ctx, buf);
      *tail = fe_cons(ctx, fe_symbol(ctx, buf), ctx->nil);
      tail = &cdr(*tail);
      if (peek(ctx) == ',') next(ctx);
    }
    next(ctx); // )
    get_token(ctx, buf); // {
    fe_Object *body = parse_block(ctx);
    fe_Object *lambda = fe_list(ctx, (fe_Object*[]){ fe_symbol(ctx, "fn"), args, body }, 3);
    return fe_list(ctx, (fe_Object*[]){ fe_symbol(ctx, "="), name, lambda }, 3);
  }

  if (t == TK_IF) { /* if (cond) { ... } else { ... } */
    fe_Object *cond = parse_expr(ctx);
    get_token(ctx, buf); // {
    fe_Object *then_b = parse_block(ctx);
    fe_Object *else_b = ctx->nil;
    if (peek(ctx) == 'e') { /* Simplification pour else */
      get_token(ctx, buf); // else
      get_token(ctx, buf); // {
      else_b = parse_block(ctx);
    }
    return fe_list(ctx, (fe_Object*[]){ fe_symbol(ctx, "if"), cond, then_b, else_b }, 4);
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

static fe_Object* eval(fe_Context *ctx, fe_Object *obj, fe_Object *env);

static fe_Object* evlist(fe_Context *ctx, fe_Object *obj, fe_Object *env) {
  fe_Object *res = ctx->nil;
  fe_Object **tail = &res;
  while (obj != ctx->nil) {
    *tail = fe_cons(ctx, eval(ctx, fe_nextarg(ctx, &obj), env), ctx->nil);
    tail = &cdr(*tail);
  }
  return res;
}

static fe_Object* eval(fe_Context *ctx, fe_Object *obj, fe_Object *env) {
  if (tag(obj) == TK_NUM || tag(obj) == TK_STR) return obj;
  if (tag(obj) == TK_SYM) {
    /* lookup env */
    while (env != ctx->nil) {
      fe_Object *bind = car(env);
      if (car(bind) == obj) return cdr(bind);
      env = cdr(env);
    }
    fe_error(ctx, "unbound variable");
  }
  if (tag(obj) == FE_TPAIR) {
    fe_Object *fn = eval(ctx, car(obj), env);
    fe_Object *args = cdr(obj);
    if (tag(fn) == FE_TPRIM) {
      /* Primitives execution logic (Switch case) */
      switch (prim(fn)) {
        case P_ADD: {
          fe_Number n = 0;
          while (args != ctx->nil) n += number(eval(ctx, fe_nextarg(ctx, &args), env));
          return fe_number(ctx, n);
        }
        // Dans la fonction eval(), remplacer les lignes 339-341:
case P_PRINT: {
    while (args != ctx->nil) {
        fe_Object *v = eval(ctx, fe_nextarg(ctx, &args), env);
        // Correction: utiliser printf directement au lieu de fe_write
        if (tag(v) == FE_TNUMBER) {
            printf("%g", number(v));
        } else if (tag(v) == FE_TSTRING) {
            printf("%s", strbuf(v));
        } else if (tag(v) == FE_TSYMBOL) {
            printf("%s", strbuf(v));
        } else {
            printf("#<object>");
        }
        printf(args != ctx->nil ? " " : "");
    }
    printf("\n");
    return ctx->nil;
}
        case P_SET: {
          fe_Object *sym = fe_nextarg(ctx, &args);
          fe_Object *val = eval(ctx, fe_nextarg(ctx, &args), env);
          /* global set */
          fe_Object *pair = fe_cons(ctx, sym, val);
          ctx->symlist = fe_cons(ctx, pair, ctx->symlist);
          return val;
        }
        /* ... more primitives ... */
      }
    }
    if (tag(fn) == FE_TFUNC) {
      fe_Object *params = car(cdr(fn));
      fe_Object *body = car(cdr(cdr(fn)));
      fe_Object *new_env = car(fn); // closure
      fe_Object *ev_args = evlist(ctx, args, env);
      /* bind params */
      while (params != ctx->nil) {
        new_env = fe_cons(ctx, fe_cons(ctx, car(params), car(ev_args)), new_env);
        params = cdr(params); ev_args = cdr(ev_args);
      }
      return eval(ctx, body, new_env);
    }
  }
  return obj;
}

/* --- Public API --- */

fe_Context* fe_open(void *ptr, int size) {
  fe_Context *ctx = ptr;
  memset(ctx, 0, sizeof(fe_Context));
  ctx->objects = (fe_Object*) (ctx + 1);
  ctx->object_count = (size - sizeof(fe_Context)) / sizeof(fe_Object);
  ctx->gcstack = (fe_Object**) &ctx->objects[ctx->object_count]; /* heuristic placement */
  
  static fe_Object nil_obj = { { (fe_Object*) FE_TNIL }, { (fe_Object*) FE_TNIL } };
  ctx->nil = &nil_obj;
  ctx->symlist = ctx->nil;
  
  /* Register primitives */
  for (int i = 0; i < P_MAX; i++) {
    fe_Object *p = object(ctx);
    settype(p, FE_TPRIM);
    prim(p) = i;
    /* Bind to global */
    fe_Object *sym = fe_symbol(ctx, primnames[i]);
    ctx->symlist = fe_cons(ctx, fe_cons(ctx, sym, p), ctx->symlist);
  }
  
  /* fs_init(ctx);  <- À appeler ici si fs.c est lié */
  
  return ctx;
}

/* --- REPL / Main --- */

#ifdef FE_STANDALONE

static char read_file(fe_Context *ctx, void *udata) {
  unused(ctx);
  return fgetc((FILE*) udata);
}

int main(int argc, char **argv) {
  char memory[1024 * 512]; // 512KB pour GoScript
  fe_Context *ctx = fe_open(memory, sizeof(memory));
  ctx->readfp = read_file;

  if (argc > 1) {
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;
    ctx->udata = f;
    while (peek(ctx) != EOF && peek(ctx) != '\0') {
      fe_Object *obj = parse_expr(ctx);
      eval(ctx, obj, ctx->nil);
    }
    fclose(f);
  } else {
    printf("GoScript GJS 1.0 (Syntax: Native Rust-like)\n> ");
    ctx->udata = stdin;
    while (1) {
      fe_Object *obj = parse_expr(ctx);
      fe_Object *res = eval(ctx, obj, ctx->nil);
      // fe_write(ctx, res, stdout, 1);
      printf("\nGS> ");
    }
  }
  return 0;
}

#endif
