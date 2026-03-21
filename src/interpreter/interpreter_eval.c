#include "interpreter.h"

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
            if (val) result = *val;
            else {
                fprintf(stderr, "Undefined: %s\n", node->identifier.name);
                exit(1);
            }
            break;
        }
        
        case NODE_BINARY_OP: {
            // Assignation
            if (node->binary.op >= OP_ASSIGN && node->binary.op <= OP_MOD_ASSIGN) {
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
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val < right.int_val;
                    break;
                case OP_GT:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val > right.int_val;
                    break;
                case OP_LTE:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val <= right.int_val;
                    break;
                case OP_GTE:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val >= right.int_val;
                    break;
                case OP_EQ:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val == right.int_val;
                    else if (left.type == 2 && right.type == 2) result.bool_val = strcmp(left.string_val, right.string_val) == 0;
                    break;
                case OP_NEQ:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) result.bool_val = left.int_val != right.int_val;
                    break;
                case OP_AND:
                    result.type = 3;
                    if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val && right.bool_val;
                    break;
                case OP_OR:
                    result.type = 3;
                    if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val || right.bool_val;
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
                } else printf("\n");
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

int evaluate_statement(ASTNode* node, Environment* env) {
    switch (node->type) {
        case NODE_LET: {
            Value val = evaluate_expr(node->var_decl.value, env);
            env_set(env, node->var_decl.name, val);
            return 0;
        }
        case NODE_BREAK: {
            return 2; // Signal break
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
                    if (evaluate_statement(node->if_stmt.then_branch->nodes[i], env)) return 1;
                }
            } else if (node->if_stmt.else_branch) {
                for (int i = 0; i < node->if_stmt.else_branch->count; i++) {
                    if (evaluate_statement(node->if_stmt.else_branch->nodes[i], env)) return 1;
                }
            }
            return 0;
        }
        
        case NODE_WHILE: {
            while (1) {
                Value cond = evaluate_expr(node->while_stmt.condition, env);
                if (cond.type != 3 || !cond.bool_val) break;
                for (int i = 0; i < node->while_stmt.body->count; i++) {
                    if (evaluate_statement(node->while_stmt.body->nodes[i], env)) return 1;
                }
            }
            return 0;
        }
        
        case NODE_LOOP: {
            while (1) {
                for (int i = 0; i < node->loop_stmt.body->count; i++) {
                    if (evaluate_statement(node->loop_stmt.body->nodes[i], env)) return 1;
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

void interpret_program(ASTNode* program) {
    Environment* global = create_env(NULL);
    
    void* libc = dlopen("libc.so.6", RTLD_LAZY);
    if (libc) {
        register_c_function(global, "printf", dlsym(libc, "printf"), "int", -1);
        register_c_function(global, "strlen", dlsym(libc, "strlen"), "int", 1, "char*");
        register_c_function(global, "strcmp", dlsym(libc, "strcmp"), "int", 2, "char*", "char*");
        register_c_function(global, "atoi", dlsym(libc, "atoi"), "int", 1, "char*");
        register_c_function(global, "atof", dlsym(libc, "atof"), "double", 1, "char*");
        register_c_function(global, "system", dlsym(libc, "system"), "int", 1, "char*");
        register_c_function(global, "exit", dlsym(libc, "exit"), "void", 1, "int");
    }
    
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
            if (stmt->type == NODE_EXPR_STMT) evaluate_statement(stmt, global);
        }
        free(global);
        return;
    }
    
    for (int i = 0; i < main_func->function.body->count; i++) {
        if (evaluate_statement(main_func->function.body->nodes[i], global)) break;
    }
    
    free(global);
}
