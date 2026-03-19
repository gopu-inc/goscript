/*
** GoScript (GJS) Header
** GOPU INC - 2026
** Defining the core structures for the GoScript Runtime.
*/

#ifndef GSC_H
#define GSC_H

#include <stdio.h>
#include <setjmp.h>

/* --- Configuration & Version --- */
#define GSC_VERSION "1.0.0"
typedef float gs_Number; /* Type numérique de base */

/* --- Types d'objets GoScript --- */
enum {
  GS_TPAIR = 1,      /* Liste / Paire cons */
  GS_TFREE,          /* Objet libre (Garbage Collector) */
  GS_TNIL,           /* Valeur nulle / Fin de liste */
  GS_TNUMBER,        /* Nombre (float) */
  GS_TSYMBOL,        /* Symbole / Identifiant */
  GS_TSTRING,        /* Chaîne de caractères */
  GS_TFUNC,          /* Fonction (Closure) */
  GS_TMACRO,         /* Macro */
  GS_TPRIM,          /* Primitive native (C interne) */
  GS_TCFUNC,         /* Fonction C externe (Callback) */
  GS_TPTR            /* Pointeur brut (pour extensions) */
};

/* --- Définitions des types opaques --- */
typedef struct gs_Object gs_Object;
typedef struct gs_Context gs_Context;

/* --- Prototypes des fonctions de rappel (Callbacks) --- */
typedef gs_Object* (*gs_CFunc)(gs_Context *ctx, gs_Object *args);
typedef void (*gs_ErrorFn)(gs_Context *ctx, const char *err, gs_Object *cl);
typedef void (*gs_WriteFn)(gs_Context *ctx, void *udata, char chr);
typedef char (*gs_ReadFn)(gs_Context *ctx, void *udata);

typedef struct {
  gs_ErrorFn error;
  gs_CFunc mark;
  gs_CFunc gc;
} gs_Handlers;

/* --- Fonctions de Gestion du Contexte --- */
gs_Context* gs_open(void *ptr, int size);
void gs_close(gs_Context *ctx);
gs_Handlers* gs_handlers(gs_Context *ctx);
void gs_error(gs_Context *ctx, const char *msg);

/* --- Fonctions du Garbage Collector (GC) --- */
void gs_pushgc(gs_Context *ctx, gs_Object *obj);
void gs_restoregc(gs_Context *ctx, int idx);
int gs_savegc(gs_Context *ctx);
void gs_mark(gs_Context *ctx, gs_Object *obj);

/* --- Création d'objets --- */
gs_Object* gs_cons(gs_Context *ctx, gs_Object *car, gs_Object *cdr);
gs_Object* gs_bool(gs_Context *ctx, int b);
gs_Object* gs_number(gs_Context *ctx, gs_Number n);
gs_Object* gs_string(gs_Context *ctx, const char *str);
gs_Object* gs_symbol(gs_Context *ctx, const char *name);
gs_Object* gs_cfunc(gs_Context *ctx, gs_CFunc fn);
gs_Object* gs_ptr(gs_Context *ctx, void *ptr);
gs_Object* gs_list(gs_Context *ctx, gs_Object **objs, int n);

/* --- Accès aux données des objets --- */
gs_Object* gs_car(gs_Context *ctx, gs_Object *obj);
gs_Object* gs_cdr(gs_Context *ctx, gs_Object *obj);
gs_Object* gs_nextarg(gs_Context *ctx, gs_Object **arg);
int gs_type(gs_Context *ctx, gs_Object *obj);
int gs_isnil(gs_Context *ctx, gs_Object *obj);
gs_Number gs_tonumber(gs_Context *ctx, gs_Object *obj);
void gs_tostring(gs_Context *ctx, gs_Object *obj, char *dst, int size);
void* gs_toptr(gs_Context *ctx, gs_Object *obj);

/* --- Entrées / Sorties --- */
gs_Object* gs_read(gs_Context *ctx, gs_ReadFn fn, void *udata);
gs_Object* gs_readfp(gs_Context *ctx, FILE *fp);
void gs_write(gs_Context *ctx, gs_Object *obj, gs_WriteFn fn, void *udata, int quoted);

/* --- Évaluation --- */
gs_Object* gs_eval(gs_Context *ctx, gs_Object *obj);

/* --- Fonctions utilitaires --- */
void gs_set(gs_Context *ctx, gs_Object *sym, gs_Object *v);

/* --- Nouveau : Prototypes pour les modules natifs --- */
#ifdef __cplusplus
extern "C" {
#endif

/* Module système de fichiers */
void fs_init(gs_Context *ctx);

#ifdef __cplusplus
}
#endif

#endif /* GSC_H */
