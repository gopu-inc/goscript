#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <ffi.h>
#include "ast.h"

/* Types de valeurs */
typedef enum {
    VAL_INT,
    VAL_FLOAT,
    VAL_STRING,
    VAL_BOOL,
    VAL_NIL,
    VAL_FUNCTION,
    VAL_CFUNCTION,
    VAL_STRUCT,
    VAL_ARRAY
} ValueType;

/* Structure pour les valeurs */
typedef struct Value {
    ValueType type;
    union {
        int int_val;
        double float_val;
        char* string_val;
        int bool_val;
        struct {
            ASTNode* node;
            struct Environment* closure;
        } func_val;
        struct {
            void* func_ptr;
            ffi_cif cif;
            ffi_type** arg_types;
            int arg_count;
            ffi_type* ret_type;
            char* name;
        } cfunc_val;
        struct {
            char* name;
            struct Value* fields;
            int field_count;
        } struct_val;
        struct {
            struct Value* elements;
            int count;
            int capacity;
        } array_val;
    };
} Value;

/* Environnement */
typedef struct Environment {
    struct Environment* parent;
    struct {
        char* name;
        Value value;
    }* vars;
    int var_count;
    int var_capacity;
} Environment;

/* Prototypes */
Environment* create_env(Environment* parent);
void env_set(Environment* env, char* name, Value value);
Value* env_get(Environment* env, char* name);
Value evaluate_expr(ASTNode* node, Environment* env);
int evaluate_statement(ASTNode* node, Environment* env);
void print_value(Value val, int newline);
void register_c_function(Environment* env, char* name, void* func_ptr, 
                         ffi_type* ret_type, int arg_count, ...);

/* ==================== Création d'environnement ==================== */

Environment* create_env(Environment* parent) {
    Environment* env = malloc(sizeof(Environment));
    env->parent = parent;
    env->vars = NULL;
    env->var_count = 0;
    env->var_capacity = 0;
    return env;
}

void env_set(Environment* env, char* name, Value value) {
    for (int i = 0; i < env->var_count; i++) {
        if (strcmp(env->vars[i].name, name) == 0) {
            env->vars[i].value = value;
            return;
        }
    }
    
    if (env->var_count >= env->var_capacity) {
        env->var_capacity = env->var_capacity == 0 ? 10 : env->var_capacity * 2;
        env->vars = realloc(env->vars, env->var_capacity * sizeof(*env->vars));
    }
    
    env->vars[env->var_count].name = strdup(name);
    env->vars[env->var_count].value = value;
    env->var_count++;
}

Value* env_get(Environment* env, char* name) {
    for (int i = 0; i < env->var_count; i++) {
        if (strcmp(env->vars[i].name, name) == 0) {
            return &env->vars[i].value;
        }
    }
    if (env->parent) {
        return env_get(env->parent, name);
    }
    return NULL;
}

/* ==================== FFI Helpers ==================== */

ffi_type* get_ffi_type(ValueType type) {
    switch (type) {
        case VAL_INT: return &ffi_type_sint32;
        case VAL_FLOAT: return &ffi_type_double;
        case VAL_STRING: return &ffi_type_pointer;
        case VAL_BOOL: return &ffi_type_sint32;
        default: return &ffi_type_void;
    }
}

void* value_to_ffi_arg(Value val, ffi_type* type) {
    void* ptr = malloc(type->size);
    if (type == &ffi_type_sint32) {
        *(int*)ptr = val.int_val;
    } else if (type == &ffi_type_double) {
        *(double*)ptr = val.float_val;
    } else if (type == &ffi_type_pointer) {
        *(char**)ptr = val.string_val;
    }
    return ptr;
}

Value ffi_to_value(void* result, ffi_type* type) {
    Value val = {0};
    if (type == &ffi_type_sint32) {
        val.type = VAL_INT;
        val.int_val = *(int*)result;
    } else if (type == &ffi_type_double) {
        val.type = VAL_FLOAT;
        val.float_val = *(double*)result;
    } else if (type == &ffi_type_pointer) {
        val.type = VAL_STRING;
        val.string_val = strdup(*(char**)result);
    } else if (type == &ffi_type_void) {
        val.type = VAL_NIL;
    }
    return val;
}

/* ==================== Fonctions C natives ==================== */

// Fonctions mathématiques C
int c_add(int a, int b) { return a + b; }
int c_sub(int a, int b) { return a - b; }
int c_mul(int a, int b) { return a * b; }
int c_div(int a, int b) { return b != 0 ? a / b : 0; }
double c_pow(double x, double y) { 
    double result = 1.0;
    for (int i = 0; i < (int)y; i++) result *= x;
    return result;
}
int c_abs(int x) { return x < 0 ? -x : x; }
int c_max(int a, int b) { return a > b ? a : b; }
int c_min(int a, int b) { return a < b ? a : b; }

// Fonctions I/O
void c_print(char* s) { printf("%s", s); fflush(stdout); }
void c_println(char* s) { printf("%s\n", s); fflush(stdout); }
void c_print_int(int n) { printf("%d", n); fflush(stdout); }
void c_print_float(double f) { printf("%f", f); fflush(stdout); }

// Fonctions mémoire
void* c_malloc(int size) { return malloc(size); }
void c_free(void* ptr) { free(ptr); }

// Fonctions chaînes
char* c_strcat(char* a, char* b) {
    char* result = malloc(strlen(a) + strlen(b) + 1);
    strcpy(result, a);
    strcat(result, b);
    return result;
}
int c_strlen(char* s) { return strlen(s); }
char* c_strdup(char* s) { return strdup(s); }

// Fonctions système
int c_system(char* cmd) { return system(cmd); }
void c_exit(int code) { exit(code); }

/* ==================== Enregistrement des fonctions C ==================== */

void register_c_function(Environment* env, char* name, void* func_ptr,
                         ffi_type* ret_type, int arg_count, ...) {
    Value val;
    val.type = VAL_CFUNCTION;
    val.cfunc_val.func_ptr = func_ptr;
    val.cfunc_val.arg_count = arg_count;
    val.cfunc_val.ret_type = ret_type;
    val.cfunc_val.name = strdup(name);
    
    // Allouer les types d'arguments
    val.cfunc_val.arg_types = malloc(arg_count * sizeof(ffi_type*));
    va_list args;
    va_start(args, arg_count);
    for (int i = 0; i < arg_count; i++) {
        val.cfunc_val.arg_types[i] = va_arg(args, ffi_type*);
    }
    va_end(args);
    
    // Préparer ffi_cif
    ffi_prep_cif(&val.cfunc_val.cif, FFI_DEFAULT_ABI, arg_count,
                 ret_type, val.cfunc_val.arg_types);
    
    env_set(env, name, val);
}

void register_all_c_functions(Environment* env) {
    // Math
    register_c_function(env, "c_add", c_add, &ffi_type_sint32, 2,
                        &ffi_type_sint32, &ffi_type_sint32);
    register_c_function(env, "c_sub", c_sub, &ffi_type_sint32, 2,
                        &ffi_type_sint32, &ffi_type_sint32);
    register_c_function(env, "c_mul", c_mul, &ffi_type_sint32, 2,
                        &ffi_type_sint32, &ffi_type_sint32);
    register_c_function(env, "c_div", c_div, &ffi_type_sint32, 2,
                        &ffi_type_sint32, &ffi_type_sint32);
    register_c_function(env, "c_pow", c_pow, &ffi_type_double, 2,
                        &ffi_type_double, &ffi_type_double);
    register_c_function(env, "c_abs", c_abs, &ffi_type_sint32, 1,
                        &ffi_type_sint32);
    register_c_function(env, "c_max", c_max, &ffi_type_sint32, 2,
                        &ffi_type_sint32, &ffi_type_sint32);
    register_c_function(env, "c_min", c_min, &ffi_type_sint32, 2,
                        &ffi_type_sint32, &ffi_type_sint32);
    
    // I/O
    register_c_function(env, "c_print", c_print, &ffi_type_void, 1,
                        &ffi_type_pointer);
    register_c_function(env, "c_println", c_println, &ffi_type_void, 1,
                        &ffi_type_pointer);
    register_c_function(env, "c_print_int", c_print_int, &ffi_type_void, 1,
                        &ffi_type_sint32);
    register_c_function(env, "c_print_float", c_print_float, &ffi_type_void, 1,
                        &ffi_type_double);
    
    // Strings
    register_c_function(env, "c_strcat", c_strcat, &ffi_type_pointer, 2,
                        &ffi_type_pointer, &ffi_type_pointer);
    register_c_function(env, "c_strlen", c_strlen, &ffi_type_sint32, 1,
                        &ffi_type_pointer);
    register_c_function(env, "c_strdup", c_strdup, &ffi_type_pointer, 1,
                        &ffi_type_pointer);
    
    // System
    register_c_function(env, "c_system", c_system, &ffi_type_sint32, 1,
                        &ffi_type_pointer);
    register_c_function(env, "c_exit", c_exit, &ffi_type_void, 1,
                        &ffi_type_sint32);
    
    // Memory
    register_c_function(env, "c_malloc", c_malloc, &ffi_type_pointer, 1,
                        &ffi_type_sint32);
    register_c_function(env, "c_free", c_free, &ffi_type_void, 1,
                        &ffi_type_pointer);
}

/* ==================== Affichage des valeurs ==================== */

void print_value(Value val, int newline) {
    switch (val.type) {
        case VAL_INT:
            printf("%d", val.int_val);
            break;
        case VAL_FLOAT:
            printf("%f", val.float_val);
            break;
        case VAL_STRING:
            printf("%s", val.string_val);
            break;
        case VAL_BOOL:
            printf("%s", val.bool_val ? "true" : "false");
            break;
        case VAL_NIL:
            printf("nil");
            break;
        case VAL_CFUNCTION:
            printf("<C function: %s>", val.cfunc_val.name);
            break;
        default:
            printf("<value>");
            break;
    }
    if (newline) printf("\n");
}

/* ==================== Évaluation des expressions ==================== */

Value evaluate_expr(ASTNode* node, Environment* env) {
    Value result = {0};
    
    switch (node->type) {
        case NODE_NUMBER:
            result.type = VAL_INT;
            result.int_val = node->number.value;
            break;
            
        case NODE_FLOAT:
            result.type = VAL_FLOAT;
            result.float_val = node->float_val.value;
            break;
            
        case NODE_STRING:
            result.type = VAL_STRING;
            result.string_val = strdup(node->string_val.value);
            break;
            
        case NODE_BOOL:
            result.type = VAL_BOOL;
            result.bool_val = node->bool_val.value;
            break;
            
        case NODE_IDENTIFIER: {
            Value* val = env_get(env, node->identifier.name);
            if (val) {
                result = *val;
            } else {
                fprintf(stderr, "Undefined variable: %s\n", node->identifier.name);
                exit(1);
            }
            break;
        }
        
        case NODE_BINARY_OP: {
            // Assignation
            if (node->binary.op == OP_ASSIGN ||
                node->binary.op == OP_ADD_ASSIGN ||
                node->binary.op == OP_SUB_ASSIGN ||
                node->binary.op == OP_MUL_ASSIGN ||
                node->binary.op == OP_DIV_ASSIGN ||
                node->binary.op == OP_MOD_ASSIGN) {
                
                if (node->binary.left->type == NODE_IDENTIFIER) {
                    char* var_name = node->binary.left->identifier.name;
                    Value* current = env_get(env, var_name);
                    Value right_val = evaluate_expr(node->binary.right, env);
                    Value new_val = {0};
                    
                    if (!current && node->binary.op == OP_ASSIGN) {
                        new_val = right_val;
                    } else if (current) {
                        switch (node->binary.op) {
                            case OP_ASSIGN:
                                new_val = right_val;
                                break;
                            case OP_ADD_ASSIGN:
                                if (current->type == VAL_INT && right_val.type == VAL_INT) {
                                    new_val.type = VAL_INT;
                                    new_val.int_val = current->int_val + right_val.int_val;
                                }
                                break;
                            case OP_SUB_ASSIGN:
                                if (current->type == VAL_INT && right_val.type == VAL_INT) {
                                    new_val.type = VAL_INT;
                                    new_val.int_val = current->int_val - right_val.int_val;
                                }
                                break;
                            case OP_MUL_ASSIGN:
                                if (current->type == VAL_INT && right_val.type == VAL_INT) {
                                    new_val.type = VAL_INT;
                                    new_val.int_val = current->int_val * right_val.int_val;
                                }
                                break;
                            case OP_DIV_ASSIGN:
                                if (current->type == VAL_INT && right_val.type == VAL_INT && right_val.int_val != 0) {
                                    new_val.type = VAL_INT;
                                    new_val.int_val = current->int_val / right_val.int_val;
                                }
                                break;
                            case OP_MOD_ASSIGN:
                                if (current->type == VAL_INT && right_val.type == VAL_INT && right_val.int_val != 0) {
                                    new_val.type = VAL_INT;
                                    new_val.int_val = current->int_val % right_val.int_val;
                                }
                                break;
                        }
                    }
                    env_set(env, var_name, new_val);
                    result = new_val;
                }
                break;
            }
            
            // Opérations binaires normales
            Value left = evaluate_expr(node->binary.left, env);
            Value right = evaluate_expr(node->binary.right, env);
            
            switch (node->binary.op) {
                case OP_ADD:
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.type = VAL_INT;
                        result.int_val = left.int_val + right.int_val;
                    } else if (left.type == VAL_FLOAT && right.type == VAL_FLOAT) {
                        result.type = VAL_FLOAT;
                        result.float_val = left.float_val + right.float_val;
                    } else if (left.type == VAL_STRING || right.type == VAL_STRING) {
                        char* left_str = (left.type == VAL_STRING) ? left.string_val : "";
                        char* right_str = (right.type == VAL_STRING) ? right.string_val : "";
                        char* num_buf = NULL;
                        
                        if (left.type == VAL_INT) {
                            num_buf = malloc(32);
                            sprintf(num_buf, "%d", left.int_val);
                            left_str = num_buf;
                        }
                        if (right.type == VAL_INT) {
                            num_buf = malloc(32);
                            sprintf(num_buf, "%d", right.int_val);
                            right_str = num_buf;
                        }
                        
                        result.type = VAL_STRING;
                        result.string_val = malloc(strlen(left_str) + strlen(right_str) + 1);
                        strcpy(result.string_val, left_str);
                        strcat(result.string_val, right_str);
                        if (num_buf) free(num_buf);
                    }
                    break;
                case OP_SUB:
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.type = VAL_INT;
                        result.int_val = left.int_val - right.int_val;
                    }
                    break;
                case OP_MUL:
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.type = VAL_INT;
                        result.int_val = left.int_val * right.int_val;
                    }
                    break;
                case OP_DIV:
                    if (left.type == VAL_INT && right.type == VAL_INT && right.int_val != 0) {
                        result.type = VAL_INT;
                        result.int_val = left.int_val / right.int_val;
                    }
                    break;
                case OP_MOD:
                    if (left.type == VAL_INT && right.type == VAL_INT && right.int_val != 0) {
                        result.type = VAL_INT;
                        result.int_val = left.int_val % right.int_val;
                    }
                    break;
                case OP_LT:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.bool_val = left.int_val < right.int_val;
                    }
                    break;
                case OP_GT:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.bool_val = left.int_val > right.int_val;
                    }
                    break;
                case OP_LTE:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.bool_val = left.int_val <= right.int_val;
                    }
                    break;
                case OP_GTE:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.bool_val = left.int_val >= right.int_val;
                    }
                    break;
                case OP_EQ:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.bool_val = left.int_val == right.int_val;
                    } else if (left.type == VAL_STRING && right.type == VAL_STRING) {
                        result.bool_val = strcmp(left.string_val, right.string_val) == 0;
                    } else if (left.type == VAL_BOOL && right.type == VAL_BOOL) {
                        result.bool_val = left.bool_val == right.bool_val;
                    }
                    break;
                case OP_NEQ:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_INT && right.type == VAL_INT) {
                        result.bool_val = left.int_val != right.int_val;
                    }
                    break;
                case OP_AND:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_BOOL && right.type == VAL_BOOL) {
                        result.bool_val = left.bool_val && right.bool_val;
                    }
                    break;
                case OP_OR:
                    result.type = VAL_BOOL;
                    if (left.type == VAL_BOOL && right.type == VAL_BOOL) {
                        result.bool_val = left.bool_val || right.bool_val;
                    }
                    break;
            }
            break;
        }
        
        case NODE_UNARY_OP: {
            Value operand = evaluate_expr(node->unary.operand, env);
            switch (node->unary.op) {
                case OP_NOT:
                    result.type = VAL_BOOL;
                    result.bool_val = !operand.bool_val;
                    break;
                case OP_NEG:
                    if (operand.type == VAL_INT) {
                        result.type = VAL_INT;
                        result.int_val = -operand.int_val;
                    }
                    break;
            }
            break;
        }
        
        case NODE_CALL:
        case NODE_METHOD_CALL: {
            ASTNode* callee = node->type == NODE_CALL ? node->call.callee : node->method_call.object;
            char* func_name = callee->identifier.name;
            Value* func_val = env_get(env, func_name);
            
            if (func_val && func_val->type == VAL_CFUNCTION) {
                // Appel de fonction C via FFI
                Value* args = NULL;
                int arg_count = 0;
                
                if (node->type == NODE_CALL && node->call.args) {
                    arg_count = node->call.args->count;
                    args = malloc(arg_count * sizeof(Value));
                    for (int i = 0; i < arg_count; i++) {
                        args[i] = evaluate_expr(node->call.args->nodes[i], env);
                    }
                }
                
                // Préparer les arguments pour FFI
                void** ffi_args = malloc(arg_count * sizeof(void*));
                for (int i = 0; i < arg_count; i++) {
                    ffi_args[i] = value_to_ffi_arg(args[i], func_val->cfunc_val.arg_types[i]);
                }
                
                // Appeler la fonction C
                void* ret_val = malloc(func_val->cfunc_val.ret_type->size);
                ffi_call(&func_val->cfunc_val.cif, FFI_FN(func_val->cfunc_val.func_ptr),
                        ret_val, ffi_args);
                
                // Convertir le résultat
                result = ffi_to_value(ret_val, func_val->cfunc_val.ret_type);
                
                // Nettoyer
                for (int i = 0; i < arg_count; i++) free(ffi_args[i]);
                free(ffi_args);
                free(ret_val);
                if (args) free(args);
                
            } else if (func_val && func_val->type == VAL_FUNCTION) {
                // Appel de fonction Goscript
                ASTNode* func_node = func_val->func_val.node;
                Environment* func_env = create_env(func_val->func_val.closure);
                
                if (node->type == NODE_CALL && node->call.args) {
                    for (int i = 0; i < node->call.args->count && i < func_node->function.params->count; i++) {
                        Value arg_val = evaluate_expr(node->call.args->nodes[i], env);
                        ASTNode* param = func_node->function.params->nodes[i];
                        env_set(func_env, param->identifier.name, arg_val);
                    }
                }
                
                for (int i = 0; i < func_node->function.body->count; i++) {
                    int ret = evaluate_statement(func_node->function.body->nodes[i], func_env);
                    if (ret) break;
                }
                
                free(func_env);
                result.type = VAL_NIL;
            }
            break;
        }
        
        case NODE_MEMBER_ACCESS: {
            Value obj = evaluate_expr(node->member.object, env);
            if (obj.type == VAL_STRUCT) {
                for (int i = 0; i < obj.struct_val.field_count; i++) {
                    if (strcmp(obj.struct_val.fields[i].string_val, node->member.member) == 0) {
                        result = obj.struct_val.fields[i];
                        break;
                    }
                }
            }
            break;
        }
        
        default:
            result.type = VAL_NIL;
            break;
    }
    
    return result;
}

/* ==================== Évaluation des statements ==================== */

int evaluate_statement(ASTNode* node, Environment* env) {
    switch (node->type) {
        case NODE_LET: {
            Value val = evaluate_expr(node->var_decl.value, env);
            env_set(env, node->var_decl.name, val);
            return 0;
        }
        
        case NODE_RETURN: {
            if (node->return_stmt.value) {
                Value val = evaluate_expr(node->return_stmt.value, env);
                print_value(val, 1);
            }
            return 1;
        }
        
        case NODE_IF: {
            Value cond = evaluate_expr(node->if_stmt.condition, env);
            if (cond.type == VAL_BOOL && cond.bool_val) {
                for (int i = 0; i < node->if_stmt.then_branch->count; i++) {
                    int ret = evaluate_statement(node->if_stmt.then_branch->nodes[i], env);
                    if (ret) return 1;
                }
            } else if (node->if_stmt.else_branch) {
                for (int i = 0; i < node->if_stmt.else_branch->count; i++) {
                    int ret = evaluate_statement(node->if_stmt.else_branch->nodes[i], env);
                    if (ret) return 1;
                }
            }
            return 0;
        }
        
        case NODE_WHILE: {
            while (1) {
                Value cond = evaluate_expr(node->while_stmt.condition, env);
                if (cond.type != VAL_BOOL || !cond.bool_val) break;
                for (int i = 0; i < node->while_stmt.body->count; i++) {
                    int ret = evaluate_statement(node->while_stmt.body->nodes[i], env);
                    if (ret) return 1;
                }
            }
            return 0;
        }
        
        case NODE_LOOP: {
            while (1) {
                for (int i = 0; i < node->loop_stmt.body->count; i++) {
                    int ret = evaluate_statement(node->loop_stmt.body->nodes[i], env);
                    if (ret == 1) return 1;
                    if (ret == 2) break;
                }
            }
            return 0;
        }
        
        case NODE_BREAK:
            return 2;
            
        case NODE_EXPR_STMT: {
            evaluate_expr(node->expr_stmt.expr, env);
            return 0;
        }
        
        default:
            return 0;
    }
}

/* ==================== Interprétation du programme ==================== */

void interpret_program(ASTNode* program) {
    Environment* global = create_env(NULL);
    
    // Enregistrer les fonctions C
    register_all_c_functions(global);
    
    // Enregistrer les fonctions Goscript
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION) {
            Value func_val;
            func_val.type = VAL_FUNCTION;
            func_val.func_val.node = stmt;
            func_val.func_val.closure = global;
            env_set(global, stmt->function.name, func_val);
        }
    }
    
    // Chercher et exécuter main
    ASTNode* main_func = NULL;
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION && strcmp(stmt->function.name, "main") == 0) {
            main_func = stmt;
            break;
        }
    }
    
    if (!main_func) {
        // Exécuter les expressions directes
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt->type == NODE_EXPR_STMT || stmt->type == NODE_LET) {
                evaluate_statement(stmt, global);
            }
        }
    } else {
        for (int i = 0; i < main_func->function.body->count; i++) {
            int ret = evaluate_statement(main_func->function.body->nodes[i], global);
            if (ret) break;
        }
    }
    
    free(global);
}
