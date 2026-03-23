#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TypeInfo* create_type_int(void) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_INT;
    t->element_type = NULL;
    t->is_optional = 0;
    return t;
}

TypeInfo* create_type_float(void) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_FLOAT;
    return t;
}

TypeInfo* create_type_bool(void) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_BOOL;
    return t;
}

TypeInfo* create_type_string(void) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_STRING;
    return t;
}

TypeInfo* create_type_nil(void) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_NIL;
    return t;
}

TypeInfo* create_type_array(TypeInfo* element_type) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_ARRAY;
    t->element_type = element_type;
    return t;
}

TypeInfo* create_type_struct(char* name) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_STRUCT;
    t->struct_name = strdup(name);
    return t;
}

TypeInfo* create_type_function(TypeInfo* return_type, TypeInfo** param_types, int param_count) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_FUNCTION;
    t->return_type = return_type;
    t->param_types = malloc(param_count * sizeof(TypeInfo*));
    for (int i = 0; i < param_count; i++) {
        t->param_types[i] = param_types[i];
    }
    t->param_count = param_count;
    return t;
}

TypeInfo* create_type_optional(TypeInfo* base_type) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_OPTIONAL;
    t->element_type = base_type;
    t->is_optional = 1;
    return t;
}

TypeInfo* create_type_union(TypeInfo* left, TypeInfo* right) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_UNION;
    t->left = left;
    t->right = right;
    return t;
}

TypeInfo* create_type_any(void) {
    TypeInfo* t = malloc(sizeof(TypeInfo));
    t->kind = TYPE_ANY;
    return t;
}

int types_equal(TypeInfo* a, TypeInfo* b) {
    if (!a || !b) return a == b;
    if (a->kind != b->kind) return 0;
    
    switch (a->kind) {
        case TYPE_INT:
        case TYPE_FLOAT:
        case TYPE_BOOL:
        case TYPE_STRING:
        case TYPE_NIL:
        case TYPE_ANY:
            return 1;
            
        case TYPE_ARRAY:
            return types_equal(a->element_type, b->element_type);
            
        case TYPE_STRUCT:
            return strcmp(a->struct_name, b->struct_name) == 0;
            
        case TYPE_FUNCTION:
            if (a->param_count != b->param_count) return 0;
            if (!types_equal(a->return_type, b->return_type)) return 0;
            for (int i = 0; i < a->param_count; i++) {
                if (!types_equal(a->param_types[i], b->param_types[i])) return 0;
            }
            return 1;
            
        case TYPE_OPTIONAL:
            return types_equal(a->element_type, b->element_type);
            
        case TYPE_UNION:
            return types_equal(a->left, b->left) && types_equal(a->right, b->right);
            
        default:
            return 0;
    }
}

void print_type(TypeInfo* type) {
    if (!type) {
        printf("unknown");
        return;
    }
    
    switch (type->kind) {
        case TYPE_INT: printf("int"); break;
        case TYPE_FLOAT: printf("float"); break;
        case TYPE_BOOL: printf("bool"); break;
        case TYPE_STRING: printf("string"); break;
        case TYPE_NIL: printf("nil"); break;
        case TYPE_ANY: printf("any"); break;
        case TYPE_ARRAY:
            printf("[");
            print_type(type->element_type);
            printf("]");
            break;
        case TYPE_STRUCT:
            printf("struct %s", type->struct_name);
            if (type->is_optional) printf("?");
            break;
        case TYPE_FUNCTION:
            printf("fn(");
            for (int i = 0; i < type->param_count; i++) {
                if (i > 0) printf(", ");
                print_type(type->param_types[i]);
            }
            printf(") -> ");
            print_type(type->return_type);
            break;
        case TYPE_OPTIONAL:
            print_type(type->element_type);
            printf("?");
            break;
        case TYPE_UNION:
            print_type(type->left);
            printf(" | ");
            print_type(type->right);
            break;
    }
}
