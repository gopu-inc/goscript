%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;
extern char* yytext;

void yyerror(const char* msg);
int yylex(void);
ASTNode* parse_f_string(char* template);
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
%token TOKEN_DICT TOKEN_MAP
%token TOKEN_FN TOKEN_LET TOKEN_CONST TOKEN_RETURN
%token TOKEN_IF TOKEN_ELSE
%token TOKEN_FOR TOKEN_WHILE TOKEN_LOOP TOKEN_BREAK TOKEN_CONTINUE
%token TOKEN_IMPORT TOKEN_EXPORT TOKEN_PACKET
%token TOKEN_STRUCT TOKEN_ENUM TOKEN_IMPL TOKEN_MATCH TOKEN_TYPE
%token TOKEN_TRUE TOKEN_FALSE TOKEN_NIL
%token TOKEN_AS TOKEN_IN TOKEN_FROM TOKEN_PUB
%token TOKEN_NEW TOKEN_UNSAFE
%token TOKEN_NNL TOKEN_JMP
/* Tokens - Ajoutez ces lignes */
%token TOKEN_MODULE TOKEN_ONLY TOKEN_TIMEOUT TOKEN_SANDBOX TOKEN_ALLOW_FFI
%token TOKEN_ASYNC TOKEN_AWAIT TOKEN_SPAWN
%token TOKEN_LAMBDA
%token TOKEN_EXTENDS
%token TOKEN_UNDERSCORE
%token TOKEN_SWITCH
%token TOKEN_USE

/* Operators */
%token TOKEN_PLUS TOKEN_MINUS TOKEN_MULTIPLY TOKEN_DIVIDE TOKEN_MODULO
%token TOKEN_ASSIGN TOKEN_PLUS_ASSIGN TOKEN_MINUS_ASSIGN
%token TOKEN_MULTIPLY_ASSIGN TOKEN_DIVIDE_ASSIGN TOKEN_MODULO_ASSIGN
%token TOKEN_EQ TOKEN_NEQ TOKEN_LT TOKEN_LTE TOKEN_GT TOKEN_GTE
%token TOKEN_AND TOKEN_OR TOKEN_NOT
%token TOKEN_AMP TOKEN_PIPE TOKEN_XOR TOKEN_LSHIFT TOKEN_RSHIFT
%token TOKEN_DOUBLE_COLON TOKEN_DOT TOKEN_SECURITY
%token TOKEN_COLON TOKEN_SEMICOLON TOKEN_COMMA
%token TOKEN_ARROW TOKEN_FAT_ARROW TOKEN_PIPE_FORWARD
%token TOKEN_OPTIONAL TOKEN_COALESCE
%token TOKEN_RANGE TOKEN_RANGE_INC TOKEN_MUTS
%token TOKEN_SYSF TOKEN_SH



/* Delimiters */
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_LBRACE TOKEN_RBRACE
%token TOKEN_LBRACKET TOKEN_RBRACKET

%token TOKEN_TRY TOKEN_CATCH TOKEN_FINALLY TOKEN_THROW TOKEN_EXCEPT TOKEN_RAISE

/* Types */
%token <string> TOKEN_IDENTIFIER
%token <number> TOKEN_NUMBER
%token <float_val> TOKEN_FLOAT
%token <string> TOKEN_STRING
%token TOKEN_F_STRING

/* Précédence des opérateurs (du plus faible au plus fort) */
%right TOKEN_ASSIGN TOKEN_PLUS_ASSIGN TOKEN_MINUS_ASSIGN TOKEN_MULTIPLY_ASSIGN TOKEN_DIVIDE_ASSIGN TOKEN_MODULO_ASSIGN
%left TOKEN_OR
%left TOKEN_AND
%left TOKEN_EQ TOKEN_NEQ
%left TOKEN_LT TOKEN_LTE TOKEN_GT TOKEN_GTE
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MULTIPLY TOKEN_DIVIDE TOKEN_MODULO
%right TOKEN_NOT


/* Non-terminals */
%type <node> switch_statement ternary_expr
%type <node> try_statement catch_block finally_block throw_statement
%type <node> module_decl 
%type <node> continue_statement
%type <node> use_statement
%type <string> import_path use_path
%type <node_list> array_patterns
%type <node> sysf_expr sh_expr
%type <node> bracket_access
%type <node> import_constraints import_options
%type <node_list> name_list
%type <node> dict_expr dict_type
%type <node_list> dict_entries dict_entry_list
%type <node> program statement expression block
%type <node> function_decl let_decl const_decl return_statement
%type <node> if_statement for_statement while_statement loop_statement
%type <node> import_statement export_statement packet_decl
%type <node> struct_decl enum_decl impl_decl match_statement
%type <node> binary_expr unary_expr primary_expr call_expr
%type <node> array_expr struct_expr member_access
%type <node> param type return_type unsafe_stmt
%type <node> match_case pattern struct_field
%type <node_list> statement_list argument_list param_list struct_fields enum_variants array_items match_cases function_decl_list struct_init_fields
%type <node> break_statement
%type <node> nnl_statement jmp_statement
%type <node> lambda_expr 
%type <node> async_expr await_expr spawn_expr
%type <node> async_function_decl
%type <string> import_path_tail

%type <node> f_string
%start program

%%


switch_statement:
    TOKEN_SWITCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE {
        $$ = create_match_node($2, $4);
    }
    ;
ternary_expr:
    expression TOKEN_OPTIONAL expression TOKEN_COLON expression {
        // condition ? true_expr : false_expr
        $$ = create_ternary_node($1, $3, $5);
    }
    ;

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
unsafe_stmt:
    TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_unsafe_node($3);
    }
    ;
continue_statement:
    TOKEN_CONTINUE {
        $$ = create_continue_node();
    }
    ;


statement:
    import_statement
    | export_statement
    | continue_statement
    | nnl_statement
    | jmp_statement
    | module_decl
    | try_statement
    | throw_statement
    | packet_decl
    | use_statement
    | function_decl
    | struct_decl
    | switch_statement
    | enum_decl
    | impl_decl
    | let_decl
    | break_statement
    | const_decl
    | if_statement
    | for_statement
    | unsafe_stmt
    | while_statement
    | loop_statement
    | match_statement
    | return_statement
    | expression {
        $$ = create_expr_statement($1);
    }
    ;
sysf_expr:
    TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN {
        $$ = create_sysf_node($3);
    }
    | TOKEN_SYSF expression {
        $$ = create_sysf_node($2);
    }
    ;

use_statement:
    // use ft::sleep
    TOKEN_USE use_path {
        $$ = create_use_node($2, NULL);
    }
    // use ft::{sleep, now}
    | TOKEN_USE use_path TOKEN_DOUBLE_COLON TOKEN_LBRACE name_list TOKEN_RBRACE {
        $$ = create_use_node($2, $5);
    }
    // use ft::sleep as slp
    | TOKEN_USE use_path TOKEN_AS TOKEN_IDENTIFIER {
        $$ = create_use_node($2, NULL);
        // Stocker l'alias dans le nœud
        $$->use_stmt.alias = strdup($4);
    }
    ;

use_path:
    TOKEN_IDENTIFIER {
        $$ = strdup($1);
    }
    | use_path TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER {
        char* path = malloc(strlen($1) + strlen($3) + 3);
        sprintf(path, "%s::%s", $1, $3);
        free($1);
        $$ = path;
    }
    ;

sh_expr:
    TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN {
        $$ = create_sh_node($3);
    }
    | TOKEN_SH expression {
        $$ = create_sh_node($2);
    }
    ;

nnl_statement:
    TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_nnl_node($2, $4);
    }
    ;

try_statement:
    TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block {
        $$ = create_try_node($3, $5, NULL);
    }
    | TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block {
        $$ = create_try_node($3, $5, $6);
    }
    ;

catch_block:
    TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_catch_node($3, $6);
    }
    | TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_catch_node($3, $6);
    }
    ;

finally_block:
    TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_finally_node($3);
    }
    ;

throw_statement:
    TOKEN_THROW expression {
        $$ = create_throw_node($2);
    }
    | TOKEN_RAISE expression {
        $$ = create_throw_node($2);
    }
    ;
jmp_statement:
    TOKEN_JMP TOKEN_IDENTIFIER {
        $$ = create_jmp_node($2, NULL);
    }
    | TOKEN_JMP TOKEN_IDENTIFIER expression {
        $$ = create_jmp_node($2, $3);
    }
    ;
// Nouvelles règles d'import
// ==================== IMPORT STATEMENTS ====================

import_statement:
    // import time
    TOKEN_IMPORT import_path {
        $$ = create_import_node($2, NULL, NULL);
    }
    // import time as t
    | TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER {
        $$ = create_import_node($2, $4, NULL);
    }
    // import time with constraints
    | TOKEN_IMPORT import_path import_constraints {
        $$ = create_import_node($2, NULL, $3);
    }
    // import time as t with constraints
    | TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER import_constraints {
        $$ = create_import_node($2, $4, $5);
    }
    ;

// Chemin d'import avec dots (ex: time.ft, .client, ..utils.fs)
import_path_tail:
    TOKEN_IDENTIFIER {
        $$ = strdup($1);
    }
    | import_path_tail TOKEN_DOT TOKEN_IDENTIFIER {
        char* path = malloc(strlen($1) + strlen($3) + 2);
        sprintf(path, "%s.%s", $1, $3);
        free($1);
        $$ = path;
    }
    ;

import_path:
    import_path_tail { 
        $$ = $1; 
    }
    | TOKEN_DOT import_path_tail { // Import relatif: .fichier
        char* path = malloc(strlen($2) + 2);
        sprintf(path, ".%s", $2);
        free($2);
        $$ = path;
    }
    | TOKEN_RANGE import_path_tail { // Import relatif: ..fichier (utilise TOKEN_RANGE ".." du lexer)
        char* path = malloc(strlen($2) + 3);
        sprintf(path, "..%s", $2);
        free($2);
        $$ = path;
    }
    ;

import_constraints:
    TOKEN_LBRACE import_options TOKEN_RBRACE {
        $$ = $2;
    }
    ;

import_options:
    TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET {
        $$ = create_constraints_node("only", $4);
    }
    | import_options TOKEN_COMMA import_options {
        $$ = merge_constraints($1, $3);
    }
    ;

name_list:
    TOKEN_IDENTIFIER {
        $$ = create_node_list();
        add_to_node_list($$, create_identifier_node($1));
    }
    | name_list TOKEN_COMMA TOKEN_IDENTIFIER {
        add_to_node_list($1, create_identifier_node($3));
        $$ = $1;
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
    | TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE {
        ASTNode* node = create_function_node($3, $5, $7, $9);
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        $$ = node;
    }
    | TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE {
        ASTNode* node = create_function_node($4, $6, $8, $10);
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        $$ = node;
    }
    | TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node($8);
        add_to_node_list(body, return_stmt);
        $$ = create_function_node($2, $4, $6, body);
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

/* Dans parser.y */

param:
    TOKEN_IDENTIFIER 
    { $$ = create_param_node($1, NULL, NULL); }
|   TOKEN_IDENTIFIER TOKEN_COLON type 
    { $$ = create_param_node($1, $3, NULL); }
|   TOKEN_IDENTIFIER TOKEN_ASSIGN expression 
    { $$ = create_param_node($1, NULL, $3); } /* Version simple : ident = valeur */
|   TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression 
    { $$ = create_param_node($1, $3, $5); }   /* Version complète : ident: type = valeur */
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


/* Dictionnaire */
dict_expr:
    TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE { $$ = create_dict_node($3); }
    | TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE { $$ = create_dict_node($3); }
    | TOKEN_LBRACE dict_entries TOKEN_RBRACE { $$ = create_dict_node($2); }
    ;

dict_entries:
    /* empty */ {
        $$ = NULL;
    }
    | dict_entry_list {
        $$ = $1;
    }
    ;

dict_entry_list:
    expression TOKEN_FAT_ARROW expression {
        $$ = create_node_list();
        ASTNode* pair = create_binary_op($1, OP_ASSIGN, $3);
        add_to_node_list($$, pair);
    }
    | dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression {
        ASTNode* pair = create_binary_op($3, OP_ASSIGN, $5);
        add_to_node_list($1, pair);
        $$ = $1;
    }
    ;

/* Accès dictionnaire */
/* UNIFIE : un seul type d'accès par crochet */
bracket_access:
    primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET {
        $$ = create_array_access_node($1, $3);
    }
    ;

/* Type dictionnaire */
dict_type:
    TOKEN_DICT TOKEN_LT type TOKEN_COMMA type TOKEN_GT {
        $$ = create_dict_type_node($3, $5);
    }
    | TOKEN_MAP TOKEN_LT type TOKEN_COMMA type TOKEN_GT {
        $$ = create_dict_type_node($3, $5);
    }
    ;

return_type:
    /* empty */ {
        $$ = NULL;
    }
    | TOKEN_COLON type {
        $$ = $2;
    }
    | TOKEN_ARROW primary_expr {
        // Pour les retours directs: -> expr
        $$ = create_return_direct_node($2);
    }
    ;

let_decl:
    TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
        $$ = create_let_node($2, NULL, $4);
    }
    | TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression {
        $$ = create_let_node($2, $4, $6);
    }
    | TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
        ASTNode* node = create_let_node($3, NULL, $5);
        node->var_decl.is_public = 1;
        $$ = node;
    }
    // Ajoute ces deux règles pour muts:
    | TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
        $$ = create_muts_node($2, NULL, $4);
    }
    | TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression {
        $$ = create_muts_node($2, $4, $6);
    }
    ;
const_decl:
    TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
        $$ = create_const_node($2, $4);
    }
    | TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression {
        // Créer une constante publique
        ASTNode* node = create_const_node($3, $5);
        node->var_decl.is_public = 1;
        $$ = node;
    }
    ;

if_statement:
    TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_if_node($2, $4, NULL);
    }
    | TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_if_node($2, $4, $8);
    }
    | TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE if_statement {
        // else if -> le else contient un autre if
        ASTNodeList* else_branch = create_node_list();
        add_to_node_list(else_branch, $7);
        $$ = create_if_node($2, $4, else_branch);
    }
    ;
break_statement:
    TOKEN_BREAK {
        $$ = create_break_node();
    }
    ;
for_statement:
    TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        ASTNode* init = create_let_node($2, NULL, $4);
        ASTNode* cond = $6;
        ASTNode* inc = create_expr_statement($8);
        $$ = create_for_node(init, cond, inc, $10);
    }
    | TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_while_node($2, $4);
    }
    | TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        // for x in array { ... }
        ASTNode* array_expr = $4;
        ASTNodeList* body = $6;
        
        // Créer un nœud spécial pour for-in
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_IN;
        node->for_in.var = strdup($2);
        node->for_in.collection = array_expr;
        node->for_in.body = body;
        $$ = node;
    }
    | TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        // for i in 0..10 { ... }
        ASTNode* start = $4;
        ASTNode* end = $6;
        ASTNodeList* body = $8;
        
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_RANGE;
        node->for_range.var = strdup($2);
        node->for_range.start = start;
        node->for_range.end = end;
        node->for_range.body = body;
        node->for_range.inclusive = 0;
        $$ = node;
    }
    | TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE_INC expression TOKEN_LBRACE statement_list TOKEN_RBRACE {
        // for i in 0..=10 { ... } (inclusif)
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_RANGE;
        node->for_range.var = strdup($2);
        node->for_range.start = $4;
        node->for_range.end = $6;
        node->for_range.body = $8;
        node->for_range.inclusive = 1;
        $$ = node;
    }
    ;
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
    | pattern TOKEN_FAT_ARROW block {
        $$ = create_match_case_node($1, (ASTNode*)$3);
    }
    ;

pattern:
    TOKEN_NUMBER { $$ = create_pattern_number($1); }
    | TOKEN_STRING { $$ = create_pattern_string($1); }
    | TOKEN_IDENTIFIER { $$ = create_pattern_ident($1); }
    | TOKEN_UNDERSCORE { $$ = create_pattern_wildcard(); }
    | TOKEN_LBRACKET array_patterns TOKEN_RBRACKET { $$ = create_pattern_array($2); }
    | TOKEN_LET TOKEN_IDENTIFIER { $$ = create_pattern_binding($2); }
    ;

array_patterns:
    /* empty */ { $$ = NULL; }
    | pattern { $$ = create_node_list(); add_to_node_list($$, $1); }
    | array_patterns TOKEN_COMMA pattern { add_to_node_list($1, $3); $$ = $1; }
    ;


struct_decl:
    TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE {
        $$ = create_struct_node($2, $4);
    }
    | TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE {
        $$ = create_struct_extend_node($2, $4, $6);
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
    | struct_fields TOKEN_COMMA struct_field {
        add_to_node_list($1, $3);
        $$ = $1;
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

module_decl:
    TOKEN_MODULE TOKEN_IDENTIFIER {
        // Créer un nœud nil pour éviter l'erreur
        $$ = create_expr_statement(create_nil_node());
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
    | expression TOKEN_DOT TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN {
        // 'expression' est l'objet ($1), 'TOKEN_IDENTIFIER' est la méthode ($3)
        // 'argument_list' est la liste des arguments ($5)
        $$ = create_method_call_node($1, $3, $5);
    }
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

// Lambda expression
lambda_expr:
    TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_lambda_node($2, $4);
    }
    | TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_lambda_node($3, $6);
    }
    ;

// Array access


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
    | bracket_access
    | dict_expr
    | array_expr
    | struct_expr
    | member_access
    | lambda_expr
    | await_expr
    | sysf_expr  
    | sh_expr   
    | spawn_expr
    | f_string
    ;

f_string:
    TOKEN_F_STRING {
        $$ = parse_f_string($<string>1);
    }
    ;

member_access:
    primary_expr TOKEN_DOT TOKEN_IDENTIFIER {
        $$ = create_member_access($1, $3);
    }
    | primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER {
        $$ = create_static_access($1, $3);
    }
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
/* Fonction asynchrone */
async_function_decl:
    TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE {
        ASTNode* node = create_function_node($3, $5, $7, $9);
        node->function.is_async = 1;
        $$ = node;
    }
    ;

/* Expression await */
await_expr:
    TOKEN_AWAIT primary_expr {
        $$ = create_await_node($2);
    }
    | TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE {
        $$ = create_await_block_node($3);
    }
    ;

/* Expression spawn (exécution parallèle) */
spawn_expr:
    TOKEN_SPAWN primary_expr {
        $$ = create_spawn_node($2);
    }
    ;
async_expr:
    TOKEN_ASYNC primary_expr {
        // Pour l'instant, on traite comme une expression normale
        $$ = $2;
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
    TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE {
        $$ = create_struct_init_node($2, $4);
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
