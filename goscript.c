/*
** goscript - Un interpréteur Lisp moderne inspiré de Rust
** Copyright (c) 2026 Mauricio Mangituka
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
*/

#include "goscript.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <setjmp.h>
#include <math.h>

// ----------------------------------------------------------------------------
// Structures internes
// ----------------------------------------------------------------------------

typedef union {
    gs_Object *o;
    gs_CFunc f;
    gs_Number n;
    void *p;
    char c;
    uintptr_t raw;
} gs_Value;

struct gs_Object {
    gs_Value car;
    gs_Value cdr;
};
// Ajouter cette structure et fonction en haut du fichier, après les includes
struct StringReader {
    const char *p;
};

static char string_read_char(gs_Context *ctx, void *udata) {
    (void)ctx;
    struct StringReader *r = (struct StringReader*)udata;
    return *r->p ? *r->p++ : EOF;
}


// Marqueur de bit pour le GC
#define GC_MARK_BIT 0x2

// Macros d'accès
#define obj_car(x) ((x)->car.o)
#define obj_cdr(x) ((x)->cdr.o)
#define obj_tag(x) ((x)->car.raw)
#define obj_set_tag(x, t) ((x)->car.raw = ((uintptr_t)(t) << 2) | 1)
#define obj_type(x) ((obj_tag(x) & 1) ? (obj_tag(x) >> 2) : GS_T_PAIR)
#define obj_number(x) ((x)->cdr.n)
#define obj_prim(x) ((x)->cdr.c)
#define obj_cfunc(x) ((x)->cdr.f)
#define obj_ptr(x) ((x)->cdr.p)
#define obj_string_chunk(x) ((char*)&(x)->car.c + 1)

// Objet nil global
static gs_Object g_nil_object = {{ (void*)(GS_T_NIL << 2 | 1) }, { NULL }};
static gs_Object* const NIL = &g_nil_object;

// Marqueur de fin de liste pour la lecture
static gs_Object g_rparen = {{NULL}, {NULL}};
#define RPAREN (&g_rparen)

struct gs_Context {
    gs_Handlers handlers;
    
    // Pile GC
    gs_Object *gc_stack[GOSCRIPT_GC_STACK_SIZE];
    int gc_stack_idx;
    
    // Pool d'objets
    gs_Object *objects;
    int object_count;
    
    // Listes chaînées internes
    gs_Object *call_stack;      // Pile d'appels pour le debug
    gs_Object *free_list;       // Liste des objets libres
    gs_Object *symbol_table;    // Table des symboles
    gs_Object *global_env;      // Environnement global
    
    // Cache pour objets fréquents
    gs_Object *true_obj;
    gs_Object *false_obj;
    
    // État du lecteur
    int next_char;
    
    // Point de sauvegarde pour les erreurs
    jmp_buf *error_jmp;
    char error_msg[256];
};

// ----------------------------------------------------------------------------
// Primitives internes (enum)
// ----------------------------------------------------------------------------

enum {
    PRIM_LET, PRIM_SET, PRIM_IF, PRIM_FN, PRIM_MACRO, PRIM_WHILE, PRIM_QUOTE,
    PRIM_AND, PRIM_OR, PRIM_DO, PRIM_CONS, PRIM_CAR, PRIM_CDR, PRIM_SET_CAR,
    PRIM_SET_CDR, PRIM_LIST, PRIM_NOT, PRIM_EQ, PRIM_ATOM, PRIM_PRINT,
    PRIM_LT, PRIM_LTE, PRIM_GT, PRIM_GTE, PRIM_ADD, PRIM_SUB, PRIM_MUL,
    PRIM_DIV, PRIM_MOD, PRIM_TYPE, PRIM_ERROR, PRIM_EVAL, PRIM_LOAD,
    PRIM_MAX
};

static const char *prim_names[] = {
    "let", "set!", "if", "fn", "macro", "while", "quote",
    "and", "or", "do", "cons", "car", "cdr", "set-car!",
    "set-cdr!", "list", "not", "eq?", "atom?", "print",
    "<", "<=", ">", ">=", "+", "-", "*", "/", "%", "type",
    "error", "eval", "load"
};

static const char *type_names[] = {
    "pair", "free", "nil", "number", "symbol", "string",
    "function", "macro", "primitive", "c-function", "pointer",
    "boolean", "error"
};

// ----------------------------------------------------------------------------
// Gestion des erreurs (maintenant avec formatage)
// ----------------------------------------------------------------------------

__attribute__((noreturn))
void gs_error(gs_Context *ctx, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(ctx->error_msg, sizeof(ctx->error_msg), format, args);
    va_end(args);
    
    // Appeler le handler d'erreur si défini
    if (ctx->handlers.error) {
        ctx->handlers.error(ctx, ctx->error_msg, ctx->call_stack);
    }
    
    // Si on a un point de sauvegarde, y retourner
    if (ctx->error_jmp) {
        longjmp(*ctx->error_jmp, 1);
    }
    
    // Sinon, écrire sur stderr et quitter
    fprintf(stderr, "Error: %s\n", ctx->error_msg);
    
    // Afficher la pile d'appels
    for (gs_Object *cl = ctx->call_stack; !gs_is_nil(ctx, cl); cl = obj_cdr(cl)) {
        char buf[64];
        gs_write_string(ctx, obj_car(cl), buf, sizeof(buf));
        fprintf(stderr, "  at %s\n", buf);
    }
    
    exit(EXIT_FAILURE);
}

// ----------------------------------------------------------------------------
// Fonctions internes utilitaires
// ----------------------------------------------------------------------------

static inline bool is_nil(gs_Object *obj) {
    return obj == NIL;
}

static inline int object_type(gs_Object *obj) {
    return obj_type(obj);
}

static gs_Object* check_type(gs_Context *ctx, gs_Object *obj, int expected_type) {
    int actual = object_type(obj);
    if (actual != expected_type) {
        gs_error(ctx, "Type error: expected %s, got %s", 
                 type_names[expected_type], type_names[actual]);
    }
    return obj;
}

static gs_Object* allocate_object(gs_Context *ctx) {
    // Lancer le GC si nécessaire
    if (is_nil(ctx->free_list)) {
        gs_collect(ctx);
        if (is_nil(ctx->free_list)) {
            gs_error(ctx, "Out of memory: cannot allocate more objects");
        }
    }
    
    // Prendre un objet de la free list
    gs_Object *obj = ctx->free_list;
    ctx->free_list = obj_cdr(obj);
    
    // Le pousser sur la pile GC
    if (ctx->gc_stack_idx >= GOSCRIPT_GC_STACK_SIZE) {
        gs_error(ctx, "GC stack overflow");
    }
    ctx->gc_stack[ctx->gc_stack_idx++] = obj;
    
    return obj;
}

// ----------------------------------------------------------------------------
// Garbage Collector
// ----------------------------------------------------------------------------

void gs_push_gc(gs_Context *ctx, gs_Object *obj) {
    if (ctx->gc_stack_idx >= GOSCRIPT_GC_STACK_SIZE) {
        gs_error(ctx, "GC stack overflow");
    }
    ctx->gc_stack[ctx->gc_stack_idx++] = obj;
}

void gs_pop_gc(gs_Context *ctx, int count) {
    ctx->gc_stack_idx -= count;
    if (ctx->gc_stack_idx < 0) {
        ctx->gc_stack_idx = 0;
    }
}

int gs_save_gc(gs_Context *ctx) {
    return ctx->gc_stack_idx;
}

void gs_restore_gc(gs_Context *ctx, int idx) {
    if (idx >= 0 && idx <= ctx->gc_stack_idx) {
        ctx->gc_stack_idx = idx;
    }
}

void gs_mark(gs_Context *ctx, gs_Object *obj) {
    gs_Object *car;
    
begin:
    if (obj == NIL || (obj_tag(obj) & GC_MARK_BIT)) {
        return;
    }
    
    car = obj_car(obj);
    obj_tag(obj) |= GC_MARK_BIT;
    
    switch (object_type(obj)) {
        case GS_T_PAIR:
            gs_mark(ctx, car);
            // fall through
            
        case GS_T_FUNC:
        case GS_T_MACRO:
        case GS_T_SYMBOL:
        case GS_T_STRING:
            obj = obj_cdr(obj);
            goto begin;
            
        case GS_T_PTR:
            if (ctx->handlers.mark) {
                ctx->handlers.mark(ctx, obj);
            }
            break;
            
        default:
            break;
    }
}

void gs_collect(gs_Context *ctx) {
    // Mark phase
    for (int i = 0; i < ctx->gc_stack_idx; i++) {
        gs_mark(ctx, ctx->gc_stack[i]);
    }
    gs_mark(ctx, ctx->symbol_table);
    gs_mark(ctx, ctx->global_env);
    gs_mark(ctx, ctx->call_stack);
    gs_mark(ctx, ctx->true_obj);
    gs_mark(ctx, ctx->false_obj);
    
    // Sweep phase
    for (int i = 0; i < ctx->object_count; i++) {
        gs_Object *obj = &ctx->objects[i];
        
        if (object_type(obj) == GS_T_FREE) {
            continue;
        }
        
        if (!(obj_tag(obj) & GC_MARK_BIT)) {
            // Objet non marqué -> libérer
            if (object_type(obj) == GS_T_PTR && ctx->handlers.gc) {
                ctx->handlers.gc(ctx, obj);
            }
            
            obj_set_tag(obj, GS_T_FREE);
            obj_cdr(obj) = ctx->free_list;
            ctx->free_list = obj;
        } else {
            // Enlever le marqueur
            obj_tag(obj) &= ~GC_MARK_BIT;
        }
    }
}

// ----------------------------------------------------------------------------
// Création d'objets
// ----------------------------------------------------------------------------

gs_Object* gs_cons(gs_Context *ctx, gs_Object *car, gs_Object *cdr) {
    gs_Object *obj = allocate_object(ctx);
    obj_car(obj) = car;
    obj_cdr(obj) = cdr;
    return obj;
}

gs_Object* gs_bool(gs_Context *ctx, bool value) {
    return value ? ctx->true_obj : ctx->false_obj;
}

gs_Object* gs_number(gs_Context *ctx, gs_Number n) {
    gs_Object *obj = allocate_object(ctx);
    obj_set_tag(obj, GS_T_NUMBER);
    obj_number(obj) = n;
    return obj;
}

static gs_Object* build_string_chunk(gs_Context *ctx, gs_Object *tail, int chr) {
    if (!tail || obj_string_chunk(tail)[GOSCRIPT_STRING_CHUNK_SIZE - 1] != '\0') {
        gs_Object *obj = gs_cons(ctx, NULL, NIL);
        obj_set_tag(obj, GS_T_STRING);
        
        if (tail) {
            obj_cdr(tail) = obj;
            ctx->gc_stack_idx--; // Retirer tail car déjà protégé
        }
        tail = obj;
        
        // Initialiser le chunk avec des zéros
        memset(obj_string_chunk(tail), 0, GOSCRIPT_STRING_CHUNK_SIZE);
    }
    
    // Ajouter le caractère
    char *p = obj_string_chunk(tail);
    p[strlen(p)] = (char)chr;
    
    return tail;
}

gs_Object* gs_string(gs_Context *ctx, const char *str) {
    if (!str) {
        return NIL;
    }
    
    gs_Object *obj = build_string_chunk(ctx, NULL, '\0');
    gs_Object *tail = obj;
    
    while (*str) {
        tail = build_string_chunk(ctx, tail, *str++);
    }
    
    return obj;
}

gs_Object* gs_symbol(gs_Context *ctx, const char *name) {
    if (!name || !*name) {
        return NIL;
    }
    
    // Chercher dans la table des symboles
    for (gs_Object *sym = ctx->symbol_table; !is_nil(sym); sym = obj_cdr(sym)) {
        gs_Object *s = obj_car(sym);
        gs_Object *str = obj_cdr(s);
        
        // Vérifier si le nom correspond
        bool match = true;
        const char *n = name;
        
        while (!is_nil(str)) {
            const char *chunk = obj_string_chunk(str);
            for (int i = 0; i < GOSCRIPT_STRING_CHUNK_SIZE && chunk[i]; i++) {
                if (chunk[i] != *n || !*n) {
                    match = false;
                    break;
                }
                n++;
            }
            if (!match) break;
            str = obj_cdr(str);
        }
        
        if (match && *n == '\0') {
            return s;
        }
    }
    
    // Créer un nouveau symbole
    gs_Object *obj = allocate_object(ctx);
    obj_set_tag(obj, GS_T_SYMBOL);
    obj_cdr(obj) = gs_string(ctx, name);
    
    // Ajouter à la table des symboles
    ctx->symbol_table = gs_cons(ctx, obj, ctx->symbol_table);
    
    return obj;
}

gs_Object* gs_cfunc(gs_Context *ctx, gs_CFunc fn) {
    gs_Object *obj = allocate_object(ctx);
    obj_set_tag(obj, GS_T_CFUNC);
    obj_cfunc(obj) = fn;
    return obj;
}

gs_Object* gs_ptr(gs_Context *ctx, void *ptr) {
    gs_Object *obj = allocate_object(ctx);
    obj_set_tag(obj, GS_T_PTR);
    obj_ptr(obj) = ptr;
    return obj;
}

gs_Object* gs_make_error(gs_Context *ctx, const char *msg) {
    gs_Object *obj = allocate_object(ctx);
    obj_set_tag(obj, GS_T_ERROR);
    obj_cdr(obj) = gs_string(ctx, msg);
    return obj;
}

// ----------------------------------------------------------------------------
// Accès et prédicats
// ----------------------------------------------------------------------------

gs_Type gs_type(gs_Context *ctx, gs_Object *obj) {
    (void)ctx;
    if (obj == NIL) return GS_T_NIL;
    return object_type(obj);
}

bool gs_is_nil(gs_Context *ctx, gs_Object *obj) {
    (void)ctx;
    return obj == NIL;
}

bool gs_is_true(gs_Context *ctx, gs_Object *obj) {
    (void)ctx;
    return obj != NIL && obj != ctx->false_obj;
}

gs_Object* gs_car(gs_Context *ctx, gs_Object *obj) {
    if (is_nil(obj)) return NIL;
    return obj_car(check_type(ctx, obj, GS_T_PAIR));
}

gs_Object* gs_cdr(gs_Context *ctx, gs_Object *obj) {
    if (is_nil(obj)) return NIL;
    return obj_cdr(check_type(ctx, obj, GS_T_PAIR));
}

gs_Number gs_to_number(gs_Context *ctx, gs_Object *obj) {
    return obj_number(check_type(ctx, obj, GS_T_NUMBER));
}

void* gs_to_ptr(gs_Context *ctx, gs_Object *obj) {
    return obj_ptr(check_type(ctx, obj, GS_T_PTR));
}

const char* gs_to_string(gs_Context *ctx, gs_Object *obj, char *buf, int size) {
    gs_write_string(ctx, obj, buf, size);
    return buf;
}

gs_Object* gs_next_arg(gs_Context *ctx, gs_Object **args) {
    gs_Object *a = *args;
    
    if (object_type(a) != GS_T_PAIR) {
        if (is_nil(a)) {
            gs_error(ctx, "Too few arguments");
        }
        gs_error(ctx, "Dotted pair in argument list");
    }
    
    *args = obj_cdr(a);
    return obj_car(a);
}

// ----------------------------------------------------------------------------
// Environnement
// ----------------------------------------------------------------------------

static gs_Object* find_binding(gs_Object *sym, gs_Object *env) {
    // Chercher dans l'environnement local
    for (; !is_nil(env); env = obj_cdr(env)) {
        gs_Object *binding = obj_car(env);
        if (obj_car(binding) == sym) {
            return binding;
        }
    }
    
    // Retourner la liaison globale (contenue dans le symbole lui-même)
    return sym;
}

void gs_set(gs_Context *ctx, gs_Object *sym, gs_Object *value) {
    (void)ctx;
    gs_Object *binding = find_binding(sym, NIL);
    obj_cdr(binding) = value;
}

gs_Object* gs_get(gs_Context *ctx, gs_Object *sym, gs_Object *env) {
    (void)ctx;
    gs_Object *binding = find_binding(sym, env);
    return obj_cdr(binding);
}

// ----------------------------------------------------------------------------
// Lecture (parser)
// ----------------------------------------------------------------------------

static char default_read_char(gs_Context *ctx, void *udata) {
    (void)ctx;
    return fgetc((FILE*)udata);
}

static int is_delimiter(int c) {
    return isspace(c) || c == '(' || c == ')' || c == ';' || c == '"' || c == '\'' || c == EOF;
}

static gs_Object* read_expr(gs_Context *ctx, char (*read_fn)(gs_Context*, void*), void *udata) {
    char buf[GOSCRIPT_MAX_SYMBOL_LEN];
    int c;
    
    // Récupérer le prochain caractère
    if (ctx->next_char) {
        c = ctx->next_char;
        ctx->next_char = 0;
    } else {
        c = read_fn(ctx, udata);
    }
    
    // Ignorer les espaces
    while (c != EOF && isspace(c)) {
        c = read_fn(ctx, udata);
    }
    
    if (c == EOF) {
        return NULL;
    }
    
    switch (c) {
        case ';': // Commentaire
            while (c != EOF && c != '\n') {
                c = read_fn(ctx, udata);
            }
            return read_expr(ctx, read_fn, udata);
            
        case ')':
            return RPAREN;
            
        case '(': {
            // Lecture d'une liste
            int gc = gs_save_gc(ctx);
            gs_Object *list = NIL;
            gs_Object **tail = &list;
            
            while (1) {
                gs_Object *item = read_expr(ctx, read_fn, udata);
                
                if (item == NULL) {
                    gs_error(ctx, "Unclosed list");
                }
                
                if (item == RPAREN) {
                    break;
                }
                
                // Vérifier pour la notation pointée
                if (object_type(item) == GS_T_SYMBOL && 
                    strcmp(obj_string_chunk(obj_cdr(item)), ".") == 0) {
                    // Lire l'expression suivante comme cdr
                    *tail = read_expr(ctx, read_fn, udata);
                    if (*tail == RPAREN || *tail == NULL) {
                        gs_error(ctx, "Invalid dotted pair");
                    }
                    
                    // Lire et vérifier la parenthèse fermante
                    gs_Object *next = read_expr(ctx, read_fn, udata);
                    if (next != RPAREN) {
                        gs_error(ctx, "Expected ')' after dotted pair");
                    }
                    break;
                } else {
                    // Construction normale de liste
                    *tail = gs_cons(ctx, item, NIL);
                    tail = &obj_cdr(*tail);
                }
                
                gs_restore_gc(ctx, gc);
                gs_push_gc(ctx, list);
            }
            
            return list;
        }
        
        case '\'': {
            // Quote
            gs_Object *quoted = read_expr(ctx, read_fn, udata);
            if (!quoted || quoted == RPAREN) {
                gs_error(ctx, "Invalid quote syntax");
            }
            return gs_cons(ctx, 
                          gs_symbol(ctx, "quote"),
                          gs_cons(ctx, quoted, NIL));
        }
        
        case '"': {
            // Chaîne de caractères
            gs_Object *str_obj = build_string_chunk(ctx, NULL, '\0');
            gs_Object *tail = str_obj;
            
            while ((c = read_fn(ctx, udata)) != '"') {
                if (c == EOF) {
                    gs_error(ctx, "Unclosed string");
                }
                
                if (c == '\\') {
                    c = read_fn(ctx, udata);
                    switch (c) {
                        case 'n': c = '\n'; break;
                        case 't': c = '\t'; break;
                        case 'r': c = '\r'; break;
                        case '\\': c = '\\'; break;
                        case '"': c = '"'; break;
                        default:
                            gs_error(ctx, "Invalid escape sequence: \\%c", c);
                    }
                }
                
                tail = build_string_chunk(ctx, tail, c);
            }
            
            return str_obj;
        }
        
        default: {
            // Symbole ou nombre
            int i = 0;
            buf[i++] = c;
            
            while ((c = read_fn(ctx, udata)) != EOF && !is_delimiter(c)) {
                if (i < GOSCRIPT_MAX_SYMBOL_LEN - 1) {
                    buf[i++] = c;
                }
            }
            buf[i] = '\0';
            
            ctx->next_char = c;
            
            // Essayer de parser comme nombre
            char *endptr;
            double num = strtod(buf, &endptr);
            if (endptr != buf && is_delimiter(*endptr)) {
                return gs_number(ctx, num);
            }
            
            // Symbole spécial nil
            if (strcmp(buf, "nil") == 0) {
                return NIL;
            }
            
            // Booléens
            if (strcmp(buf, "true") == 0) {
                return ctx->true_obj;
            }
            if (strcmp(buf, "false") == 0) {
                return ctx->false_obj;
            }
            
            return gs_symbol(ctx, buf);
        }
    }
}

gs_Object* gs_read(gs_Context *ctx, char (*read_fn)(gs_Context*, void*), void *udata) {
    gs_Object *obj = read_expr(ctx, read_fn, udata);
    
    if (obj == RPAREN) {
        gs_error(ctx, "Unexpected ')'");
    }
    
    return obj;
}

gs_Object* gs_read_string(gs_Context *ctx, const char *input) {
    struct StringReader reader;
    reader.p = input;
    return gs_read(ctx, string_read_char, &reader);
}
    
    char read_char(gs_Context *ctx, void *udata) {
        (void)ctx;
        struct StringReader *r = udata;
        return *r->p ? *r->p++ : EOF;
    }
    
    return gs_read(ctx, read_char, &reader);
}

gs_Object* gs_read_file(gs_Context *ctx, FILE *fp) {
    return gs_read(ctx, default_read_char, fp);
}

// ----------------------------------------------------------------------------
// Écriture (sérialisation)
// ----------------------------------------------------------------------------

static void default_write_char(gs_Context *ctx, void *udata, char c) {
    (void)ctx;
    fputc(c, (FILE*)udata);
}

static void write_string_raw(gs_Context *ctx, void (*write_fn)(gs_Context*, void*, char), 
                             void *udata, const char *s) {
    while (*s) {
        write_fn(ctx, udata, *s++);
    }
}

void gs_write(gs_Context *ctx, gs_Object *obj, 
              void (*write_fn)(gs_Context*, void*, char), 
              void *udata, bool quote_strings) {
    
    if (!obj) return;
    
    char buf[64];
    
    switch (object_type(obj)) {
        case GS_T_NIL:
            write_string_raw(ctx, write_fn, udata, "nil");
            break;
            
        case GS_T_BOOL:
            write_string_raw(ctx, write_fn, udata, obj == ctx->true_obj ? "true" : "false");
            break;
            
        case GS_T_NUMBER:
            snprintf(buf, sizeof(buf), "%.10g", obj_number(obj));
            write_string_raw(ctx, write_fn, udata, buf);
            break;
            
        case GS_T_PAIR:
            write_fn(ctx, udata, '(');
            while (object_type(obj) == GS_T_PAIR) {
                gs_write(ctx, obj_car(obj), write_fn, udata, true);
                obj = obj_cdr(obj);
                if (object_type(obj) == GS_T_PAIR) {
                    write_fn(ctx, udata, ' ');
                }
            }
            if (!is_nil(obj)) {
                write_string_raw(ctx, write_fn, udata, " . ");
                gs_write(ctx, obj, write_fn, udata, true);
            }
            write_fn(ctx, udata, ')');
            break;
            
        case GS_T_SYMBOL:
            gs_write(ctx, obj_cdr(obj), write_fn, udata, false);
            break;
            
        case GS_T_STRING:
            if (quote_strings) {
                write_fn(ctx, udata, '"');
            }
            
            while (!is_nil(obj)) {
                const char *chunk = obj_string_chunk(obj);
                for (int i = 0; i < GOSCRIPT_STRING_CHUNK_SIZE && chunk[i]; i++) {
                    char c = chunk[i];
                    if (quote_strings) {
                        if (c == '"' || c == '\\') {
                            write_fn(ctx, udata, '\\');
                        }
                    }
                    write_fn(ctx, udata, c);
                }
                obj = obj_cdr(obj);
            }
            
            if (quote_strings) {
                write_fn(ctx, udata, '"');
            }
            break;
            
        case GS_T_ERROR:
            write_string_raw(ctx, write_fn, udata, "#<error: ");
            gs_write(ctx, obj_cdr(obj), write_fn, udata, false);
            write_string_raw(ctx, write_fn, udata, ">");
            break;
            
        default:
            snprintf(buf, sizeof(buf), "#<%s %p>", 
                     type_names[object_type(obj)], (void*)obj);
            write_string_raw(ctx, write_fn, udata, buf);
            break;
    }
}

struct StringWriter {
    char *buf;
    int size;
    int pos;
};

static void string_writer(gs_Context *ctx, void *udata, char c) {
    (void)ctx;
    struct StringWriter *w = udata;
    if (w->pos < w->size - 1) {
        w->buf[w->pos++] = c;
    }
}

void gs_write_string(gs_Context *ctx, gs_Object *obj, char *buf, int size) {
    if (size <= 0) return;
    
    struct StringWriter writer = { buf, size, 0 };
    gs_write(ctx, obj, string_writer, &writer, false);
    writer.buf[writer.pos] = '\0';
}

void gs_write_file(gs_Context *ctx, gs_Object *obj, FILE *fp) {
    gs_write(ctx, obj, default_write_char, fp, false);
}

// ----------------------------------------------------------------------------
// Évaluation (le cœur de l'interpréteur)
// ----------------------------------------------------------------------------

static gs_Object* eval(gs_Context *ctx, gs_Object *obj, gs_Object *env, gs_Object **new_env);
static gs_Object* eval_list(gs_Context *ctx, gs_Object *list, gs_Object *env);
static gs_Object* do_sequence(gs_Context *ctx, gs_Object *list, gs_Object *env);

// Fonctions d'aide pour l'évaluation
#define EVAL_ARG() eval(ctx, gs_next_arg(ctx, &args), env, NULL)

#define ARITH_OP(op) { \
    gs_Number result = gs_to_number(ctx, EVAL_ARG()); \
    while (!is_nil(args)) { \
        result = result op gs_to_number(ctx, EVAL_ARG()); \
    } \
    result_obj = gs_number(ctx, result); \
}

#define CMP_OP(op) { \
    gs_Number a = gs_to_number(ctx, EVAL_ARG()); \
    gs_Number b = gs_to_number(ctx, EVAL_ARG()); \
    result_obj = gs_bool(ctx, a op b); \
}

static gs_Object* eval(gs_Context *ctx, gs_Object *obj, gs_Object *env, gs_Object **new_env) {
    gs_Object *fn, *args, *result_obj = NIL;
    gs_Object *a, *b;
    int gc_save;
    
    // Cas de base
    switch (object_type(obj)) {
        case GS_T_SYMBOL:
            return gs_get(ctx, obj, env);
            
        case GS_T_NUMBER:
        case GS_T_STRING:
        case GS_T_BOOL:
        case GS_T_NIL:
        case GS_T_PRIM:
        case GS_T_CFUNC:
        case GS_T_FUNC:
        case GS_T_MACRO:
        case GS_T_PTR:
        case GS_T_ERROR:
            return obj;
            
        case GS_T_PAIR:
            // C'est un appel de fonction
            break;
            
        default:
            gs_error(ctx, "Cannot evaluate object of type %s", type_names[object_type(obj)]);
    }
    
    // Mise à jour de la pile d'appels
    gs_Object call_frame;
    obj_car(&call_frame) = obj;
    obj_cdr(&call_frame) = ctx->call_stack;
    ctx->call_stack = &call_frame;
    
    gc_save = gs_save_gc(ctx);
    
    // Évaluer la fonction
    fn = eval(ctx, obj_car(obj), env, NULL);
    args = obj_cdr(obj);
    
    switch (object_type(fn)) {
        // Primitives intégrées
        case GS_T_PRIM: {
            int prim = (int)(uintptr_t)obj_prim(fn);
            
            switch (prim) {
                case PRIM_LET: {
                    // (let name value)
                    gs_Object *name = check_type(ctx, gs_next_arg(ctx, &args), GS_T_SYMBOL);
                    gs_Object *value = EVAL_ARG();
                    
                    if (new_env) {
                        *new_env = gs_cons(ctx, gs_cons(ctx, name, value), env);
                    }
                    result_obj = value;
                    break;
                }
                
                case PRIM_SET: {
                    // (set! name value)
                    gs_Object *name = check_type(ctx, gs_next_arg(ctx, &args), GS_T_SYMBOL);
                    gs_Object *value = EVAL_ARG();
                    
                    gs_Object *binding = find_binding(name, env);
                    obj_cdr(binding) = value;
                    result_obj = value;
                    break;
                }
                
                case PRIM_IF: {
                    // (if cond then [else])
                    gs_Object *cond = EVAL_ARG();
                    gs_Object *then_expr = gs_next_arg(ctx, &args);
                    gs_Object *else_expr = is_nil(args) ? NIL : gs_next_arg(ctx, &args);
                    
                    if (gs_is_true(ctx, cond)) {
                        result_obj = eval(ctx, then_expr, env, NULL);
                    } else if (!is_nil(else_expr)) {
                        result_obj = eval(ctx, else_expr, env, NULL);
                    }
                    break;
                }
                
                case PRIM_FN:
                case PRIM_MACRO: {
                    // (fn (params ...) body ...)
                    // (macro (params ...) body ...)
                    gs_Object *params = gs_next_arg(ctx, &args);
                    gs_Object *body = args;
                    
                    gs_Object *func_obj = allocate_object(ctx);
                    obj_set_tag(func_obj, prim == PRIM_FN ? GS_T_FUNC : GS_T_MACRO);
                    obj_cdr(func_obj) = gs_cons(ctx, env, gs_cons(ctx, params, body));
                    
                    result_obj = func_obj;
                    break;
                }
                
                case PRIM_WHILE: {
                    // (while cond body ...)
                    gs_Object *cond = gs_next_arg(ctx, &args);
                    
                    while (gs_is_true(ctx, eval(ctx, cond, env, NULL))) {
                        result_obj = do_sequence(ctx, args, env);
                    }
                    break;
                }
                
                case PRIM_QUOTE: {
                    // (quote expr)
                    result_obj = gs_next_arg(ctx, &args);
                    break;
                }
                
                case PRIM_AND: {
                    // (and expr ...)
                    result_obj = ctx->true_obj;
                    while (!is_nil(args)) {
                        result_obj = EVAL_ARG();
                        if (!gs_is_true(ctx, result_obj)) {
                            result_obj = ctx->false_obj;
                            break;
                        }
                    }
                    break;
                }
                
                case PRIM_OR: {
                    // (or expr ...)
                    result_obj = ctx->false_obj;
                    while (!is_nil(args)) {
                        result_obj = EVAL_ARG();
                        if (gs_is_true(ctx, result_obj)) {
                            break;
                        }
                    }
                    break;
                }
                
                case PRIM_DO:
                    // (do expr ...)
                    result_obj = do_sequence(ctx, args, env);
                    break;
                    
                case PRIM_CONS:
                    // (cons a b)
                    a = EVAL_ARG();
                    b = EVAL_ARG();
                    result_obj = gs_cons(ctx, a, b);
                    break;
                    
                case PRIM_CAR:
                    // (car pair)
                    result_obj = gs_car(ctx, EVAL_ARG());
                    break;
                    
                case PRIM_CDR:
                    // (cdr pair)
                    result_obj = gs_cdr(ctx, EVAL_ARG());
                    break;
                    
                case PRIM_SET_CAR: {
                    // (set-car! pair value)
                    gs_Object *pair = check_type(ctx, EVAL_ARG(), GS_T_PAIR);
                    obj_car(pair) = EVAL_ARG();
                    result_obj = pair;
                    break;
                }
                
                case PRIM_SET_CDR: {
                    // (set-cdr! pair value)
                    gs_Object *pair = check_type(ctx, EVAL_ARG(), GS_T_PAIR);
                    obj_cdr(pair) = EVAL_ARG();
                    result_obj = pair;
                    break;
                }
                
                case PRIM_LIST:
                    // (list ...)
                    result_obj = eval_list(ctx, args, env);
                    break;
                    
                case PRIM_NOT:
                    // (not x)
                    result_obj = gs_bool(ctx, !gs_is_true(ctx, EVAL_ARG()));
                    break;
                    
                case PRIM_EQ:
                    // (eq? a b)
                    a = EVAL_ARG();
                    b = EVAL_ARG();
                    result_obj = gs_bool(ctx, a == b);
                    break;
                    
                case PRIM_ATOM:
                    // (atom? x)
                    result_obj = gs_bool(ctx, object_type(EVAL_ARG()) != GS_T_PAIR);
                    break;
                    
                case PRIM_PRINT: {
                    // (print ...)
                    if (ctx->handlers.print) {
                        char buf[1024];
                        gs_write_string(ctx, args, buf, sizeof(buf));
                        ctx->handlers.print(ctx, buf);
                    }
                    result_obj = NIL;
                    break;
                }
                
                case PRIM_LT:  CMP_OP(<); break;
                case PRIM_LTE: CMP_OP(<=); break;
                case PRIM_GT:  CMP_OP(>); break;
                case PRIM_GTE: CMP_OP(>=); break;
                case PRIM_ADD: ARITH_OP(+); break;
                case PRIM_SUB: ARITH_OP(-); break;
                case PRIM_MUL: ARITH_OP(*); break;
                case PRIM_DIV: ARITH_OP(/); break;
                case PRIM_MOD: {
                    gs_Number a = gs_to_number(ctx, EVAL_ARG());
                    gs_Number b = gs_to_number(ctx, EVAL_ARG());
                    if (b == 0) {
                        gs_error(ctx, "Division by zero in modulo");
                    }
                    result_obj = gs_number(ctx, fmod(a, b));
                    break;
                }
                
                case PRIM_TYPE:
                    // (type x)
                    result_obj = gs_symbol(ctx, type_names[object_type(EVAL_ARG())]);
                    break;
                    
                case PRIM_ERROR: {
                    // (error msg)
                    a = EVAL_ARG();
                    char msg_buf[256];
                    gs_write_string(ctx, a, msg_buf, sizeof(msg_buf));
                    gs_error(ctx, "%s", msg_buf);
                    break;
                }
                    
                case PRIM_EVAL:
                    // (eval expr)
                    result_obj = gs_eval(ctx, EVAL_ARG());
                    break;
                    
                case PRIM_LOAD: {
                    // (load filename)
                    a = EVAL_ARG();
                    char fname[256];
                    gs_write_string(ctx, a, fname, sizeof(fname));
                    
                    FILE *fp = fopen(fname, "r");
                    if (!fp) {
                        gs_error(ctx, "Cannot open file: %s", fname);
                    }
                    
                    result_obj = gs_eval_file(ctx, fp);
                    fclose(fp);
                    break;
                }
                
                default:
                    gs_error(ctx, "Unknown primitive");
            }
            break;
        }
        
        // Fonction C
        case GS_T_CFUNC: {
            gs_Object *arg_list = eval_list(ctx, args, env);
            result_obj = obj_cfunc(fn)(ctx, arg_list);
            break;
        }
        
        // Fonction utilisateur
        case GS_T_FUNC: {
            gs_Object *func_data = obj_cdr(fn);      // (env params . body)
            gs_Object *func_env = obj_car(func_data); // environnement de fermeture
            gs_Object *func_params = obj_car(obj_cdr(func_data));
            gs_Object *func_body = obj_cdr(obj_cdr(func_data));
            
            // Évaluer les arguments
            gs_Object *arg_vals = eval_list(ctx, args, env);
            
            // Créer l'environnement local
            gs_Object *local_env = func_env;
            gs_Object *params = func_params;
            gs_Object *arg = arg_vals;
            
            while (!is_nil(params)) {
                if (object_type(params) != GS_T_PAIR) {
                    // Paramètre restant
                    local_env = gs_cons(ctx, 
                                       gs_cons(ctx, params, arg),
                                       local_env);
                    break;
                }
                
                local_env = gs_cons(ctx, 
                                   gs_cons(ctx, obj_car(params), 
                                          object_type(arg) == GS_T_PAIR ? obj_car(arg) : NIL),
                                   local_env);
                
                params = obj_cdr(params);
                arg = object_type(arg) == GS_T_PAIR ? obj_cdr(arg) : NIL;
            }
            
            // Exécuter le corps
            result_obj = do_sequence(ctx, func_body, local_env);
            break;
        }
        
        // Macro
        case GS_T_MACRO: {
            gs_Object *macro_data = obj_cdr(fn);
            gs_Object *macro_env = obj_car(macro_data);
            gs_Object *macro_params = obj_car(obj_cdr(macro_data));
            gs_Object *macro_body = obj_cdr(obj_cdr(macro_data));
            
            // Les arguments ne sont PAS évalués pour une macro
            gs_Object *local_env = macro_env;
            gs_Object *params = macro_params;
            gs_Object *arg = args;
            
            while (!is_nil(params)) {
                if (object_type(params) != GS_T_PAIR) {
                    local_env = gs_cons(ctx, 
                                       gs_cons(ctx, params, arg),
                                       local_env);
                    break;
                }
                
                local_env = gs_cons(ctx, 
                                   gs_cons(ctx, obj_car(params),
                                          object_type(arg) == GS_T_PAIR ? obj_car(arg) : NIL),
                                   local_env);
                
                params = obj_cdr(params);
                arg = object_type(arg) == GS_T_PAIR ? obj_cdr(arg) : NIL;
            }
            
            // Générer le code
            gs_Object *expanded = do_sequence(ctx, macro_body, local_env);
            
            // Ré-évaluer le code généré
            gs_restore_gc(ctx, gc_save);
            ctx->call_stack = obj_cdr(&call_frame);
            return eval(ctx, expanded, env, NULL);
        }
        
        default:
            gs_error(ctx, "Tried to call non-callable value of type %s", 
                     type_names[object_type(fn)]);
    }
    
    gs_restore_gc(ctx, gc_save);
    gs_push_gc(ctx, result_obj);
    ctx->call_stack = obj_cdr(&call_frame);
    
    return result_obj;
}

static gs_Object* eval_list(gs_Context *ctx, gs_Object *list, gs_Object *env) {
    gs_Object *result = NIL;
    gs_Object **tail = &result;
    
    while (!is_nil(list)) {
        *tail = gs_cons(ctx, 
                       eval(ctx, obj_car(list), env, NULL),
                       NIL);
        tail = &obj_cdr(*tail);
        list = obj_cdr(list);
    }
    
    return result;
}

static gs_Object* do_sequence(gs_Context *ctx, gs_Object *list, gs_Object *env) {
    gs_Object *result = NIL;
    int gc_save = gs_save_gc(ctx);
    
    while (!is_nil(list)) {
        gs_restore_gc(ctx, gc_save);
        gs_push_gc(ctx, list);
        gs_push_gc(ctx, env);
        
        result = eval(ctx, obj_car(list), env, NULL);
        list = obj_cdr(list);
    }
    
    return result;
}

// ----------------------------------------------------------------------------
// API publique d'évaluation
// ----------------------------------------------------------------------------

gs_Object* gs_eval(gs_Context *ctx, gs_Object *obj) {
    jmp_buf jmp;
    jmp_buf *old_jmp = ctx->error_jmp;
    ctx->error_jmp = &jmp;
    gs_Object *result;
    
    if (setjmp(jmp) == 0) {
        result = eval(ctx, obj, ctx->global_env, NULL);
    } else {
        // Une erreur est survenue
        result = gs_make_error(ctx, ctx->error_msg);
    }
    
    ctx->error_jmp = old_jmp;
    return result;
}

gs_Object* gs_eval_string(gs_Context *ctx, const char *input) {
    gs_Object *expr = gs_read_string(ctx, input);
    if (!expr) return NIL;
    return gs_eval(ctx, expr);
}

gs_Object* gs_eval_file(gs_Context *ctx, FILE *fp) {
    gs_Object *result = NIL;
    gs_Object *expr;
    
    while ((expr = gs_read_file(ctx, fp)) != NULL) {
        result = gs_eval(ctx, expr);
    }
    
    return result;
}

gs_Object* gs_eval_in_env(gs_Context *ctx, gs_Object *obj, gs_Object *env) {
    return eval(ctx, obj, env, NULL);
}

// ----------------------------------------------------------------------------
// Utilitaires pour listes
// ----------------------------------------------------------------------------

gs_Object* gs_list(gs_Context *ctx, gs_Object **items, int count) {
    gs_Object *result = NIL;
    
    for (int i = count - 1; i >= 0; i--) {
        result = gs_cons(ctx, items[i], result);
    }
    
    return result;
}

gs_Object* gs_list_from_args(gs_Context *ctx, gs_Object *args) {
    gs_Object *result = NIL;
    gs_Object **tail = &result;
    
    while (!is_nil(args)) {
        *tail = gs_cons(ctx, obj_car(args), NIL);
        tail = &obj_cdr(*tail);
        args = obj_cdr(args);
    }
    
    return result;
}

int gs_list_length(gs_Context *ctx, gs_Object *list) {
    (void)ctx;
    int len = 0;
    
    while (!is_nil(list)) {
        if (object_type(list) != GS_T_PAIR) {
            return -1; // Pas une liste propre
        }
        len++;
        list = obj_cdr(list);
    }
    
    return len;
}

gs_Object* gs_append(gs_Context *ctx, gs_Object *a, gs_Object *b) {
    if (is_nil(a)) return b;
    
    gs_Object *result = gs_cons(ctx, obj_car(a), NIL);
    gs_Object *tail = result;
    a = obj_cdr(a);
    
    while (!is_nil(a)) {
        obj_cdr(tail) = gs_cons(ctx, obj_car(a), NIL);
        tail = obj_cdr(tail);
        a = obj_cdr(a);
    }
    
    obj_cdr(tail) = b;
    return result;
}

gs_Object* gs_reverse(gs_Context *ctx, gs_Object *list) {
    gs_Object *result = NIL;
    
    while (!is_nil(list)) {
        result = gs_cons(ctx, obj_car(list), result);
        list = obj_cdr(list);
    }
    
    return result;
}

// ----------------------------------------------------------------------------
// Initialisation du contexte
// ----------------------------------------------------------------------------

gs_Handlers* gs_handlers(gs_Context *ctx) {
    return &ctx->handlers;
}

gs_Context* gs_open(void *memory, int size) {
    if (!memory || size < (int)sizeof(gs_Context)) {
        return NULL;
    }
    
    gs_Context *ctx = (gs_Context*)memory;
    memset(ctx, 0, sizeof(gs_Context));
    
    // Initialiser la zone mémoire pour les objets
    void *obj_mem = (char*)memory + sizeof(gs_Context);
    int obj_size = size - sizeof(gs_Context);
    
    ctx->objects = (gs_Object*)obj_mem;
    ctx->object_count = obj_size / sizeof(gs_Object);
    
    // Initialiser les listes
    ctx->call_stack = NIL;
    ctx->free_list = NIL;
    ctx->symbol_table = NIL;
    
    // Remplir la free list
    for (int i = 0; i < ctx->object_count; i++) {
        gs_Object *obj = &ctx->objects[i];
        obj_set_tag(obj, GS_T_FREE);
        obj_cdr(obj) = ctx->free_list;
        ctx->free_list = obj;
    }
    
    // Créer les objets booléens
    ctx->true_obj = allocate_object(ctx);
    obj_set_tag(ctx->true_obj, GS_T_BOOL);
    
    ctx->false_obj = allocate_object(ctx);
    obj_set_tag(ctx->false_obj, GS_T_BOOL);
    
    // Créer l'environnement global
    ctx->global_env = NIL;
    
    // Enregistrer les primitives
    int gc_save = gs_save_gc(ctx);
    for (int i = 0; i < PRIM_MAX; i++) {
        gs_Object *prim = allocate_object(ctx);
        obj_set_tag(prim, GS_T_PRIM);
        obj_prim(prim) = (char)(uintptr_t)i;
        
        gs_Object *sym = gs_symbol(ctx, prim_names[i]);
        gs_set(ctx, sym, prim);
        
        gs_restore_gc(ctx, gc_save);
    }
    
    // Définir le symbole 't' comme vrai
    gs_set(ctx, gs_symbol(ctx, "t"), ctx->true_obj);
    
    return ctx;
}

void gs_close(gs_Context *ctx) {
    // Nettoyer la pile GC et les listes internes
    ctx->gc_stack_idx = 0;
    ctx->symbol_table = NIL;
    ctx->global_env = NIL;
    ctx->call_stack = NIL;
    
    // Forcer un GC
    gs_collect(ctx);
    
    // Appeler les handlers de fermeture si nécessaire
    if (ctx->handlers.gc) {
        for (int i = 0; i < ctx->object_count; i++) {
            gs_Object *obj = &ctx->objects[i];
            if (object_type(obj) == GS_T_PTR) {
                ctx->handlers.gc(ctx, obj);
            }
        }
    }
}

// ----------------------------------------------------------------------------
// Version standalone avec REPL silencieux
// ----------------------------------------------------------------------------

#ifdef GOSCRIPT_STANDALONE

static void default_error_handler(gs_Context *ctx, const char *msg, gs_Object *callstack) {
    (void)ctx;
    fprintf(stderr, "Error: %s\n", msg);
    
    for (; !gs_is_nil(ctx, callstack); callstack = gs_cdr(ctx, callstack)) {
        char buf[64];
        gs_write_string(ctx, gs_car(ctx, callstack), buf, sizeof(buf));
        fprintf(stderr, "  at %s\n", buf);
    }
}

static void silent_print(gs_Context *ctx, const char *msg) {
    (void)ctx;
    // Interpréteur silencieux - ne rien imprimer
    // Mais on peut décommenter pour le debug
    // printf("%s\n", msg);
}

int main(int argc, char **argv) {
    char memory[256 * 1024]; // 256KB devrait suffire
    gs_Context *ctx = gs_open(memory, sizeof(memory));
    
    if (!ctx) {
        fprintf(stderr, "Failed to initialize goscript context\n");
        return 1;
    }
    
    // Configurer les handlers
    gs_handlers(ctx)->error = default_error_handler;
    gs_handlers(ctx)->print = silent_print;
    
    if (argc > 1) {
        // Mode script : exécuter le fichier
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "Cannot open file: %s\n", argv[1]);
            return 1;
        }
        
        gs_eval_file(ctx, fp);
        fclose(fp);
    } else {
        // Mode REPL silencieux (pas de prompt, pas de sortie)
        char line[4096];
        while (fgets(line, sizeof(line), stdin)) {
            gs_eval_string(ctx, line);
            // Pas de sortie - interpréteur silencieux
        }
    }
    
    gs_close(ctx);
    return 0;
}

#endif // GOSCRIPT_STANDALONE
