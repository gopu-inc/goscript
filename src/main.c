#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"

extern ASTNode* program_root;
extern FILE* yyin;
extern int yyparse(void);
// extern int repl_main(void);  // Commentez temporairement
extern void interpret_program(ASTNode* program);

void print_ast(ASTNode* node, int depth);

int main(int argc, char** argv) {
    int debug_mode = 0;
    int repl_mode = 0;
    char* filename = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            debug_mode = 1;
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interactive") == 0) {
            repl_mode = 1;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Goscript - A modern scripting language\n");
            printf("Usage: %s [options] [file.gjs]\n", argv[0]);
            printf("Options:\n");
            printf("  -d, --debug    Show AST\n");
            printf("  -h, --help     Show this help\n");
            return 0;
        } else if (argv[i][0] != '-') {
            filename = argv[i];
        }
    }
    
    // Mode REPL désactivé temporairement
    if (!filename || repl_mode) {
        printf("REPL mode coming soon!\n");
        printf("Please provide a file: %s <file.gjs>\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(filename, "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open '%s'\n", filename);
        return 1;
    }
    
    int parse_result = yyparse();
    fclose(yyin); 
    
    if (parse_result != 0 || !program_root) {
        fprintf(stderr, "Error: Parsing failed\n");
        return 1;
    }
    
    if (debug_mode) {
        printf("\n===( AST )===\n");
        print_ast(program_root, 0);
        printf("\n");
    }
    
    interpret_program(program_root);
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
            
            
        case NODE_MODULE:
            printf("Module: %s\n", node->module.name);
            break;
            
        case NODE_STRUCT:
            printf("Struct: %s\n", node->struct_def.name);
            if (node->struct_def.fields) {
                for (int i = 0; i < node->struct_def.fields->count; i++) {
                    print_ast(node->struct_def.fields->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_IMPL:
            printf("Impl: %s\n", node->impl.name);
            if (node->impl.methods) {
                for (int i = 0; i < node->impl.methods->count; i++) {
                    print_ast(node->impl.methods->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_FUNCTION:
            printf("Function: %s", node->function.name);
            if (node->function.is_main) printf(" (main)");
            if (node->function.is_public) printf(" (public)");
            printf("\n");
            if (node->function.params) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Params:\n");
                for (int i = 0; i < node->function.params->count; i++) {
                    print_ast(node->function.params->nodes[i], depth + 2);
                }
            }
            if (node->function.body) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Body:\n");
                for (int i = 0; i < node->function.body->count; i++) {
                    print_ast(node->function.body->nodes[i], depth + 2);
                }
            }
            break;
            
        case NODE_LET:
            printf("Let: %s = ", node->var_decl.name);
            if (node->var_decl.value) print_ast(node->var_decl.value, 0);
            printf("\n");
            break;
            
        case NODE_METHOD_CALL:
            printf("MethodCall: ");
            print_ast(node->method_call.object, 0);
            printf(".%s(", node->method_call.method);
            if (node->method_call.args) {
                for (int i = 0; i < node->method_call.args->count; i++) {
                    if (i > 0) printf(", ");
                    print_ast(node->method_call.args->nodes[i], 0);
                }
            }
            printf(")\n");
            break;
            
        case NODE_MEMBER_ACCESS:
            printf("MemberAccess: ");
            print_ast(node->member.object, 0);
            printf(".%s\n", node->member.member);
            break;
           
        
       case NODE_STATIC_ACCESS:
           printf("StaticAccess: ");
           print_ast(node->static_access.object, 0);
           printf("::%s\n", node->static_access.member);
           break;

        case NODE_IMPORT:
            printf("Import: %s", node->import.path);
   
            if (node->import.alias) {
                printf(" as %s", node->import.alias);
            } 
            printf("\n");
            break;

            
        case NODE_STRUCT_INIT:
            printf("StructInit: %s\n", node->struct_init.name);
            if (node->struct_init.fields) {
                for (int i = 0; i < node->struct_init.fields->count; i++) {
                    print_ast(node->struct_init.fields->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_FIELD_INIT:
            printf("Field: %s = ", node->field_init.name);
            if (node->field_init.value) print_ast(node->field_init.value, 0);
            printf("\n");
            break;
            
        case NODE_CALL:
            printf("Call: ");
            print_ast(node->call.callee, 0);
            printf("(");
            if (node->call.args) {
                for (int i = 0; i < node->call.args->count; i++) {
                    if (i > 0) printf(", ");
                    print_ast(node->call.args->nodes[i], 0);
                }
            }
            printf(")\n");
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
                case OP_MOD: printf(" %% "); break;
                case OP_EQ: printf(" == "); break;
                case OP_NEQ: printf(" != "); break;
                case OP_LT: printf(" < "); break;
                case OP_GT: printf(" > "); break;
                case OP_LTE: printf(" <= "); break;
                case OP_GTE: printf(" >= "); break;
                case OP_AND: printf(" && "); break;
                case OP_OR: printf(" || "); break;
                case OP_ASSIGN: printf(" = "); break;
                default: printf(" ? "); break;
            }
            print_ast(node->binary.right, 0);
            printf(")\n");
            break;
            
        case NODE_NUMBER:
            printf("%d", node->number.value);
            break;
            
        case NODE_STRING:
            printf("\"%s\"", node->string_val.value);
            break;
            
        case NODE_BOOL:
            printf("%s", node->bool_val.value ? "true" : "false");
            break;
            
        case NODE_IDENTIFIER:
            printf("%s", node->identifier.name);
            break;
            
        default:
            printf("Node(%d)", node->type);
            break;
    }
}
