#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== Fonctions de création de listes ====================

ASTNodeList* create_node_list() {
    ASTNodeList* list = malloc(sizeof(ASTNodeList));
    list->nodes = NULL;
    list->count = 0;
    list->capacity = 0;
    return list;
}
ASTNode* create_struct_extend_node(char* name, char* parent, ASTNodeList* fields) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT_EXTENDS;
    node->struct_extend.name = strdup(name);
    node->struct_extend.parent = strdup(parent);
    node->struct_extend.fields = fields;
    node->struct_extend.is_public = 0;
    return node;
}

void add_to_node_list(ASTNodeList* list, ASTNode* node) {
    if (!list) return;
    
    if (list->count >= list->capacity) {
        list->capacity = list->capacity == 0 ? 10 : list->capacity * 2;
        list->nodes = realloc(list->nodes, list->capacity * sizeof(ASTNode*));
    }
    list->nodes[list->count++] = node;
}
ASTNode* create_return_direct_node(ASTNode* expr) {
    return create_return_node(expr);
}

ASTNode* create_nnl_node(char* label, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NNL;
    node->nnl_stmt.label = strdup(label);
    node->nnl_stmt.body = body;
    return node;
}

ASTNode* create_jmp_node(char* label, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_JMP;
    node->jmp_stmt.label = strdup(label);
    node->jmp_stmt.value = value;
    return node;
}
ASTNodeList* create_arg_list() {
    return create_node_list();
}

void add_arg(ASTNodeList* list, ASTNode* arg) {
    add_to_node_list(list, arg);
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

ASTNodeList* create_array_items() {
    return create_node_list();
}

void add_array_item(ASTNodeList* list, ASTNode* item) {
    add_to_node_list(list, item);
}

ASTNodeList* create_field_init_list() {
    return create_node_list();
}

void add_field_init(ASTNodeList* list, ASTNode* init) {
    add_to_node_list(list, init);
}

// ==================== Nœuds principaux ====================

ASTNode* create_program_node(ASTNodeList* statements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->program.statements = statements;
    return node;
}

ASTNode* create_for_in_node(char* var, ASTNode* collection, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FOR_IN;
    node->for_in.var = strdup(var);
    node->for_in.collection = collection;
    node->for_in.body = body;
    return node;
}

ASTNode* create_import_node(char* path, char* alias, ASTNode* constraints) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IMPORT;
    node->import.path = strdup(path);
    node->import.alias = alias ? strdup(alias) : NULL;
    node->import.constraints = constraints;
    return node;
}

ASTNode* create_export_node(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_EXPORT;
    node->export.name = strdup(name);
    return node;
}

ASTNode* create_lambda_node(ASTNodeList* params, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_LAMBDA;
    node->lambda.params = params;
    node->lambda.body = body;
    node->lambda.closure = NULL;
    return node;
}

ASTNode* create_array_access_node(ASTNode* array, ASTNode* index) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->array_access.array = array;
    node->array_access.index = index;
    return node;
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
    node->function.is_public = 0;
    return node;
}

ASTNode* create_public_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body) {
    ASTNode* node = create_function_node(name, params, return_type, body);
    node->type = NODE_PUBLIC_FUNCTION;
    node->function.is_public = 1;
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
    node->var_decl.var_type = type;
    node->var_decl.value = value;
    node->var_decl.is_public = 0;  // Ajoutez cette ligne
    return node;
}
ASTNode* create_const_node(char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CONST;
    node->var_decl.name = strdup(name);
    node->var_decl.var_type = NULL;
    node->var_decl.value = value;
    node->var_decl.is_public = 0;  // Ajoutez cette ligne
    return node;
}
ASTNode* create_unsafe_node(ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_UNSAFE;
    node->unsafe_block.body = body;
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

ASTNode* create_break_node() {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BREAK;
    return node;
}

ASTNode* create_continue_node() {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CONTINUE;
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

ASTNode* create_for_range_node(char* var, ASTNode* start, ASTNode* end, ASTNodeList* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FOR_RANGE;
    node->for_range.var = strdup(var);
    node->for_range.start = start;
    node->for_range.end = end;
    node->for_range.body = body;
    node->for_range.inclusive = 0;
    return node;
}

ASTNode* create_match_node(ASTNode* value, ASTNodeList* cases) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_MATCH;
    node->match_stmt.value = value;
    node->match_stmt.cases = cases;
    return node;
}

ASTNode* create_match_case_node(ASTNode* pattern, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_MATCH_CASE;
    node->match_case.pattern = pattern;
    node->match_case.value = value;
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

ASTNode* create_assign_node(ASTNode* left, ASTNode* right) {
    return create_binary_op(left, OP_ASSIGN, right);
}

ASTNode* create_assign_op_node(ASTNode* left, Operator op, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN_OP;
    node->assign_op.left = left;
    node->assign_op.op = op;
    node->assign_op.right = right;
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

ASTNode* create_muts_node(char* name, ASTNode* type, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_MUTS;
    node->muts_decl.name = strdup(name);
    node->muts_decl.var_type = type;
    node->muts_decl.value = value;
    node->muts_decl.is_public = 0;
    return node;
}

// Version publique
ASTNode* create_public_muts_node(char* name, ASTNode* type, ASTNode* value) {
    ASTNode* node = create_muts_node(name, type, value);
    node->muts_decl.is_public = 1;
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

ASTNode* create_method_call_node(ASTNode* object, char* method, ASTNodeList* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_METHOD_CALL;
    node->method_call.object = object;
    node->method_call.method = strdup(method);
    node->method_call.args = args;
    return node;
}

ASTNode* create_array_node(ASTNodeList* elements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY;
    node->array.elements = elements;
    return node;
}

ASTNode* create_array_type_node(ASTNode* element_type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_TYPE;
    node->array_type.element_type = element_type;
    return node;
}
ASTNode* create_struct_node(char* name, ASTNodeList* fields) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT;
    node->struct_def.name = strdup(name);
    node->struct_def.fields = fields;
    node->struct_def.is_public = 0;  // Ajouter cette ligne
    return node;
}

ASTNode* create_struct_init_node(char* name, ASTNodeList* fields) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT_INIT;
    node->struct_init.name = strdup(name);
    node->struct_init.fields = fields;
    return node;
}

ASTNode* create_enum_node(char* name, ASTNodeList* variants) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ENUM;
    node->enum_def.name = strdup(name);
    node->enum_def.variants = variants;
    return node;
}

ASTNode* create_impl_node(char* name, ASTNodeList* methods) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IMPL;
    node->impl.name = strdup(name);
    node->impl.methods = methods;
    return node;
}
ASTNode* create_return_struct_field_node(char* struct_name, char* field_name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN_STRUCT_FIELD;
    node->return_struct_field.struct_name = strdup(struct_name);
    node->return_struct_field.field_name = strdup(field_name);
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
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STATIC_ACCESS;
    node->static_access.object = object;
    node->static_access.member = strdup(member);
    return node;
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

ASTNode* create_type_node(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_TYPE_DEF;
    node->type_def.name = strdup(name);
    return node;
}

ASTNode* create_optional_type_node(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_OPTIONAL_TYPE;
    node->optional_type.name = strdup(name);
    return node;
}

ASTNode* create_param_node(char* name, ASTNode* type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->param.name = strdup(name);
    node->param.param_type = type;
    return node;
}

ASTNode* create_field_node(char* name, ASTNode* type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FIELD;
    node->field.name = strdup(name);
    node->field.field_type = type;
    return node;
}

ASTNode* create_field_init_node(char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FIELD_INIT;
    node->field_init.name = strdup(name);
    node->field_init.value = value;
    return node;
}

ASTNode* create_pattern_number(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PATTERN_NUMBER;
    node->pattern_number.value = value;
    return node;
}

ASTNode* create_pattern_string(char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PATTERN_STRING;
    node->pattern_string.value = strdup(value);
    return node;
}

ASTNode* create_pattern_ident(char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PATTERN_IDENT;
    node->pattern_ident.value = strdup(value);
    return node;
}

ASTNode* create_pattern_wildcard() {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PATTERN_WILDCARD;
    return node;
}
ASTNode* create_constraints_node(char* type, ASTNodeList* list) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CONSTRAINT;
    node->constraint.constraint_type = strdup(type);
    node->constraint.list = list;
    node->constraint.int_value = 0;
    return node;
}

ASTNode* merge_constraints(ASTNode* a, ASTNode* b) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CONSTRAINT_LIST;
    node->constraint_list.a = a;
    node->constraint_list.b = b;
    return node;
}
// ==================== Fonctions utilitaires ====================

void free_ast(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_MUTS:
            free(node->muts_decl.name);
            if (node->muts_decl.var_type) free_ast(node->muts_decl.var_type);
            if (node->muts_decl.value) free_ast(node->muts_decl.value);
            break;
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
            free(node->import.path);
            if (node->import.alias) free(node->import.alias);
            break;
        case NODE_FUNCTION:
        case NODE_PUBLIC_FUNCTION:
            free(node->function.name);
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
            free(node->var_decl.name);
            if (node->var_decl.var_type) free_ast(node->var_decl.var_type);
            if (node->var_decl.value) free_ast(node->var_decl.value);
            break;
        case NODE_STRING:
            free(node->string_val.value);
            break;
        case NODE_IDENTIFIER:
            free(node->identifier.name);
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
        default:
            break;
    }
    free(node);
}
