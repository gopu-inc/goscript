#include "interpreter.h"
#include <dlfcn.h>
#include <ffi.h>

 extern Value evaluate_expr(ASTNode* node, Environment* env);
extern int evaluate_statement(ASTNode* node, Environment* env, char* current_file);
/* static char* current_source_file = NULL; */
// ==================== GESTION DES IMPLÉMENTATIONS ====================

typedef struct {
    char* struct_name;
    ASTNode* impl_node;
} ImplEntry;

static ImplEntry* impl_table = NULL;
static int impl_count = 0;
static int impl_capacity = 0;

// Enregistrer une implémentation
void register_impl(char* struct_name, ASTNode* impl_node) {
    if (impl_count >= impl_capacity) {
        impl_capacity = impl_capacity == 0 ? 10 : impl_capacity * 2;
        impl_table = realloc(impl_table, impl_capacity * sizeof(ImplEntry));
    }
    impl_table[impl_count].struct_name = strdup(struct_name);
    impl_table[impl_count].impl_node = impl_node;
    impl_count++;
}
void dump_module_env(LoadedModule* mod) {
    if (!mod || !mod->env) return;
    printf("--- Symboles dans le module [%s] ---\n", mod->module_name);
    for (int i = 0; i < mod->env->var_count; i++) {
        printf("  [%d] %s (Type: %d)\n", i, mod->env->vars[i].name, mod->env->vars[i].value.type);
    }
    printf("-----------------------------------\n");
}

// Trouver une implémentation par nom de structure
ASTNode* find_impl(char* struct_name) {
    for (int i = 0; i < impl_count; i++) {
        if (strcmp(impl_table[i].struct_name, struct_name) == 0) {
            return impl_table[i].impl_node;
        }
    }
    return NULL;
}

static ModuleRegistry* module_registry = NULL;

ModuleRegistry* get_module_registry(void) {
    if (!module_registry) {
        module_registry = init_module_registry();
    }
    return module_registry;
}

// Handle global pour la libc (ouvert une seule fois)
extern ASTNode* program_root;
static void* libc_handle = NULL;
static int libc_initialized = 0;

// Initialiser le handle de la libc
void init_libc() {
    if (!libc_initialized) {
        // Sur Alpine Linux, la libc est musl
        libc_handle = dlopen("libc.musl-x86.so.1", RTLD_LAZY);
        if (!libc_handle) {
            // Essayer avec le nom standard
            libc_handle = dlopen("libc.so.6", RTLD_LAZY);
        }
        if (!libc_handle) {
            // Essayer avec NULL pour le programme courant
            libc_handle = dlopen(NULL, RTLD_LAZY);
        }
        libc_initialized = 1;
    }
}

// Fonction pour appeler une fonction C via FFI
Value call_c_function_ffi(void* func_ptr, Value* args, int arg_count, ffi_type* ret_type, ffi_type** arg_types) {
    Value result = {0};
    
    if (!func_ptr) {
        fprintf(stderr, "Error: NULL function pointer\n");
        return result;
    }
    
    // Préparer la CIF (Call Interface)
    ffi_cif cif;
    ffi_status status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, arg_count, ret_type, arg_types);
    
    if (status != FFI_OK) {
        fprintf(stderr, "Error: ffi_prep_cif failed with status %d\n", status);
        return result;
    }
    
    // Préparer les valeurs
    void** values = malloc(arg_count * sizeof(void*));
    void* ret_val = malloc(32);
    
    for (int i = 0; i < arg_count; i++) {
        switch (args[i].type) {
            case 0: values[i] = &args[i].int_val; break;
            case 1: values[i] = &args[i].float_val; break;
            case 2: values[i] = &args[i].string_val; break;
            case 3: values[i] = &args[i].bool_val; break;
            default: values[i] = NULL;
        }
    }
    
    ffi_call(&cif, FFI_FN(func_ptr), ret_val, values);
    
    if (ret_type == &ffi_type_sint32 || ret_type == &ffi_type_sint) {
        result.type = 0;
        result.int_val = *(int*)ret_val;
    } else if (ret_type == &ffi_type_sint64) {
        result.type = 0;
        result.int_val = *(long long*)ret_val;
    } else if (ret_type == &ffi_type_float) {
        result.type = 1;
        result.float_val = *(float*)ret_val;
    } else if (ret_type == &ffi_type_double) {
        result.type = 1;
        result.float_val = *(double*)ret_val;
    } else if (ret_type == &ffi_type_pointer) {
        result.type = 2;
        char* str = *(char**)ret_val;
        result.string_val = str ? strdup(str) : strdup("");
    } else if (ret_type == &ffi_type_void) {
        result.type = 0;
        result.int_val = 0;
    }
    
    free(values);
    free(ret_val);
    return result;
}

// Fonction pour appeler puts
Value call_puts(Value* args, int arg_count) {
    Value result = {0};
    if (arg_count > 0 && args[0].type == 2) {
        printf("%s\n", args[0].string_val);
    }
    return result;
}

// Fonction pour appeler putchar
Value call_putchar(Value* args, int arg_count) {
    Value result = {0};
    if (arg_count > 0 && args[0].type == 0) {
        putchar(args[0].int_val);
        result.int_val = args[0].int_val;
    }
    return result;
}

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

void register_native_c_functions(Environment* env) {
    init_libc();
    
    if (libc_handle) {
        void* strlen_ptr = dlsym(libc_handle, "strlen");
        if (strlen_ptr) {
            ffi_type* arg_types[] = {&ffi_type_pointer};
            Value func_val;
            func_val.type = 5;
            func_val.cfunc_val.func_ptr = strlen_ptr;
            func_val.cfunc_val.ret_type = &ffi_type_sint32;
            func_val.cfunc_val.arg_count = 1;
            func_val.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
            func_val.cfunc_val.arg_types[0] = &ffi_type_pointer;
            ffi_prep_cif(&func_val.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, arg_types);
            env_set(env, "strlen", func_val);
        }
        
        void* strcmp_ptr = dlsym(libc_handle, "strcmp");
        if (strcmp_ptr) {
            ffi_type* arg_types[] = {&ffi_type_pointer, &ffi_type_pointer};
            Value func_val;
            func_val.type = 5;
            func_val.cfunc_val.func_ptr = strcmp_ptr;
            func_val.cfunc_val.ret_type = &ffi_type_sint32;
            func_val.cfunc_val.arg_count = 2;
            func_val.cfunc_val.arg_types = malloc(2 * sizeof(ffi_type*));
            func_val.cfunc_val.arg_types[0] = &ffi_type_pointer;
            func_val.cfunc_val.arg_types[1] = &ffi_type_pointer;
            ffi_prep_cif(&func_val.cfunc_val.cif, FFI_DEFAULT_ABI, 2, &ffi_type_sint32, arg_types);
            env_set(env, "strcmp", func_val);
        }
        
        void* atoi_ptr = dlsym(libc_handle, "atoi");
        if (atoi_ptr) {
            ffi_type* arg_types[] = {&ffi_type_pointer};
            Value func_val;
            func_val.type = 5;
            func_val.cfunc_val.func_ptr = atoi_ptr;
            func_val.cfunc_val.ret_type = &ffi_type_sint32;
            func_val.cfunc_val.arg_count = 1;
            func_val.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
            func_val.cfunc_val.arg_types[0] = &ffi_type_pointer;
            ffi_prep_cif(&func_val.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, arg_types);
            env_set(env, "atoi", func_val);
        }
        
        void* system_ptr = dlsym(libc_handle, "system");
        if (system_ptr) {
            ffi_type* arg_types[] = {&ffi_type_pointer};
            Value func_val;
            func_val.type = 5;
            func_val.cfunc_val.func_ptr = system_ptr;
            func_val.cfunc_val.ret_type = &ffi_type_sint32;
            func_val.cfunc_val.arg_count = 1;
            func_val.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
            func_val.cfunc_val.arg_types[0] = &ffi_type_pointer;
            ffi_prep_cif(&func_val.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, arg_types);
            env_set(env, "system", func_val);
        }
        
        void* malloc_ptr = dlsym(libc_handle, "malloc");
        if (malloc_ptr) {
            ffi_type* arg_types[] = {&ffi_type_sint32};
            Value func_val;
            func_val.type = 5;
            func_val.cfunc_val.func_ptr = malloc_ptr;
            func_val.cfunc_val.ret_type = &ffi_type_pointer;
            func_val.cfunc_val.arg_count = 1;
            func_val.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
            func_val.cfunc_val.arg_types[0] = &ffi_type_sint32;
            ffi_prep_cif(&func_val.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_pointer, arg_types);
            env_set(env, "malloc", func_val);
        }
        
        void* free_ptr = dlsym(libc_handle, "free");
        if (free_ptr) {
            ffi_type* arg_types[] = {&ffi_type_pointer};
            Value func_val;
            func_val.type = 5;
            func_val.cfunc_val.func_ptr = free_ptr;
            func_val.cfunc_val.ret_type = &ffi_type_void;
            func_val.cfunc_val.arg_count = 1;
            func_val.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
            func_val.cfunc_val.arg_types[0] = &ffi_type_pointer;
            ffi_prep_cif(&func_val.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_void, arg_types);
            env_set(env, "free", func_val);
        }
    }
    
    // puts et putchar
    Value puts_func;
    puts_func.type = 5;
    puts_func.cfunc_val.func_ptr = (void*)call_puts;
    puts_func.cfunc_val.ret_type = &ffi_type_sint32;
    puts_func.cfunc_val.arg_count = 1;
    puts_func.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
    puts_func.cfunc_val.arg_types[0] = &ffi_type_pointer;
    ffi_prep_cif(&puts_func.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, (ffi_type*[]){&ffi_type_pointer});
    env_set(env, "puts", puts_func);
    
    Value putchar_func;
    putchar_func.type = 5;
    putchar_func.cfunc_val.func_ptr = (void*)call_putchar;
    putchar_func.cfunc_val.ret_type = &ffi_type_sint32;
    putchar_func.cfunc_val.arg_count = 1;
    putchar_func.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
    putchar_func.cfunc_val.arg_types[0] = &ffi_type_sint32;
    ffi_prep_cif(&putchar_func.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, (ffi_type*[]){&ffi_type_sint32});
    env_set(env, "putchar", putchar_func);
}
// cette fonction pour trouver une méthode dans une implémentation
ASTNode* find_method(ASTNode* impl_node, char* method_name) {
    if (!impl_node || impl_node->type != NODE_IMPL) return NULL;
    
    for (int i = 0; i < impl_node->impl.methods->count; i++) {
        ASTNode* method = impl_node->impl.methods->nodes[i];
        if (method->type == NODE_FUNCTION && 
            strcmp(method->function.name, method_name) == 0) {
            return method;
        }
    }
    return NULL;
}


Value call_method(Value* obj, char* method_name, ASTNodeList* args, Environment* env) {
    Value result = {0};
    
    if (obj->type != 6) return result;
    
    ASTNode* impl_node = find_impl(obj->struct_val.struct_name);
    if (!impl_node) return result;
    
    ASTNode* method = find_method(impl_node, method_name);
    if (!method) return result;
    
    Environment* method_env = create_env(env);
    env_set(method_env, "self", *obj);
    
    if (args) {
        for (int i = 0; i < args->count; i++) {
            Value arg_val = evaluate_expr(args->nodes[i], env);
            if (method->function.params && i < method->function.params->count) {
                ASTNode* param = method->function.params->nodes[i];
                env_set(method_env, param->identifier.name, arg_val);
            }
        }
    }
    
    for (int i = 0; i < method->function.body->count; i++) {
        ASTNode* stmt = method->function.body->nodes[i];
        if (stmt->type == NODE_RETURN) {
            result = evaluate_expr(stmt->return_stmt.value, method_env);
            break;
        } else {
            evaluate_statement(stmt, method_env, NULL);  // Ajoutez NULL comme current_file
        }
    }
    
    free(method_env);
    return result;
}

Value evaluate_expr(ASTNode* node, Environment* env) {
    Value result = {0};
    
    switch (node->type) {
        // ==================== VALEURS LITTÉRALES ====================
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
            
        case NODE_NIL:
            result.type = 0;
            result.int_val = 0;
            break;
            
        // ==================== IDENTIFIANT ====================
        case NODE_IDENTIFIER: {
            Value* val = env_get(env, node->identifier.name);
            if (val) {
                result = *val;
            } else {
                fprintf(stderr, "Undefined: %s\n", node->identifier.name);
            }
            break;
        }
        
        // ==================== OPÉRATIONS BINAIRES ====================
        case NODE_BINARY_OP: {
            // Gestion des assignations composées
            if (node->binary.op == OP_ADD_ASSIGN ||
                node->binary.op == OP_SUB_ASSIGN ||
                node->binary.op == OP_MUL_ASSIGN ||
                node->binary.op == OP_DIV_ASSIGN ||
                node->binary.op == OP_MOD_ASSIGN) {
                
                if (node->binary.left->type == NODE_IDENTIFIER) {
                    char* var_name = node->binary.left->identifier.name;
                    Value* current = env_get(env, var_name);
                    Value right_val = evaluate_expr(node->binary.right, env);
                    Value new_val = {0};
                    
                    if (current) {
                        switch (node->binary.op) {
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
                        env_set(env, var_name, new_val);
                        result = new_val;
                    }
                }
                break;
            }
            
            // Assignation simple
            if (node->binary.op == OP_ASSIGN) {
                if (node->binary.left->type == NODE_IDENTIFIER) {
                    char* var_name = node->binary.left->identifier.name;
                    Value right_val = evaluate_expr(node->binary.right, env);
                    env_set(env, var_name, right_val);
                    result = right_val;
                }
                break;
            }
            
            // Opérations binaires standard
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
                        char buf1[128], buf2[128];
                        char* left_str = "";
                        char* right_str = "";
                        if (left.type == 0) { sprintf(buf1, "%d", left.int_val); left_str = buf1; }
                        else if (left.type == 1) { sprintf(buf1, "%f", left.float_val); left_str = buf1; }
                        else if (left.type == 2) left_str = left.string_val;
                        else if (left.type == 3) left_str = left.bool_val ? "true" : "false";
                        if (right.type == 0) { sprintf(buf2, "%d", right.int_val); right_str = buf2; }
                        else if (right.type == 1) { sprintf(buf2, "%f", right.float_val); right_str = buf2; }
                        else if (right.type == 2) right_str = right.string_val;
                        else if (right.type == 3) right_str = right.bool_val ? "true" : "false";
                        result.type = 2;
                        result.string_val = malloc(strlen(left_str) + strlen(right_str) + 1);
                        strcpy(result.string_val, left_str);
                        strcat(result.string_val, right_str);
                    }
                    break;
                    
                case OP_SUB:
                    if (left.type == 0 && right.type == 0) {
                        result.type = 0;
                        result.int_val = left.int_val - right.int_val;
                    } else if (left.type == 1 && right.type == 1) {
                        result.type = 1;
                        result.float_val = left.float_val - right.float_val;
                    }
                    break;
                    
                case OP_MUL:
                    if (left.type == 0 && right.type == 0) {
                        result.type = 0;
                        result.int_val = left.int_val * right.int_val;
                    } else if (left.type == 1 && right.type == 1) {
                        result.type = 1;
                        result.float_val = left.float_val * right.float_val;
                    }
                    break;
                    
                case OP_DIV:
                    if (left.type == 0 && right.type == 0 && right.int_val != 0) {
                        result.type = 0;
                        result.int_val = left.int_val / right.int_val;
                    } else if (left.type == 1 && right.type == 1 && right.float_val != 0) {
                        result.type = 1;
                        result.float_val = left.float_val / right.float_val;
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
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val < right.int_val;
                    else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val < right.float_val;
                    break;
                    
                case OP_GT:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val > right.int_val;
                    else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val > right.float_val;
                    break;
                    
                case OP_LTE:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val <= right.int_val;
                    else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val <= right.float_val;
                    break;
                    
                case OP_GTE:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val >= right.int_val;
                    else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val >= right.float_val;
                    break;
                    
                case OP_EQ:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val == right.int_val;
                    else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val == right.float_val;
                    else if (left.type == 2 && right.type == 2) result.bool_val = strcmp(left.string_val, right.string_val) == 0;
                    else if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val == right.bool_val;
                    break;
                    
                case OP_NEQ:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val != right.int_val;
                    else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val != right.float_val;
                    break;
                    
                case OP_AND:
                    result.type = 3;
                    if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val && right.bool_val;
                    break;
                    
                case OP_OR:
                    result.type = 3;
                    if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val || right.bool_val;
                    break;
                    
                case OP_RANGE:
                    result.type = 0;
                    result.int_val = 0;
                    break;
                    
                case OP_PIPE:
                    result = right;
                    break;
                    
                default:
                    result.type = 0;
                    result.int_val = 0;
                    break;
            }
            break;
        }
        
        // ==================== OPÉRATIONS UNAIRES ====================
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
                default:
                    result.type = 0;
                    result.int_val = 0;
                    break;
            }
            break;
        }
        
        // ==================== STRUCTURE INIT ====================
        case NODE_STRUCT_INIT: {
            result.type = 6;
            result.struct_val.struct_name = strdup(node->struct_init.name);
            
            int field_count = 0;
            if (node->struct_init.fields) {
                field_count = node->struct_init.fields->count;
            }
            
            result.struct_val.field_count = field_count;
            result.struct_val.fields = malloc(field_count * sizeof(*result.struct_val.fields));
            
            for (int i = 0; i < field_count; i++) {
                ASTNode* field_node = node->struct_init.fields->nodes[i];
                if (field_node->type == NODE_FIELD_INIT) {
                    result.struct_val.fields[i].name = strdup(field_node->field_init.name);
                    result.struct_val.fields[i].value = malloc(sizeof(Value));
                    *(result.struct_val.fields[i].value) = evaluate_expr(field_node->field_init.value, env);
                } else {
                    result.struct_val.fields[i].name = NULL;
                    result.struct_val.fields[i].value = NULL;
                }
            }
            break;
        }
        
        // ==================== ACCÈS MEMBRE ====================
        case NODE_MEMBER_ACCESS: {
            Value obj = evaluate_expr(node->member.object, env);
            
            if (obj.type == 6) {
                char* member_name = node->member.member;
                Value* found = NULL;
                for (int i = 0; i < obj.struct_val.field_count; i++) {
                    if (obj.struct_val.fields[i].name && 
                        strcmp(obj.struct_val.fields[i].name, member_name) == 0) {
                        found = obj.struct_val.fields[i].value;
                        break;
                    }
                }
                if (found) {
                    result = *found;
                } else {
                    result.type = 0;
                    result.int_val = 0;
                }
            }
            break;
        }
        
        // ==================== ACCÈS STATIQUE (MODULE) ====================
        case NODE_STATIC_ACCESS: {
    Value obj = evaluate_expr(node->static_access.object, env);
    
    if (obj.type == 7) {  // Type Module
        LoadedModule* mod = (LoadedModule*)obj.int_val;
        if (!mod || !mod->env) {
            fprintf(stderr, "Error: Module not initialized\n");
            result.type = 0;
            result.int_val = 0;
            break;
        }
        
        char* member_name = node->static_access.member;
        Value* val = env_get(mod->env, member_name);
        
        if (val) {
            result = *val;
        } else {
            fprintf(stderr, "Undefined: %s in module %s\n", 
                    member_name, mod->module_name);
            result.type = 0;
            result.int_val = 0;
        }
    } else {
        result.type = 0;
        result.int_val = 0;
    }
    break;
}
        // ==================== APPEL DE MÉTHODE ====================
case NODE_METHOD_CALL: {
    Value obj = evaluate_expr(node->method_call.object, env);
    
    // Cas 1: Structure (type 6)
    if (obj.type == 6) {
        char* method_name = node->method_call.method;
        ASTNode* impl_node = find_impl(obj.struct_val.struct_name);
        
        if (impl_node) {
            ASTNode* method = find_method(impl_node, method_name);
            if (method) {
                Environment* method_env = create_env(env);
                if (method->function.params && method->function.params->count > 0) {
                    ASTNode* first_param = method->function.params->nodes[0];
                    env_set(method_env, first_param->identifier.name, obj);
                    if (node->method_call.args) {
                        for (int i = 0; i < node->method_call.args->count && (i + 1) < method->function.params->count; i++) {
                            Value arg_val = evaluate_expr(node->method_call.args->nodes[i], env);
                            ASTNode* param = method->function.params->nodes[i + 1];
                            env_set(method_env, param->identifier.name, arg_val);
                        }
                    }
                } else {
                    env_set(method_env, "self", obj);
                }
                
                for (int i = 0; i < method->function.body->count; i++) {
                    ASTNode* stmt = method->function.body->nodes[i];
                    if (stmt->type == NODE_RETURN) {
                        result = evaluate_expr(stmt->return_stmt.value, method_env);
                        break;
                    } else {
                        evaluate_statement(stmt, method_env, NULL);
                    }
                }
                free(method_env);
            }
        }
    }
    // === NOUVEAU : Cas 2: Module (type 7) ===
    else if (obj.type == 7) {
        LoadedModule* module = (LoadedModule*)obj.int_val;
        char* method_name = node->method_call.method;
        Value* func = env_get(module->env, method_name);
        
        if (func && func->type == 4) {
            Environment* func_env = create_env(func->func_val.closure);
            
            if (node->method_call.args && func->func_val.node->function.params) {
                int arg_count = node->method_call.args->count;
                int param_count = func->func_val.node->function.params->count;
                for (int i = 0; i < arg_count && i < param_count; i++) {
                    Value arg_val = evaluate_expr(node->method_call.args->nodes[i], env);
                    ASTNode* param = func->func_val.node->function.params->nodes[i];
                    env_set(func_env, param->identifier.name, arg_val);
                }
            }
            
            for (int i = 0; i < func->func_val.node->function.body->count; i++) {
                ASTNode* stmt = func->func_val.node->function.body->nodes[i];
                if (stmt->type == NODE_RETURN) {
                    result = evaluate_expr(stmt->return_stmt.value, func_env);
                    break;
                } else {
                    evaluate_statement(stmt, func_env, NULL);
                }
            }
            free(func_env);
        } else {
            fprintf(stderr, "Error: Function '%s' not found in module\n", method_name);
        }
    }
    break;
}
        
        // ==================== APPEL DE FONCTION ====================
        case NODE_CALL: {
            char* func_name = node->call.callee->identifier.name;
            Value* func = env_get(env, func_name);
            
            if (func && func->type == 4) {
                Environment* func_env = create_env(func->func_val.closure);
                
                if (node->call.args && func->func_val.node->function.params) {
                    for (int i = 0; i < node->call.args->count && i < func->func_val.node->function.params->count; i++) {
                        Value arg_val = evaluate_expr(node->call.args->nodes[i], env);
                        ASTNode* param = func->func_val.node->function.params->nodes[i];
                        env_set(func_env, param->identifier.name, arg_val);
                    }
                }
                
                for (int i = 0; i < func->func_val.node->function.body->count; i++) {
                    ASTNode* stmt = func->func_val.node->function.body->nodes[i];
                    if (stmt->type == NODE_RETURN) {
                        result = evaluate_expr(stmt->return_stmt.value, func_env);
                        break;
                    } else {
                        evaluate_statement(stmt, func_env, NULL);
                    }
                }
                free(func_env);
            } else if (func && func->type == 5) {
                int arg_count = node->call.args ? node->call.args->count : 0;
                Value* args = malloc(arg_count * sizeof(Value));
                for (int i = 0; i < arg_count; i++) {
                    args[i] = evaluate_expr(node->call.args->nodes[i], env);
                }
                result = call_c_function_ffi(func->cfunc_val.func_ptr, args, arg_count,
                                             func->cfunc_val.ret_type, func->cfunc_val.arg_types);
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
                fprintf(stderr, "Error: Undefined function '%s'\n", func_name);
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
int evaluate_statement(ASTNode* node, Environment* env, char* current_file) {
    switch (node->type) {
        case NODE_LET: {
            Value val = evaluate_expr(node->var_decl.value, env);
            env_set(env, node->var_decl.name, val);
            return 0;
        }
        
        case NODE_CONST: {
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
                    if (evaluate_statement(node->if_stmt.then_branch->nodes[i], env, current_file)) return 1;
                }
            } else if (node->if_stmt.else_branch) {
                for (int i = 0; i < node->if_stmt.else_branch->count; i++) {
                    if (evaluate_statement(node->if_stmt.else_branch->nodes[i], env, current_file)) return 1;
                }
            }
            return 0;
        }
        
        case NODE_WHILE: {
            while (1) {
                Value cond = evaluate_expr(node->while_stmt.condition, env);
                if (cond.type != 3 || !cond.bool_val) break;
                for (int i = 0; i < node->while_stmt.body->count; i++) {
                    if (evaluate_statement(node->while_stmt.body->nodes[i], env, current_file)) return 1;
                }
            }
            return 0;
        }
        
        case NODE_LOOP: {
            while (1) {
                int break_flag = 0;
                for (int i = 0; i < node->loop_stmt.body->count; i++) {
                    int ret = evaluate_statement(node->loop_stmt.body->nodes[i], env, current_file);
                    if (ret == 1) return 1;
                    if (ret == 2) { break_flag = 1; break; }
                }
                if (break_flag) break;
            }
            return 0;
        }
        
        case NODE_FOR: {
            // Initialisation
            if (node->for_range.start) {
                evaluate_statement(node->for_range.start, env, current_file);
            }
            
            // Boucle
            while (1) {
                if (node->for_range.end) {
                    Value cond = evaluate_expr(node->for_range.end, env);
                    if (cond.type != 3 || !cond.bool_val) break;
                }
                
                for (int i = 0; i < node->for_range.body->count; i++) {
                    int ret = evaluate_statement(node->for_range.body->nodes[i], env, current_file);
                    if (ret == 1) return 1;
                    if (ret == 2) return 0;
                }
                
                // Incrémentation (gérée par l'expression dans la boucle for)
                if (node->for_range.var) {
                    // L'incrémentation est déjà dans le corps de la boucle
                }
            }
            return 0;
        }
        
        case NODE_BREAK:
            return 2;
        
        case NODE_CONTINUE:
            return 3;
        
        case NODE_MATCH: {
            Value val = evaluate_expr(node->match_stmt.value, env);
            for (int i = 0; i < node->match_stmt.cases->count; i++) {
                ASTNode* case_node = node->match_stmt.cases->nodes[i];
                if (case_node->type == NODE_MATCH_CASE) {
                    Value pattern_val = evaluate_expr(case_node->match_case.pattern, env);
                    if (val.type == pattern_val.type) {
                        int match = 0;
                        if (val.type == 0 && val.int_val == pattern_val.int_val) match = 1;
                        else if (val.type == 1 && val.float_val == pattern_val.float_val) match = 1;
                        else if (val.type == 2 && strcmp(val.string_val, pattern_val.string_val) == 0) match = 1;
                        else if (val.type == 3 && val.bool_val == pattern_val.bool_val) match = 1;
                        
                        if (match) {
                            Value result = evaluate_expr(case_node->match_case.value, env);
                            print_value(result, 1);
                            return 0;
                        }
                    }
                }
            }
            return 0;
        }
        
        case NODE_IMPORT: {
    // Charger le module
    ModuleRegistry* reg = get_module_registry();
    LoadedModule* module = load_module(
        reg,
        env,
        current_file,
        node->import.path,
        node->import.alias,
        node->import.constraints
    );
    
    if (module) {
        // Le module est chargé, la valeur est déjà dans l'environnement
        // via load_module qui appelle env_set
        return 0;
    } else {
        fprintf(stderr, "Failed to load module: %s\n", node->import.path);
        return 0;
    }
}
        
        case NODE_EXPR_STMT: {
            evaluate_expr(node->expr_stmt.expr, env);
            return 0;
        }
        /*
        case NODE_STRUCT_DEF:
        case NODE_ENUM_DEF:
        case NODE_IMPL_DEF:
            // Les définitions sont enregistrées au niveau global, rien à exécuter
            return 0;
        */
        default:
            return 0;
    }
}
void init_interpreter() {
    init_libc();
}
void interpret_program(ASTNode* program) {
    Environment* global = create_env(NULL);
    init_interpreter();
    register_native_c_functions(global);
    get_module_registry();
    
    // 1. Enregistrer les fonctions
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
    
    // 2. Enregistrer les structures
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_STRUCT) {
            Value struct_val;
            struct_val.type = 6;
            struct_val.struct_val.struct_name = strdup(stmt->struct_def.name);
            struct_val.struct_val.fields = NULL;
            struct_val.struct_val.field_count = 0;
            env_set(global, stmt->struct_def.name, struct_val);
        }
    }
    
    // 3. Enregistrer les implémentations
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_IMPL) {
            register_impl(stmt->impl.name, stmt);
        }
    }
    
    // === NOUVEAU : 3.5 Exécuter les imports ===
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_IMPORT) {
            evaluate_statement(stmt, global, NULL);
        }
    }
    
    // 4. Chercher la fonction main
    ASTNode* main_func = NULL;
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION && strcmp(stmt->function.name, "main") == 0) {
            main_func = stmt;
            break;
        }
    }
    
    // 5. Exécuter main
    if (main_func) {
        Environment* main_env = create_env(global);
        for (int i = 0; i < main_func->function.body->count; i++) {
            int ret = evaluate_statement(main_func->function.body->nodes[i], main_env, NULL);
            if (ret) break;
        }
        free(main_env);
    } else {
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt->type == NODE_EXPR_STMT) {
                evaluate_statement(stmt, global, NULL);
            }
        }
    }
    
    free(global);
}

// ==================== NETTOYAGE DE LA MÉMOIRE ====================

void free_impl_table() {
    for (int i = 0; i < impl_count; i++) {
        free(impl_table[i].struct_name);
    }
    free(impl_table);
    impl_table = NULL;
    impl_count = 0;
    impl_capacity = 0;
}
