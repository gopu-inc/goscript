#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"

typedef struct Value {
    int type;  // 0=int, 1=float, 2=string, 3=bool
    union {
        int int_val;
        double float_val;
        char* string_val;
        int bool_val;
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

void print_value(Value val, int newline) {
    switch (val.type) {
        case 0:  // int
            printf("%d", val.int_val);
            break;
        case 1:  // float
            printf("%f", val.float_val);
            break;
        case 2:  // string
            printf("%s", val.string_val);
            break;
        case 3:  // bool
            printf("%s", val.bool_val ? "true" : "false");
            break;
    }
    if (newline) {
        printf("\n");
    }
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
            if (val) {
                result = *val;
            } else {
                fprintf(stderr, "Undefined variable: %s\n", node->identifier.name);
                exit(1);
            }
            break;
        }
        
        case NODE_BINARY_OP: {
            // Handle assignment first
            if (node->binary.op == OP_ASSIGN) {
                if (node->binary.left->type == NODE_IDENTIFIER) {
                    Value right_val = evaluate_expr(node->binary.right, env);
                    env_set(env, node->binary.left->identifier.name, right_val);
                    result = right_val;
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
                        } else if (left.type == 1) {
                            num_buf = malloc(32);
                            sprintf(num_buf, "%f", left.float_val);
                            left_str = num_buf;
                        }
                        if (right.type == 0) {
                            num_buf = malloc(32);
                            sprintf(num_buf, "%d", right.int_val);
                            right_str = num_buf;
                        } else if (right.type == 1) {
                            num_buf = malloc(32);
                            sprintf(num_buf, "%f", right.float_val);
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
                case OP_EQ:
                    result.type = 3;
                    if (left.type == 0 && right.type == 0) {
                        result.bool_val = left.int_val == right.int_val;
                    } else if (left.type == 2 && right.type == 2) {
                        result.bool_val = strcmp(left.string_val, right.string_val) == 0;
                    } else if (left.type == 3 && right.type == 3) {
                        result.bool_val = left.bool_val == right.bool_val;
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
                default:
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
                default:
                    break;
            }
            break;
        }
        
        case NODE_CALL: {
            char* func_name = node->call.callee->identifier.name;
            
            if (strcmp(func_name, "print") == 0) {
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
                if (cond.type != 3 || !cond.bool_val) {
                    break;
                }
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
    
    // Find main function
    ASTNode* main_func = NULL;
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION && strcmp(stmt->function.name, "main") == 0) {
            main_func = stmt;
            break;
        }
    }
    
    if (!main_func) {
        fprintf(stderr, "Error: No main function found\n");
        return;
    }
    
    // Execute main function body
    for (int i = 0; i < main_func->function.body->count; i++) {
        int ret = evaluate_statement(main_func->function.body->nodes[i], global);
        if (ret) break;
    }
    
    free(global);
}
