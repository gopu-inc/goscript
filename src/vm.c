#include "common.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
// Initialization and cleanup
//------------------------------------------------------------------------------

void init_vm(VM* vm) {
    vm->global_count = 0;
    vm->global_capacity = 16; // Start with 16, grow as needed
    vm->globals = (Value*)allocate(sizeof(Value) * vm->global_capacity);
    
    vm->stack_top = 0;
    vm->stack_capacity = STACK_MAX;
    vm->stack = (double*)allocate(sizeof(double) * vm->stack_capacity);
    
    vm->had_error = false;
    vm->return_flag = false;
    vm->return_value = 0;
    vm->current_frame = NULL;
    vm->functions = NULL;
    vm->function_count = 0;
}

void free_vm(VM* vm) {
    // Free global variables
    for (int i = 0; i < vm->global_count; i++) {
        if (vm->globals[i].name) free(vm->globals[i].name);
        if (vm->globals[i].type == TYPE_STRING && vm->globals[i].value.string) {
            free(vm->globals[i].value.string);
        }
    }
    if (vm->globals) free(vm->globals);
    
    // Free stack
    if (vm->stack) free(vm->stack);
    
    // Free functions
    Function* func = vm->functions;
    while (func) {
        Function* next = func->next;
        if (func->name) free(func->name);
        free(func);
        func = next;
    }
}

//------------------------------------------------------------------------------
// Stack operations
//------------------------------------------------------------------------------

void push(VM* vm, double value) {
    if (vm->stack_top >= vm->stack_capacity) {
        // Grow stack if needed
        vm->stack_capacity *= 2;
        vm->stack = (double*)realloc(vm->stack, sizeof(double) * vm->stack_capacity);
        if (!vm->stack) {
            fprintf(stderr, "Error: Out of memory - cannot grow stack\n");
            vm->had_error = true;
            return;
        }
    }
    vm->stack[vm->stack_top++] = value;
}

double pop(VM* vm) {
    if (vm->stack_top <= 0) {
        fprintf(stderr, "Error: Stack underflow\n");
        vm->had_error = true;
        return 0;
    }
    return vm->stack[--vm->stack_top];
}

double peek(VM* vm, int distance) {
    if (vm->stack_top - 1 - distance < 0) {
        fprintf(stderr, "Error: Invalid stack access\n");
        vm->had_error = true;
        return 0;
    }
    return vm->stack[vm->stack_top - 1 - distance];
}

//------------------------------------------------------------------------------
// Variable management
//------------------------------------------------------------------------------

static void grow_globals(VM* vm) {
    vm->global_capacity *= 2;
    vm->globals = (Value*)realloc(vm->globals, sizeof(Value) * vm->global_capacity);
    if (!vm->globals) {
        fprintf(stderr, "Error: Out of memory - cannot grow globals\n");
        vm->had_error = true;
    }
}

static Value* find_variable(VM* vm, const char* name) {
    // Look in current frame first (for local variables)
    Frame* frame = vm->current_frame;
    while (frame) {
        for (int i = 0; i < frame->local_count; i++) {
            if (strcmp(frame->locals[i].name, name) == 0) {
                return &frame->locals[i];
            }
        }
        frame = frame->parent;
    }
    
    // Then look in globals
    for (int i = 0; i < vm->global_count; i++) {
        if (strcmp(vm->globals[i].name, name) == 0) {
            return &vm->globals[i];
        }
    }
    
    return NULL;
}

static void define_global(VM* vm, const char* name, Value value) {
    // Check if already exists
    for (int i = 0; i < vm->global_count; i++) {
        if (strcmp(vm->globals[i].name, name) == 0) {
            // Update existing
            if (vm->globals[i].type == TYPE_STRING && vm->globals[i].value.string) {
                free(vm->globals[i].value.string);
            }
            vm->globals[i] = value;
            vm->globals[i].name = strdup(name);
            vm->globals[i].is_initialized = true;
            return;
        }
    }
    
    // Add new
    if (vm->global_count >= vm->global_capacity) {
        grow_globals(vm);
        if (vm->had_error) return;
    }
    
    vm->globals[vm->global_count] = value;
    vm->globals[vm->global_count].name = strdup(name);
    vm->globals[vm->global_count].is_initialized = true;
    vm->global_count++;
}

static void set_variable(VM* vm, const char* name, Value value) {
    Value* var = find_variable(vm, name);
    if (var) {
        // Free old string if needed
        if (var->type == TYPE_STRING && var->value.string) {
            free(var->value.string);
        }
        *var = value;
        var->name = strdup(name); // Keep name
        var->is_initialized = true;
    } else {
        // Not found, create as global
        define_global(vm, name, value);
    }
}

static Value get_variable(VM* vm, const char* name) {
    Value* var = find_variable(vm, name);
    if (var && var->is_initialized) {
        return *var;
    } else {
        fprintf(stderr, "Error: Variable '%s' not defined\n", name);
        vm->had_error = true;
        Value error_val = {0};
        error_val.type = TYPE_NUMBER;
        error_val.value.number = 0;
        return error_val;
    }
}

//------------------------------------------------------------------------------
// Expression evaluation
//------------------------------------------------------------------------------

static double evaluate(VM* vm, Node* node) {
    if (!node || vm->had_error) return 0;
    
    switch (node->type) {
        case NODE_LITERAL_NUMBER:
            return node->data.number_value;
            
        case NODE_LITERAL_BOOL:
            return node->data.bool_value ? 1.0 : 0.0;
            
        case NODE_LITERAL_STRING:
            // For now, strings evaluate to 0
            return 0;
            
        case NODE_VARIABLE: {
            Value val = get_variable(vm, node->data.identifier);
            if (val.type == TYPE_NUMBER) return val.value.number;
            if (val.type == TYPE_BOOL) return val.value.boolean ? 1.0 : 0.0;
            return 0;
        }
        
        case NODE_GROUPING:
            return evaluate(vm, node->left);
            
        case NODE_UNARY_OP: {
            double right = evaluate(vm, node->right);
            if (node->data.binary.op == '-') return -right;
            if (node->data.binary.op == '!') return !right;
            return right;
        }
        
        case NODE_BINARY_OP: {
            double left = evaluate(vm, node->left);
            double right = evaluate(vm, node->right);
            
            switch (node->data.binary.op) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': 
                    if (right == 0) {
                        fprintf(stderr, "Error: Division by zero\n");
                        vm->had_error = true;
                        return 0;
                    }
                    return left / right;
                case '=': return left == right ? 1.0 : 0.0;
                case '!': return left != right ? 1.0 : 0.0;
                case '<': return left < right ? 1.0 : 0.0;
                case '>': return left > right ? 1.0 : 0.0;
                case 'g': return left >= right ? 1.0 : 0.0; // >=
                case 'l': return left <= right ? 1.0 : 0.0; // <=
                default:
                    fprintf(stderr, "Error: Unknown operator %c\n", node->data.binary.op);
                    vm->had_error = true;
                    return 0;
            }
        }
        
        default:
            return 0;
    }
}

//------------------------------------------------------------------------------
// Statement execution
//------------------------------------------------------------------------------

static void execute_statement(VM* vm, Node* node) {
    if (!node || vm->had_error || vm->return_flag) return;
    
    switch (node->type) {
        case NODE_PROGRAM: {
            Node* stmt = node->left;
            while (stmt && !vm->had_error && !vm->return_flag) {
                execute_statement(vm, stmt);
                stmt = stmt->right;
            }
            break;
        }
        
        case NODE_BLOCK: {
            Node* stmt = node->left;
            while (stmt && !vm->had_error && !vm->return_flag) {
                execute_statement(vm, stmt);
                stmt = stmt->right;
            }
            break;
        }
        
        case NODE_EXPRESSION_STMT:
            evaluate(vm, node->left);
            break;
            
        case NODE_PRINT_STMT: {
            double value = evaluate(vm, node->left);
            if (!vm->had_error) {
                // Print as integer if it's a whole number
                if (value == (int)value) {
                    printf("%d\n", (int)value);
                } else {
                    printf("%g\n", value);
                }
            }
            break;
        }
        
        case NODE_GETLF_STMT: {
            double value = evaluate(vm, node->left);
            if (!vm->had_error) {
                if (value == (int)value) {
                    printf("%d\n", (int)value);
                } else {
                    printf("%g\n", value);
                }
            }
            break;
        }
        
        case NODE_INPUT_STMT: {
            char buffer[256];
            if (node->data.string_value && strlen(node->data.string_value) > 0) {
                printf("%s", node->data.string_value);
            }
            if (fgets(buffer, sizeof(buffer), stdin)) {
                buffer[strcspn(buffer, "\n")] = 0;
                char* endptr;
                double val = strtod(buffer, &endptr);
                push(vm, val);
            }
            break;
        }
        
        case NODE_VARIABLE_DECL: {
            double value = 0;
            if (node->left) {
                value = evaluate(vm, node->left);
            }
            
            if (!vm->had_error) {
                Value val;
                val.type = TYPE_NUMBER;
                val.value.number = value;
                val.is_initialized = true;
                define_global(vm, node->data.identifier, val);
            }
            break;
        }
        
        case NODE_ASSIGNMENT: {
            double value = evaluate(vm, node->left);
            if (!vm->had_error) {
                Value val;
                val.type = TYPE_NUMBER;
                val.value.number = value;
                val.is_initialized = true;
                set_variable(vm, node->data.identifier, val);
            }
            break;
        }
        
        case NODE_IF_STMT: {
            double condition = evaluate(vm, node->left);
            if (!vm->had_error) {
                if (condition != 0) {
                    execute_statement(vm, node->right);
                } else if (node->extra) {
                    execute_statement(vm, node->extra);
                }
            }
            break;
        }
        
        case NODE_WHILE_STMT: {
            while (!vm->had_error && !vm->return_flag) {
                double condition = evaluate(vm, node->left);
                if (condition == 0) break;
                execute_statement(vm, node->right);
            }
            break;
        }
        
        case NODE_FOR_STMT: {
            // Initializer
            if (node->left) {
                execute_statement(vm, node->left);
            }
            
            // The extra field contains a block with [body, increment]
            Node* for_extra = node->extra;
            
            while (!vm->had_error && !vm->return_flag) {
                // Condition
                double condition = 1.0;
                if (node->right) {
                    condition = evaluate(vm, node->right);
                }
                if (condition == 0) break;
                
                // Body
                if (for_extra && for_extra->left) {
                    execute_statement(vm, for_extra->left);
                }
                
                // Increment
                if (for_extra && for_extra->right) {
                    evaluate(vm, for_extra->right);
                }
            }
            break;
        }
        
        case NODE_RETURN_STMT: {
            if (node->left) {
                vm->return_value = evaluate(vm, node->left);
            } else {
                vm->return_value = 0;
            }
            vm->return_flag = true;
            break;
        }
        
        case NODE_FUNCTION_DECL: {
            // Store function in VM
            Function* func = (Function*)allocate(sizeof(Function));
            func->name = strdup(node->data.identifier);
            func->params = node->left;
            func->body = node->right;
            func->next = vm->functions;
            vm->functions = func;
            vm->function_count++;
            break;
        }
        
        case NODE_FUNCTION_CALL: {
            // Find function
            Function* func = vm->functions;
            while (func) {
                if (strcmp(func->name, node->data.identifier) == 0) break;
                func = func->next;
            }
            
            if (!func) {
                fprintf(stderr, "Error: Undefined function '%s'\n", node->data.identifier);
                vm->had_error = true;
                break;
            }
            
            // Create new frame for local variables
            Frame frame;
            frame.locals = (Value*)allocate(sizeof(Value) * LOCALS_MAX);
            frame.local_count = 0;
            frame.parent = vm->current_frame;
            
            vm->current_frame = &frame;
            
            // Pass arguments
            Node* arg = node->left;
            Node* param = func->params;
            
            while (arg && param) {
                double arg_value = evaluate(vm, arg);
                
                Value val;
                val.type = TYPE_NUMBER;
                val.value.number = arg_value;
                val.is_initialized = true;
                
                // Add to frame locals
                frame.locals[frame.local_count] = val;
                frame.locals[frame.local_count].name = strdup(param->data.identifier);
                frame.local_count++;
                
                arg = arg->right;
                param = param->right;
            }
            
            // Execute function body
            vm->return_flag = false;
            execute_statement(vm, func->body);
            
            // Clean up frame
            for (int i = 0; i < frame.local_count; i++) {
                if (frame.locals[i].name) free(frame.locals[i].name);
            }
            free(frame.locals);
            
            vm->current_frame = frame.parent;
            
            // Push return value
            if (vm->return_flag) {
                push(vm, vm->return_value);
                vm->return_flag = false;
            } else {
                push(vm, 0);
            }
            break;
        }
        
        default:
            // Ignore other types
            break;
    }
}

//------------------------------------------------------------------------------
// Main execution entry point
//------------------------------------------------------------------------------

bool execute(VM* vm, Node* ast) {
    if (!ast) return false;
    
    vm->had_error = false;
    vm->return_flag = false;
    
    execute_statement(vm, ast);
    
    return !vm->had_error;
}
