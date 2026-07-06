/**
 * gc.h — Garbage Collector tri-couleur (Mark-and-Sweep) + Arena Allocator
 * Goscript — GOPU inc.
 *
 * Architecture :
 *   - Arena Allocator : pour les nœuds AST (durée de vie = compilation → exécution)
 *   - Memory Pool     : pour les objets runtime Value (strings, arrays, dicts, closures)
 *   - Mark-and-Sweep  : algorithme tri-couleur (Blanc/Gris/Noir)
 *
 * Couleurs tri-couleur :
 *   GC_WHITE (0) : non découvert → sera libéré lors du sweep
 *   GC_GRAY  (1) : découvert mais enfants non encore scannés
 *   GC_BLACK (2) : entièrement traité → à conserver
 */

#ifndef GC_H
#define GC_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* ============================================================
 *  COULEURS TRI-COULEUR
 * ============================================================ */
typedef enum {
    GC_WHITE = 0,   /* Candidat à la libération */
    GC_GRAY  = 1,   /* Découvert, enfants non scannés */
    GC_BLACK = 2    /* Entièrement traité */
} GCColor;

/* ============================================================
 *  TYPES D'OBJETS GÉRÉS
 * ============================================================ */
typedef enum {
    GC_TYPE_STRING,
    GC_TYPE_ARRAY,
    GC_TYPE_DICT,
    GC_TYPE_STRUCT,
    GC_TYPE_FUNCTION,
    GC_TYPE_LAMBDA,
    GC_TYPE_ENVIRONMENT,
    GC_TYPE_PROMISE,
    GC_TYPE_UPVALUE,     /* Fermeture (upvalue pour closures) */
    GC_TYPE_MODULE,
    GC_TYPE_GENERIC      /* Objet générique opaque */
} GCObjectType;

/* ============================================================
 *  EN-TÊTE DE TOUS LES OBJETS GC
 *  Chaque objet alloué par le GC commence par ce header.
 * ============================================================ */
typedef struct GCObject {
    GCObjectType  type;     /* Type de l'objet */
    GCColor       color;    /* Couleur tri-couleur */
    uint32_t      size;     /* Taille de l'objet (hors header) */
    struct GCObject* next;  /* Liste chaînée globale des objets */
    struct GCObject* gray_next; /* Liste des objets gris (file de travail) */
} GCObject;

/* Accède à la donnée utilisateur après le header GC */
#define GC_DATA(obj)  ((void*)((GCObject*)(obj) + 1))
/* Remonte au header depuis une donnée utilisateur */
#define GC_HEADER(ptr) ((GCObject*)(ptr) - 1)

/* ============================================================
 *  ARENA ALLOCATOR (pour les nœuds AST)
 *  Bloc de mémoire contiguë — allocation par bump pointer.
 *  Libération en une seule opération arena_free().
 * ============================================================ */
#define ARENA_BLOCK_SIZE (1024 * 1024)  /* 1 Mo par bloc */

typedef struct ArenaBlock {
    uint8_t*          data;     /* Début du bloc */
    size_t            used;     /* Octets utilisés */
    size_t            capacity; /* Capacité totale */
    struct ArenaBlock* next;    /* Bloc suivant */
} ArenaBlock;

typedef struct {
    ArenaBlock* current; /* Bloc actif */
    ArenaBlock* head;    /* Premier bloc (pour itération) */
    size_t      total_allocated;
    size_t      total_wasted;
} Arena;

/* ============================================================
 *  MEMORY POOL (pour les objets runtime de taille fixe)
 *  Slabs de taille fixe — O(1) alloc/free via free-list.
 * ============================================================ */
#define POOL_SLAB_SIZE   64          /* Taille d'un objet dans le pool */
#define POOL_SLAB_COUNT  4096        /* Objets par slab */

typedef struct PoolFreeNode {
    struct PoolFreeNode* next;
} PoolFreeNode;

typedef struct PoolSlab {
    uint8_t*         data;
    int              used;
    struct PoolSlab* next;
} PoolSlab;

typedef struct {
    PoolFreeNode* free_list; /* Liste des blocs libres */
    PoolSlab*     slabs;     /* Liste des slabs alloués */
    size_t        obj_size;  /* Taille d'un objet */
    int           total;
    int           in_use;
} MemPool;

/* ============================================================
 *  ÉTAT GLOBAL DU GARBAGE COLLECTOR
 * ============================================================ */
typedef struct {
    /* Liste globale de tous les objets GC */
    GCObject*  heap_head;
    int        heap_count;
    size_t     heap_bytes;

    /* File de travail des objets gris */
    GCObject*  gray_stack;
    int        gray_count;

    /* Seuils et statistiques */
    size_t     threshold;          /* Déclenche le GC au-delà */
    size_t     threshold_growth;   /* Facteur de croissance du seuil */
    int        enabled;
    int        paused;             /* Pause temporaire (pendant imports) */

    /* Statistiques */
    uint64_t   total_collected;    /* Objets collectés au total */
    uint64_t   total_cycles;       /* Nombre de cycles GC */
    size_t     peak_bytes;         /* Pic mémoire observé */

    /* Allocateurs spécialisés */
    Arena      ast_arena;          /* Arena pour l'AST */
    MemPool    value_pool;         /* Pool pour les petits objets */
} GCState;

/* ============================================================
 *  API PUBLIQUE — GC GLOBAL
 * ============================================================ */
void  gc_init(void);
void  gc_shutdown(void);

/** Alloue un objet géré par le GC (header inclus) */
GCObject* gc_alloc(GCObjectType type, size_t data_size);

/** Alloue une chaîne gérée par le GC */
GCObject* gc_alloc_string(const char* str);

/** Déclenche un cycle Mark-and-Sweep complet */
void  gc_collect(void);

/** Marque une valeur comme racine (à appeler depuis le scanner de racines) */
void  gc_mark_object(GCObject* obj);

/** Pause / reprise du GC (pour les imports, les FFI) */
void  gc_pause(void);
void  gc_resume(void);

/** Statistiques */
void  gc_dump_stats(FILE* out);

/* ============================================================
 *  API PUBLIQUE — ARENA ALLOCATOR
 * ============================================================ */
void   arena_init(Arena* arena);
void*  arena_alloc(Arena* arena, size_t size);
void*  arena_alloc_zero(Arena* arena, size_t size);
void   arena_reset(Arena* arena);  /* Libère tout en une passe */
void   arena_free(Arena* arena);   /* Libère et détruit l'arena */

/* ============================================================
 *  API PUBLIQUE — MEMORY POOL
 * ============================================================ */
void   pool_init(MemPool* pool, size_t obj_size);
void*  pool_alloc(MemPool* pool);
void   pool_free(MemPool* pool, void* ptr);
void   pool_destroy(MemPool* pool);

/* ============================================================
 *  MACROS PRATIQUES
 * ============================================================ */

/** Alloue un objet GC typé et retourne un pointeur vers sa donnée */
#define GC_NEW(gc_type, c_type) \
    ((c_type*)GC_DATA(gc_alloc((gc_type), sizeof(c_type))))

/** Marque un pointeur brut comme objet GC */
#define GC_MARK(ptr) \
    do { if (ptr) gc_mark_object(GC_HEADER(ptr)); } while(0)

/** Alloue depuis l'arena AST globale */
#define ARENA_ALLOC(size) \
    arena_alloc(&gs_gc.ast_arena, (size))

/** Accès à l'état GC global */
extern GCState gs_gc;

#endif /* GC_H */
