#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNodeList* create_node_list() {
    ASTNodeList* list = malloc(sizeof(ASTNodeList));
    list->nodes = NULL;
    list->count = 0;
    list->capacity = 0;
    return list;
}

void add_to_node_list(ASTNodeList* list, ASTNode* node) {
    if (!list) return;
    
    if (list->count >= list->capacity) {
        list->capacity = list->capacity == 0 ? 10 : list->capacity * 2;
        list->nodes = realloc(list->nodes, list->capacity * sizeof(ASTNode*));
    }
    list->nodes[list->count++] = node;
}

ASTNodeList* create_arg_list() {
    return create_node_list();
}

void add_arg(ASTNodeList* list, ASTNode* arg) {
    add_to_node_list(list, arg);
}

ASTNodeList* create_array_items() {
    return create_node_list();
}

void add_array_item(ASTNodeList* list, ASTNode* item) {
    add_to_node_list(list, item);
}

ASTNode* create_program_node(ASTNodeList* statements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->program.statements = statements;
    return node;
}

ASTNode* create_import_node(char* path, char* alias) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IMPORT;
    node->import.path = strdup(path);
    node->import.alias = alias ? strdup(alias) : NULL;
    return node;
}

ASTNode* create_packet_import_node(char* path) {
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "/usr/local/lib/goscript/granul/%s/__self__.gjs", path);
    return create_import_node(full_path, NULL);
}

ASTNode* create_packet_node(char* name, ASTNodeList* statements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PACKET;
    node->packet.name = strdup(name);
    node->packet.statements = statements;
    return node;
}

ASTNode* create_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION;
    node->function.name = strdup(name);
    node->function.params = params;
    node->function.return_type = return_type;
    node->function.body = body;
    node->function.is_main = 0;
    return node;
}

ASTNode* create_main_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body) {
    ASTNode* node = create_function_node(name, params, return_type, body);
    node->function.is_main = 1;
    return node;
}

ASTNode* create_let_node(char* name, ASTNode* type, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_LET;
    node->var_decl.name = strdup(name);
    node->var_decl.type = type;
    node->var_decl.value = value;
    return node;
}

ASTNode* create_const_node(char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CONST;
    node->var_decl.name = strdup(name);
    node->var_decl.value = value;
    return node;
}

ASTNode* create_if_node(ASTNode* condition, ASTNodeList* then_branch, ASTNodeList* else_branch) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->if_stmt.condition = condition;
    node->if_stmt.then_branch = then_branch;
    node->if_stmt.else_branch = else_branch;
    return node;
}

ASTNode* create_elseif_node(ASTNode* condition, ASTNodeList* then_branch, ASTNodeList* else_branch) {
    return create_if_node(condition, then_branch, else_branch);
}

ASTNode* create_while_node(ASTNode* condition, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->while_stmt.condition = condition;
    node->while_stmt.body = body;
    return node;
}

ASTNode* create_loop_node(ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_LOOP;
    node->loop_stmt.body = body;
    return node;
}

ASTNode* create_return_node(ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->return_stmt.value = value;
    return node;
}

ASTNode* create_expr_statement(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_STMT;
    node->expr_stmt.expr = expr;
    return node;
}

ASTNode* create_binary_op(ASTNode* left, Operator op, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OP;
    node->binary.left = left;
    node->binary.op = op;
    node->binary.right = right;
    return node;
}

ASTNode* create_unary_op(Operator op, ASTNode* operand) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_UNARY_OP;
    node->unary.op = op;
    node->unary.operand = operand;
    return node;
}

ASTNode* create_number_node(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->number.value = value;
    return node;
}

ASTNode* create_float_node(double value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT;
    node->float_val.value = value;
    return node;
}

ASTNode* create_string_node(char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRING;
    node->string_val.value = strdup(value);
    return node;
}

ASTNode* create_bool_node(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BOOL;
    node->bool_val.value = value;
    return node;
}

ASTNode* create_nil_node() {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NIL;
    return node;
}

ASTNode* create_identifier_node(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->identifier.name = strdup(name);
    return node;
}

ASTNode* create_call_node(ASTNode* callee, ASTNodeList* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CALL;
    node->call.callee = callee;
    node->call.args = args;
    return node;
}

ASTNode* create_array_node(ASTNodeList* elements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY;
    node->array.elements = elements;
    return node;
}

ASTNode* create_for_node(ASTNode* init, ASTNode* cond, ASTNode* inc, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->for_range.var = NULL;
    node->for_range.start = init;
    node->for_range.end = cond;
    node->for_range.body = body;
    return node;
}

ASTNode* create_assign_node(ASTNode* left, ASTNode* right) {
    return create_binary_op(left, OP_ASSIGN, right);
}

void free_ast(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            if (node->program.statements) {
                for (int i = 0; i < node->program.statements->count; i++) {
                    free_ast(node->program.statements->nodes[i]);
                }
                free(node->program.statements->nodes);
                free(node->program.statements);
            }
            break;
        case NODE_IMPORT:
            if (node->import.path) free(node->import.path);
            if (node->import.alias) free(node->import.alias);
            break;
        case NODE_FUNCTION:
            if (node->function.name) free(node->function.name);
            if (node->function.body) {
                for (int i = 0; i < node->function.body->count; i++) {
                    free_ast(node->function.body->nodes[i]);
                }
                free(node->function.body->nodes);
                free(node->function.body);
            }
            break;
        case NODE_LET:
        case NODE_CONST:
            if (node->var_decl.name) free(node->var_decl.name);
            if (node->var_decl.value) free_ast(node->var_decl.value);
            break;
        case NODE_IF:
            if (node->if_stmt.condition) free_ast(node->if_stmt.condition);
            if (node->if_stmt.then_branch) {
                for (int i = 0; i < node->if_stmt.then_branch->count; i++) {
                    free_ast(node->if_stmt.then_branch->nodes[i]);
                }
                free(node->if_stmt.then_branch->nodes);
                free(node->if_stmt.then_branch);
            }
            break;
        case NODE_STRING:
            if (node->string_val.value) free(node->string_val.value);
            break;
        case NODE_IDENTIFIER:
            if (node->identifier.name) free(node->identifier.name);
            break;
        default:
            break;
    }
    free(node);
}
