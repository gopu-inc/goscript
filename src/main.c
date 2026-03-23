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
            printf("Struct: %s", node->struct_def.name);
            if (node->struct_def.is_public) printf(" (public)");
            printf("\n");
            if (node->struct_def.fields) {
                for (int i = 0; i < node->struct_def.fields->count; i++) {
                    print_ast(node->struct_def.fields->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_STRUCT_EXTENDS:
            printf("StructExtends: %s extends %s", node->struct_extend.name, node->struct_extend.parent);
            if (node->struct_extend.is_public) printf(" (public)");
            printf("\n");
            if (node->struct_extend.fields) {
                for (int i = 0; i < node->struct_extend.fields->count; i++) {
                    print_ast(node->struct_extend.fields->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_STRUCT_INIT:
            printf("StructInit: %s\n", node->struct_init.name);
            if (node->struct_init.fields) {
                for (int i = 0; i < node->struct_init.fields->count; i++) {
                    print_ast(node->struct_init.fields->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_ENUM:
            printf("Enum: %s\n", node->enum_def.name);
            if (node->enum_def.variants) {
                for (int i = 0; i < node->enum_def.variants->count; i++) {
                    for (int j = 0; j < depth + 1; j++) printf("  ");
                    printf("Variant: ");
                    print_ast(node->enum_def.variants->nodes[i], 0);
                    printf("\n");
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
        case NODE_PUBLIC_FUNCTION:
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
            if (node->function.return_type) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("ReturnType: ");
                print_ast(node->function.return_type, 0);
                printf("\n");
            }
            if (node->function.body) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Body:\n");
                for (int i = 0; i < node->function.body->count; i++) {
                    print_ast(node->function.body->nodes[i], depth + 2);
                }
            }
            break;
            
        case NODE_LAMBDA:
            printf("Lambda\n");
            if (node->lambda.params) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Params:\n");
                for (int i = 0; i < node->lambda.params->count; i++) {
                    print_ast(node->lambda.params->nodes[i], depth + 2);
                }
            }
            if (node->lambda.body) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Body:\n");
                for (int i = 0; i < node->lambda.body->count; i++) {
                    print_ast(node->lambda.body->nodes[i], depth + 2);
                }
            }
            break;
            
        case NODE_LET:
        case NODE_CONST:
            printf("%s: %s", 
                   (node->type == NODE_LET) ? "Let" : "Const", 
                   node->var_decl.name);
            if (node->var_decl.is_public) printf(" (public)");
            if (node->var_decl.var_type) {
                printf(": ");
                print_ast(node->var_decl.var_type, 0);
            }
            printf(" = ");
            if (node->var_decl.value) print_ast(node->var_decl.value, 0);
            printf("\n");
            break;
            
        case NODE_MUTS:
            printf("Mutable: %s", node->muts_decl.name);
            if (node->muts_decl.is_public) printf(" (public)");
            if (node->muts_decl.var_type) {
                printf(": ");
                print_ast(node->muts_decl.var_type, 0);
            }
            printf(" = ");
            if (node->muts_decl.value) print_ast(node->muts_decl.value, 0);
            printf("\n");
            break;
            
        case NODE_IMPORT:
            printf("Import: %s", node->import.path);
            if (node->import.alias) printf(" as %s", node->import.alias);
            if (node->import.constraints) {
                printf(" with ");
                print_ast(node->import.constraints, 0);
            }
            printf("\n");
            break;
            
        case NODE_EXPORT:
            printf("Export: %s\n", node->export.name);
            break;
            
        case NODE_PACKET:
            printf("Packet: %s\n", node->packet.name);
            if (node->packet.statements) {
                for (int i = 0; i < node->packet.statements->count; i++) {
                    print_ast(node->packet.statements->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_NNL:
            printf("NNL: %s\n", node->nnl_stmt.label);
            if (node->nnl_stmt.body) {
                for (int i = 0; i < node->nnl_stmt.body->count; i++) {
                    print_ast(node->nnl_stmt.body->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_JMP:
            printf("JMP: %s", node->jmp_stmt.label);
            if (node->jmp_stmt.value) {
                printf(" -> ");
                print_ast(node->jmp_stmt.value, 0);
            }
            printf("\n");
            break;
            
        case NODE_IF:
            printf("If\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Condition: ");
            print_ast(node->if_stmt.condition, 0);
            printf("\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Then:\n");
            for (int i = 0; i < node->if_stmt.then_branch->count; i++) {
                print_ast(node->if_stmt.then_branch->nodes[i], depth + 2);
            }
            if (node->if_stmt.else_branch) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Else:\n");
                for (int i = 0; i < node->if_stmt.else_branch->count; i++) {
                    print_ast(node->if_stmt.else_branch->nodes[i], depth + 2);
                }
            }
            break;
            
        case NODE_FOR:
            printf("For\n");
            if (node->for_range.var) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Var: %s\n", node->for_range.var);
            }
            if (node->for_range.start) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Start: ");
                print_ast(node->for_range.start, 0);
                printf("\n");
            }
            if (node->for_range.end) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("End: ");
                print_ast(node->for_range.end, 0);
                printf("\n");
            }
            if (node->for_range.body) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Body:\n");
                for (int i = 0; i < node->for_range.body->count; i++) {
                    print_ast(node->for_range.body->nodes[i], depth + 2);
                }
            }
            break;
            
        case NODE_FOR_RANGE:
            printf("ForRange: %s in ", node->for_range.var);
            print_ast(node->for_range.start, 0);
            printf("..");
            if (node->for_range.inclusive) printf("=");
            print_ast(node->for_range.end, 0);
            printf("\n");
            if (node->for_range.body) {
                for (int i = 0; i < node->for_range.body->count; i++) {
                    print_ast(node->for_range.body->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_WHILE:
            printf("While\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Condition: ");
            print_ast(node->while_stmt.condition, 0);
            printf("\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Body:\n");
            for (int i = 0; i < node->while_stmt.body->count; i++) {
                print_ast(node->while_stmt.body->nodes[i], depth + 2);
            }
            break;
            
        case NODE_LOOP:
            printf("Loop\n");
            if (node->loop_stmt.body) {
                for (int i = 0; i < node->loop_stmt.body->count; i++) {
                    print_ast(node->loop_stmt.body->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_BREAK:
            printf("Break\n");
            break;
            
        case NODE_CONTINUE:
            printf("Continue\n");
            break;
            
        case NODE_MATCH:
            printf("Match\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Value: ");
            print_ast(node->match_stmt.value, 0);
            printf("\n");
            if (node->match_stmt.cases) {
                for (int i = 0; i < node->match_stmt.cases->count; i++) {
                    print_ast(node->match_stmt.cases->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_MATCH_CASE:
            printf("Case\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Pattern: ");
            print_ast(node->match_case.pattern, 0);
            printf("\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Value: ");
            print_ast(node->match_case.value, 0);
            printf("\n");
            break;
            
        case NODE_RETURN:
            printf("Return");
            if (node->return_stmt.value) {
                printf(": ");
                print_ast(node->return_stmt.value, 0);
            }
            printf("\n");
            break;
            
        case NODE_RETURN_STRUCT_FIELD:
            printf("ReturnStructField: %s.%s\n", 
                   node->return_struct_field.struct_name,
                   node->return_struct_field.field_name);
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
                case OP_ADD_ASSIGN: printf(" += "); break;
                case OP_SUB_ASSIGN: printf(" -= "); break;
                case OP_MUL_ASSIGN: printf(" *= "); break;
                case OP_DIV_ASSIGN: printf(" /= "); break;
                case OP_MOD_ASSIGN: printf(" %%= "); break;
                case OP_RANGE: printf(".."); break;
                case OP_PIPE: printf(" |> "); break;
                default: printf(" ? "); break;
            }
            print_ast(node->binary.right, 0);
            printf(")\n");
            break;
            
        case NODE_ASSIGN_OP:
            printf("AssignOp: ");
            print_ast(node->assign_op.left, 0);
            switch (node->assign_op.op) {
                case OP_ADD_ASSIGN: printf(" += "); break;
                case OP_SUB_ASSIGN: printf(" -= "); break;
                case OP_MUL_ASSIGN: printf(" *= "); break;
                case OP_DIV_ASSIGN: printf(" /= "); break;
                case OP_MOD_ASSIGN: printf(" %%= "); break;
                default: printf(" ?= "); break;
            }
            print_ast(node->assign_op.right, 0);
            printf("\n");
            break;
            
        case NODE_UNARY_OP:
            printf("(");
            switch (node->unary.op) {
                case OP_NOT: printf("!"); break;
                case OP_NEG: printf("-"); break;
                default: printf("?"); break;
            }
            print_ast(node->unary.operand, 0);
            printf(")\n");
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
            
        case NODE_ARRAY:
            printf("[");
            if (node->array.elements) {
                for (int i = 0; i < node->array.elements->count; i++) {
                    if (i > 0) printf(", ");
                    print_ast(node->array.elements->nodes[i], 0);
                }
            }
            printf("]\n");
            break;
            
        case NODE_ARRAY_ACCESS:
            printf("ArrayAccess: ");
            print_ast(node->array_access.array, 0);
            printf("[");
            print_ast(node->array_access.index, 0);
            printf("]\n");
            break;
            
        case NODE_ARRAY_TYPE:
            printf("ArrayType: ");
            print_ast(node->array_type.element_type, 0);
            printf("[]\n");
            break;
            
        case NODE_EXPR_STMT:
            print_ast(node->expr_stmt.expr, depth);
            break;
            
        case NODE_UNSAFE:
            printf("Unsafe\n");
            if (node->unsafe_block.body) {
                for (int i = 0; i < node->unsafe_block.body->count; i++) {
                    print_ast(node->unsafe_block.body->nodes[i], depth + 1);
                }
            }
            break;
            
        case NODE_PIPE:
            printf("Pipe: ");
            print_ast(node->pipe.value, 0);
            printf(" |> ");
            print_ast(node->pipe.next, 0);
            printf("\n");
            break;
            
        case NODE_RANGE:
            printf("Range: ");
            print_ast(node->range.start, 0);
            if (node->range.inclusive) printf("..=");
            else printf("..");
            print_ast(node->range.end, 0);
            printf("\n");
            break;
            
        case NODE_PARAM:
            printf("Param: %s", node->param.name);
            if (node->param.param_type) {
                printf(": ");
                print_ast(node->param.param_type, 0);
            }
            printf("\n");
            break;
            
        case NODE_FIELD:
            printf("Field: %s", node->field.name);
            if (node->field.field_type) {
                printf(": ");
                print_ast(node->field.field_type, 0);
            }
            printf("\n");
            break;
            
        case NODE_FIELD_INIT:
            printf("FieldInit: %s = ", node->field_init.name);
            if (node->field_init.value) print_ast(node->field_init.value, 0);
            printf("\n");
            break;
            
        case NODE_TYPE_DEF:
            printf("Type: %s\n", node->type_def.name);
            break;
            
        case NODE_OPTIONAL_TYPE:
            printf("OptionalType: %s?\n", node->optional_type.name);
            break;
            
        case NODE_CONSTRAINT:
            printf("Constraint: %s", node->constraint.constraint_type);
            if (node->constraint.list) {
                printf(" [");
                for (int i = 0; i < node->constraint.list->count; i++) {
                    if (i > 0) printf(", ");
                    print_ast(node->constraint.list->nodes[i], 0);
                }
                printf("]");
            }
            if (node->constraint.int_value) {
                printf(" = %d", node->constraint.int_value);
            }
            printf("\n");
            break;
            
        case NODE_CONSTRAINT_LIST:
            printf("ConstraintList:\n");
            print_ast(node->constraint_list.a, depth + 1);
            print_ast(node->constraint_list.b, depth + 1);
            break;
            
        case NODE_NUMBER:
            printf("%d", node->number.value);
            break;
            
        case NODE_FLOAT:
            printf("%f", node->float_val.value);
            break;
            
        case NODE_STRING:
            printf("\"%s\"", node->string_val.value);
            break;
            
        case NODE_BOOL:
            printf("%s", node->bool_val.value ? "true" : "false");
            break;
            
        case NODE_NIL:
            printf("nil");
            break;
            
        case NODE_IDENTIFIER:
            printf("%s", node->identifier.name);
            break;
            
        case NODE_PATTERN_NUMBER:
            printf("PatternNumber: %d\n", node->pattern_number.value);
            break;
            
        case NODE_PATTERN_STRING:
            printf("PatternString: \"%s\"\n", node->pattern_string.value);
            break;
            
        case NODE_PATTERN_IDENT:
            printf("PatternIdent: %s\n", node->pattern_ident.value);
            break;
            
        case NODE_PATTERN_WILDCARD:
            printf("PatternWildcard: _\n");
            break;
            
        default:
            printf("Node(%d)\n", node->type);
            break;
    }
}
