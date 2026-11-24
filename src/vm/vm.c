/**
 * vm.c — Stack Virtual Machine avec Direct Threaded Code
 * Goscript — GOPU inc.
 */

#include "vm.h"
#include "../gc/gc.h"
#include "../interpreter/interpreter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

/* ============================================================
 *  NOMS DES OPCODES
 * ============================================================ */
const char* vm_opcode_names[VM_OP_COUNT] = {
    [VM_OP_NOP]          = "NOP",
    [VM_OP_PUSH_NIL]     = "PUSH_NIL",
    [VM_OP_PUSH_TRUE]    = "PUSH_TRUE",
    [VM_OP_PUSH_FALSE]   = "PUSH_FALSE",
    [VM_OP_PUSH_INT]     = "PUSH_INT",
    [VM_OP_PUSH_FLOAT]   = "PUSH_FLOAT",
    [VM_OP_PUSH_STRING]  = "PUSH_STRING",
    [VM_OP_POP]          = "POP",
    [VM_OP_DUP]          = "DUP",
    [VM_OP_SWAP]         = "SWAP",
    [VM_OP_LOAD_LOCAL]   = "LOAD_LOCAL",
    [VM_OP_STORE_LOCAL]  = "STORE_LOCAL",
    [VM_OP_LOAD_GLOBAL]  = "LOAD_GLOBAL",
    [VM_OP_STORE_GLOBAL] = "STORE_GLOBAL",
    [VM_OP_LOAD_UPVALUE] = "LOAD_UPVALUE",
    [VM_OP_STORE_UPVALUE]= "STORE_UPVALUE",
    [VM_OP_CLOSE_UPVALUE]= "CLOSE_UPVALUE",
    [VM_OP_ADD]          = "ADD",
    [VM_OP_SUB]          = "SUB",
    [VM_OP_MUL]          = "MUL",
    [VM_OP_DIV]          = "DIV",
    [VM_OP_MOD]          = "MOD",
    [VM_OP_POW]          = "POW",
    [VM_OP_NEG]          = "NEG",
    [VM_OP_EQ]           = "EQ",
    [VM_OP_NEQ]          = "NEQ",
    [VM_OP_LESS]         = "LESS",
    [VM_OP_LESS_EQ]      = "LESS_EQ",
    [VM_OP_GREATER]      = "GREATER",
    [VM_OP_GREATER_EQ]   = "GREATER_EQ",
    [VM_OP_AND]          = "AND",
    [VM_OP_OR]           = "OR",
    [VM_OP_NOT]          = "NOT",
    [VM_OP_BAND]         = "BAND",
    [VM_OP_BOR]          = "BOR",
    [VM_OP_BXOR]         = "BXOR",
    [VM_OP_BNOT]         = "BNOT",
    [VM_OP_LSHIFT]       = "LSHIFT",
    [VM_OP_RSHIFT]       = "RSHIFT",
    [VM_OP_JUMP]         = "JUMP",
    [VM_OP_JUMP_IF_FALSE]= "JUMP_IF_FALSE",
    [VM_OP_JUMP_IF_TRUE] = "JUMP_IF_TRUE",
    [VM_OP_LOOP]         = "LOOP",
    [VM_OP_CALL]         = "CALL",
    [VM_OP_CALL_NATIVE]  = "CALL_NATIVE",
    [VM_OP_RETURN]       = "RETURN",
    [VM_OP_MAKE_CLOSURE] = "MAKE_CLOSURE",
    [VM_OP_TAIL_CALL]    = "TAIL_CALL",
    [VM_OP_MAKE_ARRAY]   = "MAKE_ARRAY",
    [VM_OP_MAKE_DICT]    = "MAKE_DICT",
    [VM_OP_GET_INDEX]    = "GET_INDEX",
    [VM_OP_SET_INDEX]    = "SET_INDEX",
    [VM_OP_GET_FIELD]    = "GET_FIELD",
    [VM_OP_SET_FIELD]    = "SET_FIELD",
    [VM_OP_GET_SUPER]    = "GET_SUPER",
    [VM_OP_TRY_BEGIN]    = "TRY_BEGIN",
    [VM_OP_TRY_END]      = "TRY_END",
    [VM_OP_THROW]        = "THROW",
    [VM_OP_CATCH]        = "CATCH",
    [VM_OP_SPAWN]        = "SPAWN",
    [VM_OP_YIELD]        = "YIELD",
    [VM_OP_AWAIT]        = "AWAIT",
    [VM_OP_IMPORT]       = "IMPORT",
    [VM_OP_PRINT]        = "PRINT",
    [VM_OP_BREAKPOINT]   = "BREAKPOINT",
    [VM_OP_ASSERT]       = "ASSERT",
    [VM_OP_HALT]         = "HALT",
};

/* ============================================================
 *  CHUNK
 * ============================================================ */
VMChunk* vm_chunk_new(const char* name) {
    VMChunk* c = (VMChunk*)calloc(1, sizeof(VMChunk));
    c->name     = name ? strdup(name) : strdup("<chunk>");
    c->capacity = 64;
    c->code     = (VMInstruction*)malloc(sizeof(VMInstruction) * c->capacity);
    return c;
}

void vm_chunk_free(VMChunk* c) {
    if (!c) return;
    free(c->code);
    for (int i = 0; i < c->string_count; i++) free(c->string_pool[i]);
    free(c->string_pool);
    for (int i = 0; i < c->name_count; i++) free(c->name_pool[i]);
    free(c->name_pool);
    free(c->float_pool);
    for (int i = 0; i < c->func_count; i++) vm_chunk_free(c->funcs[i]);
    free(c->funcs);
    free(c->name);
    free(c);
}

int vm_emit(VMChunk* c, uint8_t op, int32_t a, int32_t b, uint32_t line) {
    if (c->count >= c->capacity) {
        c->capacity *= 2;
        c->code = (VMInstruction*)realloc(c->code,
                    sizeof(VMInstruction) * c->capacity);
    }
    VMInstruction ins = { op, a, b, line };
    c->code[c->count] = ins;
    return c->count++;
}

void vm_patch_jump(VMChunk* c, int idx, int32_t operand) {
    if (idx >= 0 && idx < c->count)
        c->code[idx].operand = operand;
}

#define POOL_PUSH(pool, cap, cnt, type, val)              \
    do {                                                   \
        if ((cnt) >= (cap)) {                              \
            (cap) = (cap) ? (cap)*2 : 8;                   \
            (pool) = realloc((pool), sizeof(type)*(cap));  \
        }                                                  \
        (pool)[(cnt)++] = (val);                           \
    } while(0)

int vm_add_float(VMChunk* c, double v) {
    POOL_PUSH(c->float_pool, c->float_cap, c->float_count, double, v);
    return c->float_count - 1;
}
int vm_add_string(VMChunk* c, const char* s) {
    POOL_PUSH(c->string_pool, c->string_cap, c->string_count, char*, strdup(s));
    return c->string_count - 1;
}
int vm_add_name(VMChunk* c, const char* n) {
    for (int i = 0; i < c->name_count; i++)
        if (strcmp(c->name_pool[i], n) == 0) return i;
    POOL_PUSH(c->name_pool, c->name_cap, c->name_count, char*, strdup(n));
    return c->name_count - 1;
}

/* ============================================================
 *  DISASSEMBLEUR
 * ============================================================ */
void vm_chunk_disasm(FILE* out, VMChunk* c, const char* title) {
    if (!out) out = stdout;
    fprintf(out, "══════════════════════════════════\n");
    fprintf(out, " %s (%d instructions)\n", title ? title : c->name, c->count);
    fprintf(out, "══════════════════════════════════\n");
    for (int i = 0; i < c->count; i++) {
        VMInstruction* ins = &c->code[i];
        const char* nm = (ins->op < VM_OP_COUNT) ? vm_opcode_names[ins->op] : "???";
        fprintf(out, "  %04d  %-16s", i, nm);
        switch (ins->op) {
            case VM_OP_PUSH_INT:    fprintf(out, " %d", ins->operand); break;
            case VM_OP_PUSH_FLOAT:
                fprintf(out, " [%d] %.6g", ins->operand,
                    (ins->operand < c->float_count) ? c->float_pool[ins->operand] : 0.0);
                break;
            case VM_OP_PUSH_STRING:
                fprintf(out, " [%d] \"%s\"", ins->operand,
                    (ins->operand < c->string_count) ? c->string_pool[ins->operand] : "?");
                break;
            case VM_OP_LOAD_GLOBAL: case VM_OP_STORE_GLOBAL:
            case VM_OP_LOAD_LOCAL:  case VM_OP_STORE_LOCAL:
            case VM_OP_LOAD_UPVALUE: case VM_OP_STORE_UPVALUE:
            case VM_OP_GET_FIELD:   case VM_OP_SET_FIELD:
            case VM_OP_IMPORT:
                fprintf(out, " [%d] \"%s\"", ins->operand,
                    (ins->operand < c->name_count) ? c->name_pool[ins->operand] : "?");
                break;
            case VM_OP_JUMP: case VM_OP_JUMP_IF_FALSE: case VM_OP_JUMP_IF_TRUE:
            case VM_OP_LOOP:
                fprintf(out, " -> %d", i + ins->operand); break;
            default:
                if (ins->operand != 0) fprintf(out, " %d", ins->operand);
                break;
        }
        fprintf(out, "  ; line %d\n", ins->line);
    }
    fprintf(out, "══════════════════════════════════\n");
    for (int i = 0; i < c->func_count; i++)
        vm_chunk_disasm(out, c->funcs[i], c->funcs[i]->name);
}

/* ============================================================
 *  VM — INIT
 * ============================================================ */
void vm_init(VM* vm) {
    memset(vm, 0, sizeof(VM));
    vm->sp = vm->stack;
    vm->status = VM_OK;
}

void vm_reset(VM* vm) {
    vm->sp = vm->stack;
    vm->frame_count = 0;
    vm->status = VM_OK;
    vm->has_exception = 0;
    vm->open_upvalues = NULL;
}

void vm_free(VM* vm) { (void)vm; }

/* ── Pile ── */
static inline void vm_push(VM* vm, vm_Value v) {
    if (vm->sp >= vm->stack + VM_STACK_SIZE) {
        fprintf(stderr, "[VM] Stack overflow\n");
        vm->status = VM_RUNTIME_ERROR;
        return;
    }
    *vm->sp++ = v;
}

static inline vm_Value vm_pop(VM* vm) {
    if (vm->sp <= vm->stack) {
        fprintf(stderr, "[VM] Stack underflow\n");
        vm->status = VM_RUNTIME_ERROR;
        return VM_MAKE_NIL();
    }
    return *--vm->sp;
}

static inline vm_Value vm_peek(VM* vm, int offset) {
    if (offset < 0 || offset >= (int)(vm->sp - vm->stack)) {
        snprintf(vm->error_msg, sizeof(vm->error_msg), "Stack underflow");
        vm->status = VM_RUNTIME_ERROR;
        return VM_MAKE_NIL();
    }
    return *(vm->sp - 1 - offset);
}

/* ── Affichage ── */
static void vm_print_value(vm_Value v) {
    if (VM_IS_FLOAT(v)) {
        double d = VM_FLOAT(v);
        if (d == (long long)d) printf("%.0f", d);
        else printf("%g", d);
    } else if (VM_IS_INT(v))  printf("%d",  VM_INT(v));
    else if (VM_IS_BOOL(v))   printf("%s",  VM_BOOL(v) ? "true" : "false");
    else if (VM_IS_NIL(v))    printf("nil");
    else if (VM_IS_OBJ(v)) {
        GCObject* obj = VM_OBJ(v);
        if (obj && obj->type == GC_TYPE_STRING)
            printf("%s", (char*)GC_DATA(obj));
        else
            printf("<object>");
    } else {
        printf("<value:0x%016llx>", (unsigned long long)v);
    }
}

vm_Value vm_from_gs_value(void* gs_val) {
    if (!gs_val) return VM_MAKE_NIL();
    Value* value = (Value*)gs_val;
    switch (value->type) {
        case 0: return VM_MAKE_INT((int32_t)value->int_val);
        case 1: return VM_MAKE_FLOAT(value->float_val);
        case 2: return VM_MAKE_OBJ(gc_alloc_string(value->string_val ? value->string_val : ""));
        case 3: return VM_MAKE_BOOL(value->bool_val);
        default: return VM_MAKE_NIL();
    }
}

void vm_to_gs_value(vm_Value value, void* gs_val) {
    if (!gs_val) return;
    Value* out = (Value*)gs_val;
    memset(out, 0, sizeof(*out));
    if (VM_IS_INT(value)) { out->type = 0; out->int_val = VM_INT(value); }
    else if (VM_IS_FLOAT(value)) { out->type = 1; out->float_val = VM_FLOAT(value); }
    else if (VM_IS_BOOL(value)) { out->type = 3; out->bool_val = VM_BOOL(value); }
    else if (VM_IS_OBJ(value)) {
        GCObject* obj = VM_OBJ(value);
        if (obj && obj->type == GC_TYPE_STRING) { out->type = 2; out->string_val = strdup((char*)GC_DATA(obj)); }
        else out->type = 0;
    } else { out->type = 0; out->int_val = 0; }
}

/* ── Arithmétique ── */
static const char* vm_value_text(vm_Value value, char* buffer, size_t size);

static inline vm_Value vm_add_values(VM* vm, vm_Value a, vm_Value b) {
    if (VM_IS_INT(a) && VM_IS_INT(b)) {
        /* Goscript integers are signed 32-bit values. Do the operation as
         * unsigned arithmetic so overflow has defined wraparound behavior. */
        uint32_t sum = (uint32_t)VM_INT(a) + (uint32_t)VM_INT(b);
        return VM_MAKE_INT((int32_t)sum);
    }
    int a_is_string = 0, b_is_string = 0;
    if (VM_IS_OBJ(a)) { GCObject* o=VM_OBJ(a); a_is_string=o&&o->type==GC_TYPE_STRING; }
    if (VM_IS_OBJ(b)) { GCObject* o=VM_OBJ(b); b_is_string=o&&o->type==GC_TYPE_STRING; }
    if (a_is_string || b_is_string) {
        char a_buf[64], b_buf[64];
        const char* sa=vm_value_text(a,a_buf,sizeof(a_buf));
        const char* sb=vm_value_text(b,b_buf,sizeof(b_buf));
        size_t la=strlen(sa),lb=strlen(sb);
        GCObject* obj=gc_alloc(GC_TYPE_STRING,la+lb+1);
        if(!obj){snprintf(vm->error_msg,sizeof(vm->error_msg),"Out of memory concatenating strings");vm->status=VM_RUNTIME_ERROR;return VM_MAKE_NIL();}
        char* dst=(char*)GC_DATA(obj);
        memcpy(dst,sa,la);memcpy(dst+la,sb,lb+1);
        return VM_MAKE_OBJ(obj);
    }
    if ((VM_IS_FLOAT(a) || VM_IS_INT(a)) && (VM_IS_FLOAT(b) || VM_IS_INT(b))) {
        double fa = VM_IS_FLOAT(a) ? VM_FLOAT(a) : (double)VM_INT(a);
        double fb = VM_IS_FLOAT(b) ? VM_FLOAT(b) : (double)VM_INT(b);
        return VM_MAKE_FLOAT(fa + fb);
    }
    snprintf(vm->error_msg, sizeof(vm->error_msg), "Unsupported operands for addition");
    vm->status = VM_RUNTIME_ERROR;
    return VM_MAKE_NIL();
}

static inline double to_double(vm_Value v) {
    return VM_IS_FLOAT(v) ? VM_FLOAT(v) : VM_IS_INT(v) ? (double)VM_INT(v) : 0.0;
}

static const char* vm_value_text(vm_Value value, char* buffer, size_t size) {
    if (VM_IS_OBJ(value)) {
        GCObject* object = VM_OBJ(value);
        if (object && object->type == GC_TYPE_STRING) return (const char*)GC_DATA(object);
    }
    if (VM_IS_INT(value)) snprintf(buffer, size, "%d", VM_INT(value));
    else if (VM_IS_FLOAT(value)) snprintf(buffer, size, "%.15g", VM_FLOAT(value));
    else if (VM_IS_BOOL(value)) snprintf(buffer, size, "%s", VM_BOOL(value) ? "true" : "false");
    else snprintf(buffer, size, "nil");
    return buffer;
}

static inline vm_Value vm_arith(VM* vm, uint8_t op, vm_Value a, vm_Value b) {
    if (VM_IS_INT(a) && VM_IS_INT(b)) {
        int32_t ia = VM_INT(a), ib = VM_INT(b);
        switch (op) {
            case VM_OP_SUB:
                return VM_MAKE_INT((int32_t)((uint32_t)ia - (uint32_t)ib));
            case VM_OP_MUL:
                return VM_MAKE_INT((int32_t)((uint32_t)ia * (uint32_t)ib));
            case VM_OP_DIV:
                if (ib == 0) {
                    snprintf(vm->error_msg, sizeof(vm->error_msg), "Division by zero");
                    vm->status = VM_RUNTIME_ERROR;
                    return VM_MAKE_NIL();
                }
            return VM_MAKE_INT(ia == INT32_MIN && ib == -1 ? INT32_MIN : ia / ib);
            case VM_OP_MOD:
                if (ib == 0) {
                    snprintf(vm->error_msg, sizeof(vm->error_msg), "Modulo by zero");
                    vm->status = VM_RUNTIME_ERROR;
                    return VM_MAKE_NIL();
                }
                return VM_MAKE_INT(ia == INT32_MIN && ib == -1 ? 0 : ia % ib);
        }
    }
    double fa = to_double(a), fb = to_double(b);
    switch (op) {
        case VM_OP_SUB:
            if ((VM_IS_FLOAT(a) || VM_IS_INT(a)) && (VM_IS_FLOAT(b) || VM_IS_INT(b))) return VM_MAKE_FLOAT(fa - fb);
            break;
        case VM_OP_MUL:
            if ((VM_IS_FLOAT(a) || VM_IS_INT(a)) && (VM_IS_FLOAT(b) || VM_IS_INT(b))) return VM_MAKE_FLOAT(fa * fb);
            break;
        case VM_OP_DIV:
            if (fb == 0.0) {
                snprintf(vm->error_msg, sizeof(vm->error_msg), "Division par zéro");
                vm->status = VM_RUNTIME_ERROR;
                return VM_MAKE_NIL();
            }
            if ((VM_IS_FLOAT(a) || VM_IS_INT(a)) && (VM_IS_FLOAT(b) || VM_IS_INT(b))) return VM_MAKE_FLOAT(fa / fb);
            break;
        case VM_OP_MOD: {
            int64_t ia = (int64_t)fa, ib = (int64_t)fb;
            if (ib == 0) {
                snprintf(vm->error_msg, sizeof(vm->error_msg), "Modulo par zéro");
                vm->status = VM_RUNTIME_ERROR;
                return VM_MAKE_NIL();
            }
            return VM_MAKE_INT((int32_t)(ia % ib));
        }
        case VM_OP_POW: return VM_MAKE_FLOAT(pow(fa, fb));
    }
    return VM_MAKE_NIL();
}

static inline vm_Value vm_compare(uint8_t op, vm_Value a, vm_Value b) {
    if (VM_IS_OBJ(a) && VM_IS_OBJ(b)) {
        GCObject* oa = VM_OBJ(a);
        GCObject* ob = VM_OBJ(b);
        if (oa && ob && oa->type == GC_TYPE_STRING && ob->type == GC_TYPE_STRING) {
            int cmp = strcmp((const char*)GC_DATA(oa), (const char*)GC_DATA(ob));
            switch (op) {
                case VM_OP_EQ:         return VM_MAKE_BOOL(cmp == 0);
                case VM_OP_NEQ:        return VM_MAKE_BOOL(cmp != 0);
                case VM_OP_LESS:       return VM_MAKE_BOOL(cmp < 0);
                case VM_OP_LESS_EQ:    return VM_MAKE_BOOL(cmp <= 0);
                case VM_OP_GREATER:    return VM_MAKE_BOOL(cmp > 0);
                case VM_OP_GREATER_EQ: return VM_MAKE_BOOL(cmp >= 0);
            }
        }
    }
    if (VM_IS_INT(a) && VM_IS_INT(b)) {
        int32_t ia = VM_INT(a), ib = VM_INT(b);
        switch (op) {
            case VM_OP_EQ:         return VM_MAKE_BOOL(ia == ib);
            case VM_OP_NEQ:        return VM_MAKE_BOOL(ia != ib);
            case VM_OP_LESS:       return VM_MAKE_BOOL(ia <  ib);
            case VM_OP_LESS_EQ:    return VM_MAKE_BOOL(ia <= ib);
            case VM_OP_GREATER:    return VM_MAKE_BOOL(ia >  ib);
            case VM_OP_GREATER_EQ: return VM_MAKE_BOOL(ia >= ib);
        }
    }
    double fa = to_double(a), fb = to_double(b);
    switch (op) {
        case VM_OP_EQ:         return VM_MAKE_BOOL(fa == fb);
        case VM_OP_NEQ:        return VM_MAKE_BOOL(fa != fb);
        case VM_OP_LESS:       return VM_MAKE_BOOL(fa <  fb);
        case VM_OP_LESS_EQ:    return VM_MAKE_BOOL(fa <= fb);
        case VM_OP_GREATER:    return VM_MAKE_BOOL(fa >  fb);
        case VM_OP_GREATER_EQ: return VM_MAKE_BOOL(fa >= fb);
    }
    return VM_MAKE_FALSE();
}

/* ============================================================
 *  BOUCLE D'EXÉCUTION — DIRECT THREADED CODE (GCC computed gotos)
 * ============================================================ */
VMResult vm_run(VM* vm, VMChunk* chunk) {
    if (!chunk || chunk->count == 0) return VM_OK;

    VMInstruction* ip     = chunk->code;
    VMInstruction* ip_end = chunk->code + chunk->count;

    if (vm->frame_count >= VM_CALL_FRAMES) {
        snprintf(vm->error_msg, sizeof(vm->error_msg),
                 "Trop de cadres imbriqués");
        return VM_RUNTIME_ERROR;
    }
    CallFrame* frame  = &vm->frames[vm->frame_count++];
    frame->closure    = NULL;
    frame->ip         = ip;
    frame->slots      = vm->sp;
    vm->current_frame = frame;

    for (int i = 0; i < chunk->local_count; i++)
        vm_push(vm, VM_MAKE_NIL());

#ifdef __GNUC__
    /* ── Dispatch table (Direct Threaded Code) ── */
    static const void* DT[VM_OP_COUNT] = {
        [VM_OP_NOP]          = &&L_NOP,
        [VM_OP_PUSH_NIL]     = &&L_PUSH_NIL,
        [VM_OP_PUSH_TRUE]    = &&L_PUSH_TRUE,
        [VM_OP_PUSH_FALSE]   = &&L_PUSH_FALSE,
        [VM_OP_PUSH_INT]     = &&L_PUSH_INT,
        [VM_OP_PUSH_FLOAT]   = &&L_PUSH_FLOAT,
        [VM_OP_PUSH_STRING]  = &&L_PUSH_STRING,
        [VM_OP_POP]          = &&L_POP,
        [VM_OP_DUP]          = &&L_DUP,
        [VM_OP_SWAP]         = &&L_SWAP,
        [VM_OP_LOAD_LOCAL]   = &&L_LOAD_LOCAL,
        [VM_OP_STORE_LOCAL]  = &&L_STORE_LOCAL,
        [VM_OP_LOAD_GLOBAL]  = &&L_LOAD_GLOBAL,
        [VM_OP_STORE_GLOBAL] = &&L_STORE_GLOBAL,
        [VM_OP_LOAD_UPVALUE] = &&L_LOAD_UPVALUE,
        [VM_OP_STORE_UPVALUE]= &&L_STORE_UPVALUE,
        [VM_OP_CLOSE_UPVALUE]= &&L_CLOSE_UPVALUE,
        [VM_OP_ADD]          = &&L_ADD,
        [VM_OP_SUB]          = &&L_SUB,
        [VM_OP_MUL]          = &&L_MUL,
        [VM_OP_DIV]          = &&L_DIV,
        [VM_OP_MOD]          = &&L_MOD,
        [VM_OP_POW]          = &&L_POW,
        [VM_OP_NEG]          = &&L_NEG,
        [VM_OP_EQ]           = &&L_EQ,
        [VM_OP_NEQ]          = &&L_NEQ,
        [VM_OP_LESS]         = &&L_LESS,
        [VM_OP_LESS_EQ]      = &&L_LESS_EQ,
        [VM_OP_GREATER]      = &&L_GREATER,
        [VM_OP_GREATER_EQ]   = &&L_GREATER_EQ,
        [VM_OP_AND]          = &&L_AND,
        [VM_OP_OR]           = &&L_OR,
        [VM_OP_NOT]          = &&L_NOT,
        [VM_OP_BAND]         = &&L_BAND,
        [VM_OP_BOR]          = &&L_BOR,
        [VM_OP_BXOR]         = &&L_BXOR,
        [VM_OP_BNOT]         = &&L_BNOT,
        [VM_OP_LSHIFT]       = &&L_LSHIFT,
        [VM_OP_RSHIFT]       = &&L_RSHIFT,
        [VM_OP_JUMP]         = &&L_JUMP,
        [VM_OP_JUMP_IF_FALSE]= &&L_JUMP_IF_FALSE,
        [VM_OP_JUMP_IF_TRUE] = &&L_JUMP_IF_TRUE,
        [VM_OP_LOOP]         = &&L_LOOP,
        [VM_OP_CALL]         = &&L_CALL,
        [VM_OP_CALL_NATIVE]  = &&L_CALL_NATIVE,
        [VM_OP_RETURN]       = &&L_RETURN,
        [VM_OP_MAKE_CLOSURE] = &&L_MAKE_CLOSURE,
        [VM_OP_TAIL_CALL]    = &&L_TAIL_CALL,
        [VM_OP_MAKE_ARRAY]   = &&L_MAKE_ARRAY,
        [VM_OP_MAKE_DICT]    = &&L_MAKE_DICT,
        [VM_OP_GET_INDEX]    = &&L_GET_INDEX,
        [VM_OP_SET_INDEX]    = &&L_SET_INDEX,
        [VM_OP_GET_FIELD]    = &&L_GET_FIELD,
        [VM_OP_SET_FIELD]    = &&L_SET_FIELD,
        [VM_OP_GET_SUPER]    = &&L_GET_SUPER,
        [VM_OP_TRY_BEGIN]    = &&L_TRY_BEGIN,
        [VM_OP_TRY_END]      = &&L_TRY_END,
        [VM_OP_THROW]        = &&L_THROW,
        [VM_OP_CATCH]        = &&L_CATCH,
        [VM_OP_SPAWN]        = &&L_SPAWN,
        [VM_OP_YIELD]        = &&L_YIELD,
        [VM_OP_AWAIT]        = &&L_AWAIT,
        [VM_OP_IMPORT]       = &&L_IMPORT,
        [VM_OP_PRINT]        = &&L_PRINT,
        [VM_OP_BREAKPOINT]   = &&L_BREAKPOINT,
        [VM_OP_ASSERT]       = &&L_ASSERT,
        [VM_OP_HALT]         = &&L_HALT,
    };

    #define DISPATCH() \
        do { if (ip >= ip_end || vm->status != VM_OK) goto L_HALT; \
             if (ip->op >= VM_OP_COUNT) { \
                 snprintf(vm->error_msg, sizeof(vm->error_msg), "Invalid opcode %u", ip->op); \
                 vm->status = VM_RUNTIME_ERROR; goto L_HALT; \
             } \
             goto *DT[ip->op]; } while(0)
    #define NEXT() do { ip++; DISPATCH(); } while(0)

    DISPATCH();

    L_NOP:          ip++; DISPATCH();
    L_PUSH_NIL:     vm_push(vm, VM_MAKE_NIL());    NEXT();
    L_PUSH_TRUE:    vm_push(vm, VM_MAKE_TRUE());   NEXT();
    L_PUSH_FALSE:   vm_push(vm, VM_MAKE_FALSE());  NEXT();
    L_PUSH_INT:     vm_push(vm, VM_MAKE_INT(ip->operand)); NEXT();
    L_PUSH_FLOAT:
        if (ip->operand < 0 || ip->operand >= chunk->float_count) {
            snprintf(vm->error_msg, sizeof(vm->error_msg), "Invalid float constant index %d", ip->operand);
            vm->status = VM_RUNTIME_ERROR; goto L_HALT;
        }
        vm_push(vm, VM_MAKE_FLOAT(chunk->float_pool[ip->operand]));
        NEXT();
    L_PUSH_STRING: {
        if (ip->operand < 0 || ip->operand >= chunk->string_count) {
            snprintf(vm->error_msg, sizeof(vm->error_msg), "Invalid string constant index %d", ip->operand);
            vm->status = VM_RUNTIME_ERROR; goto L_HALT;
        }
        const char* s = chunk->string_pool[ip->operand];
        vm_push(vm, VM_MAKE_OBJ(gc_alloc_string(s)));
        NEXT();
    }

    L_POP:  vm_pop(vm); NEXT();
    L_DUP:  vm_push(vm, vm_peek(vm, 0)); NEXT();
    L_SWAP: { vm_Value a = vm_pop(vm); vm_Value b = vm_pop(vm);
              vm_push(vm, a); vm_push(vm, b); NEXT(); }

    L_LOAD_LOCAL:
    L_STORE_LOCAL:
        if (ip->operand < 0 || ip->operand >= chunk->local_count) {
            snprintf(vm->error_msg, sizeof(vm->error_msg), "Invalid local slot %d", ip->operand);
            vm->status = VM_RUNTIME_ERROR; goto L_HALT;
        }
        if (ip->op == VM_OP_LOAD_LOCAL) vm_push(vm, frame->slots[ip->operand]);
        else frame->slots[ip->operand] = vm_peek(vm, 0);
        NEXT();
    L_LOAD_GLOBAL: {
        const char* name = ip->operand >= 0 && ip->operand < chunk->name_count ? chunk->name_pool[ip->operand] : "";
        Value* value = env_get((Environment*)vm->interp_env, (char*)name);
        if (!value) {
            snprintf(vm->error_msg, sizeof(vm->error_msg), "Undefined global '%s'", name);
            vm->status = VM_RUNTIME_ERROR;
            vm_push(vm, VM_MAKE_NIL());
        } else vm_push(vm, vm_from_gs_value(value));
        NEXT();
    }
    L_STORE_GLOBAL: {
        const char* name = ip->operand >= 0 && ip->operand < chunk->name_count ? chunk->name_pool[ip->operand] : "";
        Value value;
        vm_Value stored = vm_pop(vm);
        vm_to_gs_value(stored, &value);
        env_set((Environment*)vm->interp_env, (char*)name, value);
        vm_push(vm, stored);
        NEXT();
    }
    L_LOAD_UPVALUE: {
        VMClosure* cl = frame->closure;
        if (cl && ip->operand < cl->upvalue_count) {
            VMUpvalue* uv = cl->upvalues[ip->operand];
            vm_push(vm, uv->is_closed ? uv->closed : *uv->location);
        } else { vm_push(vm, VM_MAKE_NIL()); }
        NEXT();
    }
    L_STORE_UPVALUE: {
        VMClosure* cl = frame->closure;
        if (cl && ip->operand < cl->upvalue_count) {
            VMUpvalue* uv = cl->upvalues[ip->operand];
            if (uv->is_closed) uv->closed = vm_peek(vm, 0);
            else *uv->location = vm_peek(vm, 0);
        }
        NEXT();
    }
    L_CLOSE_UPVALUE: {
        VMUpvalue* uv = vm->open_upvalues;
        while (uv && uv->location >= vm->sp - 1) {
            uv->closed = *uv->location;
            uv->is_closed = 1;
            uv->location  = &uv->closed;
            vm->open_upvalues = uv->next;
            uv = vm->open_upvalues;
        }
        vm_pop(vm);
        NEXT();
    }

    /* ── Arithmétique ── */
    L_ADD: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_add_values(vm,a,b)); NEXT(); }
    L_SUB: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_SUB,a,b)); NEXT(); }
    L_MUL: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_MUL,a,b)); NEXT(); }
    L_DIV: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_DIV,a,b)); NEXT(); }
    L_MOD: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_MOD,a,b)); NEXT(); }
    L_POW: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_POW,a,b)); NEXT(); }
    L_NEG: { vm_Value a=vm_pop(vm);
             vm_push(vm, VM_IS_INT(a) ? VM_MAKE_INT((int32_t)(0u - (uint32_t)VM_INT(a))) : VM_MAKE_FLOAT(-to_double(a)));
             NEXT(); }

    /* ── Comparaisons ── */
    L_EQ:         { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_compare(VM_OP_EQ,a,b));         NEXT(); }
    L_NEQ:        { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_compare(VM_OP_NEQ,a,b));        NEXT(); }
    L_LESS:       { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_compare(VM_OP_LESS,a,b));       NEXT(); }
    L_LESS_EQ:    { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_compare(VM_OP_LESS_EQ,a,b));    NEXT(); }
    L_GREATER:    { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_compare(VM_OP_GREATER,a,b));    NEXT(); }
    L_GREATER_EQ: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_compare(VM_OP_GREATER_EQ,a,b)); NEXT(); }

    /* ── Logique ── */
    L_AND: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm);
             vm_push(vm,VM_MAKE_BOOL(VM_IS_TRUTHY(a)&&VM_IS_TRUTHY(b))); NEXT(); }
    L_OR:  { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm);
             vm_push(vm,VM_IS_TRUTHY(a)?a:b); NEXT(); }
    L_NOT: { vm_Value a=vm_pop(vm); vm_push(vm,VM_MAKE_BOOL(!VM_IS_TRUTHY(a))); NEXT(); }

    /* ── Bitwise ── */
    L_BAND:   { int32_t b=VM_INT(vm_pop(vm)); int32_t a=VM_INT(vm_pop(vm)); vm_push(vm,VM_MAKE_INT(a&b)); NEXT(); }
    L_BOR:    { int32_t b=VM_INT(vm_pop(vm)); int32_t a=VM_INT(vm_pop(vm)); vm_push(vm,VM_MAKE_INT(a|b)); NEXT(); }
    L_BXOR:   { int32_t b=VM_INT(vm_pop(vm)); int32_t a=VM_INT(vm_pop(vm)); vm_push(vm,VM_MAKE_INT(a^b)); NEXT(); }
    L_BNOT:   { vm_push(vm,VM_MAKE_INT(~VM_INT(vm_pop(vm)))); NEXT(); }
    L_LSHIFT: { int32_t b=VM_INT(vm_pop(vm)); int32_t a=VM_INT(vm_pop(vm)); vm_push(vm,VM_MAKE_INT(a<<b)); NEXT(); }
    L_RSHIFT: { int32_t b=VM_INT(vm_pop(vm)); int32_t a=VM_INT(vm_pop(vm)); vm_push(vm,VM_MAKE_INT(a>>b)); NEXT(); }

    /* ── Contrôle de flux ── */
    L_JUMP:
    L_JUMP_IF_FALSE:
    L_JUMP_IF_TRUE:
    L_LOOP: {
        ptrdiff_t current = ip - chunk->code;
        ptrdiff_t target = current + ip->operand;
        int take = ip->op == VM_OP_JUMP || ip->op == VM_OP_LOOP ||
                   (ip->op == VM_OP_JUMP_IF_FALSE && !VM_IS_TRUTHY(vm_peek(vm, 0))) ||
                   (ip->op == VM_OP_JUMP_IF_TRUE && VM_IS_TRUTHY(vm_peek(vm, 0)));
        if (take) {
            if (target < 0 || target >= chunk->count) {
                snprintf(vm->error_msg, sizeof(vm->error_msg), "Invalid jump target %ld", (long)target);
                vm->status = VM_RUNTIME_ERROR; goto L_HALT;
            }
            ip = chunk->code + target;
        } else ip++;
        DISPATCH();
    }

    /* ── Fonctions ── */
    L_CALL:
    L_CALL_NATIVE:
        snprintf(vm->error_msg, sizeof(vm->error_msg), "CALL opcode is not implemented by this VM build");
        vm->status = VM_RUNTIME_ERROR; goto L_HALT;
    L_RETURN: {
        vm_Value result = ip->operand ? vm_pop(vm) : VM_MAKE_NIL();
        vm->sp = frame->slots;
        vm->frame_count--;
        if (vm->frame_count == 0) { vm_push(vm, result); goto L_HALT; }
        vm->current_frame = frame = &vm->frames[vm->frame_count - 1];
        ip = frame->ip;
        ip_end = NULL;
        vm_push(vm, result);
        NEXT();
    }
    L_MAKE_CLOSURE:
    L_TAIL_CALL:
        snprintf(vm->error_msg, sizeof(vm->error_msg), "closure/tail-call opcode is not implemented by this VM build");
        vm->status = VM_RUNTIME_ERROR; goto L_HALT;

    /* ── Objets ── */
    L_MAKE_ARRAY: {
        typedef struct { GCObject** elems; int count; int cap; } GCArray;
        int n = ip->operand;
        GCObject* obj = gc_alloc(GC_TYPE_ARRAY, sizeof(GCArray));
        GCArray* arr  = (GCArray*)GC_DATA(obj);
        arr->count = arr->cap = n;
        arr->elems = n ? (GCObject**)malloc(sizeof(GCObject*)*n) : NULL;
        for (int i = n-1; i >= 0; i--) {
            vm_Value v = vm_pop(vm);
            arr->elems[i] = VM_IS_OBJ(v) ? VM_OBJ(v) : NULL;
        }
        vm_push(vm, VM_MAKE_OBJ(obj));
        NEXT();
    }
    L_MAKE_DICT: {
        typedef struct { GCObject** keys; GCObject** vals; int count; int cap; } GCDict;
        int n = ip->operand;
        GCObject* obj = gc_alloc(GC_TYPE_DICT, sizeof(GCDict));
        GCDict* d     = (GCDict*)GC_DATA(obj);
        d->count = d->cap = n;
        d->keys = n ? (GCObject**)malloc(sizeof(GCObject*)*n) : NULL;
        d->vals = n ? (GCObject**)malloc(sizeof(GCObject*)*n) : NULL;
        for (int i = n-1; i >= 0; i--) {
            vm_Value val = vm_pop(vm);
            vm_Value key = vm_pop(vm);
            d->keys[i] = VM_IS_OBJ(key) ? VM_OBJ(key) : NULL;
            d->vals[i] = VM_IS_OBJ(val) ? VM_OBJ(val) : NULL;
        }
        vm_push(vm, VM_MAKE_OBJ(obj));
        NEXT();
    }
    L_GET_INDEX:
    L_SET_INDEX:
    L_GET_FIELD:
    L_SET_FIELD:
    L_GET_SUPER:
        snprintf(vm->error_msg, sizeof(vm->error_msg), "object access opcode is not implemented by this VM build");
        vm->status = VM_RUNTIME_ERROR; goto L_HALT;

    /* ── Gestion d'erreurs ── */
    L_TRY_BEGIN:
    L_TRY_END:
        snprintf(vm->error_msg, sizeof(vm->error_msg), "exception handler opcodes are not implemented by this VM build");
        vm->status = VM_RUNTIME_ERROR; goto L_HALT;
    L_THROW: {
        vm->current_exception = vm_pop(vm);
        vm->has_exception = 1;
        snprintf(vm->error_msg, sizeof(vm->error_msg), "[VM] Exception levée");
        vm->status = VM_RUNTIME_ERROR;
        goto L_HALT;
    }
    L_CATCH: {
        vm_push(vm, vm->has_exception ? vm->current_exception : VM_MAKE_NIL());
        vm->has_exception = 0;
        NEXT();
    }

    /* ── Async ── */
    L_SPAWN:
    L_YIELD:
    L_AWAIT:
    L_IMPORT:
        snprintf(vm->error_msg, sizeof(vm->error_msg), "async/import opcode is not implemented by this VM build");
        vm->status = VM_RUNTIME_ERROR; goto L_HALT;

    /* ── Débogage ── */
    L_PRINT: {
        if (ip->operand2) putchar(' ');
        vm_print_value(vm_pop(vm));
        if (ip->operand) putchar('\n');
        NEXT();
    }
    L_BREAKPOINT: {
        fprintf(stderr, "[VM BP] ip=%ld sp=%ld\n",
            (long)(ip - chunk->code), (long)(vm->sp - vm->stack));
        NEXT();
    }
    L_ASSERT: {
        vm_Value cond = vm_pop(vm);
        if (!VM_IS_TRUTHY(cond)) {
            snprintf(vm->error_msg, sizeof(vm->error_msg),
                     "Assertion échouée @ inst %ld", (long)(ip - chunk->code));
            vm->status = VM_RUNTIME_ERROR;
        }
        NEXT();
    }

    L_HALT:
        vm->frame_count = vm->frame_count > 0 ? vm->frame_count - 1 : 0;
        return vm->status;

#else /* Fallback switch() */
    while (ip < ip_end && vm->status == VM_OK) {
        switch (ip->op) {
            case VM_OP_NOP:        break;
            case VM_OP_PUSH_NIL:   vm_push(vm, VM_MAKE_NIL());  break;
            case VM_OP_PUSH_TRUE:  vm_push(vm, VM_MAKE_TRUE()); break;
            case VM_OP_PUSH_FALSE: vm_push(vm, VM_MAKE_FALSE()); break;
            case VM_OP_PUSH_INT:   vm_push(vm, VM_MAKE_INT(ip->operand)); break;
            case VM_OP_PUSH_FLOAT: vm_push(vm, VM_MAKE_FLOAT(ip->operand>=0&&ip->operand<chunk->float_count?chunk->float_pool[ip->operand]:0.0)); break;
            case VM_OP_PUSH_STRING: vm_push(vm,VM_MAKE_OBJ(gc_alloc_string(ip->operand>=0&&ip->operand<chunk->string_count?chunk->string_pool[ip->operand]:""))); break;
            case VM_OP_POP:  vm_pop(vm); break;
            case VM_OP_DUP:  vm_push(vm, vm_peek(vm, 0)); break;
            case VM_OP_LOAD_GLOBAL: {const char*n=ip->operand>=0&&ip->operand<chunk->name_count?chunk->name_pool[ip->operand]:"";Value*v=env_get((Environment*)vm->interp_env,(char*)n);vm_push(vm,v?vm_from_gs_value(v):VM_MAKE_NIL());break;}
            case VM_OP_STORE_GLOBAL: {const char*n=ip->operand>=0&&ip->operand<chunk->name_count?chunk->name_pool[ip->operand]:"";Value v;vm_to_gs_value(vm_pop(vm),&v);env_set((Environment*)vm->interp_env,(char*)n,v);vm_push(vm,vm_from_gs_value(&v));break;}
            case VM_OP_ADD: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_add_values(vm,a,b)); break; }
            case VM_OP_SUB: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_SUB,a,b)); break; }
            case VM_OP_MUL: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_MUL,a,b)); break; }
            case VM_OP_DIV: { vm_Value b=vm_pop(vm); vm_Value a=vm_pop(vm); vm_push(vm,vm_arith(vm,VM_OP_DIV,a,b)); break; }
            case VM_OP_MOD: case VM_OP_POW: {vm_Value b=vm_pop(vm),a=vm_pop(vm);vm_push(vm,vm_arith(vm,ip->op,a,b));break;}
            case VM_OP_NEG: {vm_Value v=vm_pop(vm);vm_push(vm,VM_IS_INT(v)?VM_MAKE_INT((int32_t)(0u-(uint32_t)VM_INT(v))):VM_MAKE_FLOAT(-to_double(v)));break;}
            case VM_OP_EQ: case VM_OP_NEQ: case VM_OP_LESS: case VM_OP_LESS_EQ: case VM_OP_GREATER: case VM_OP_GREATER_EQ: {vm_Value b=vm_pop(vm),a=vm_pop(vm);vm_push(vm,vm_compare(ip->op,a,b));break;}
            case VM_OP_AND: {vm_Value b=vm_pop(vm),a=vm_pop(vm);vm_push(vm,VM_MAKE_BOOL(VM_IS_TRUTHY(a)&&VM_IS_TRUTHY(b)));break;}
            case VM_OP_OR: {vm_Value b=vm_pop(vm),a=vm_pop(vm);vm_push(vm,VM_IS_TRUTHY(a)?a:b);break;}
            case VM_OP_NOT: vm_push(vm,VM_MAKE_BOOL(!VM_IS_TRUTHY(vm_pop(vm))));break;
            case VM_OP_JUMP: case VM_OP_LOOP: case VM_OP_JUMP_IF_FALSE: case VM_OP_JUMP_IF_TRUE: {
                int take = ip->op == VM_OP_JUMP || ip->op == VM_OP_LOOP ||
                    (ip->op == VM_OP_JUMP_IF_FALSE && !VM_IS_TRUTHY(vm_peek(vm,0))) ||
                    (ip->op == VM_OP_JUMP_IF_TRUE && VM_IS_TRUTHY(vm_peek(vm,0)));
                if (take) {
                    ptrdiff_t target = (ip - chunk->code) + ip->operand;
                    if (target < 0 || target >= chunk->count) {
                        snprintf(vm->error_msg, sizeof(vm->error_msg), "Invalid jump target %ld", (long)target);
                        vm->status = VM_RUNTIME_ERROR;
                        goto end_sw;
                    }
                    ip = chunk->code + target;
                } else ip++;
                continue;
            }
            case VM_OP_RETURN: {
                vm_Value result = ip->operand ? vm_pop(vm) : VM_MAKE_NIL();
                vm->sp = frame->slots; vm->frame_count--;
                (void)result; goto end_sw;
            }
            case VM_OP_PRINT: { if(ip->operand2)putchar(' ');vm_print_value(vm_pop(vm));if(ip->operand)putchar('\n');break; }
            case VM_OP_HALT:  goto end_sw;
            default:
                snprintf(vm->error_msg, sizeof(vm->error_msg), "Opcode %u is not implemented by this VM build", ip->op);
                vm->status = VM_RUNTIME_ERROR;
                goto end_sw;
        }
        ip++;
    }
    end_sw:
    return vm->status;
#endif
}

/* ============================================================
 *  COMPILATEUR AST → BYTECODE (portable scalar/control-flow subset)
 * ============================================================ */
static int vm_compile_failed;
static NodeType vm_compile_failed_node;

static int vm_compile_expr(VMChunk* chunk, ASTNode* node);
static int vm_compile_stmt_list(VMChunk* chunk, ASTNodeList* list);

static int vm_emit_name(VMChunk* chunk, uint8_t op, const char* name, uint32_t line) {
    int index = vm_add_name(chunk, name ? name : "");
    if (index < 0) return 0;
    vm_emit(chunk, op, index, 0, line);
    return 1;
}

static int vm_compile_expr(VMChunk* chunk, ASTNode* node) {
    if (!node) { vm_emit(chunk, VM_OP_PUSH_NIL, 0, 0, 0); return 1; }
    switch (node->type) {
        case NODE_NUMBER:
            if (node->number.value < INT32_MIN || node->number.value > INT32_MAX) return 0;
            vm_emit(chunk, VM_OP_PUSH_INT, (int32_t)node->number.value, 0, (uint32_t)node->line);
            return 1;
        case NODE_FLOAT: {
            int index = vm_add_float(chunk, node->float_val.value);
            if (index < 0) return 0;
            vm_emit(chunk, VM_OP_PUSH_FLOAT, index, 0, (uint32_t)node->line);
            return 1;
        }
        case NODE_STRING: {
            int index = vm_add_string(chunk, node->string_val.value ? node->string_val.value : "");
            if (index < 0) return 0;
            vm_emit(chunk, VM_OP_PUSH_STRING, index, 0, (uint32_t)node->line);
            return 1;
        }
        case NODE_BOOL:
            vm_emit(chunk, node->bool_val.value ? VM_OP_PUSH_TRUE : VM_OP_PUSH_FALSE, 0, 0, (uint32_t)node->line);
            return 1;
        case NODE_NIL:
            vm_emit(chunk, VM_OP_PUSH_NIL, 0, 0, (uint32_t)node->line);
            return 1;
        case NODE_IDENTIFIER:
            return vm_emit_name(chunk, VM_OP_LOAD_GLOBAL, node->identifier.name, (uint32_t)node->line);
        case NODE_UNARY_OP:
            if (!vm_compile_expr(chunk, node->unary.operand)) return 0;
            if (node->unary.op == OP_NEG) vm_emit(chunk, VM_OP_NEG, 0, 0, (uint32_t)node->line);
            else if (node->unary.op == OP_NOT) vm_emit(chunk, VM_OP_NOT, 0, 0, (uint32_t)node->line);
            else return 0;
            return 1;
        case NODE_BINARY_OP: {
            if (node->binary.op == OP_ASSIGN && node->binary.left && node->binary.left->type == NODE_IDENTIFIER) {
                if (!vm_compile_expr(chunk, node->binary.right)) return 0;
                vm_emit(chunk, VM_OP_DUP, 0, 0, (uint32_t)node->line);
                if (!vm_emit_name(chunk, VM_OP_STORE_GLOBAL, node->binary.left->identifier.name, (uint32_t)node->line)) return 0;
                vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
                return 1;
            }
            if (node->binary.op == OP_AND || node->binary.op == OP_OR) {
                int is_and = node->binary.op == OP_AND;
                if (!vm_compile_expr(chunk, node->binary.left)) return 0;
                int branch = vm_emit(chunk, is_and ? VM_OP_JUMP_IF_FALSE : VM_OP_JUMP_IF_TRUE, 0, 0, (uint32_t)node->line);
                vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
                if (!vm_compile_expr(chunk, node->binary.right)) return 0;
                int done = vm_emit(chunk, VM_OP_JUMP, 0, 0, (uint32_t)node->line);
                vm_patch_jump(chunk, branch, chunk->count - branch);
                vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
                vm_emit(chunk, is_and ? VM_OP_PUSH_FALSE : VM_OP_PUSH_TRUE, 0, 0, (uint32_t)node->line);
                vm_patch_jump(chunk, done, chunk->count - done);
                return 1;
            }
            if (!vm_compile_expr(chunk, node->binary.left) || !vm_compile_expr(chunk, node->binary.right)) return 0;
            uint8_t op;
            switch (node->binary.op) {
                case OP_ADD: op=VM_OP_ADD; break; case OP_SUB: op=VM_OP_SUB; break;
                case OP_MUL: op=VM_OP_MUL; break; case OP_DIV: op=VM_OP_DIV; break;
                case OP_MOD: op=VM_OP_MOD; break; case OP_EQ: op=VM_OP_EQ; break;
                case OP_NEQ: op=VM_OP_NEQ; break; case OP_LT: op=VM_OP_LESS; break;
                case OP_LTE: op=VM_OP_LESS_EQ; break; case OP_GT: op=VM_OP_GREATER; break;
                case OP_GTE: op=VM_OP_GREATER_EQ; break;
                default: return 0;
            }
            vm_emit(chunk, op, 0, 0, (uint32_t)node->line);
            return 1;
        }
        case NODE_TERNARY: {
            if (!vm_compile_expr(chunk, node->ternary.condition)) return 0;
            int branch = vm_emit(chunk, VM_OP_JUMP_IF_FALSE, 0, 0, (uint32_t)node->line);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            if (!vm_compile_expr(chunk, node->ternary.true_expr)) return 0;
            int done = vm_emit(chunk, VM_OP_JUMP, 0, 0, (uint32_t)node->line);
            vm_patch_jump(chunk, branch, chunk->count - branch);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            if (!vm_compile_expr(chunk, node->ternary.false_expr)) return 0;
            vm_patch_jump(chunk, done, chunk->count - done);
            return 1;
        }
        case NODE_CALL: {
            if (!node->call.callee || node->call.callee->type != NODE_IDENTIFIER) return 0;
            const char* name = node->call.callee->identifier.name;
            int is_println = strcmp(name, "println") == 0;
            if (!is_println && strcmp(name, "print") != 0) return 0;
            int argc = node->call.args ? node->call.args->count : 0;
            if (argc == 0 && is_println) {
                int empty = vm_add_string(chunk, "");
                if (empty < 0) return 0;
                vm_emit(chunk, VM_OP_PUSH_STRING, empty, 0, (uint32_t)node->line);
                vm_emit(chunk, VM_OP_PRINT, 1, 0, (uint32_t)node->line);
            } else {
                for (int i=0; i<argc; i++) {
                    if (!vm_compile_expr(chunk, node->call.args->nodes[i])) return 0;
                    vm_emit(chunk, VM_OP_PRINT, is_println && i == argc-1, i > 0, (uint32_t)node->line);
                }
            }
            vm_emit(chunk, VM_OP_PUSH_NIL, 0, 0, (uint32_t)node->line);
            return 1;
        }
        default: vm_compile_failed_node=node->type; return 0;
    }
}

static int vm_compile_stmt(VMChunk* chunk, ASTNode* node) {
    if (!node) return 1;
    switch (node->type) {
        case NODE_LET: case NODE_CONST: case NODE_MUTS: {
            const char* name = node->type == NODE_MUTS ? node->muts_decl.name : node->var_decl.name;
            ASTNode* value = node->type == NODE_MUTS ? node->muts_decl.value : node->var_decl.value;
            if (!vm_compile_expr(chunk, value) || !vm_emit_name(chunk, VM_OP_STORE_GLOBAL, name, (uint32_t)node->line)) return 0;
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            return 1;
        }
        case NODE_EXPR_STMT:
            if (!vm_compile_expr(chunk, node->expr_stmt.expr)) return 0;
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            return 1;
        case NODE_RETURN:
            if (!vm_compile_expr(chunk, node->return_stmt.value)) return 0;
            vm_emit(chunk, VM_OP_RETURN, 1, 0, (uint32_t)node->line);
            return 1;
        case NODE_IF: {
            if (!vm_compile_expr(chunk, node->if_stmt.condition)) return 0;
            int otherwise = vm_emit(chunk, VM_OP_JUMP_IF_FALSE, 0, 0, (uint32_t)node->line);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            if (!vm_compile_stmt_list(chunk, node->if_stmt.then_branch)) return 0;
            int done = vm_emit(chunk, VM_OP_JUMP, 0, 0, (uint32_t)node->line);
            vm_patch_jump(chunk, otherwise, chunk->count - otherwise);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            if (!vm_compile_stmt_list(chunk, node->if_stmt.else_branch)) return 0;
            vm_patch_jump(chunk, done, chunk->count - done);
            return 1;
        }
        case NODE_WHILE: {
            int start = chunk->count;
            if (!vm_compile_expr(chunk, node->while_stmt.condition)) return 0;
            int done = vm_emit(chunk, VM_OP_JUMP_IF_FALSE, 0, 0, (uint32_t)node->line);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            if (!vm_compile_stmt_list(chunk, node->while_stmt.body)) return 0;
            int back = vm_emit(chunk, VM_OP_LOOP, 0, 0, (uint32_t)node->line);
            vm_patch_jump(chunk, back, start - back);
            vm_patch_jump(chunk, done, chunk->count - done);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            return 1;
        }
        case NODE_FOR_RANGE: {
            if (!vm_compile_expr(chunk, node->for_range.start) ||
                !vm_emit_name(chunk, VM_OP_STORE_GLOBAL, node->for_range.var, (uint32_t)node->line)) return 0;
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            int start = chunk->count;
            if (!vm_emit_name(chunk, VM_OP_LOAD_GLOBAL, node->for_range.var, (uint32_t)node->line) ||
                !vm_compile_expr(chunk, node->for_range.end)) return 0;
            vm_emit(chunk, node->for_range.inclusive ? VM_OP_LESS_EQ : VM_OP_LESS, 0, 0, (uint32_t)node->line);
            int done = vm_emit(chunk, VM_OP_JUMP_IF_FALSE, 0, 0, (uint32_t)node->line);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            if (!vm_compile_stmt_list(chunk, node->for_range.body)) return 0;
            if (!vm_emit_name(chunk, VM_OP_LOAD_GLOBAL, node->for_range.var, (uint32_t)node->line)) return 0;
            vm_emit(chunk, VM_OP_PUSH_INT, 1, 0, (uint32_t)node->line);
            vm_emit(chunk, VM_OP_ADD, 0, 0, (uint32_t)node->line);
            if (!vm_emit_name(chunk, VM_OP_STORE_GLOBAL, node->for_range.var, (uint32_t)node->line)) return 0;
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            int back = vm_emit(chunk, VM_OP_LOOP, 0, 0, (uint32_t)node->line);
            vm_patch_jump(chunk, back, start - back);
            vm_patch_jump(chunk, done, chunk->count - done);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            return 1;
        }
        case NODE_FOR: {
            if (node->for_loop.init && !vm_compile_stmt(chunk, node->for_loop.init)) return 0;
            int start = chunk->count;
            if (node->for_loop.condition) {
                if (!vm_compile_expr(chunk, node->for_loop.condition)) return 0;
            } else vm_emit(chunk, VM_OP_PUSH_TRUE, 0, 0, (uint32_t)node->line);
            int done = vm_emit(chunk, VM_OP_JUMP_IF_FALSE, 0, 0, (uint32_t)node->line);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            if (!vm_compile_stmt_list(chunk, node->for_loop.body)) return 0;
            if (node->for_loop.increment && !vm_compile_stmt(chunk, node->for_loop.increment)) return 0;
            int back = vm_emit(chunk, VM_OP_LOOP, 0, 0, (uint32_t)node->line);
            vm_patch_jump(chunk, back, start - back);
            vm_patch_jump(chunk, done, chunk->count - done);
            vm_emit(chunk, VM_OP_POP, 0, 0, (uint32_t)node->line);
            return 1;
        }
        case NODE_FUNCTION: case NODE_PUBLIC_FUNCTION: case NODE_ASYNC_FUNCTION:
        case NODE_EXPORT: case NODE_MODULE:
            return 1;
        case NODE_IMPORT:
            vm_compile_failed_node=node->type;
            return 0;
        case NODE_PROGRAM:
            return vm_compile_stmt_list(chunk, node->program.statements);
        default:
            vm_compile_failed_node=node->type;
            return 0;
    }
}

static int vm_compile_stmt_list(VMChunk* chunk, ASTNodeList* list) {
    for (int i=0; list && i<list->count; i++)
        if (!vm_compile_stmt(chunk, list->nodes[i])) return 0;
    return 1;
}

VMChunk* vm_compile(struct ASTNode* program) {
    VMChunk* chunk = vm_chunk_new("<main>");
    vm_compile_failed = 0;
    vm_compile_failed_node = (NodeType)-1;
    ASTNode* entry = NULL;
    if (program && program->type == NODE_PROGRAM && program->program.statements) {
        for (int i=0; i<program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if ((stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION || stmt->type == NODE_ASYNC_FUNCTION) &&
                stmt->function.name && strcmp(stmt->function.name, "main") == 0) { entry = stmt; break; }
        }
        for (int i=0; i<program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt == entry) continue;
            if (stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION || stmt->type == NODE_ASYNC_FUNCTION) continue;
            if (!vm_compile_stmt(chunk, stmt)) { vm_compile_failed=1; break; }
        }
        if (!vm_compile_failed && entry && !vm_compile_stmt_list(chunk, entry->function.body)) vm_compile_failed=1;
    } else if (!vm_compile_stmt(chunk, program)) vm_compile_failed=1;
    if (vm_compile_failed) { vm_chunk_free(chunk); return NULL; }
    vm_emit(chunk, VM_OP_HALT, 0, 0, 0);
    return chunk;
}

VMResult vm_execute(struct ASTNode* program, void* interp_env) {
    VMChunk* chunk = vm_compile(program);
    if (!chunk) {
        fprintf(stderr, "[VM] unsupported AST node %d\n", (int)vm_compile_failed_node);
        return VM_COMPILE_ERROR;
    }
    Environment* env = interp_env ? (Environment*)interp_env : create_env(NULL);
    VM vm;
    vm_init(&vm);
    vm.interp_env = env;
    VMResult res = vm_run(&vm, chunk);
    if (res != VM_OK && vm.error_msg[0]) fprintf(stderr, "[VM] %s\n", vm.error_msg);
    vm_free(&vm);
    vm_chunk_free(chunk);
    if (!interp_env) free(env);
    return res;
}
