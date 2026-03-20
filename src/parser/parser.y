%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;
extern char* yytext;

void yyerror(const char* msg);
int yylex();

ASTNode* program_root;
%}

%union {
    int number;
    double float_val;
    char* string;
    ASTNode* node;
    ASTNodeList* node_list;
}

/* Tokens */
%token TOKEN_FN TOKEN_LET TOKEN_CONST TOKEN_RETURN
%token TOKEN_IF TOKEN_ELSE TOKEN_ELSEIF TOKEN_THEN
%token TOKEN_FOR TOKEN_WHILE TOKEN_LOOP TOKEN_BREAK TOKEN_CONTINUE
%token TOKEN_MATCH TOKEN_STRUCT TOKEN_ENUM TOKEN_IMPL
%token TOKEN_IMPORT TOKEN_PACKET TOKEN_EXPORT TOKEN_TYPE
%token TOKEN_GO TOKEN_CHAN TOKEN_SELECT
%token TOKEN_TRY TOKEN_CATCH TOKEN_FINALLY
%token TOKEN_NIL TOKEN_TRUE TOKEN_FALSE TOKEN_WHERE TOKEN_AS

/* Opérateurs */
%token TOKEN_PLUS TOKEN_MINUS TOKEN_MULTIPLY TOKEN_DIVIDE TOKEN_MODULO
%token TOKEN_ASSIGN TOKEN_EQ TOKEN_NEQ TOKEN_LT TOKEN_LTE TOKEN_GT TOKEN_GTE
%token TOKEN_AND TOKEN_OR TOKEN_NOT TOKEN_AMP TOKEN_PIPE
%token TOKEN_ARROW TOKEN_FAT_ARROW TOKEN_RANGE TOKEN_RANGE_INC
%token TOKEN_COALESCE TOKEN_OPTIONAL TOKEN_BANG
%token TOKEN_COLON TOKEN_SEMICOLON TOKEN_COMMA TOKEN_DOT TOKEN_DOUBLE_COLON
%token TOKEN_PIPE_FORWARD

/* Délimiteurs */
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_LBRACE TOKEN_RBRACE
%token TOKEN_LBRACKET TOKEN_RBRACKET

/* Types */
%token <string> TOKEN_IDENTIFIER
%token <number> TOKEN_NUMBER
%token <float_val> TOKEN_FLOAT
%token <string> TOKEN_STRING

/* Types non-terminaux */
%type <node> program statement expression block if_statement
%type <node> for_statement while_statement loop_statement
%type <node> match_statement match_case struct_decl enum_decl
%type <node> import_statement packet_decl function_decl
%type <node> let_decl const_decl return_statement
%type <node> binary_expr unary_expr primary_expr call_expr
%type <node> array_expr struct_expr
%type <node_list> statement_list import_list match_cases

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
    | packet_decl
    | function_decl
    | struct_decl
    | enum_decl
    | let_decl
    | const_decl
    | if_statement
    | for_statement
    | while_statement
    | loop_statement
    | match_statement
    | return_statement
    | expression TOKEN_SEMICOLON {
        $$ = create_expr_statement($1);
    }
    ;

/* Imports sans guillemets */
import_statement:
    TOKEN_IMPORT TOKEN_IDENTIFIER {
        $$ = create_import_node($2, NULL);
    }
    | TOKEN_IMPORT TOKEN_DOT TOKEN_IDENTIFIER {
        char* path = malloc(strlen($3) + 3);
        sprintf(path, "./%s", $3);
        $$ = create_import_node(path, NULL);
        free(path);
    }
    | TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_IDENTIFIER {
        $$ = create_import_node($4, $2);
    }
    | TOKEN_IMPORT TOKEN_PACKET TOKEN_IDENTIFIER {
        $$ = create_packet_import_node($3);
    }
    | TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_IF expression {
        $$ = create_conditional_import_node($2, $4);
    }
    ;

packet_decl:
    TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_packet_node($2, $4);
    }
    | TOKEN_PACKET TOKEN_IDENTIFIER {
        $$ = create_packet_node($2, NULL);
    }
    ;

function_decl:
    TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_function_node($2, $4, $6, $8);
    }
    | TOKEN_FN TOKEN_AT TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_main_function_node($3, $5, $7, $9);
    }
    ;

param_list:
    /* empty */ {
        $$ = NULL;
    }
    | param {
        $$ = create_param_list();
        add_param($$, $1);
    }
    | param_list TOKEN_COMMA param {
        add_param($1, $3);
        $$ = $1;
    }
    ;

param:
    TOKEN_IDENTIFIER TOKEN_COLON type {
        $$ = create_param_node($1, $3);
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

type:
    TOKEN_IDENTIFIER {
        $$ = create_type_node($1);
    }
    | TOKEN_IDENTIFIER TOKEN_OPTIONAL {
        char* type_name = malloc(strlen($1) + 2);
        sprintf(type_name, "%s?", $1);
        $$ = create_type_node(type_name);
        free(type_name);
    }
    | TOKEN_LBRACKET TOKEN_RBRACKET type {
        $$ = create_array_type_node($3);
    }
    | TOKEN_CHAN type {
        $$ = create_chan_type_node($2);
    }
    ;

let_decl:
    TOKEN_LET TOKEN_IDENTIFIER type_opt TOKEN_ASSIGN expression {
        $$ = create_let_node($2, $3, $5);
    }
    | TOKEN_LET TOKEN_IDENTIFIER type_opt {
        $$ = create_let_node($2, $3, NULL);
    }
    ;

const_decl:
    TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
        $$ = create_const_node($2, $4);
    }
    ;

type_opt:
    /* empty */ { $$ = NULL; }
    | TOKEN_COLON type { $$ = $2; }
    ;

if_statement:
    TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE else_clause {
        $$ = create_if_node($2, $4, $6);
    }
    | TOKEN_IF expression TOKEN_THEN statement TOKEN_ELSE statement {
        $$ = create_if_node($2, $4, $6);
    }
    ;

else_clause:
    /* empty */ { $$ = NULL; }
    | TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = $3;
    }
    | TOKEN_ELSEIF expression TOKEN_LBRACE statement_list TOKEN_RBRACE else_clause {
        $$ = create_elseif_node($2, $4, $6);
    }
    ;

for_statement:
    TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_for_range_node($2, $4, $6, $8);
    }
    | TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_for_cond_node($2, $4);
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
        $$ = create_case_list();
        add_case($$, $1);
    }
    | match_cases match_case {
        add_case($1, $2);
        $$ = $1;
    }
    ;

match_case:
    pattern TOKEN_FAT_ARROW expression TOKEN_COMMA {
        $$ = create_match_case_node($1, $3);
    }
    | pattern TOKEN_FAT_ARROW TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_match_case_node($1, $4);
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
    | TOKEN_IDENTIFIER TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER {
        $$ = create_pattern_enum($1, $3);
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
    /* empty */ { $$ = NULL; }
    | struct_field {
        $$ = create_field_list();
        add_field($$, $1);
    }
    | struct_fields struct_field {
        add_field($1, $2);
        $$ = $1;
    }
    ;

struct_field:
    TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_COMMA {
        $$ = create_field_node($1, $3);
    }
    ;

enum_decl:
    TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE {
        $$ = create_enum_node($2, $4);
    }
    ;

enum_variants:
    /* empty */ { $$ = NULL; }
    | enum_variant {
        $$ = create_variant_list();
        add_variant($$, $1);
    }
    | enum_variants enum_variant {
        add_variant($1, $2);
        $$ = $1;
    }
    ;

enum_variant:
    TOKEN_IDENTIFIER TOKEN_COMMA {
        $$ = create_variant_node($1, NULL);
    }
    | TOKEN_IDENTIFIER TOKEN_LPAREN type_list TOKEN_RPAREN TOKEN_COMMA {
        $$ = create_variant_node($1, $3);
    }
    ;

return_statement:
    TOKEN_RETURN expression TOKEN_SEMICOLON {
        $$ = create_return_node($2);
    }
    | TOKEN_RETURN TOKEN_SEMICOLON {
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
    | expression TOKEN_PIPE_FORWARD expression {
        $$ = create_pipe_op($1, $3);
    }
    | expression TOKEN_RANGE expression {
        $$ = create_range_node($1, $3, 0);
    }
    | expression TOKEN_RANGE_INC expression {
        $$ = create_range_node($1, $3, 1);
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
    | primary_expr TOKEN_DOT TOKEN_IDENTIFIER {
        $$ = create_member_access($1, $3);
    }
    | primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER {
        $$ = create_static_access($1, $3);
    }
    ;

argument_list:
    /* empty */ { $$ = NULL; }
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
    /* empty */ { $$ = NULL; }
    | expression {
        $$ = create_array_items();
        add_array_item($$, $1);
    }
    | array_items TOKEN_COMMA expression {
        add_array_item($1, $3);
        $$ = $1;
    }
    ;

struct_expr:
    TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE {
        $$ = create_struct_init_node($1, $3);
    }
    ;

struct_init_fields:
    /* empty */ { $$ = NULL; }
    | struct_init_field {
        $$ = create_field_init_list();
        add_field_init($$, $1);
    }
    | struct_init_fields TOKEN_COMMA struct_init_field {
        add_field_init($1, $3);
        $$ = $1;
    }
    ;

struct_init_field:
    TOKEN_IDENTIFIER TOKEN_COLON expression {
        $$ = create_field_init_node($1, $3);
    }
    ;

type_list:
    type {
        $$ = create_type_list();
        add_type($$, $1);
    }
    | type_list TOKEN_COMMA type {
        add_type($1, $3);
        $$ = $1;
    }
    ;

%%

void yyerror(const char* msg) {
    fprintf(stderr, "Erreur ligne %d: %s near '%s'\n", yylineno, msg, yytext);
}
