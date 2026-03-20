/*
** GoScript (GJS) Interpreter
** Core Implementation - GOPU INC 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include "gsc.h"

/* --- Macros internes --- */

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

/* --- Structures internes --- */

typedef struct { gs_CFunc f; gs_Number n; void *p; char c; } Value;

struct gs_Object {
  union { gs_Object *o; char c; int i; } car;
  union { gs_Object *o; int i; } cdr;
  Value v;
};

struct gs_Context {
  gs_Handlers handlers;
  gs_Object *objects;
  gs_Object **gcstack;
  int object_count;
  int gcstack_idx;
  int gcstack_max;
  gs_Object *nil;
  gs_Object *t;
  gs_Object *sym_list;
  gs_ReadFn readfp;
  void *udata;
  char lookahead;
  jmp_buf error_jmp;
};

/* --- Gestion des erreurs --- */

void gs_error(gs_Context *ctx, const char *msg) {
  if (ctx->handlers.error) {
    ctx->handlers.error(ctx, msg, NULL);
  } else {
    fprintf(stderr, "Error: %s\n", msg);
  }
  exit(1);
}

/* --- Garbage Collector --- */

void gs_mark(gs_Context *ctx, gs_Object *obj) {
  int t;
  if (!obj || (t = tag(obj)) & 0x80) return;
  settype(obj, t | 0x80);
  if (t == GS_TPAIR) {
    gs_mark(ctx, car(obj));
    gs_mark(ctx, cdr(obj));
  } else if (t == GS_TSYMBOL || t == GS_TFUNC || t == GS_TMACRO) {
    gs_mark(ctx, car(obj));
    gs_mark(ctx, cdr(obj));
  }
}

static void collectgarbage(gs_Context *ctx) {
  int i;
  /* Mark */
  gs_mark(ctx, ctx->nil);
  gs_mark(ctx, ctx->t);
  gs_mark(ctx, ctx->sym_list);
  for (i = 0; i < ctx->gcstack_idx; i++) {
    gs_mark(ctx, ctx->gcstack[i]);
  }
  /* Sweep */
  for (i = 0; i < ctx->object_count; i++) {
    int t = tag(&ctx->objects[i]);
    if (t & 0x80) {
      settype(&ctx->objects[i], t & 0x7f);
    } else if (t != GS_TFREE) {
      settype(&ctx->objects[i], GS_TFREE);
    }
  }
}

static gs_Object* object(gs_Context *ctx) {
  gs_Object *obj = NULL;
  int i;
  for (i = 0; i < ctx->object_count; i++) {
    if (tag(&ctx->objects[i]) == GS_TFREE) {
      obj = &ctx->objects[i];
      break;
    }
  }
  if (!obj) {
    collectgarbage(ctx);
    for (i = 0; i < ctx->object_count; i++) {
      if (tag(&ctx->objects[i]) == GS_TFREE) {
        obj = &ctx->objects[i];
        break;
      }
    }
    if (!obj) gs_error(ctx, "out of memory");
  }
  settype(obj, GS_TNIL); /* Par sécurité */
  return obj;
}

void gs_pushgc(gs_Context *ctx, gs_Object *obj) {
  if (ctx->gcstack_idx >= ctx->gcstack_max) {
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

/* --- Constructeurs d'objets --- */

gs_Object* gs_cons(gs_Context *ctx, gs_Object *a, gs_Object *b) {
  gs_Object *obj = object(ctx);
  car(obj) = a;
  cdr(obj) = b;
  settype(obj, GS_TPAIR);
  return obj;
}

gs_Object* gs_number(gs_Context *ctx, gs_Number n) {
  gs_Object *obj = object(ctx);
  number(obj) = n;
  settype(obj, GS_TNUMBER);
  return obj;
}

gs_Object* gs_bool(gs_Context *ctx, int b) {
  return b ? ctx->t : ctx->nil;
}

gs_Object* gs_symbol(gs_Context *ctx, const char *name) {
  gs_Object *obj;
  /* Recherche si le symbole existe déjà */
  for (obj = ctx->sym_list; obj != ctx->nil; obj = cdr(obj)) {
    if (strcmp(name, (char*)strbuf(car(obj))) == 0) return car(obj);
  }
  /* Création du nouveau symbole */
  int len = strlen(name);
  obj = object(ctx);
  settype(obj, GS_TSYMBOL);
  memcpy(strbuf(obj), name, len + 1);
  car(obj) = ctx->nil; /* Valeur par défaut */
  ctx->sym_list = gs_cons(ctx, obj, ctx->sym_list);
  return obj;
}

/* --- Parser / Reader (Simplifié) --- */

static char next(gs_Context *ctx) {
  char c = ctx->lookahead;
  if (c) { ctx->lookahead = 0; return c; }
  return ctx->readfp(ctx, ctx->udata);
}

static char peek(gs_Context *ctx) {
  if (ctx->lookahead) return ctx->lookahead;
  return ctx->lookahead = ctx->readfp(ctx, ctx->udata);
}

static void skip_ws(gs_Context *ctx) {
  while (isspace(peek(ctx))) next(ctx);
}

static gs_Object* parse_expr(gs_Context *ctx) {
  skip_ws(ctx);
  char c = peek(ctx);
  if (isdigit(c)) {
    float n = 0;
    while (isdigit(peek(ctx))) n = n * 10 + (next(ctx) - '0');
    return gs_number(ctx, n);
  }
  if (isalpha(c)) {
    char buf[64]; int i = 0;
    while (isalnum(peek(ctx)) && i < 63) buf[i++] = next(ctx);
    buf[i] = '\0';
    return gs_symbol(ctx, buf);
  }
  /* Parenthèses, listes, etc. à implémenter ici */
  next(ctx);
  return ctx->nil;
}

/* --- Initialisation du Contexte --- */

gs_Context* gs_open(void *ptr, int size) {
  gs_Context *ctx = (gs_Context*)ptr;
  memset(ctx, 0, sizeof(gs_Context));

  /* Configuration de la pile du GC */
  int gc_stack_slots = 2048;
  int gc_stack_bytes = gc_stack_slots * sizeof(gs_Object*);

  /* Calcul de l'espace pour les objets */
  int usable_size = size - sizeof(gs_Context) - gc_stack_bytes;
  ctx->object_count = usable_size / sizeof(gs_Object);
  
  if (ctx->object_count < 100) {
    fprintf(stderr, "Fatal: memory block too small\n");
    exit(1);
  }

  ctx->objects = (gs_Object*)((char*)ptr + sizeof(gs_Context));
  ctx->gcstack = (gs_Object**)(&ctx->objects[ctx->object_count]);
  ctx->gcstack_max = gc_stack_slots;
  ctx->gcstack_idx = 0;

  /* IMPORTANT: Initialisation de tous les objets à FREE */
  for (int i = 0; i < ctx->object_count; i++) {
    settype(&ctx->objects[i], GS_TFREE);
  }

  /* Création des objets de base */
  ctx->nil = object(ctx);
  settype(ctx->nil, GS_TNIL);
  
  ctx->sym_list = ctx->nil;
  ctx->t = gs_symbol(ctx, "t");

  return ctx;
}

/* --- Standalone Main --- */

#ifdef GS_STANDALONE

static char file_read(gs_Context *ctx, void *udata) {
  unused(ctx);
  int c = fgetc((FILE*)udata);
  return (c == EOF) ? '\0' : (char)c;
}

int main(int argc, char **argv) {
  static char memory[1024 * 1024]; /* 1MB */
  gs_Context *ctx = gs_open(memory, sizeof(memory));

  if (argc > 1) {
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;
    ctx->readfp = file_read;
    ctx->udata = f;
    
    /* REPL Loop */
    while (peek(ctx) != '\0') {
      int gc = gs_savegc(ctx);
      gs_Object *obj = parse_expr(ctx);
      /* eval(obj) et print(obj) ici */
      gs_restoregc(ctx, gc);
      skip_ws(ctx);
    }
    fclose(f);
  }
  return 0;
}
#endif
