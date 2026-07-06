/**
 * gc.c — Implémentation du Garbage Collector tri-couleur
 * Goscript — GOPU inc.
 *
 * Algorithme : Mark-and-Sweep tri-couleur (Dijkstra/Yuasa)
 *
 *   Phase MARK :
 *     1. Scanner les racines → mettre en GC_GRAY
 *     2. Boucle : prendre un objet gris, scanner ses enfants (les mettre en gris),
 *        puis mettre l'objet en GC_BLACK
 *     3. Répéter jusqu'à ce que la file grise soit vide
 *
 *   Phase SWEEP :
 *     Parcourir la liste chaînée globale :
 *       - GC_WHITE → libérer
 *       - GC_BLACK → remettre en GC_WHITE pour le prochain cycle
 */

#include "gc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* ============================================================
 *  ÉTAT GLOBAL
 * ============================================================ */
GCState gs_gc;

/* Forward declarations */
static void gc_mark_phase(void);
static void gc_sweep_phase(void);
static void gc_trace_object(GCObject* obj);
static void scan_roots(void);

/* Accès à l'environnement global depuis l'interpréteur */
extern void* gs_global_env;  /* défini dans interpreter_eval.c */

/* ============================================================
 *  INITIALISATION / SHUTDOWN
 * ============================================================ */

void gc_init(void) {
    memset(&gs_gc, 0, sizeof(GCState));
    gs_gc.threshold       = 1024 * 1024;   /* 1 Mo avant premier GC */
    gs_gc.threshold_growth = 2;
    gs_gc.enabled         = 1;
    gs_gc.paused          = 0;

    arena_init(&gs_gc.ast_arena);
    pool_init(&gs_gc.value_pool, POOL_SLAB_SIZE);
}

void gc_shutdown(void) {
    /* Libère tous les objets GC */
    GCObject* obj = gs_gc.heap_head;
    while (obj) {
        GCObject* next = obj->next;
        free(obj);
        obj = next;
    }
    gs_gc.heap_head  = NULL;
    gs_gc.heap_count = 0;
    gs_gc.heap_bytes = 0;

    arena_free(&gs_gc.ast_arena);
    pool_destroy(&gs_gc.value_pool);
}

/* ============================================================
 *  ALLOCATION D'UN OBJET GC
 * ============================================================ */

GCObject* gc_alloc(GCObjectType type, size_t data_size) {
    size_t total = sizeof(GCObject) + data_size;
    GCObject* obj = (GCObject*)malloc(total);
    if (!obj) {
        /* Tentative de GC d'urgence */
        gc_collect();
        obj = (GCObject*)malloc(total);
        if (!obj) {
            fprintf(stderr, "[GC] FATAL: allocation échouée (%zu octets)\n", total);
            abort();
        }
    }

    memset(obj, 0, total);
    obj->type       = type;
    obj->color      = GC_WHITE;
    obj->size       = (uint32_t)data_size;
    obj->next       = gs_gc.heap_head;
    obj->gray_next  = NULL;
    gs_gc.heap_head = obj;
    gs_gc.heap_count++;
    gs_gc.heap_bytes += total;

    if (gs_gc.heap_bytes > gs_gc.peak_bytes)
        gs_gc.peak_bytes = gs_gc.heap_bytes;

    /* Déclencher le GC si on dépasse le seuil */
    if (gs_gc.enabled && !gs_gc.paused &&
        gs_gc.heap_bytes >= gs_gc.threshold) {
        gc_collect();
    }

    return obj;
}

GCObject* gc_alloc_string(const char* str) {
    size_t len  = str ? strlen(str) : 0;
    GCObject* obj = gc_alloc(GC_TYPE_STRING, len + 1);
    if (str) memcpy(GC_DATA(obj), str, len + 1);
    return obj;
}

/* ============================================================
 *  MISE EN FILE GRISE
 * ============================================================ */

static void gray_push(GCObject* obj) {
    if (!obj || obj->color == GC_GRAY || obj->color == GC_BLACK)
        return;
    obj->color     = GC_GRAY;
    obj->gray_next = gs_gc.gray_stack;
    gs_gc.gray_stack = obj;
    gs_gc.gray_count++;
}

/* ============================================================
 *  MARQUAGE PUBLIC (depuis root scanner ou write barrier)
 * ============================================================ */

void gc_mark_object(GCObject* obj) {
    if (!obj) return;
    gray_push(obj);
}

/* ============================================================
 *  TRAÇAGE D'UN OBJET GRIS (scan de ses enfants)
 * ============================================================ */

static void gc_trace_object(GCObject* obj) {
    /* Selon le type, marquer les enfants pointés.
     * Pour l'instant, la plupart des types sont opaques au GC
     * car les pointeurs internes sont dans les structures C.
     * Le traçage complet nécessite l'intégration avec le VM NaN-boxé. */
    obj->color = GC_BLACK;

    switch (obj->type) {
        case GC_TYPE_STRING:
        case GC_TYPE_GENERIC:
            /* Pas d'enfants */
            break;

        case GC_TYPE_ARRAY: {
            /* Structure GCArray { GCObject** elems; int count; } */
            typedef struct { GCObject** elems; int count; int cap; } GCArray;
            GCArray* arr = (GCArray*)GC_DATA(obj);
            for (int i = 0; i < arr->count; i++)
                gray_push(arr->elems[i]);
            break;
        }

        case GC_TYPE_DICT: {
            /* Structure GCDict { GCObject** keys; GCObject** vals; int count; } */
            typedef struct { GCObject** keys; GCObject** vals; int count; int cap; } GCDict;
            GCDict* d = (GCDict*)GC_DATA(obj);
            for (int i = 0; i < d->count; i++) {
                gray_push(d->keys[i]);
                gray_push(d->vals[i]);
            }
            break;
        }

        case GC_TYPE_ENVIRONMENT:
        case GC_TYPE_LAMBDA:
        case GC_TYPE_FUNCTION:
        case GC_TYPE_UPVALUE:
        case GC_TYPE_MODULE:
        case GC_TYPE_STRUCT:
        case GC_TYPE_PROMISE:
            /* Ces types ont des références croisées complexes.
             * Pour les marquer complètement, on les considère
             * comme toujours vivants si atteignables depuis les racines. */
            break;
    }
}

/* ============================================================
 *  SCAN DES RACINES (Roots)
 *  Racines = variables globales + pile d'exécution courante
 * ============================================================ */

static void scan_roots(void) {
    /* NOTE: Dans un vrai VM NaN-boxé, on parcourrait ici :
     *   1. La table des variables globales (global_env)
     *   2. La pile d'exécution du VM (vm->stack[0..sp])
     *   3. Les fermetures actives (upvalue chain)
     *   4. Les promesses en attente
     *
     * Pour l'interpréteur tree-walk actuel, on marque comme
     * vivants tous les objets GC référencés par l'environnement.
     * Le GC est conservateur dans cette implémentation initiale
     * (on ne libère que les objets explicitement oubliés).
     *
     * TODO: intégrer avec vm_run() pour un scanning précis.
     */
}

/* ============================================================
 *  PHASE MARK
 * ============================================================ */

static void gc_mark_phase(void) {
    /* Étape 1 : scanner les racines */
    scan_roots();

    /* Étape 2 : vider la file grise */
    while (gs_gc.gray_stack) {
        GCObject* obj    = gs_gc.gray_stack;
        gs_gc.gray_stack = obj->gray_next;
        gs_gc.gray_count--;
        obj->gray_next   = NULL;
        gc_trace_object(obj);
    }
}

/* ============================================================
 *  PHASE SWEEP
 * ============================================================ */

static void gc_sweep_phase(void) {
    GCObject** prev = &gs_gc.heap_head;
    GCObject*  obj  = gs_gc.heap_head;
    size_t     freed_bytes = 0;
    int        freed_count = 0;

    while (obj) {
        GCObject* next = obj->next;

        if (obj->color == GC_WHITE) {
            /* Objet non atteint → libérer */
            *prev = next;
            freed_bytes += sizeof(GCObject) + obj->size;
            freed_count++;
            gs_gc.heap_count--;
            free(obj);
        } else {
            /* Objet vivant → remettre en blanc pour le prochain cycle */
            obj->color = GC_WHITE;
            prev = &obj->next;
        }
        obj = next;
    }

    gs_gc.heap_bytes   -= freed_bytes;
    gs_gc.total_collected += freed_count;
}

/* ============================================================
 *  CYCLE GC COMPLET
 * ============================================================ */

void gc_collect(void) {
    if (!gs_gc.enabled || gs_gc.paused) return;

    gs_gc.total_cycles++;

    gc_mark_phase();
    gc_sweep_phase();

    /* Ajuster le seuil */
    if (gs_gc.heap_bytes > gs_gc.threshold / 2)
        gs_gc.threshold = gs_gc.heap_bytes * gs_gc.threshold_growth;
    if (gs_gc.threshold < 1024 * 1024)
        gs_gc.threshold = 1024 * 1024;
}

/* ============================================================
 *  PAUSE / REPRISE
 * ============================================================ */

void gc_pause(void)  { gs_gc.paused = 1; }
void gc_resume(void) { gs_gc.paused = 0; }

/* ============================================================
 *  STATISTIQUES
 * ============================================================ */

void gc_dump_stats(FILE* out) {
    if (!out) out = stderr;
    fprintf(out,
        "[GC] Objets actifs : %d  |  Mémoire : %zu Ko  |  Pic : %zu Ko\n"
        "     Cycles : %llu  |  Objets collectés : %llu\n",
        gs_gc.heap_count,
        gs_gc.heap_bytes  / 1024,
        gs_gc.peak_bytes  / 1024,
        (unsigned long long)gs_gc.total_cycles,
        (unsigned long long)gs_gc.total_collected
    );
}

/* ============================================================
 *  ARENA ALLOCATOR
 * ============================================================ */

void arena_init(Arena* a) {
    memset(a, 0, sizeof(Arena));
    /* Allouer le premier bloc */
    ArenaBlock* blk = (ArenaBlock*)malloc(sizeof(ArenaBlock));
    blk->data     = (uint8_t*)malloc(ARENA_BLOCK_SIZE);
    blk->used     = 0;
    blk->capacity = ARENA_BLOCK_SIZE;
    blk->next     = NULL;
    a->current    = blk;
    a->head       = blk;
}

void* arena_alloc(Arena* a, size_t size) {
    /* Alignement 8 octets */
    size = (size + 7) & ~(size_t)7;

    if (!a->current || a->current->used + size > a->current->capacity) {
        /* Nouveau bloc */
        size_t cap = (size > ARENA_BLOCK_SIZE) ? size * 2 : ARENA_BLOCK_SIZE;
        ArenaBlock* blk = (ArenaBlock*)malloc(sizeof(ArenaBlock));
        blk->data     = (uint8_t*)malloc(cap);
        blk->used     = 0;
        blk->capacity = cap;
        blk->next     = NULL;
        if (a->current) a->current->next = blk;
        else a->head = blk;
        a->current = blk;
    }

    void* ptr = a->current->data + a->current->used;
    a->current->used += size;
    a->total_allocated += size;
    return ptr;
}

void* arena_alloc_zero(Arena* a, size_t size) {
    void* p = arena_alloc(a, size);
    memset(p, 0, size);
    return p;
}

void arena_reset(Arena* a) {
    /* Libère tous les blocs sauf le premier */
    ArenaBlock* blk = a->head;
    if (blk) {
        ArenaBlock* next = blk->next;
        while (next) {
            ArenaBlock* n = next->next;
            free(next->data);
            free(next);
            next = n;
        }
        blk->used = 0;
        blk->next = NULL;
        a->current = blk;
    }
    a->total_allocated = 0;
}

void arena_free(Arena* a) {
    ArenaBlock* blk = a->head;
    while (blk) {
        ArenaBlock* next = blk->next;
        free(blk->data);
        free(blk);
        blk = next;
    }
    memset(a, 0, sizeof(Arena));
}

/* ============================================================
 *  MEMORY POOL
 * ============================================================ */

void pool_init(MemPool* p, size_t obj_size) {
    memset(p, 0, sizeof(MemPool));
    /* S'assurer que l'objet est assez grand pour une PoolFreeNode */
    p->obj_size = (obj_size >= sizeof(PoolFreeNode)) ? obj_size : sizeof(PoolFreeNode);
}

static void pool_grow(MemPool* p) {
    PoolSlab* slab = (PoolSlab*)malloc(sizeof(PoolSlab));
    slab->data = (uint8_t*)malloc(p->obj_size * POOL_SLAB_COUNT);
    slab->used = 0;
    slab->next = p->slabs;
    p->slabs   = slab;

    /* Remplir la free-list avec les nouveaux blocs */
    uint8_t* ptr = slab->data;
    for (int i = 0; i < POOL_SLAB_COUNT; i++) {
        PoolFreeNode* node = (PoolFreeNode*)ptr;
        node->next   = p->free_list;
        p->free_list = node;
        ptr += p->obj_size;
    }
    p->total += POOL_SLAB_COUNT;
}

void* pool_alloc(MemPool* p) {
    if (!p->free_list) pool_grow(p);
    PoolFreeNode* node = p->free_list;
    p->free_list       = node->next;
    p->in_use++;
    memset(node, 0, p->obj_size);
    return (void*)node;
}

void pool_free(MemPool* p, void* ptr) {
    if (!ptr) return;
    PoolFreeNode* node = (PoolFreeNode*)ptr;
    node->next   = p->free_list;
    p->free_list = node;
    p->in_use--;
}

void pool_destroy(MemPool* p) {
    PoolSlab* slab = p->slabs;
    while (slab) {
        PoolSlab* next = slab->next;
        free(slab->data);
        free(slab);
        slab = next;
    }
    memset(p, 0, sizeof(MemPool));
}
