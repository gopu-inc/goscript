#include "common.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void execute_statement(VM* vm, Node* node);
static double evaluate(VM* vm, Node* node);

void init_vm(VM* vm) {
    vm->global_count = 0;
    vm->global_capacity = 16;
    vm->globals = (Value*)allocate(sizeof(Value) * vm->global_capacity);
    vm->stack_top = 0;
    vm->stack_capacity = STACK_MAX;
    vm->stack = (double*)allocate(sizeof(double) * vm->stack_capacity);
    vm->had_error = false;
    vm->return_flag = false;
    vm->return_value = 0;
    vm->current_frame = NULL;
    vm->functions = NULL;
}

void free_vm(VM* vm) {
    for (int i = 0; i < vm->global_count; i++) {
        if (vm->globals[i].name) free(vm->globals[i].name);
    }
    free(vm->globals);
    free(vm->stack);
    Function* f = vm->functions;
    while(f) {
        Function* next = f->next;
        free(f->name);
        free(f);
        f = next;
    }
}

void push(VM* vm, double value) {
    if (vm->stack_top < STACK_MAX) vm->stack[vm->stack_top++] = value;
}

double pop(VM* vm) {
    return (vm->stack_top > 0) ? vm->stack[--vm->stack_top] : 0;
}

static Value* find_var(VM* vm, const char* name) {
    Frame* f = vm->current_frame;
    while(f) {
        for(int i=0; i<f->local_count; i++)
            if(strcmp(f->locals[i].name, name) == 0) return &f->locals[i];
        f = f->parent;
    }
    for(int i=0; i<vm->global_count; i++)
        if(strcmp(vm->globals[i].name, name) == 0) return &vm->globals[i];
    return NULL;
}

static double evaluate(VM* vm, Node* node) {
    if (!node || vm->had_error) return 0;
    switch (node->type) {
        case NODE_LITERAL_NUMBER: return node->data.number_value;
        case NODE_VARIABLE: {
            Value* v = find_var(vm, node->data.identifier);
            return v ? v->value.number : 0;
        }
        case NODE_BINARY_OP: {
            double l = evaluate(vm, node->left);
            double r = evaluate(vm, node->right);
            if (node->data.binary.op == '+') return l + r;
            if (node->data.binary.op == '-') return l - r;
            if (node->data.binary.op == '*') return l * r;
            if (node->data.binary.op == '/' && r != 0) return l / r;
            return 0;
        }
        case NODE_FUNCTION_CALL: {
            int old_top = vm->stack_top;
            execute_statement(vm, node);
            return (vm->stack_top > old_top) ? pop(vm) : 0;
        }
        default: return 0;
    }
}

static void execute_statement(VM* vm, Node* node) {
    if (!node || vm->had_error || vm->return_flag) return;
    switch (node->type) {
        case NODE_PROGRAM:
        case NODE_BLOCK: {
            Node* stmt = node->left;
            while (stmt && !vm->return_flag) {
                execute_statement(vm, stmt);
                stmt = stmt->right;
            }
            break;
        }
        case NODE_PRINT_STMT:
            printf("%g\n", evaluate(vm, node->left));
            break;
        case NODE_FUNCTION_DECL: {
            Function* f = allocate(sizeof(Function));
            f->name = strdup(node->data.identifier);
            f->params = node->left;
            f->body = node->extra; // On récupère le corps depuis EXTRA
            f->next = vm->functions;
            vm->functions = f;
            break;
        }
        case NODE_RETURN_STMT:
            vm->return_value = evaluate(vm, node->left);
            vm->return_flag = true;
            break;
        case NODE_FUNCTION_CALL: {
            Function* f = vm->functions;
            while(f && strcmp(f->name, node->data.identifier) != 0) f = f->next;
            if(!f) return;
            
            Frame frame = {allocate(sizeof(Value)*10), 0, vm->current_frame};
            Node* arg = node->left; Node* param = f->params;
            while(arg && param) {
                frame.locals[frame.local_count++] = (Value){strdup(param->data.identifier), true, TYPE_NUMBER, {evaluate(vm, arg)}};
                arg = arg->right; param = param->right;
            }
            vm->current_frame = &frame;
            bool old_ret = vm->return_flag; vm->return_flag = false;
            execute_statement(vm, f->body);
            double res = vm->return_value;
            for(int i=0; i<frame.local_count; i++) free(frame.locals[i].name);
            free(frame.locals);
            vm->current_frame = frame.parent;
            vm->return_flag = old_ret;
            push(vm, res);
            break;
        }
        case NODE_VARIABLE_DECL: {
            if (vm->global_count >= vm->global_capacity) {
                vm->global_capacity *= 2;
                vm->globals = realloc(vm->globals, sizeof(Value) * vm->global_capacity);
            }
            vm->globals[vm->global_count++] = (Value){strdup(node->data.identifier), true, TYPE_NUMBER, {evaluate(vm, node->left)}};
            break;
        }
        default: break;
    }
}

bool execute(VM* vm, Node* ast) {
    execute_statement(vm, ast);
    return !vm->had_error;
}
