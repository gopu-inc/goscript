/**
 * vm.h — Stack Virtual Machine + NaN-Boxing
 * Goscript — GOPU inc.
 *
 * NaN-BOXING (IEEE 754 double) :
 *   Double valide → valeur directe (exp != 0x7FF)
 *   QNAN | TAG_INT    → int32 (low 32 bits)
 *   QNAN | TAG_OBJ    → GCObject* (low 48 bits)
 *   QNAN | TAG_BOOL   → booléen (bit 0)
 *   QNAN | TAG_NIL    → nil
 *   QNAN | TAG_NATIVE → pointeur C natif (low 48 bits)
 *
 * Tous les opcodes sont préfixés VM_OP_ pour éviter les conflits
 * avec l'enum Operator de ast.h (OP_ADD, OP_SUB…).
 */

#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "../gc/gc.h"

/* ── Forward declarations ─────────────────────────────────── */
struct ASTNode;
struct VMChunk;

/* ============================================================
 *  NaN-BOXING
 * ============================================================ */
typedef uint64_t vm_Value;

#define QNAN_MASK    ((uint64_t)0x7FFC000000000000ULL)
#define TAG_NIL      ((uint64_t)1 << 48)
#define TAG_BOOL     ((uint64_t)2 << 48)
#define TAG_INT      ((uint64_t)3 << 48)
#define TAG_OBJ      ((uint64_t)4 << 48)
#define TAG_NATIVE   ((uint64_t)5 << 48)
#define TAG_MASK     ((uint64_t)0x7 << 48)

#define VM_IS_FLOAT(v)  (((v) & QNAN_MASK) != QNAN_MASK)
#define VM_IS_NIL(v)    ((v) == (QNAN_MASK | TAG_NIL))
#define VM_IS_BOOL(v)   (((v) & (QNAN_MASK | TAG_MASK)) == (QNAN_MASK | TAG_BOOL))
#define VM_IS_INT(v)    (((v) & (QNAN_MASK | TAG_MASK)) == (QNAN_MASK | TAG_INT))
#define VM_IS_OBJ(v)    (((v) & (QNAN_MASK | TAG_MASK)) == (QNAN_MASK | TAG_OBJ))
#define VM_IS_NATIVE(v) (((v) & (QNAN_MASK | TAG_MASK)) == (QNAN_MASK | TAG_NATIVE))
#define VM_IS_TRUTHY(v) (!VM_IS_NIL(v) && \
                         !(VM_IS_BOOL(v) && !VM_BOOL(v)) && \
                         !(VM_IS_INT(v) && VM_INT(v) == 0))

static inline double vm_float_decode(vm_Value v) {
    double d; __builtin_memcpy(&d, &v, 8); return d;
}
static inline vm_Value vm_float_encode(double d) {
    vm_Value v; __builtin_memcpy(&v, &d, 8); return v;
}

#define VM_FLOAT(v)    vm_float_decode(v)
#define VM_BOOL(v)     ((int)((v) & 1))
#define VM_INT(v)      ((int32_t)((v) & 0xFFFFFFFFULL))
#define VM_OBJ(v)      ((GCObject*)(uintptr_t)((v) & 0x0000FFFFFFFFFFFFULL))
#define VM_NATIVE(v)   ((void(*)(void))(uintptr_t)((v) & 0x0000FFFFFFFFFFFFULL))

#define VM_MAKE_FLOAT(d)   vm_float_encode(d)
#define VM_MAKE_NIL()      (QNAN_MASK | TAG_NIL)
#define VM_MAKE_BOOL(b)    (QNAN_MASK | TAG_BOOL | ((uint64_t)((b) ? 1 : 0)))
#define VM_MAKE_INT(i)     (QNAN_MASK | TAG_INT  | ((uint64_t)(uint32_t)(i)))
#define VM_MAKE_OBJ(p)     (QNAN_MASK | TAG_OBJ  | ((uint64_t)(uintptr_t)(p) & 0x0000FFFFFFFFFFFFULL))
#define VM_MAKE_NATIVE(p)  (QNAN_MASK | TAG_NATIVE | ((uint64_t)(uintptr_t)(p) & 0x0000FFFFFFFFFFFFULL))
#define VM_MAKE_TRUE()     VM_MAKE_BOOL(1)
#define VM_MAKE_FALSE()    VM_MAKE_BOOL(0)

/* ============================================================
 *  JEU D'INSTRUCTIONS  (préfixe VM_OP_ pour éviter les conflits)
 * ============================================================ */
typedef enum {
    /* ── Pile ── */
    VM_OP_NOP = 0,
    VM_OP_PUSH_NIL,
    VM_OP_PUSH_TRUE,
    VM_OP_PUSH_FALSE,
    VM_OP_PUSH_INT,        /* operand = int32 inline */
    VM_OP_PUSH_FLOAT,      /* operand = index dans float_pool */
    VM_OP_PUSH_STRING,     /* operand = index dans string_pool */
    VM_OP_POP,
    VM_OP_DUP,
    VM_OP_SWAP,

    /* ── Variables ── */
    VM_OP_LOAD_LOCAL,      /* operand = slot */
    VM_OP_STORE_LOCAL,     /* operand = slot */
    VM_OP_LOAD_GLOBAL,     /* operand = name_pool index */
    VM_OP_STORE_GLOBAL,    /* operand = name_pool index */
    VM_OP_LOAD_UPVALUE,    /* operand = upvalue index */
    VM_OP_STORE_UPVALUE,
    VM_OP_CLOSE_UPVALUE,

    /* ── Arithmétique ── */
    VM_OP_ADD,
    VM_OP_SUB,
    VM_OP_MUL,
    VM_OP_DIV,
    VM_OP_MOD,
    VM_OP_POW,
    VM_OP_NEG,

    /* ── Comparaisons ── */
    VM_OP_EQ,
    VM_OP_NEQ,
    VM_OP_LESS,
    VM_OP_LESS_EQ,
    VM_OP_GREATER,
    VM_OP_GREATER_EQ,

    /* ── Logique ── */
    VM_OP_AND,
    VM_OP_OR,
    VM_OP_NOT,

    /* ── Bitwise ── */
    VM_OP_BAND,
    VM_OP_BOR,
    VM_OP_BXOR,
    VM_OP_BNOT,
    VM_OP_LSHIFT,
    VM_OP_RSHIFT,

    /* ── Contrôle de flux ── */
    VM_OP_JUMP,
    VM_OP_JUMP_IF_FALSE,
    VM_OP_JUMP_IF_TRUE,
    VM_OP_LOOP,

    /* ── Fonctions ── */
    VM_OP_CALL,
    VM_OP_CALL_NATIVE,
    VM_OP_RETURN,
    VM_OP_MAKE_CLOSURE,
    VM_OP_TAIL_CALL,

    /* ── Objets ── */
    VM_OP_MAKE_ARRAY,
    VM_OP_MAKE_DICT,
    VM_OP_GET_INDEX,
    VM_OP_SET_INDEX,
    VM_OP_GET_FIELD,
    VM_OP_SET_FIELD,
    VM_OP_GET_SUPER,

    /* ── Gestion d'erreurs ── */
    VM_OP_TRY_BEGIN,
    VM_OP_TRY_END,
    VM_OP_THROW,
    VM_OP_CATCH,

    /* ── Async ── */
    VM_OP_SPAWN,
    VM_OP_YIELD,
    VM_OP_AWAIT,

    /* ── Import ── */
    VM_OP_IMPORT,

    /* ── Débogage ── */
    VM_OP_PRINT,
    VM_OP_BREAKPOINT,
    VM_OP_ASSERT,

    VM_OP_HALT,
    VM_OP_COUNT
} VMOpCode;

/* ============================================================
 *  INSTRUCTION
 * ============================================================ */
typedef struct {
    uint8_t  op;
    int32_t  operand;
    int32_t  operand2;
    uint32_t line;
} VMInstruction;

/* ============================================================
 *  CHUNK DE BYTECODE
 * ============================================================ */
typedef struct VMChunk {
    VMInstruction* code;
    int            count;
    int            capacity;

    double*  float_pool;
    int      float_count, float_cap;

    char**   string_pool;
    int      string_count, string_cap;

    char**   name_pool;
    int      name_count, name_cap;

    struct VMChunk** funcs;
    int              func_count, func_cap;

    char* name;
    int   arity;
    int   local_count;
    int   upvalue_count;
} VMChunk;

typedef VMChunk VMFunc;

/* ============================================================
 *  UPVALUE & CLOSURE
 * ============================================================ */
#define VM_STACK_SIZE   4096
#define VM_CALL_FRAMES  512
#define VM_MAX_UPVALUES 256

typedef struct VMUpvalue {
    vm_Value*         location;
    vm_Value          closed;
    int               is_closed;
    struct VMUpvalue* next;
} VMUpvalue;

typedef struct {
    VMFunc*    func;
    VMUpvalue* upvalues[VM_MAX_UPVALUES];
    int        upvalue_count;
} VMClosure;

/* ============================================================
 *  CALL FRAME
 * ============================================================ */
typedef struct {
    VMClosure*     closure;
    VMInstruction* ip;
    vm_Value*      slots;
    int            slot_count;
} CallFrame;

/* ============================================================
 *  ÉTAT DE LA VM
 * ============================================================ */
typedef enum {
    VM_OK = 0,
    VM_COMPILE_ERROR,
    VM_RUNTIME_ERROR,
    VM_HALTED
} VMResult;

typedef struct {
    vm_Value   stack[VM_STACK_SIZE];
    vm_Value*  sp;
    CallFrame  frames[VM_CALL_FRAMES];
    int        frame_count;
    CallFrame* current_frame;
    VMUpvalue* open_upvalues;
    vm_Value   current_exception;
    int        has_exception;
    VMResult   status;
    char       error_msg[512];
    void*      interp_env;
} VM;

/* ============================================================
 *  API PUBLIQUE — CHUNK
 * ============================================================ */
VMChunk* vm_chunk_new(const char* name);
void     vm_chunk_free(VMChunk* chunk);
int      vm_emit(VMChunk* chunk, uint8_t op, int32_t operand, int32_t operand2, uint32_t line);
int      vm_add_float(VMChunk* chunk, double val);
int      vm_add_string(VMChunk* chunk, const char* str);
int      vm_add_name(VMChunk* chunk, const char* name);
void     vm_patch_jump(VMChunk* chunk, int idx, int32_t new_operand);
void     vm_chunk_disasm(FILE* out, VMChunk* chunk, const char* title);

/* ============================================================
 *  API PUBLIQUE — VM
 * ============================================================ */
void     vm_init(VM* vm);
void     vm_reset(VM* vm);
VMResult vm_run(VM* vm, VMChunk* chunk);
void     vm_free(VM* vm);

vm_Value vm_from_gs_value(void* gs_val);
void     vm_to_gs_value(vm_Value v, void* out_gs_val);

/* ============================================================
 *  API PUBLIQUE — COMPILATEUR
 * ============================================================ */
VMChunk* vm_compile(struct ASTNode* program);
VMResult vm_execute(struct ASTNode* program, void* interp_env);

extern const char* vm_opcode_names[VM_OP_COUNT];

#endif /* VM_H */
