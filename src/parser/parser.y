%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;
extern char* yytext;

void yyerror(const char* msg);
int yylex(void);

ASTNode* program_root;
%}

%union {
    int number;
    double float_val;
    char* string;
    struct ASTNode* node;
    struct ASTNodeList* node_list;
}

/* Tokens */
%token TOKEN_FN TOKEN_LET TOKEN_CONST TOKEN_RETURN
%token TOKEN_IF TOKEN_ELSE
%token TOKEN_FOR TOKEN_WHILE TOKEN_LOOP TOKEN_BREAK
%token TOKEN_IMPORT TOKEN_PACKET
%token TOKEN_NIL TOKEN_TRUE TOKEN_FALSE

/* Operators */
%token TOKEN_PLUS TOKEN_MINUS TOKEN_MULTIPLY TOKEN_DIVIDE
%token TOKEN_ASSIGN TOKEN_EQ TOKEN_NEQ TOKEN_LT TOKEN_LTE TOKEN_GT TOKEN_GTE
%token TOKEN_AND TOKEN_OR TOKEN_NOT
%token TOKEN_COLON TOKEN_SEMICOLON TOKEN_COMMA TOKEN_DOT

/* Delimiters */
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_LBRACE TOKEN_RBRACE
%token TOKEN_LBRACKET TOKEN_RBRACKET

/* Types */
%token <string> TOKEN_IDENTIFIER
%token <number> TOKEN_NUMBER
%token <float_val> TOKEN_FLOAT
%token <string> TOKEN_STRING

/* Non-terminals */
%type <node> program statement expression
%type <node> function_decl let_decl const_decl return_statement
%type <node> if_statement for_statement while_statement loop_statement
%type <node> import_statement
%type <node> binary_expr unary_expr primary_expr call_expr
%type <node_list> statement_list argument_list param_list

%start program

%%

program:
    statement_list {
        program_root = create_program_node($1);
    }
    ;

statement_list:
    statement {
        $$ = create_node_list();
        add_to_node_list($$, $1);
    }
    | statement_list statement {
        add_to_node_list($1, $2);
        $$ = $1;
    }
    ;

statement:
    import_statement
    | function_decl
    | let_decl
    | const_decl
    | if_statement
    | for_statement
    | while_statement
    | loop_statement
    | return_statement
    | expression opt_semicolon {
        $$ = create_expr_statement($1);
    }
    ;

opt_semicolon:
    /* empty */
    | TOKEN_SEMICOLON
    ;

import_statement:
    TOKEN_IMPORT TOKEN_IDENTIFIER opt_semicolon {
        $$ = create_import_node($2, NULL);
    }
    ;

function_decl:
    TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_function_node($2, $4, NULL, $7);
    }
    ;

param_list:
    /* empty */ {
        $$ = NULL;
    }
    | TOKEN_IDENTIFIER {
        $$ = create_node_list();
        add_to_node_list($$, create_identifier_node($1));
    }
    | param_list TOKEN_COMMA TOKEN_IDENTIFIER {
        add_to_node_list($1, create_identifier_node($3));
        $$ = $1;
    }
    ;

let_decl:
    TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression opt_semicolon {
        $$ = create_let_node($2, NULL, $4);
    }
    ;

const_decl:
    TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression opt_semicolon {
        $$ = create_const_node($2, $4);
    }
    ;

if_statement:
    TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_if_node($2, $4, NULL);
    }
    | TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_if_node($2, $4, $8);
    }
    ;

for_statement:
    TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_while_node($2, $4);
    }
    ;

while_statement:
    TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_while_node($2, $4);
    }
    ;

loop_statement:
    TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_loop_node($3);
    }
    ;

return_statement:
    TOKEN_RETURN expression opt_semicolon {
        $$ = create_return_node($2);
    }
    | TOKEN_RETURN opt_semicolon {
        $$ = create_return_node(NULL);
    }
    ;

expression:
    binary_expr
    | unary_expr
    | primary_expr
    ;

binary_expr:
    expression TOKEN_PLUS expression {
        $$ = create_binary_op($1, OP_ADD, $3);
    }
    | expression TOKEN_MINUS expression {
        $$ = create_binary_op($1, OP_SUB, $3);
    }
    | expression TOKEN_MULTIPLY expression {
        $$ = create_binary_op($1, OP_MUL, $3);
    }
    | expression TOKEN_DIVIDE expression {
        $$ = create_binary_op($1, OP_DIV, $3);
    }
    | expression TOKEN_EQ expression {
        $$ = create_binary_op($1, OP_EQ, $3);
    }
    | expression TOKEN_NEQ expression {
        $$ = create_binary_op($1, OP_NEQ, $3);
    }
    | expression TOKEN_LT expression {
        $$ = create_binary_op($1, OP_LT, $3);
    }
    | expression TOKEN_GT expression {
        $$ = create_binary_op($1, OP_GT, $3);
    }
    | expression TOKEN_AND expression {
        $$ = create_binary_op($1, OP_AND, $3);
    }
    | expression TOKEN_OR expression {
        $$ = create_binary_op($1, OP_OR, $3);
    }
    ;

unary_expr:
    TOKEN_NOT expression {
        $$ = create_unary_op(OP_NOT, $2);
    }
    | TOKEN_MINUS expression {
        $$ = create_unary_op(OP_NEG, $2);
    }
    ;

primary_expr:
    TOKEN_NUMBER {
        $$ = create_number_node($1);
    }
    | TOKEN_FLOAT {
        $$ = create_float_node($1);
    }
    | TOKEN_STRING {
        $$ = create_string_node($1);
    }
    | TOKEN_TRUE {
        $$ = create_bool_node(1);
    }
    | TOKEN_FALSE {
        $$ = create_bool_node(0);
    }
    | TOKEN_NIL {
        $$ = create_nil_node();
    }
    | TOKEN_IDENTIFIER {
        $$ = create_identifier_node($1);
    }
    | TOKEN_LPAREN expression TOKEN_RPAREN {
        $$ = $2;
    }
    | call_expr
    ;

call_expr:
    TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN {
        ASTNode* callee = create_identifier_node($1);
        $$ = create_call_node(callee, $3);
    }
    ;

argument_list:
    /* empty */ {
        $$ = NULL;
    }
    | expression {
        $$ = create_arg_list();
        add_arg($$, $1);
    }
    | argument_list TOKEN_COMMA expression {
        add_arg($1, $3);
        $$ = $1;
    }
    ;

%%

void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}
