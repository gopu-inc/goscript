#ifndef GC_H
#define GC_H

#include <stddef.h>

// Types d'objets gérés par le GC
typedef enum {
    GC_TYPE_STRING,
    GC_TYPE_ARRAY,
    GC_TYPE_DICT,
    GC_TYPE_STRUCT,
    GC_TYPE_FUNCTION,
    GC_TYPE_ENVIRONMENT,
    GC_TYPE_PROMISE
} GCObjectType;

// En-tête de tous les objets gérés par le GC
typedef struct GCObject {
    GCObjectType type;
    int marked;              // 1 = vivant, 0 = à nettoyer
    struct GCObject* next;   // Liste chaînée
} GCObject;

// Structure de l'état global du GC
typedef struct {
    GCObject* head;          // Début de la liste des objets
    int count;               // Nombre d'objets actuels
    int threshold;           // Seuil avant déclenchement
    int enabled;             // 1 = GC actif
} GCState;

// Fonctions publiques
void gc_init(void);
void* gc_allocate(GCObjectType type, size_t size);
void gc_collect(struct Environment* global_env);
void gc_mark_value(struct Value* val);
void gc_free_all(void);

// Macros pratiques
#define GC_NEW(type, struct_type) \
    (struct_type*)gc_allocate(type, sizeof(struct_type))

#define GC_NEW_STRING(str) \
    gc_allocate_string(str)

#endif // GC_H
