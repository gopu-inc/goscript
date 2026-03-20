#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_PROGRAM,
    NODE_IMPORT,
    NODE_PACKET,
    NODE_FUNCTION,
    NODE_LET,
    NODE_CONST,
    NODE_IF,
    NODE_FOR,
    NODE_WHILE,
    NODE_LOOP,
    NODE_MATCH,
    NODE_RETURN,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_NUMBER,
    NODE_FLOAT,
    NODE_STRING,
    NODE_BOOL,
    NODE_IDENTIFIER,
    NODE_CALL,
    NODE_ARRAY,
    NODE_STRUCT,
    NODE_ENUM,
    NODE_EXPR_STMT,
    NODE_MEMBER_ACCESS,
    NODE_NIL
} NodeType;

typedef enum {
    OP_ADD = 1,
    OP_SUB = 2,
    OP_MUL = 3,
    OP_DIV = 4,
    OP_EQ = 5,
    OP_NEQ = 6,
    OP_LT = 7,
    OP_GT = 8,
    OP_AND = 9,
    OP_OR = 10,
    OP_NOT = 11,
    OP_NEG = 12,
    OP_ASSIGN = 13
} Operator;

typedef struct ASTNodeList {
    struct ASTNode** nodes;
    int count;
    int capacity;
} ASTNodeList;

typedef struct ASTNode {
    NodeType type;
    int line;
    union {
        struct {
            ASTNodeList* statements;
        } program;
        struct {
            char* path;
            char* alias;
        } import;
        struct {
            char* name;
            ASTNodeList* statements;
        } packet;
        struct {
            char* name;
            ASTNodeList* params;
            struct ASTNode* return_type;
            ASTNodeList* body;
            int is_main;
        } function;
        struct {
            char* name;
            struct ASTNode* type;
            struct ASTNode* value;
        } var_decl;
        struct {
            struct ASTNode* condition;
            ASTNodeList* then_branch;
            ASTNodeList* else_branch;
        } if_stmt;
        struct {
            char* var;
            struct ASTNode* start;
            struct ASTNode* end;
            ASTNodeList* body;
        } for_range;
        struct {
            struct ASTNode* condition;
            ASTNodeList* body;
        } while_stmt;
        struct {
            ASTNodeList* body;
        } loop_stmt;
        struct {
            struct ASTNode* value;
            ASTNodeList* cases;
        } match_stmt;
        struct {
            struct ASTNode* value;
        } return_stmt;
        struct {
            Operator op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binary;
        struct {
            Operator op;
            struct ASTNode* operand;
        } unary;
        struct {
            int value;
        } number;
        struct {
            double value;
        } float_val;
        struct {
            char* value;
        } string_val;
        struct {
            int value;
        } bool_val;
        struct {
            char* name;
        } identifier;
        struct {
            struct ASTNode* callee;
            ASTNodeList* args;
        } call;
        struct {
            ASTNodeList* elements;
        } array;
        struct {
            char* name;
            ASTNodeList* fields;
        } struct_def;
        struct {
            char* name;
            ASTNodeList* variants;
        } enum_def;
        struct {
            struct ASTNode* expr;
        } expr_stmt;
        struct {
            struct ASTNode* object;
            char* member;
        } member;
    };
} ASTNode;

// List functions
ASTNodeList* create_node_list(void);
void add_to_node_list(ASTNodeList* list, ASTNode* node);
ASTNodeList* create_arg_list(void);
void add_arg(ASTNodeList* list, ASTNode* arg);

// Node creation functions
ASTNode* create_program_node(ASTNodeList* statements);
ASTNode* create_import_node(char* path, char* alias);
ASTNode* create_packet_import_node(char* path);
ASTNode* create_packet_node(char* name, ASTNodeList* statements);
ASTNode* create_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body);
ASTNode* create_main_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body);
ASTNode* create_let_node(char* name, ASTNode* type, ASTNode* value);
ASTNode* create_const_node(char* name, ASTNode* value);
ASTNode* create_if_node(ASTNode* condition, ASTNodeList* then_branch, ASTNodeList* else_branch);
ASTNode* create_while_node(ASTNode* condition, ASTNodeList* body);
ASTNode* create_loop_node(ASTNodeList* body);
ASTNode* create_return_node(ASTNode* value);
ASTNode* create_expr_statement(ASTNode* expr);
ASTNode* create_binary_op(ASTNode* left, Operator op, ASTNode* right);
ASTNode* create_unary_op(Operator op, ASTNode* operand);
ASTNode* create_number_node(int value);
ASTNode* create_float_node(double value);
ASTNode* create_string_node(char* value);
ASTNode* create_bool_node(int value);
ASTNode* create_nil_node(void);
ASTNode* create_identifier_node(char* name);
ASTNode* create_call_node(ASTNode* callee, ASTNodeList* args);
ASTNode* create_member_access(ASTNode* object, char* member);
ASTNode* create_static_access(ASTNode* object, char* member);
ASTNode* create_array_node(ASTNodeList* elements);
ASTNode* create_struct_node(char* name, ASTNodeList* fields);
ASTNode* create_enum_node(char* name, ASTNodeList* variants);
ASTNode* create_struct_init_node(char* name, ASTNodeList* fields);
ASTNode* create_for_node(ASTNode* init, ASTNode* cond, ASTNode* inc, ASTNodeList* body);
ASTNode* create_assign_node(ASTNode* left, ASTNode* right);

// Free function
void free_ast(ASTNode* node);

#endif
