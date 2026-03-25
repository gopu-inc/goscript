#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <ffi.h>
#include "../ast/ast.h"
#include <setjmp.h>

typedef struct NnlContext NnlContext;

typedef struct Value {
    int type;
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
            struct {
                struct Value* key;
                struct Value* value;
            }* entries;
            int count;
            int capacity;
        } dict_val;
struct {
    ASTNode* node;
    struct Environment* closure;
} lambda_val;

struct {
    ASTNodeList* elements;
    int count;
} array_val;
        struct {
            void* func_ptr;
            ffi_cif cif;
            ffi_type** arg_types;
            ffi_type* ret_type;
            int arg_count;
            char* name;
        } cfunc_val;
        struct {
            char* struct_name;
            struct {
                char* name;
                struct Value* value;
            }* fields;
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
// Structure pour un module chargé
#define VALUE_TYPE_DICT 10

typedef struct LoadedModule {
    char* module_path;      // Chemin absolu
    char* module_name;      // Nom du module
    char* alias;            // Alias d'import (optionnel)
    Environment* env;       // Environnement propre au module
    int status;             // 0: loading, 1: loaded, -1: error
    int ref_count;          // Nombre de références
    struct {
        char** allowed_names;  // Noms autorisés (only)
        int allowed_count;
        int timeout_ms;        // Timeout en ms
        int sandbox;           // 1 = sandboxé
        int allow_ffi;         // 1 = FFI autorisé
    } constraints;
} LoadedModule;
// Table globale des modules
typedef struct ModuleRegistry {
    LoadedModule** modules;
    int count;
    int capacity;
} ModuleRegistry;

// Input function
Value call_input(Value* args, int arg_count);
ModuleRegistry* init_module_registry(void);
void register_module(ModuleRegistry* reg, LoadedModule* mod);
LoadedModule* find_module(ModuleRegistry* reg, char* path);
void free_module_registry(ModuleRegistry* reg);
char* resolve_module_path(char* current_file, char* import_path);
LoadedModule* load_module(ModuleRegistry* reg, Environment* parent_env,
                          char* current_file, char* import_path, 
                          char* alias, ASTNode* constraints);
ASTNode* create_constraints_node(char* constraint_type, ASTNodeList* list);
ASTNode* create_timeout_constraint(int timeout_ms);
ASTNode* merge_constraints(ASTNode* a, ASTNode* b);
void process_constraints(LoadedModule* module, ASTNode* constraints);
int is_name_allowed(LoadedModule* module, char* name);
int is_ffi_allowed(LoadedModule* module);
// Fonctions de gestion des modules
ModuleRegistry* init_module_registry();
void register_native_c_functions(Environment* env);
void register_module(ModuleRegistry* reg, LoadedModule* mod);
LoadedModule* find_module(ModuleRegistry* reg, char* path);
void free_module_registry(ModuleRegistry* reg);
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
int evaluate_statement(ASTNode* node, Environment* env, char* current_file);
void interpret_program(ASTNode* program);

#endif
