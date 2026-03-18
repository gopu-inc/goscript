#ifndef GOSCRIPT_VM_H
#define GOSCRIPT_VM_H

#include "ast.h"

#define STACK_MAX 256
#define LOCALS_MAX 64

typedef enum {
    TYPE_NUMBER,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_FUNCTION
} ValueType;

typedef struct {
    char* name;
    bool is_initialized;
    ValueType type;
    union {
        double number;
        char* string;
        bool boolean;
    } value;
} Value;

typedef struct Frame {
    Value* locals;
    int local_count;
    struct Frame* parent;
} Frame;

typedef struct Function {
    char* name;
    Node* params;
    Node* body;
    struct Function* next;
} Function;

typedef struct {
    Value* globals;
    int global_count;
    int global_capacity;
    
    double* stack;
    int stack_top;
    int stack_capacity;
    
    Frame* current_frame;
    
    bool had_error;
    bool return_flag;
    double return_value;
    
    Function* functions;
    int function_count;
} VM;

// Core functions
void init_vm(VM* vm);
void free_vm(VM* vm);
bool execute(VM* vm, Node* ast);

// Stack operations
void push(VM* vm, double value);
double pop(VM* vm);
double peek(VM* vm, int distance);

#endif
