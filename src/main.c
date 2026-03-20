#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"

extern ASTNode* program_root;
extern FILE* yyin;
extern int yyparse(void);
extern int yylineno;

int main(int argc, char** argv) {
    int debug_mode = 0;
    char* filename = NULL;
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s [options] <file.gjs>\n", argv[0]);
            printf("Options:\n");
            printf("  -d, --debug  Enable debug mode (show AST)\n");
            printf("  -h, --help   Show this help\n");
            return 0;
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            debug_mode = 1;
        } else if (argv[i][0] != '-') {
            filename = argv[i];
        }
    }
    
    if (!filename) {
        fprintf(stderr, "Error: No input file specified\n");
        return 1;
    }
    
    yyin = fopen(filename, "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return 1;
    }
    
    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result != 0 || !program_root) {
        fprintf(stderr, "Error: Parsing failed\n");
        return 1;
    }
    
    if (debug_mode) {
        printf("\n=== AST ===\n");
        print_ast(program_root, 0);
        printf("\n");
    }
    
    free_ast(program_root);
    return 0;
}

void print_ast(ASTNode* node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++) printf("  ");
    
    switch (node->type) {
        case NODE_PROGRAM:
            printf("Program\n");
            if (node->program.statements) {
                for (int i = 0; i < node->program.statements->count; i++) {
                    print_ast(node->program.statements->nodes[i], depth + 1);
                }
            }
            break;
        case NODE_FUNCTION:
            printf("Function: %s\n", node->function.name);
            if (node->function.body) {
                for (int i = 0; i < node->function.body->count; i++) {
                    print_ast(node->function.body->nodes[i], depth + 1);
                }
            }
            break;
        case NODE_LET:
            printf("Let: %s = ", node->var_decl.name);
            if (node->var_decl.value) print_ast(node->var_decl.value, 0);
            printf("\n");
            break;
        case NODE_RETURN:
            printf("Return: ");
            if (node->return_stmt.value) print_ast(node->return_stmt.value, 0);
            printf("\n");
            break;
        case NODE_BINARY_OP:
            printf("(");
            print_ast(node->binary.left, 0);
            switch (node->binary.op) {
                case OP_ADD: printf(" + "); break;
                case OP_SUB: printf(" - "); break;
                case OP_MUL: printf(" * "); break;
                case OP_DIV: printf(" / "); break;
                default: printf(" ? "); break;
            }
            print_ast(node->binary.right, 0);
            printf(")");
            break;
        case NODE_NUMBER:
            printf("%d", node->number.value);
            break;
        case NODE_IDENTIFIER:
            printf("%s", node->identifier.name);
            break;
        default:
            printf("Node(%d)", node->type);
            break;
    }
}
