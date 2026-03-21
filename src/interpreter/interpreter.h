#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <ffi.h>
#include "../ast/ast.h"

typedef struct Value {
    int type;  // 0=int, 1=float, 2=string, 3=bool, 4=function, 5=cfunction, 6=struct
    union {
        int int_val;
        double float_val;
        char* string_val;
        int bool_val;
        struct {
            struct ASTNode* node;
            struct Environment* closure;
        } func_val;
        struct {
            void* func_ptr;
            ffi_cif cif;
            ffi_type** arg_types;
            ffi_type* ret_type;
            int arg_count;
            char* name;
        } cfunc_val;
        struct {
            struct Value** fields;  // Tableau de pointeurs vers Value
            int field_count;
        } struct_val;
    };
} Value;
typedef struct Environment {
    struct Environment* parent;
    struct {
        char* name;
        Value value;
    }* vars;
    int var_count;
    int var_capacity;
} Environment;

// Fonctions d'environnement
Environment* create_env(Environment* parent);
void env_set(Environment* env, char* name, Value value);
Value* env_get(Environment* env, char* name);

// Fonctions FFI
ffi_type* get_ffi_type(char* type_name);
void register_c_function(Environment* env, char* name, void* func_ptr, char* ret_type, int arg_count, ...);
void* load_c_library(char* path);
void call_c_function(Value* cfunc, Value* args, int arg_count, Value* result);

// Fonctions d'affichage
void print_value(Value val, int newline);

// Fonctions d'évaluation
void init_interpreter(void); 
Value evaluate_expr(ASTNode* node, Environment* env);
int evaluate_statement(ASTNode* node, Environment* env);
void interpret_program(ASTNode* program);

#endif
