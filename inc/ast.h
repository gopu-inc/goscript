#ifndef GOSCRIPT_AST_H
#define GOSCRIPT_AST_H

typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    
    // Expressions
    NODE_LITERAL_NUMBER,
    NODE_LITERAL_STRING,
    NODE_LITERAL_BOOL,
    NODE_VARIABLE,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_GROUPING,
    
    // Instructions
    NODE_EXPRESSION_STMT,
    NODE_VARIABLE_DECL,
    NODE_ASSIGNMENT,
    NODE_PRINT_STMT,
    NODE_GETLF_STMT,
    NODE_INPUT_STMT,
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_FUNCTION_DECL,
    NODE_FUNCTION_CALL,
    NODE_RETURN_STMT
} NodeType;

typedef struct Node {
    NodeType type;
    struct Node* left;
    struct Node* right;
    struct Node* extra; // Pour les structures à 3 branches (if, for)
    
    union {
        double number_value;
        char* string_value;
        bool bool_value;
        char* identifier;
        struct {
            char op;
            struct Node* left;
            struct Node* right;
        } binary;
    } data;
} Node;

Node* create_program(Node* first_stmt);
Node* create_block(Node* statements);
Node* create_number(double value);
Node* create_string(const char* value);
Node* create_bool(bool value);
Node* create_variable(const char* name);
Node* create_binary_op(char op, Node* left, Node* right);
Node* create_unary_op(char op, Node* right);
Node* create_grouping(Node* expr);
Node* create_expression_stmt(Node* expr);
Node* create_var_decl(const char* name, Node* initializer);
Node* create_assignment(const char* name, Node* value);
Node* create_print(Node* expr);
Node* create_getlf(Node* expr);
Node* create_input(const char* prompt);
Node* create_if(Node* condition, Node* then_branch, Node* else_branch);
Node* create_while(Node* condition, Node* body);
Node* create_for(Node* initializer, Node* condition, Node* increment, Node* body);
Node* create_function(const char* name, Node* params, Node* body);
Node* create_function_call(const char* name, Node* args);
Node* create_return(Node* value);
void free_ast(Node* node);

#endif
