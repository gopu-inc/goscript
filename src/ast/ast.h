#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// forware
struct Environment;

/* Types de nœuds AST */
typedef enum {
    NODE_PROGRAM,
    NODE_DICT,
    NODE_DICT_ACCESS,
    NODE_DICT_TYPE,
    NODE_NNL,
    NODE_JMP,
    NODE_NNL_CONTEXT,
    NODE_MUTS,
    NODE_IMPORT,
    NODE_LAMBDA,
    NODE_ARRAY_ACCESS,
    NODE_EXPORT,
    NODE_RETURN_STRUCT_FIELD,  
    NODE_PACKET,
    NODE_FUNCTION,
    NODE_PUBLIC_FUNCTION,
    NODE_LET,
    NODE_CONST,
    NODE_IF,
    NODE_FOR,
    NODE_FOR_RANGE,
    NODE_FOR_IN,
    NODE_WHILE,
    NODE_LOOP,
    NODE_BREAK,
    NODE_CONTINUE,
    NODE_MATCH,
    NODE_MATCH_CASE,
    NODE_RETURN,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_NUMBER, 
    NODE_FLOAT,
    NODE_STRING,
    NODE_BOOL,
    NODE_IDENTIFIER,
    NODE_CALL,
    NODE_METHOD_CALL,
    NODE_ARRAY,
    NODE_UNSAFE,
    NODE_ARRAY_TYPE,
    NODE_STRUCT,
    NODE_STRUCT_INIT,
    NODE_ENUM,
    NODE_IMPL,
    NODE_EXPR_STMT,
    NODE_MEMBER_ACCESS,
    NODE_STATIC_ACCESS,
    NODE_PIPE,
    NODE_RANGE,
    NODE_NIL,
    NODE_TYPE_DEF,
    NODE_OPTIONAL_TYPE,
    NODE_PARAM,
    NODE_FIELD,
    NODE_FIELD_INIT,
    NODE_PATTERN_NUMBER,
    NODE_PATTERN_STRING,
    NODE_PATTERN_IDENT,
    NODE_PATTERN_WILDCARD,
    NODE_CONSTRAINT,
    NODE_CONSTRAINT_LIST,
    NODE_STRUCT_EXTENDS,
    NODE_MATCH_STRUCT,
    NODE_MODULE,
    NODE_ASSIGN_OP
} NodeType;

/* Opérateurs */
typedef enum {
    OP_ADD = 1,
    OP_SUB = 2,
    OP_MUL = 3,
    OP_DIV = 4,
    OP_MOD = 5,
    OP_EQ = 6,
    OP_NEQ = 7,
    OP_LT = 8,
    OP_GT = 9,
    OP_LTE = 10,
    OP_GTE = 11,
    OP_AND = 12,
    OP_OR = 13,
    OP_NOT = 14,
    OP_NEG = 15,
    OP_ASSIGN = 16,
    OP_ADD_ASSIGN = 17,
    OP_SUB_ASSIGN = 18,
    OP_MUL_ASSIGN = 19,
    OP_DIV_ASSIGN = 20,
    OP_MOD_ASSIGN = 21,
    OP_RANGE = 22,
    OP_PIPE = 23
} Operator;





/* Structure pour les listes de nœuds */
typedef struct ASTNodeList {
    struct ASTNode** nodes;
    int count;
    int capacity;
} ASTNodeList;

/* Structure principale ASTNode */
typedef struct ASTNode {
    NodeType type;
    int line;
    union {
        /* Programme */
        struct {
            ASTNodeList* statements;
        } program;
          struct {
           struct ASTNodeList* body;
        } unsafe_block;
/* Dictionnaire */
struct {
    ASTNodeList* entries;  /* Liste de paires clé-valeur */
} dict;

/* Accès dictionnaire */
struct {
    struct ASTNode* dict;
    struct ASTNode* key;
} dict_access;

/* Type dictionnaire */
struct {
    struct ASTNode* key_type;
    struct ASTNode* value_type;
} dict_type;

/* For-in loop */
struct {
    char* var;
    struct ASTNode* collection;
    ASTNodeList* body;
} for_in;
     struct {
    struct ASTNode* target; // l'expression à tester
    struct ASTNodeList* cases;
} match_expr;
/* Lambda function */
struct {
    ASTNodeList* params;
    ASTNodeList* body;
    struct Environment* closure;
} lambda;

/* Array access */
struct {
    struct ASTNode* array;
    struct ASTNode* index;
} array_access;
/* Non-local jumps */
struct {
    char* label;
    struct ASTNodeList* body;
} nnl_stmt;

struct {
    char* label;
    struct ASTNode* value;
} jmp_stmt;

struct {
    struct ASTNodeList* contexts;
} nnl_context;
struct {
    char* name;
    char* parent;
    ASTNodeList* fields;
    int is_public;
} struct_extend;

/* Pattern matching sur structure */
struct {
    char* struct_name;
    struct {
        char* field_name;
        struct ASTNode* pattern;
    }* fields;
    int field_count;
} match_struct;
/* Return struct field */
struct {
    char* struct_name;
    char* field_name;
} return_struct_field;
/* Variables mutables */
struct {
    char* name;
    struct ASTNode* var_type;
    struct ASTNode* value;
    int is_public;
} muts_decl;

// Struct pour une branche

        /* Import/Export */
        struct {
            char* path;
            char* alias;
            struct ASTNode* constraints;  // Contraintes d'import (only, timeout, etc.)
        } import;
        struct {
            char* name;
        } export;
        
        /* Packet */
        struct {
            char* name;
            ASTNodeList* statements;
        } packet;
        
        /* Fonctions */
        struct {
            char* name;
            ASTNodeList* params;
            struct ASTNode* return_type;
            ASTNodeList* body;
            int is_main;
            int is_public;
        } function;
        
        /* Variables */
        struct {
            char* name;
            struct ASTNode* var_type;
            struct ASTNode* value;
            int is_public;
        } var_decl;
        
        /* Conditions */
        struct {
            struct ASTNode* condition;
            ASTNodeList* then_branch;
            ASTNodeList* else_branch;
        } if_stmt;
        
        /* Boucles */
        struct {
            struct ASTNode* init;
            struct ASTNode* condition;
            struct ASTNode* increment;
            ASTNodeList* body;
        } for_loop;
        struct {
            char* var;
            struct ASTNode* start;
            struct ASTNode* end;
            ASTNodeList* body;
            int inclusive;
        } for_range;
        struct {
            struct ASTNode* condition;
            ASTNodeList* body;
        } while_stmt;
        struct {
            ASTNodeList* body;
        } loop_stmt;
        
        /* Break/Continue */
        struct {
            int dummy;
        } break_stmt;
        struct {
            int dummy;
        } continue_stmt;
        
        /* Match */
        struct {
            struct ASTNode* value;
            ASTNodeList* cases;
        } match_stmt;
        struct {
            struct ASTNode* pattern;
            struct ASTNode* value;
        } match_case;
        
        /* Return */
        struct {
            struct ASTNode* value;
        } return_stmt;
        
        /* Opérations binaires */
        struct {
            Operator op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binary;

        
        /* Opérations unaires */
        struct {
            Operator op;
            struct ASTNode* operand;
        } unary;
        
        /* Valeurs littérales */
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
        
        /* Identifiant */
        struct {
            char* name;
        } identifier;
        
        /* Appels */
        struct {
            struct ASTNode* callee;
            ASTNodeList* args;
        } call;
        struct {
            struct ASTNode* object;
            char* method;
            ASTNodeList* args;
        } method_call;
        
        /* Tableaux */
        struct {
            ASTNodeList* elements;
        } array;
        struct {
            struct ASTNode* element_type;
        } array_type;
        
        /* Structures */
        struct {
            char* name;
            ASTNodeList* fields;
            int is_public;
        } struct_def;
        struct {
            char* name;
            ASTNodeList* fields;
        } struct_init;
        
        /* Énumérations */
        struct {
            char* name;
            ASTNodeList* variants;
        } enum_def;
        
        /* Implémentations */
        struct {
            char* name;
            ASTNodeList* methods;
            int is_public;
        } impl;
        
        /* Expression statement */
        struct {
            struct ASTNode* expr;
        } expr_stmt;
        
        /* Accès membres */
        struct {
            struct ASTNode* object;
            char* member;
        } member;
        struct {
            struct ASTNode* object;
            char* member;
        } static_access;
        
        /* Pipe operator */
        struct {
            struct ASTNode* value;
            struct ASTNode* next;
        } pipe;
        
        /* Range */
        struct {
            struct ASTNode* start;
            struct ASTNode* end;
            int inclusive;
        } range;

        
        /* Types */
        struct {
            char* name;
        } type_def;
        struct {
            char* name;
        } optional_type;
        
        /* Paramètres et champs */
        struct {
            char* name;
            struct ASTNode* param_type;
        } param;
        struct {
            char* name;
            struct ASTNode* field_type;
        } field;
        struct {
            char* name;
            struct ASTNode* value;
        } field_init;
        
        /* Patterns */
        struct {
            int value;
        } pattern_number;
        struct {
            char* value;
        } pattern_string;
        struct {
            char* value;
        } pattern_ident;
        struct {
            int dummy;
        } pattern_wildcard;
        
        /* Contraintes d'import */
        struct {
            char* constraint_type;  // "only", "timeout", "sandbox", "allow_ffi"
            ASTNodeList* list;       // Liste des noms autorisés pour "only"
            int int_value;           // Valeur pour timeout, etc.
        } constraint;
        
        /* Liste de contraintes */
        struct {
            struct ASTNode* a;
            struct ASTNode* b;
        } constraint_list;
        
        /* Module */
        struct {
            char* name;
            struct LoadedModule* module;
        } module;
        
        /* Assignation composée */
        struct {
            Operator op;
            struct ASTNode* left;
            struct ASTNode* right;
        } assign_op;
    };
} ASTNode;
/* ==================== Fonctions de création de listes ==================== */
ASTNodeList* create_node_list(void);
void add_to_node_list(ASTNodeList* list, ASTNode* node);
ASTNodeList* create_arg_list(void);
void add_arg(ASTNodeList* list, ASTNode* arg);
ASTNodeList* create_param_list(void);
void add_param(ASTNodeList* list, ASTNode* param);
ASTNodeList* create_field_list(void);
void add_field(ASTNodeList* list, ASTNode* field);
ASTNodeList* create_variant_list(void);
void add_variant(ASTNodeList* list, ASTNode* variant);
ASTNodeList* create_case_list(void);
void add_case(ASTNodeList* list, ASTNode* case_node);
ASTNodeList* create_array_items(void);
void add_array_item(ASTNodeList* list, ASTNode* item);
ASTNodeList* create_field_init_list(void);
void add_field_init(ASTNodeList* list, ASTNode* init);


// Ajouter ces déclarations
ASTNode* create_unsafe_node(ASTNodeList* body);
ASTNode* create_lambda_node(ASTNodeList* params, ASTNodeList* body);
ASTNode* create_array_access_node(ASTNode* array, ASTNode* index);





/* ==================== Nœuds principaux ==================== */
ASTNode* create_program_node(ASTNodeList* statements);

ASTNode* create_struct_extend_node(char* name, char* parent, ASTNodeList* fields);
/* Imports et exports */
ASTNode* create_import_node(char* path, char* alias, ASTNode* constraints);
ASTNode* create_export_node(char* name);
ASTNode* create_packet_node(char* name, ASTNodeList* statements);

/* Fonctions */
ASTNode* create_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body);
ASTNode* create_public_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body);
ASTNode* create_main_function_node(char* name, ASTNodeList* params, ASTNode* return_type, ASTNodeList* body);
ASTNode* create_nnl_node(char* label, ASTNodeList* body);
ASTNode* create_jmp_node(char* label, ASTNode* value);
/* Variables */
ASTNode* create_let_node(char* name, ASTNode* type, ASTNode* value);
ASTNode* create_const_node(char* name, ASTNode* value);

/* Conditions */
ASTNode* create_if_node(ASTNode* condition, ASTNodeList* then_branch, ASTNodeList* else_branch);

/* Boucles */
ASTNode* create_for_node(ASTNode* init, ASTNode* cond, ASTNode* inc, ASTNodeList* body);
ASTNode* create_for_range_node(char* var, ASTNode* start, ASTNode* end, ASTNodeList* body);
ASTNode* create_while_node(ASTNode* condition, ASTNodeList* body);
ASTNode* create_loop_node(ASTNodeList* body);
ASTNode* create_break_node(void);
ASTNode* create_continue_node(void);
ASTNode* create_for_in_node(char* var, ASTNode* collection, ASTNodeList* body);

ASTNode* create_dict_node(ASTNodeList* entries);
ASTNode* create_dict_access_node(ASTNode* dict, ASTNode* key);
ASTNode* create_dict_type_node(ASTNode* key_type, ASTNode* value_type);

/* Match */
ASTNode* create_match_node(ASTNode* value, ASTNodeList* cases);
ASTNode* create_match_case_node(ASTNode* pattern, ASTNode* value);

/* Return */
ASTNode* create_return_node(ASTNode* value);

/* Expressions */
ASTNode* create_constraints_node(char* type, ASTNodeList* list);
ASTNode* merge_constraints(ASTNode* a, ASTNode* b);
ASTNode* create_expr_statement(ASTNode* expr);
ASTNode* create_binary_op(ASTNode* left, Operator op, ASTNode* right);
ASTNode* create_unary_op(Operator op, ASTNode* operand);
ASTNode* create_assign_node(ASTNode* left, ASTNode* right);
ASTNode* create_assign_op_node(ASTNode* left, Operator op, ASTNode* right);

/* Valeurs littérales */
ASTNode* create_number_node(int value);
ASTNode* create_float_node(double value);
ASTNode* create_string_node(char* value);
ASTNode* create_bool_node(int value);
ASTNode* create_nil_node(void);

/* Identifiants */
ASTNode* create_identifier_node(char* name);

/* Appels */
ASTNode* create_call_node(ASTNode* callee, ASTNodeList* args);
ASTNode* create_method_call_node(ASTNode* object, char* method, ASTNodeList* args);

/* Tableaux */
ASTNode* create_array_node(ASTNodeList* elements);
ASTNode* create_array_type_node(ASTNode* element_type);
ASTNode* create_return_direct_node(ASTNode* expr);
/* Structures */
ASTNode* create_struct_node(char* name, ASTNodeList* fields);
ASTNode* create_struct_init_node(char* name, ASTNodeList* fields);

/* Énumérations */
ASTNode* create_enum_node(char* name, ASTNodeList* variants);

/* Implémentations */
ASTNode* create_impl_node(char* name, ASTNodeList* methods);

/* Accès membres */
ASTNode* create_member_access(ASTNode* object, char* member);
ASTNode* create_static_access(ASTNode* object, char* member);

/* Opérateurs spéciaux */
ASTNode* create_pipe_op(ASTNode* left, ASTNode* right);
ASTNode* create_range_node(ASTNode* start, ASTNode* end, int inclusive);

/* Types */
ASTNode* create_type_node(char* name);
ASTNode* create_optional_type_node(char* name);

ASTNode* create_muts_node(char* name, ASTNode* type, ASTNode* value);
ASTNode* create_public_muts_node(char* name, ASTNode* type, ASTNode* value);

/* Paramètres et champs */
ASTNode* create_param_node(char* name, ASTNode* type);
ASTNode* create_field_node(char* name, ASTNode* type);
ASTNode* create_field_init_node(char* name, ASTNode* value);

/* Patterns */
ASTNode* create_pattern_number(int value);
ASTNode* create_pattern_string(char* value);
ASTNode* create_pattern_ident(char* value);
ASTNode* create_pattern_wildcard(void);

/* ==================== Fonctions utilitaires ==================== */
void free_ast(ASTNode* node);
void print_ast(ASTNode* node, int depth);

#endif /* AST_H */
