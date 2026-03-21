#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            char* name;
            struct Value** fields;
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

// Forward declarations
Environment* create_env(Environment* parent);
void env_set(Environment* env, char* name, Value value);
Value* env_get(Environment* env, char* name);
Value evaluate_expr(ASTNode* node, Environment* env);
int evaluate_statement(ASTNode* node, Environment* env);
void print_value(Value val, int newline);
void register_c_function(Environment* env, char* name, void* func_ptr, char* ret_type, int arg_count, ...);
void* load_c_library(char* path);
void call_c_function(Value* cfunc, Value* args, int arg_count, Value* result);

// ==================== Gestion de l'environnement ====================

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

// ==================== FFI Helpers ====================

ffi_type* get_ffi_type(char* type_name) {
    if (strcmp(type_name, "int") == 0 || strcmp(type_name, "i32") == 0) {
        return &ffi_type_sint32;
    } else if (strcmp(type_name, "float") == 0 || strcmp(type_name, "f32") == 0) {
        return &ffi_type_float;
    } else if (strcmp(type_name, "double") == 0 || strcmp(type_name, "f64") == 0) {
        return &ffi_type_double;
    } else if (strcmp(type_name, "string") == 0 || strcmp(type_name, "char*") == 0) {
        return &ffi_type_pointer;
    } else if (strcmp(type_name, "void") == 0) {
        return &ffi_type_void;
    } else if (strcmp(type_name, "bool") == 0) {
        return &ffi_type_sint8;
    }
    return &ffi_type_pointer;
}

void register_c_function(Environment* env, char* name, void* func_ptr, char* ret_type, int arg_count, ...) {
    Value func_val;
    func_val.type = 5; // C function
    func_val.cfunc_val.func_ptr = func_ptr;
    func_val.cfunc_val.ret_type = get_ffi_type(ret_type);
    func_val.cfunc_val.arg_count = arg_count;
    func_val.cfunc_val.name = strdup(name);
    
    // Allouer les types d'arguments
    func_val.cfunc_val.arg_types = malloc(arg_count * sizeof(ffi_type*));
    
    va_list args;
    va_start(args, arg_count);
    for (int i = 0; i < arg_count; i++) {
        char* arg_type = va_arg(args, char*);
        func_val.cfunc_val.arg_types[i] = get_ffi_type(arg_type);
    }
    va_end(args);
    
    // Préparer l'appel FFI
    ffi_prep_cif(&func_val.cfunc_val.cif, FFI_DEFAULT_ABI, arg_count,
                 func_val.cfunc_val.ret_type, func_val.cfunc_val.arg_types);
    
    env_set(env, name, func_val);
}

void* load_c_library(char* path) {
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library %s: %s\n", path, dlerror());
        return NULL;
    }
    return handle;
}

void call_c_function(Value* cfunc, Value* args, int arg_count, Value* result) {
    if (cfunc->type != 5) {
        fprintf(stderr, "Not a C function\n");
        return;
    }
    
    void** values = malloc(arg_count * sizeof(void*));
    void* ret_val = malloc(32); // Espace pour le retour
    
    for (int i = 0; i < arg_count && i < cfunc->cfunc_val.arg_count; i++) {
        switch (args[i].type) {
            case 0: // int
                values[i] = &args[i].int_val;
                break;
            case 1: // float
                values[i] = &args[i].float_val;
                break;
            case 2: // string
                values[i] = &args[i].string_val;
                break;
            case 3: // bool
                values[i] = &args[i].bool_val;
                break;
            default:
                values[i] = NULL;
        }
    }
    
    ffi_call(&cfunc->cfunc_val.cif, FFI_FN(cfunc->cfunc_val.func_ptr), ret_val, values);
    
    // Convertir le résultat
    if (cfunc->cfunc_val.ret_type == &ffi_type_sint32) {
        result->type = 0;
        result->int_val = *(int*)ret_val;
    } else if (cfunc->cfunc_val.ret_type == &ffi_type_float) {
        result->type = 1;
        result->float_val = *(float*)ret_val;
    } else if (cfunc->cfunc_val.ret_type == &ffi_type_double) {
        result->type = 1;
        result->float_val = *(double*)ret_val;
    } else if (cfunc->cfunc_val.ret_type == &ffi_type_pointer) {
        result->type = 2;
        result->string_val = strdup(*(char**)ret_val);
    } else if (cfunc->cfunc_val.ret_type == &ffi_type_sint8) {
        result->type = 3;
        result->bool_val = *(int*)ret_val;
    } else {
        result->type = 0;
        result->int_val = 0;
    }
    
    free(values);
    free(ret_val);
}

// ==================== Affichage ====================

void print_value(Value val, int newline) {
    switch (val.type) {
        case 0: printf("%d", val.int_val); break;
        case 1: printf("%f", val.float_val); break;
        case 2: printf("%s", val.string_val); break;
        case 3: printf("%s", val.bool_val ? "true" : "false"); break;
        default: printf("unknown");
    }
    if (newline) printf("\n");
}

// ==================== Évaluation des expressions ====================

Value evaluate_expr(ASTNode* node, Environment* env) {
    Value result = {0};
    
    switch (node->type) {
        case NODE_NUMBER:
            result.type = 0;
            result.int_val = node->number.value;
            break;
            
        case NODE_FLOAT:
            result.type = 1;
            result.float_val = node->float_val.value;
            break;
            
        case NODE_STRING:
            result.type = 2;
            result.string_val = strdup(node->string_val.value);
            break;
            
        case NODE_BOOL:
            result.type = 3;
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
                            case OP_ASSIGN: new_val = right_val; break;
                            case OP_ADD_ASSIGN:
                                if (current->type == 0 && right_val.type == 0) {
                                    new_val.type = 0;
                                    new_val.int_val = current->int_val + right_val.int_val;
                                }
                                break;
                            case OP_SUB_ASSIGN:
                                if (current->type == 0 && right_val.type == 0) {
                                    new_val.type = 0;
                                    new_val.int_val = current->int_val - right_val.int_val;
                                }
                                break;
                            case OP_MUL_ASSIGN:
                                if (current->type == 0 && right_val.type == 0) {
                                    new_val.type = 0;
                                    new_val.int_val = current->int_val * right_val.int_val;
                                }
                                break;
                            case OP_DIV_ASSIGN:
                                if (current->type == 0 && right_val.type == 0 && right_val.int_val != 0) {
                                    new_val.type = 0;
                                    new_val.int_val = current->int_val / right_val.int_val;
                                }
                                break;
                            case OP_MOD_ASSIGN:
                                if (current->type == 0 && right_val.type == 0 && right_val.int_val != 0) {
                                    new_val.type = 0;
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
            
            Value left = evaluate_expr(node->binary.left, env);
            Value right = evaluate_expr(node->binary.right, env);
            
            switch (node->binary.op) {
                case OP_ADD:
                    if (left.type == 0 && right.type == 0) {
                        result.type = 0;
                        result.int_val = left.int_val + right.int_val;
                    } else if (left.type == 1 && right.type == 1) {
                        result.type = 1;
                        result.float_val = left.float_val + right.float_val;
                    } else if (left.type == 2 || right.type == 2) {
                        char* left_str = (left.type == 2) ? left.string_val : "";
                        char* right_str = (right.type == 2) ? right.string_val : "";
                        char* num_buf = NULL;
                        
                        if (left.type == 0) {
                            num_buf = malloc(32);
                            sprintf(num_buf, "%d", left.int_val);
                            left_str = num_buf;
                        }
                        if (right.type == 0) {
                            num_buf = malloc(32);
                            sprintf(num_buf, "%d", right.int_val);
                            right_str = num_buf;
                        }
                        
                        result.type = 2;
                        result.string_val = malloc(strlen(left_str) + strlen(right_str) + 1);
                        strcpy(result.string_val, left_str);
                        strcat(result.string_val, right_str);
                        if (num_buf) free(num_buf);
                    }
                    break;
                case OP_SUB:
                    if (left.type == 0 && right.type == 0) {
                        result.type = 0;
                        result.int_val = left.int_val - right.int_val;
                    }
                    break;
                case OP_MUL:
                    if (left.type == 0 && right.type == 0) {
                        result.type = 0;
                        result.int_val = left.int_val * right.int_val;
                    }
                    break;
                case OP_DIV:
                    if (left.type == 0 && right.type == 0 && right.int_val != 0) {
                        result.type = 0;
                        result.int_val = left.int_val / right.int_val;
                    }
                    break;
                case OP_MOD:
                    if (left.type == 0 && right.type == 0 && right.int_val != 0) {
                        result.type = 0;
                        result.int_val = left.int_val % right.int_val;
                    }
                    break;
                case OP_LT:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) {
                        result.bool_val = left.int_val < right.int_val;
                    }
                    break;
                case OP_GT:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) {
                        result.bool_val = left.int_val > right.int_val;
                    }
                    break;
                case OP_LTE:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) {
                        result.bool_val = left.int_val <= right.int_val;
                    }
                    break;
                case OP_GTE:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) {
                        result.bool_val = left.int_val >= right.int_val;
                    }
                    break;
                case OP_EQ:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) {
                        result.bool_val = left.int_val == right.int_val;
                    } else if (left.type == 2 && right.type == 2) {
                        result.bool_val = strcmp(left.string_val, right.string_val) == 0;
                    }
                    break;
                case OP_NEQ:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) {
                        result.bool_val = left.int_val != right.int_val;
                    }
                    break;
                case OP_AND:
                    result.type = 3;
                    if (left.type == 3 && right.type == 3) {
                        result.bool_val = left.bool_val && right.bool_val;
                    }
                    break;
                case OP_OR:
                    result.type = 3;
                    if (left.type == 3 && right.type == 3) {
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
                    result.type = 3;
                    result.bool_val = !operand.bool_val;
                    break;
                case OP_NEG:
                    if (operand.type == 0) {
                        result.type = 0;
                        result.int_val = -operand.int_val;
                    }
                    break;
            }
            break;
        }
        
        case NODE_CALL: {
            char* func_name = node->call.callee->identifier.name;
            Value* func = env_get(env, func_name);
            
            if (func && func->type == 5) {
                // Appel de fonction C
                int arg_count = node->call.args ? node->call.args->count : 0;
                Value* args = malloc(arg_count * sizeof(Value));
                for (int i = 0; i < arg_count; i++) {
                    args[i] = evaluate_expr(node->call.args->nodes[i], env);
                }
                call_c_function(func, args, arg_count, &result);
                free(args);
            } else if (strcmp(func_name, "print") == 0) {
                if (node->call.args && node->call.args->count > 0) {
                    Value arg = evaluate_expr(node->call.args->nodes[0], env);
                    print_value(arg, 0);
                }
                result.type = 0;
                result.int_val = 0;
            } else if (strcmp(func_name, "println") == 0) {
                if (node->call.args && node->call.args->count > 0) {
                    Value arg = evaluate_expr(node->call.args->nodes[0], env);
                    print_value(arg, 1);
                } else {
                    printf("\n");
                }
                result.type = 0;
                result.int_val = 0;
            } else {
                result.type = 0;
                result.int_val = 0;
            }
            break;
        }
        
        default:
            break;
    }
    
    return result;
}

// ==================== Évaluation des instructions ====================

int evaluate_statement(ASTNode* node, Environment* env) {
    switch (node->type) {
        case NODE_LET: {
            Value val = evaluate_expr(node->var_decl.value, env);
            env_set(env, node->var_decl.name, val);
            return 0;
        }
        
        case NODE_RETURN: {
            Value val = evaluate_expr(node->return_stmt.value, env);
            print_value(val, 1);
            return 1;
        }
        
        case NODE_IF: {
            Value cond = evaluate_expr(node->if_stmt.condition, env);
            if (cond.type == 3 && cond.bool_val) {
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
                if (cond.type != 3 || !cond.bool_val) break;
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
                    if (ret) return 1;
                }
            }
            return 0;
        }
        
        case NODE_FOR: {
            if (node->for_range.start) evaluate_statement(node->for_range.start, env);
            while (1) {
                if (node->for_range.end) {
                    Value cond = evaluate_expr(node->for_range.end, env);
                    if (cond.type != 3 || !cond.bool_val) break;
                }
                for (int i = 0; i < node->for_range.body->count; i++) {
                    int ret = evaluate_statement(node->for_range.body->nodes[i], env);
                    if (ret) return 1;
                }
            }
            return 0;
        }
        
        case NODE_EXPR_STMT: {
            evaluate_expr(node->expr_stmt.expr, env);
            return 0;
        }
        
        default:
            return 0;
    }
}

// ==================== Interprétation du programme ====================

void interpret_program(ASTNode* program) {
    Environment* global = create_env(NULL);
    
    // Charger la libc pour les fonctions système
    void* libc = dlopen("libc.so.6", RTLD_LAZY);
    if (libc) {
        // Fonctions standard C
        register_c_function(global, "printf", dlsym(libc, "printf"), "int", -1);
        register_c_function(global, "scanf", dlsym(libc, "scanf"), "int", -1);
        register_c_function(global, "malloc", dlsym(libc, "malloc"), "void*", 1, "int");
        register_c_function(global, "free", dlsym(libc, "free"), "void", 1, "void*");
        register_c_function(global, "strlen", dlsym(libc, "strlen"), "int", 1, "char*");
        register_c_function(global, "strcmp", dlsym(libc, "strcmp"), "int", 2, "char*", "char*");
        register_c_function(global, "strcpy", dlsym(libc, "strcpy"), "char*", 2, "char*", "char*");
        register_c_function(global, "atoi", dlsym(libc, "atoi"), "int", 1, "char*");
        register_c_function(global, "atof", dlsym(libc, "atof"), "double", 1, "char*");
        register_c_function(global, "system", dlsym(libc, "system"), "int", 1, "char*");
        register_c_function(global, "exit", dlsym(libc, "exit"), "void", 1, "int");
    }
    
    // Enregistrer toutes les fonctions
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION) {
            Value func_val;
            func_val.type = 4;
            func_val.func_val.node = stmt;
            func_val.func_val.closure = global;
            env_set(global, stmt->function.name, func_val);
        }
    }
    
    // Trouver et exécuter main
    ASTNode* main_func = NULL;
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION && strcmp(stmt->function.name, "main") == 0) {
            main_func = stmt;
            break;
        }
    }
    
    if (!main_func) {
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt->type == NODE_EXPR_STMT) {
                evaluate_statement(stmt, global);
            }
        }
        free(global);
        return;
    }
    
    for (int i = 0; i < main_func->function.body->count; i++) {
        int ret = evaluate_statement(main_func->function.body->nodes[i], global);
        if (ret) break;
    }
    
    free(global);
}
