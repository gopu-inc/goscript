/*
** goscript - Un interpréteur Lisp moderne inspiré de Rust
** Copyright (c) 2026 Mauricio Mangituka
**
** Un interpréteur léger, silencieux et robuste avec une syntaxe moderne.
** Extension de fichier recommandée : .gjs
*/

#ifndef GOSCRIPT_H
#define GOSCRIPT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define GOSCRIPT_VERSION "2.0.0"
#define GOSCRIPT_MAX_SYMBOL_LEN 256
#define GOSCRIPT_GC_STACK_SIZE 512
#define GOSCRIPT_STRING_CHUNK_SIZE (sizeof(void*) - 1)

typedef double gs_Number;
typedef struct gs_Object gs_Object;
typedef struct gs_Context gs_Context;

// Type de fonction C native
typedef gs_Object* (*gs_CFunc)(gs_Context *ctx, gs_Object *args);

// Handlers pour les événements
typedef struct {
    void (*error)(gs_Context *ctx, const char *msg, gs_Object *callstack);
    void (*mark)(gs_Context *ctx, gs_Object *obj);
    void (*gc)(gs_Context *ctx, gs_Object *obj);
    void (*print)(gs_Context *ctx, const char *msg);
} gs_Handlers;

// Types d'objets supportés
typedef enum {
    GS_T_PAIR = 0,
    GS_T_FREE,
    GS_T_NIL,
    GS_T_NUMBER,
    GS_T_SYMBOL,
    GS_T_STRING,
    GS_T_FUNC,
    GS_T_MACRO,
    GS_T_PRIM,
    GS_T_CFUNC,
    GS_T_PTR,
    GS_T_BOOL,
    GS_T_ERROR
} gs_Type;

// Création et gestion du contexte
gs_Context* gs_open(void *memory, int size);
void gs_close(gs_Context *ctx);
gs_Handlers* gs_handlers(gs_Context *ctx);

// Gestion des erreurs (version unifiée avec formatage)
void gs_error(gs_Context *ctx, const char *format, ...) __attribute__((noreturn));

// API GC
void gs_push_gc(gs_Context *ctx, gs_Object *obj);
void gs_pop_gc(gs_Context *ctx, int count);
int gs_save_gc(gs_Context *ctx);
void gs_restore_gc(gs_Context *ctx, int idx);
void gs_mark(gs_Context *ctx, gs_Object *obj);
void gs_collect(gs_Context *ctx);

// Création d'objets
gs_Object* gs_cons(gs_Context *ctx, gs_Object *car, gs_Object *cdr);
gs_Object* gs_bool(gs_Context *ctx, bool value);
gs_Object* gs_number(gs_Context *ctx, gs_Number n);
gs_Object* gs_string(gs_Context *ctx, const char *str);
gs_Object* gs_symbol(gs_Context *ctx, const char *name);
gs_Object* gs_cfunc(gs_Context *ctx, gs_CFunc fn);
gs_Object* gs_ptr(gs_Context *ctx, void *ptr);
gs_Object* gs_make_error(gs_Context *ctx, const char *msg); // Renommé pour éviter conflit

// Prédicats et accès
gs_Type gs_type(gs_Context *ctx, gs_Object *obj);
bool gs_is_nil(gs_Context *ctx, gs_Object *obj);
bool gs_is_true(gs_Context *ctx, gs_Object *obj);
gs_Object* gs_car(gs_Context *ctx, gs_Object *obj);
gs_Object* gs_cdr(gs_Context *ctx, gs_Object *obj);
gs_Number gs_to_number(gs_Context *ctx, gs_Object *obj);
void* gs_to_ptr(gs_Context *ctx, gs_Object *obj);
const char* gs_to_string(gs_Context *ctx, gs_Object *obj, char *buf, int size);
gs_Object* gs_next_arg(gs_Context *ctx, gs_Object **args);

// Manipulation d'environnement
void gs_set(gs_Context *ctx, gs_Object *sym, gs_Object *value);
gs_Object* gs_get(gs_Context *ctx, gs_Object *sym, gs_Object *env);

// Lecture/Ecriture
gs_Object* gs_read(gs_Context *ctx, char (*read_fn)(gs_Context*, void*), void *udata);
gs_Object* gs_read_string(gs_Context *ctx, const char *input);
gs_Object* gs_read_file(gs_Context *ctx, FILE *fp);
void gs_write(gs_Context *ctx, gs_Object *obj, void (*write_fn)(gs_Context*, void*, char), void *udata, bool quote_strings);
void gs_write_string(gs_Context *ctx, gs_Object *obj, char *buf, int size);
void gs_write_file(gs_Context *ctx, gs_Object *obj, FILE *fp);

// Évaluation
gs_Object* gs_eval(gs_Context *ctx, gs_Object *obj);
gs_Object* gs_eval_string(gs_Context *ctx, const char *input);
gs_Object* gs_eval_file(gs_Context *ctx, FILE *fp);
gs_Object* gs_eval_in_env(gs_Context *ctx, gs_Object *obj, gs_Object *env);

// Fonctions utilitaires
gs_Object* gs_list(gs_Context *ctx, gs_Object **items, int count);
gs_Object* gs_list_from_args(gs_Context *ctx, gs_Object *args);
int gs_list_length(gs_Context *ctx, gs_Object *list);
gs_Object* gs_append(gs_Context *ctx, gs_Object *a, gs_Object *b);
gs_Object* gs_reverse(gs_Context *ctx, gs_Object *list);

#endif // GOSCRIPT_H
