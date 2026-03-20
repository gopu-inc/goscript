#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonctions de création de listes
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

ASTNodeList* create_param_list() {
    return create_node_list();
}

void add_param(ASTNodeList* list, ASTNode* param) {
    add_to_node_list(list, param);
}

ASTNodeList* create_field_list() {
    return create_node_list();
}

void add_field(ASTNodeList* list, ASTNode* field) {
    add_to_node_list(list, field);
}

ASTNodeList* create_variant_list() {
    return create_node_list();
}

void add_variant(ASTNodeList* list, ASTNode* variant) {
    add_to_node_list(list, variant);
}

ASTNodeList* create_case_list() {
    return create_node_list();
}

void add_case(ASTNodeList* list, ASTNode* case_node) {
    add_to_node_list(list, case_node);
}

ASTNodeList* create_field_init_list() {
    return create_node_list();
}

void add_field_init(ASTNodeList* list, ASTNode* init) {
    add_to_node_list(list, init);
}

ASTNodeList* create_type_list() {
    return create_node_list();
}

void add_type(ASTNodeList* list, ASTNode* type) {
    add_to_node_list(list, type);
}

// Création des noeuds AST
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
    ASTNode* node = create_if_node(condition, then_branch, else_branch);
    return node;
}

ASTNode* create_for_range_node(char* var, ASTNode* start, ASTNode* end, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->for_range.var = strdup(var);
    node->for_range.start = start;
    node->for_range.end = end;
    node->for_range.body = body;
    return node;
}

ASTNode* create_for_cond_node(ASTNode* condition, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->for_range.var = NULL;
    node->for_range.start = condition;
    node->for_range.end = NULL;
    node->for_range.body = body;
    return node;
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

ASTNode* create_match_node(ASTNode* value, ASTNodeList* cases) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_MATCH;
    node->match_stmt.value = value;
    node->match_stmt.cases = cases;
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

ASTNode* create_member_access(ASTNode* object, char* member) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_MEMBER_ACCESS;
    node->member.object = object;
    node->member.member = strdup(member);
    return node;
}

ASTNode* create_static_access(ASTNode* object, char* member) {
    return create_member_access(object, member);
}

ASTNode* create_pipe_op(ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PIPE;
    node->pipe.value = left;
    node->pipe.next = right;
    return node;
}

ASTNode* create_range_node(ASTNode* start, ASTNode* end, int inclusive) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_RANGE;
    node->range.start = start;
    node->range.end = end;
    node->range.inclusive = inclusive;
    return node;
}

ASTNode* create_array_node(ASTNodeList* elements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY;
    node->array.elements = elements;
    return node;
}

ASTNode* create_struct_node(char* name, ASTNodeList* fields) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT;
    node->struct_def.name = strdup(name);
    node->struct_def.fields = fields;
    return node;
}

ASTNode* create_enum_node(char* name, ASTNodeList* variants) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ENUM;
    node->enum_def.name = strdup(name);
    node->enum_def.variants = variants;
    return node;
}

ASTNode* create_param_node(char* name, ASTNode* type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->identifier.name = strdup(name);
    return node;
}

ASTNode* create_type_node(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->identifier.name = strdup(name);
    return node;
}

ASTNode* create_array_type_node(ASTNode* element_type) {
    return element_type;
}

ASTNode* create_chan_type_node(ASTNode* channel_type) {
    return channel_type;
}

ASTNode* create_match_case_node(ASTNode* pattern, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_MATCH;
    node->match_stmt.value = pattern;
    node->match_stmt.cases = (ASTNodeList*)value;
    return node;
}

ASTNode* create_field_node(char* name, ASTNode* type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT;
    node->struct_def.name = strdup(name);
    node->struct_def.fields = (ASTNodeList*)type;
    return node;
}

ASTNode* create_variant_node(char* name, ASTNodeList* types) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ENUM;
    node->enum_def.name = strdup(name);
    node->enum_def.variants = types;
    return node;
}

ASTNode* create_field_init_node(char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->identifier.name = strdup(name);
    return node;
}

ASTNode* create_pattern_number(int value) {
    return create_number_node(value);
}

ASTNode* create_pattern_string(char* value) {
    return create_string_node(value);
}

ASTNode* create_pattern_ident(char* value) {
    return create_identifier_node(value);
}

ASTNode* create_pattern_enum(char* enum_name, char* variant) {
    char* full_name = malloc(strlen(enum_name) + strlen(variant) + 3);
    sprintf(full_name, "%s::%s", enum_name, variant);
    return create_identifier_node(full_name);
}

ASTNode* create_pattern_wildcard() {
    return create_identifier_node("_");
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
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OP;
    node->binary.left = left;
    node->binary.op = OP_ASSIGN;
    node->binary.right = right;
    return node;
}

// Fonction de libération de mémoire
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
            
        case NODE_PACKET:
            if (node->packet.name) free(node->packet.name);
            if (node->packet.statements) {
                for (int i = 0; i < node->packet.statements->count; i++) {
                    free_ast(node->packet.statements->nodes[i]);
                }
                free(node->packet.statements->nodes);
                free(node->packet.statements);
            }
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
            
        case NODE_BINARY_OP:
            free_ast(node->binary.left);
            free_ast(node->binary.right);
            break;
            
        case NODE_UNARY_OP:
            free_ast(node->unary.operand);
            break;
            
        case NODE_CALL:
            free_ast(node->call.callee);
            if (node->call.args) {
                for (int i = 0; i < node->call.args->count; i++) {
                    free_ast(node->call.args->nodes[i]);
                }
                free(node->call.args->nodes);
                free(node->call.args);
            }
            break;
            
        case NODE_ARRAY:
            if (node->array.elements) {
                for (int i = 0; i < node->array.elements->count; i++) {
                    free_ast(node->array.elements->nodes[i]);
                }
                free(node->array.elements->nodes);
                free(node->array.elements);
            }
            break;
            
        default:
            break;
    }
    
    free(node);
}
