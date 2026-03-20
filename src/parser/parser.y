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
%token TOKEN_FOR TOKEN_WHILE TOKEN_LOOP TOKEN_BREAK TOKEN_CONTINUE
%token TOKEN_IMPORT TOKEN_EXPORT TOKEN_PACKET
%token TOKEN_STRUCT TOKEN_ENUM TOKEN_IMPL TOKEN_MATCH TOKEN_TYPE
%token TOKEN_TRUE TOKEN_FALSE TOKEN_NIL
%token TOKEN_AS TOKEN_IN TOKEN_FROM TOKEN_PUB
%token TOKEN_UNDERSCORE

/* Operators */
%token TOKEN_PLUS TOKEN_MINUS TOKEN_MULTIPLY TOKEN_DIVIDE TOKEN_MODULO
%token TOKEN_ASSIGN TOKEN_PLUS_ASSIGN TOKEN_MINUS_ASSIGN
%token TOKEN_MULTIPLY_ASSIGN TOKEN_DIVIDE_ASSIGN TOKEN_MODULO_ASSIGN
%token TOKEN_EQ TOKEN_NEQ TOKEN_LT TOKEN_LTE TOKEN_GT TOKEN_GTE
%token TOKEN_AND TOKEN_OR TOKEN_NOT
%token TOKEN_AMP TOKEN_PIPE TOKEN_XOR TOKEN_LSHIFT TOKEN_RSHIFT
%token TOKEN_DOUBLE_COLON TOKEN_DOT
%token TOKEN_COLON TOKEN_SEMICOLON TOKEN_COMMA
%token TOKEN_ARROW TOKEN_FAT_ARROW TOKEN_PIPE_FORWARD
%token TOKEN_OPTIONAL TOKEN_COALESCE
%token TOKEN_RANGE TOKEN_RANGE_INC

/* Delimiters */
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_LBRACE TOKEN_RBRACE
%token TOKEN_LBRACKET TOKEN_RBRACKET

/* Types */
%token <string> TOKEN_IDENTIFIER
%token <number> TOKEN_NUMBER
%token <float_val> TOKEN_FLOAT
%token <string> TOKEN_STRING

/* Non-terminals */
%type <node> program statement expression block
%type <node> function_decl let_decl const_decl return_statement
%type <node> if_statement for_statement while_statement loop_statement
%type <node> import_statement export_statement packet_decl
%type <node> struct_decl enum_decl impl_decl match_statement
%type <node> binary_expr unary_expr primary_expr call_expr
%type <node> array_expr struct_expr
%type <node> param type return_type
%type <node_list> statement_list argument_list param_list struct_fields enum_variants array_items match_cases function_decl_list struct_init_fields

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
    | export_statement
    | packet_decl
    | function_decl
    | struct_decl
    | enum_decl
    | impl_decl
    | let_decl
    | const_decl
    | if_statement
    | for_statement
    | while_statement
    | loop_statement
    | match_statement
    | return_statement
    | expression {
        $$ = create_expr_statement($1);
    }
    ;

import_statement:
    TOKEN_IMPORT TOKEN_IDENTIFIER {
        $$ = create_import_node($2, NULL);
    }
    | TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_STRING {
        $$ = create_import_node($4, $2);
    }
    ;

export_statement:
    TOKEN_EXPORT TOKEN_IDENTIFIER {
        $$ = create_export_node($2);
    }
    ;

packet_decl:
    TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_packet_node($2, $4);
    }
    ;

function_decl:
    TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_function_node($2, $4, $6, $8);
    }
    | TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_public_function_node($3, $5, $7, $9);
    }
    ;

param_list:
    /* empty */ {
        $$ = NULL;
    }
    | param {
        $$ = create_node_list();
        add_to_node_list($$, $1);
    }
    | param_list TOKEN_COMMA param {
        add_to_node_list($1, $3);
        $$ = $1;
    }
    ;

param:
    TOKEN_IDENTIFIER {
        $$ = create_identifier_node($1);
    }
    | TOKEN_IDENTIFIER TOKEN_COLON type {
        $$ = create_param_node($1, $3);
    }
    ;

type:
    TOKEN_IDENTIFIER {
        $$ = create_type_node($1);
    }
    | TOKEN_IDENTIFIER TOKEN_OPTIONAL {
        $$ = create_optional_type_node($1);
    }
    | TOKEN_LBRACKET TOKEN_RBRACKET type {
        $$ = create_array_type_node($3);
    }
    ;

return_type:
    /* empty */ {
        $$ = NULL;
    }
    | TOKEN_COLON type {
        $$ = $2;
    }
    ;

let_decl:
    TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
        $$ = create_let_node($2, NULL, $4);
    }
    | TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression {
        $$ = create_let_node($2, $4, $6);
    }
    ;

const_decl:
    TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
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
    | TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_for_range_node($2, $4, $6, $8);
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

match_statement:
    TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE {
        $$ = create_match_node($2, $4);
    }
    ;

match_cases:
    match_case {
        $$ = create_node_list();
        add_to_node_list($$, $1);
    }
    | match_cases match_case {
        add_to_node_list($1, $2);
        $$ = $1;
    }
    ;

match_case:
    pattern TOKEN_FAT_ARROW expression {
        $$ = create_match_case_node($1, $3);
    }
    ;

pattern:
    TOKEN_NUMBER {
        $$ = create_pattern_number($1);
    }
    | TOKEN_STRING {
        $$ = create_pattern_string($1);
    }
    | TOKEN_IDENTIFIER {
        $$ = create_pattern_ident($1);
    }
    | TOKEN_UNDERSCORE {
        $$ = create_pattern_wildcard();
    }
    ;

struct_decl:
    TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE {
        $$ = create_struct_node($2, $4);
    }
    ;

struct_fields:
    /* empty */ {
        $$ = NULL;
    }
    | struct_field {
        $$ = create_node_list();
        add_to_node_list($$, $1);
    }
    | struct_fields struct_field {
        add_to_node_list($1, $2);
        $$ = $1;
    }
    ;

struct_field:
    TOKEN_IDENTIFIER TOKEN_COLON type {
        $$ = create_field_node($1, $3);
    }
    ;

enum_decl:
    TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE {
        $$ = create_enum_node($2, $4);
    }
    ;

enum_variants:
    /* empty */ {
        $$ = NULL;
    }
    | TOKEN_IDENTIFIER {
        $$ = create_node_list();
        add_to_node_list($$, create_identifier_node($1));
    }
    | enum_variants TOKEN_COMMA TOKEN_IDENTIFIER {
        add_to_node_list($1, create_identifier_node($3));
        $$ = $1;
    }
    ;

impl_decl:
    TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE {
        $$ = create_impl_node($2, $4);
    }
    ;

function_decl_list:
    /* empty */ {
        $$ = NULL;
    }
    | function_decl {
        $$ = create_node_list();
        add_to_node_list($$, $1);
    }
    | function_decl_list function_decl {
        add_to_node_list($1, $2);
        $$ = $1;
    }
    ;

return_statement:
    TOKEN_RETURN expression {
        $$ = create_return_node($2);
    }
    | TOKEN_RETURN {
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
    | expression TOKEN_MODULO expression {
        $$ = create_binary_op($1, OP_MOD, $3);
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
    | expression TOKEN_LTE expression {
        $$ = create_binary_op($1, OP_LTE, $3);
    }
    | expression TOKEN_GT expression {
        $$ = create_binary_op($1, OP_GT, $3);
    }
    | expression TOKEN_GTE expression {
        $$ = create_binary_op($1, OP_GTE, $3);
    }
    | expression TOKEN_AND expression {
        $$ = create_binary_op($1, OP_AND, $3);
    }
    | expression TOKEN_OR expression {
        $$ = create_binary_op($1, OP_OR, $3);
    }
    | expression TOKEN_ASSIGN expression {
        $$ = create_assign_node($1, $3);
    }
    | expression TOKEN_PLUS_ASSIGN expression {
        $$ = create_assign_op_node($1, OP_ADD_ASSIGN, $3);
    }
    | expression TOKEN_MINUS_ASSIGN expression {
        $$ = create_assign_op_node($1, OP_SUB_ASSIGN, $3);
    }
    | expression TOKEN_MULTIPLY_ASSIGN expression {
        $$ = create_assign_op_node($1, OP_MUL_ASSIGN, $3);
    }
    | expression TOKEN_DIVIDE_ASSIGN expression {
        $$ = create_assign_op_node($1, OP_DIV_ASSIGN, $3);
    }
    | expression TOKEN_MODULO_ASSIGN expression {
        $$ = create_assign_op_node($1, OP_MOD_ASSIGN, $3);
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
    | array_expr
    | struct_expr
    ;

call_expr:
    primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN {
        $$ = create_call_node($1, $3);
    }
    | primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN {
        $$ = create_method_call_node($1, $3, $5);
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

array_expr:
    TOKEN_LBRACKET array_items TOKEN_RBRACKET {
        $$ = create_array_node($2);
    }
    ;

array_items:
    /* empty */ {
        $$ = NULL;
    }
    | expression {
        $$ = create_node_list();
        add_to_node_list($$, $1);
    }
    | array_items TOKEN_COMMA expression {
        add_to_node_list($1, $3);
        $$ = $1;
    }
    ;

struct_expr:
    TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE {
        $$ = create_struct_init_node($1, $3);
    }
    ;

struct_init_fields:
    /* empty */ {
        $$ = NULL;
    }
    | TOKEN_IDENTIFIER TOKEN_COLON expression {
        $$ = create_node_list();
        add_to_node_list($$, create_field_init_node($1, $3));
    }
    | struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression {
        add_to_node_list($1, create_field_init_node($3, $5));
        $$ = $1;
    }
    ;

block:
    TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = (ASTNode*)$2;
    }
    ;

%%

void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}
