#ifndef GOSCRIPT_BYTECODE_H
#define GOSCRIPT_BYTECODE_H

#include "../ast/ast.h"
#include "../interpreter/interpreter.h"

typedef enum {
    BC_NOP = 0,
    BC_PUSH_INT,
    BC_PUSH_FLOAT,
    BC_PUSH_STRING,
    BC_PUSH_BOOL,
    BC_PUSH_NIL,
    BC_LOAD_NAME,
    BC_STORE_NAME,
    BC_POP,
    BC_DUP,
    BC_ADD,
    BC_SUB,
    BC_MUL,
    BC_DIV,
    BC_MOD,
    BC_EQ,
    BC_NEQ,
    BC_LT,
    BC_LTE,
    BC_GT,
    BC_GTE,
    BC_AND,
    BC_OR,
    BC_NOT,
    BC_NEG,
    BC_ASSIGN,
    BC_ADD_ASSIGN,
    BC_SUB_ASSIGN,
    BC_MUL_ASSIGN,
    BC_DIV_ASSIGN,
    BC_MOD_ASSIGN,
    BC_BUILD_ARRAY,
    BC_BUILD_DICT,
    BC_CALL,
    BC_IF,
    BC_WHILE,
    BC_LOOP,
    BC_RETURN,
    BC_BREAK,
    BC_CONTINUE,
    BC_EVAL_EXPR,
    BC_EVAL_STMT,
    BC_HALT
} BCOpCode;

typedef struct BCChunk BCChunk;

typedef struct BCInstruction {
    BCOpCode op;
    int a;
    int b;
    double num;
    char* str;
    ASTNode* node;
    BCChunk* chunk_a;
    BCChunk* chunk_b;
    BCChunk* chunk_c;
} BCInstruction;

struct BCChunk {
    BCInstruction* code;
    int count;
    int capacity;
    char* name;
};

BCChunk* bc_chunk_new(const char* name);
void bc_chunk_free(BCChunk* chunk);
int bc_chunk_emit(BCChunk* chunk, BCInstruction ins);
void bc_chunk_dump(BCChunk* chunk);
void bc_chunk_dump_to_file(FILE* out, BCChunk* chunk);
char* bc_program_dump(ASTNode* program);

void interpret_program_bytecode(ASTNode* program, int dump_bytecode);

#endif
