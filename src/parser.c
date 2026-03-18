#include "common.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"

typedef struct {
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;
} Parser;

static Parser parser;

// Forward declarations
static void advance();
static void consume(TokenType type, const char* message);
static bool match(TokenType type);
static bool check(TokenType type);
static void error_at_current(const char* message);
static void error_at_previous(const char* message);
static void synchronize();

// Expression parsing
static Node* expression();
static Node* assignment();
static Node* equality();
static Node* comparison();
static Node* term();
static Node* factor();
static Node* unary();
static Node* call();
static Node* primary();
static Node* finish_call(Node* callee);

// Declarations and statements
static Node* declaration();
static Node* function_declaration();
static Node* var_declaration();
static Node* statement();
static Node* expr_statement();
static Node* print_statement();
static Node* getlf_statement();
static Node* input_statement();
static Node* if_statement();
static Node* while_statement();
static Node* for_statement();
static Node* return_statement();
static Node* block_statement();
static Node* import_statement();

// Helper functions
static const char* token_type_to_string(TokenType type);

//------------------------------------------------------------------------------
// Lexical helpers
//------------------------------------------------------------------------------

static void advance() {
    parser.previous = parser.current;
    
    for (;;) {
        parser.current = scan_token();
        if (parser.current.type != TOKEN_ERROR) break;
        
        error_at_current(parser.current.start);
    }
}

static void consume(TokenType type, const char* message) {
    if (parser.current.type == type) {
        advance();
        return;
    }
    
    error_at_current(message);
}

static bool match(TokenType type) {
    if (!check(type)) return false;
    advance();
    return true;
}

static bool check(TokenType type) {
    return parser.current.type == type;
}

//------------------------------------------------------------------------------
// Error handling (ONLY in English, only when errors occur)
//------------------------------------------------------------------------------

static void error_at_current(const char* message) {
    if (parser.panic_mode) return;
    parser.panic_mode = true;
    
    fprintf(stderr, "Error at line %d", parser.current.line);
    
    if (parser.current.type == TOKEN_EOF) {
        fprintf(stderr, " at end of file");
    } else if (parser.current.type == TOKEN_ERROR) {
        // Nothing
    } else {
        fprintf(stderr, " at '%.*s'", parser.current.length, parser.current.start);
    }
    
    fprintf(stderr, ": %s\n", message);
    parser.had_error = true;
}

static void error_at_previous(const char* message) {
    if (parser.panic_mode) return;
    parser.panic_mode = true;
    
    fprintf(stderr, "Error at line %d", parser.previous.line);
    
    if (parser.previous.type == TOKEN_EOF) {
        fprintf(stderr, " at end of file");
    } else {
        fprintf(stderr, " at '%.*s'", parser.previous.length, parser.previous.start);
    }
    
    fprintf(stderr, ": %s\n", message);
    parser.had_error = true;
}

static void synchronize() {
    parser.panic_mode = false;
    
    while (parser.current.type != TOKEN_EOF) {
        if (parser.previous.type == TOKEN_SEMICOLON) return;
        
        switch (parser.current.type) {
            case TOKEN_FN:
            case TOKEN_LET:
            case TOKEN_CONST:
            case TOKEN_IF:
            case TOKEN_WHILE:
            case TOKEN_FOR:
            case TOKEN_PRINT:
            case TOKEN_GETLF:
            case TOKEN_RETURN:
            case TOKEN_USE:
                return;
            default:
                break;
        }
        
        advance();
    }
}

//------------------------------------------------------------------------------
// Expression parsing (with precedence)
//------------------------------------------------------------------------------

static Node* expression() {
    return assignment();
}

static Node* assignment() {
    Node* expr = equality();
    
    if (match(TOKEN_EQUAL)) {
        Node* value = assignment();
        
        if (expr->type == NODE_VARIABLE) {
            return create_assignment(expr->data.identifier, value);
        }
        
        error_at_previous("Invalid assignment target");
        return expr;
    }
    
    return expr;
}

static Node* equality() {
    Node* expr = comparison();
    
    while (match(TOKEN_BANG_EQUAL) || match(TOKEN_EQUAL_EQUAL)) {
        TokenType op = parser.previous.type;
        Node* right = comparison();
        
        if (op == TOKEN_BANG_EQUAL) {
            expr = create_binary_op('!', expr, right);
        } else {
            expr = create_binary_op('=', expr, right);
        }
    }
    
    return expr;
}

static Node* comparison() {
    Node* expr = term();
    
    while (match(TOKEN_GREATER) || match(TOKEN_GREATER_EQUAL) ||
           match(TOKEN_LESS) || match(TOKEN_LESS_EQUAL)) {
        
        TokenType op = parser.previous.type;
        Node* right = term();
        
        if (op == TOKEN_GREATER) {
            expr = create_binary_op('>', expr, right);
        } else if (op == TOKEN_GREATER_EQUAL) {
            expr = create_binary_op('g', expr, right); // g for >=
        } else if (op == TOKEN_LESS) {
            expr = create_binary_op('<', expr, right);
        } else {
            expr = create_binary_op('l', expr, right); // l for <=
        }
    }
    
    return expr;
}

static Node* term() {
    Node* expr = factor();
    
    while (match(TOKEN_MINUS) || match(TOKEN_PLUS)) {
        TokenType op = parser.previous.type;
        Node* right = factor();
        
        if (op == TOKEN_PLUS) {
            expr = create_binary_op('+', expr, right);
        } else {
            expr = create_binary_op('-', expr, right);
        }
    }
    
    return expr;
}

static Node* factor() {
    Node* expr = unary();
    
    while (match(TOKEN_SLASH) || match(TOKEN_STAR)) {
        TokenType op = parser.previous.type;
        Node* right = unary();
        
        if (op == TOKEN_STAR) {
            expr = create_binary_op('*', expr, right);
        } else {
            expr = create_binary_op('/', expr, right);
        }
    }
    
    return expr;
}

static Node* unary() {
    if (match(TOKEN_BANG) || match(TOKEN_MINUS)) {
        TokenType op = parser.previous.type;
        Node* right = unary();
        
        if (op == TOKEN_BANG) {
            return create_unary_op('!', right);
        } else {
            return create_unary_op('-', right);
        }
    }
    
    return call();
}

static Node* call() {
    Node* expr = primary();
    
    while (true) {
        if (match(TOKEN_LPAREN)) {
            expr = finish_call(expr);
        } else {
            break;
        }
    }
    
    return expr;
}

static Node* finish_call(Node* callee) {
    Node* args = NULL;
    Node* current = NULL;
    
    if (!check(TOKEN_RPAREN)) {
        do {
            Node* arg = expression();
            
            if (!args) {
                args = arg;
                current = arg;
            } else {
                current->right = arg;
                current = arg;
            }
        } while (match(TOKEN_COMMA));
    }
    
    consume(TOKEN_RPAREN, "Expected ')' after arguments.");
    
    // Create call node - callee should be a variable node
    if (callee->type == NODE_VARIABLE) {
        return create_function_call(callee->data.identifier, args);
    } else {
        error_at_previous("Can only call functions");
        return create_number(0);
    }
}

static Node* primary() {
    if (match(TOKEN_FALSE)) return create_bool(false);
    if (match(TOKEN_TRUE)) return create_bool(true);
    if (match(TOKEN_NIL)) return create_number(0); // nil = 0 for now
    
    if (match(TOKEN_NUMBER)) {
        double value = strtod(parser.previous.start, NULL);
        return create_number(value);
    }
    
    if (match(TOKEN_STRING)) {
        char* str = (char*)allocate(parser.previous.length + 1);
        memcpy(str, parser.previous.start, parser.previous.length);
        str[parser.previous.length] = '\0';
        return create_string(str);
    }
    
    if (match(TOKEN_IDENTIFIER)) {
        char* name = (char*)allocate(parser.previous.length + 1);
        memcpy(name, parser.previous.start, parser.previous.length);
        name[parser.previous.length] = '\0';
        return create_variable(name);
    }
    
    if (match(TOKEN_LPAREN)) {
        Node* expr = expression();
        consume(TOKEN_RPAREN, "Expected ')' after expression.");
        return create_grouping(expr);
    }
    
    error_at_current("Expected expression");
    return create_number(0);
}

//------------------------------------------------------------------------------
// Statement parsing
//------------------------------------------------------------------------------

static Node* statement() {
    if (match(TOKEN_PRINT)) return print_statement();
    if (match(TOKEN_GETLF)) return getlf_statement();
    if (match(TOKEN_INPUT)) return input_statement();
    if (match(TOKEN_IF)) return if_statement();
    if (match(TOKEN_WHILE)) return while_statement();
    if (match(TOKEN_FOR)) return for_statement();
    if (match(TOKEN_RETURN)) return return_statement();
    if (match(TOKEN_USE)) return import_statement();
    if (match(TOKEN_LBRACE)) return block_statement();
    
    return expr_statement();
}

static Node* expr_statement() {
    Node* expr = expression();
    consume(TOKEN_SEMICOLON, "Expected ';' after expression.");
    return create_expression_stmt(expr);
}

static Node* print_statement() {
    consume(TOKEN_LPAREN, "Expected '(' after 'print'.");
    Node* expr = expression();
    consume(TOKEN_RPAREN, "Expected ')' after value to print.");
    consume(TOKEN_SEMICOLON, "Expected ';' after 'print'.");
    return create_print(expr);
}

static Node* getlf_statement() {
    consume(TOKEN_LPAREN, "Expected '(' after 'getlf'.");
    Node* expr = expression();
    consume(TOKEN_RPAREN, "Expected ')' after value.");
    consume(TOKEN_SEMICOLON, "Expected ';' after 'getlf'.");
    return create_getlf(expr);
}

static Node* input_statement() {
    Node* prompt = NULL;
    
    if (match(TOKEN_LPAREN)) {
        if (!check(TOKEN_RPAREN)) {
            prompt = expression();
        }
        consume(TOKEN_RPAREN, "Expected ')' after prompt.");
    }
    
    consume(TOKEN_SEMICOLON, "Expected ';' after 'input'.");
    return create_input(prompt ? prompt->data.string_value : NULL);
}

static Node* if_statement() {
    consume(TOKEN_LPAREN, "Expected '(' after 'if'.");
    Node* condition = expression();
    consume(TOKEN_RPAREN, "Expected ')' after condition.");
    
    Node* then_branch = statement();
    Node* else_branch = NULL;
    
    if (match(TOKEN_ELSE)) {
        else_branch = statement();
    }
    
    return create_if(condition, then_branch, else_branch);
}

static Node* while_statement() {
    consume(TOKEN_LPAREN, "Expected '(' after 'while'.");
    Node* condition = expression();
    consume(TOKEN_RPAREN, "Expected ')' after condition.");
    
    Node* body = statement();
    
    return create_while(condition, body);
}

static Node* for_statement() {
    consume(TOKEN_LPAREN, "Expected '(' after 'for'.");
    
    // Initializer
    Node* initializer = NULL;
    if (match(TOKEN_SEMICOLON)) {
        // No initializer
    } else if (match(TOKEN_LET)) {
        initializer = var_declaration();
    } else {
        initializer = expr_statement();
    }
    
    // Condition
    Node* condition = NULL;
    if (!check(TOKEN_SEMICOLON)) {
        condition = expression();
    }
    consume(TOKEN_SEMICOLON, "Expected ';' after loop condition.");
    
    // Increment
    Node* increment = NULL;
    if (!check(TOKEN_RPAREN)) {
        increment = expression();
    }
    consume(TOKEN_RPAREN, "Expected ')' after for clauses.");
    
    Node* body = statement();
    
    return create_for(initializer, condition, increment, body);
}

static Node* return_statement() {
    Node* value = NULL;
    
    if (!check(TOKEN_SEMICOLON)) {
        value = expression();
    }
    
    consume(TOKEN_SEMICOLON, "Expected ';' after return value.");
    return create_return(value);
}

static Node* block_statement() {
    Node* statements = NULL;
    Node* current = NULL;
    
    while (!check(TOKEN_RBRACE) && !check(TOKEN_EOF)) {
        Node* stmt = declaration();
        
        if (stmt) {
            if (!statements) {
                statements = stmt;
                current = stmt;
            } else {
                current->right = stmt;
                current = stmt;
            }
        }
    }
    
    consume(TOKEN_RBRACE, "Expected '}' after block.");
    return create_block(statements);
}

static Node* import_statement() {
    consume(TOKEN_IDENTIFIER, "Expected module name after 'use'.");
    consume(TOKEN_SEMICOLON, "Expected ';' after module name.");
    
    // For now, just return a no-op
    return create_expression_stmt(create_number(0));
}

//------------------------------------------------------------------------------
// Declaration parsing
//------------------------------------------------------------------------------

static Node* declaration() {
    if (match(TOKEN_FN)) return function_declaration();
    if (match(TOKEN_LET)) return var_declaration();
    
    return statement();
}

static Node* function_declaration() {
    consume(TOKEN_IDENTIFIER, "Expected function name.");
    
    char* name = (char*)allocate(parser.previous.length + 1);
    memcpy(name, parser.previous.start, parser.previous.length);
    name[parser.previous.length] = '\0';
    
    consume(TOKEN_LPAREN, "Expected '(' after function name.");
    
    // Parameters
    Node* params = NULL;
    Node* current_param = NULL;
    
    if (!check(TOKEN_RPAREN)) {
        do {
            consume(TOKEN_IDENTIFIER, "Expected parameter name.");
            
            char* param_name = (char*)allocate(parser.previous.length + 1);
            memcpy(param_name, parser.previous.start, parser.previous.length);
            param_name[parser.previous.length] = '\0';
            
            Node* param = create_variable(param_name);
            
            if (!params) {
                params = param;
                current_param = param;
            } else {
                current_param->right = param;
                current_param = param;
            }
        } while (match(TOKEN_COMMA));
    }
    
    consume(TOKEN_RPAREN, "Expected ')' after parameters.");
    consume(TOKEN_LBRACE, "Expected '{' before function body.");
    
    Node* body = block_statement();
    
    return create_function(name, params, body);
}

static Node* var_declaration() {
    consume(TOKEN_IDENTIFIER, "Expected variable name.");
    
    char* name = (char*)allocate(parser.previous.length + 1);
    memcpy(name, parser.previous.start, parser.previous.length);
    name[parser.previous.length] = '\0';
    
    Node* initializer = NULL;
    if (match(TOKEN_EQUAL)) {
        initializer = expression();
    }
    
    consume(TOKEN_SEMICOLON, "Expected ';' after variable declaration.");
    return create_var_decl(name, initializer);
}

//------------------------------------------------------------------------------
// Main parse function
//------------------------------------------------------------------------------

Node* parse(void) {
    parser.had_error = false;
    parser.panic_mode = false;
    
    advance();
    
    Node* statements = NULL;
    Node* current = NULL;
    
    while (!check(TOKEN_EOF)) {
        Node* stmt = declaration();
        
        if (stmt) {
            if (!statements) {
                statements = stmt;
                current = stmt;
            } else {
                current->right = stmt;
                current = stmt;
            }
        }
        
        if (parser.panic_mode) synchronize();
    }
    
    // Only print error summary if there were errors
    if (parser.had_error) {
        fprintf(stderr, "Parsing failed with errors.\n");
        free_ast(statements);
        return NULL;
    }
    
    return create_program(statements);
}
