#include "bytecode.h"
#include <ctype.h>

extern Value evaluate_expr(ASTNode* node, Environment* env);
extern int evaluate_statement(ASTNode* node, Environment* env, char* current_file);
extern ModuleRegistry* get_module_registry(void);
extern char* resolve_module_path(char* current_file, char* import_path);
extern LoadedModule* load_module(ModuleRegistry* reg, Environment* parent_env,
                                 char* current_file, char* import_path,
                                 char* alias, ASTNode* constraints);
extern void register_impl(char* struct_name, ASTNode* impl_node);

extern int goscript_argc;
extern char** goscript_argv;

static BCChunk* bc_compile_statement_list(ASTNodeList* list, const char* name);

// ------------------------------------------------------------
// Chunk helpers
// ------------------------------------------------------------

static char* bc_strdup0(const char* s) {
    return s ? strdup(s) : NULL;
}

BCChunk* bc_chunk_new(const char* name) {
    BCChunk* chunk = (BCChunk*)malloc(sizeof(BCChunk));
    chunk->code = NULL;
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->name = bc_strdup0(name);
    return chunk;
}

static void bc_free_instruction(BCInstruction* ins) {
    if (!ins) return;
    if (ins->str) free(ins->str);
    if (ins->chunk_a) bc_chunk_free(ins->chunk_a);
    if (ins->chunk_b) bc_chunk_free(ins->chunk_b);
    if (ins->chunk_c) bc_chunk_free(ins->chunk_c);
}

void bc_chunk_free(BCChunk* chunk) {
    if (!chunk) return;
    for (int i = 0; i < chunk->count; i++) {
        bc_free_instruction(&chunk->code[i]);
    }
    free(chunk->code);
    free(chunk->name);
    free(chunk);
}

int bc_chunk_emit(BCChunk* chunk, BCInstruction ins) {
    if (chunk->count >= chunk->capacity) {
        chunk->capacity = chunk->capacity == 0 ? 32 : chunk->capacity * 2;
        chunk->code = (BCInstruction*)realloc(chunk->code, chunk->capacity * sizeof(BCInstruction));
    }
    chunk->code[chunk->count] = ins;
    return chunk->count++;
}

static const char* bc_op_name(BCOpCode op) {
    switch (op) {
        case BC_NOP: return "NOP";
        case BC_PUSH_INT: return "PUSH_INT";
        case BC_PUSH_FLOAT: return "PUSH_FLOAT";
        case BC_PUSH_STRING: return "PUSH_STRING";
        case BC_PUSH_BOOL: return "PUSH_BOOL";
        case BC_PUSH_NIL: return "PUSH_NIL";
        case BC_LOAD_NAME: return "LOAD_NAME";
        case BC_STORE_NAME: return "STORE_NAME";
        case BC_POP: return "POP";
        case BC_DUP: return "DUP";
        case BC_ADD: return "ADD";
        case BC_SUB: return "SUB";
        case BC_MUL: return "MUL";
        case BC_DIV: return "DIV";
        case BC_MOD: return "MOD";
        case BC_EQ: return "EQ";
        case BC_NEQ: return "NEQ";
        case BC_LT: return "LT";
        case BC_LTE: return "LTE";
        case BC_GT: return "GT";
        case BC_GTE: return "GTE";
        case BC_AND: return "AND";
        case BC_OR: return "OR";
        case BC_NOT: return "NOT";
        case BC_NEG: return "NEG";
        case BC_ASSIGN: return "ASSIGN";
        case BC_ADD_ASSIGN: return "ADD_ASSIGN";
        case BC_SUB_ASSIGN: return "SUB_ASSIGN";
        case BC_MUL_ASSIGN: return "MUL_ASSIGN";
        case BC_DIV_ASSIGN: return "DIV_ASSIGN";
        case BC_MOD_ASSIGN: return "MOD_ASSIGN";
        case BC_BUILD_ARRAY: return "BUILD_ARRAY";
        case BC_BUILD_DICT: return "BUILD_DICT";
        case BC_CALL: return "CALL";
        case BC_IF: return "IF";
        case BC_WHILE: return "WHILE";
        case BC_LOOP: return "LOOP";
        case BC_RETURN: return "RETURN";
        case BC_BREAK: return "BREAK";
        case BC_CONTINUE: return "CONTINUE";
        case BC_EVAL_EXPR: return "EVAL_EXPR";
        case BC_EVAL_STMT: return "EVAL_STMT";
        case BC_HALT: return "HALT";
        default: return "?";
    }
}

static void bc_chunk_dump_internal(FILE* out, BCChunk* chunk) {
    if (!chunk || !out) return;
    fprintf(out, "== BYTECODE CHUNK: %s ==\n", chunk->name ? chunk->name : "<anon>");
    for (int i = 0; i < chunk->count; i++) {
        BCInstruction* ins = &chunk->code[i];
        fprintf(out, "%04d  %-12s", i, bc_op_name(ins->op));
        if (ins->op == BC_PUSH_INT || ins->op == BC_LOAD_NAME || ins->op == BC_STORE_NAME ||
            ins->op == BC_BUILD_ARRAY || ins->op == BC_BUILD_DICT || ins->op == BC_CALL) {
            if (ins->str) fprintf(out, " %s", ins->str);
            else fprintf(out, " %d", ins->a);
        } else if (ins->op == BC_PUSH_FLOAT) {
            fprintf(out, " %f", ins->num);
        } else if (ins->op == BC_PUSH_BOOL) {
            fprintf(out, " %d", ins->a);
        } else if (ins->op == BC_IF || ins->op == BC_WHILE || ins->op == BC_LOOP ||
                   ins->op == BC_EVAL_EXPR || ins->op == BC_EVAL_STMT) {
            fprintf(out, " <chunk>");
        }
        fprintf(out, "\n");
    }
}

void bc_chunk_dump_to_file(FILE* out, BCChunk* chunk) {
    bc_chunk_dump_internal(out, chunk);
}

void bc_chunk_dump(BCChunk* chunk) {
    bc_chunk_dump_internal(stdout, chunk);
}

char* bc_program_dump(ASTNode* program) {
    FILE* mem = NULL;
    char* buffer = NULL;
    size_t size = 0;

    mem = open_memstream(&buffer, &size);
    if (!mem) return NULL;

    if (program && program->type == NODE_PROGRAM && program->program.statements) {
        ASTNode* main_func = NULL;
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if ((stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION || stmt->type == NODE_ASYNC_FUNCTION) &&
                stmt->function.name && strcmp(stmt->function.name, "main") == 0) {
                main_func = stmt;
                break;
            }
        }
        if (main_func) {
            BCChunk* chunk = bc_compile_statement_list(main_func->function.body, "main");
            bc_chunk_dump_internal(mem, chunk);
            bc_chunk_free(chunk);
        } else {
            BCChunk* chunk = bc_compile_statement_list(program->program.statements, "program");
            bc_chunk_dump_internal(mem, chunk);
            bc_chunk_free(chunk);
        }
    }

    fclose(mem);
    return buffer;
}

// ------------------------------------------------------------
// AST / value helpers
// ------------------------------------------------------------

static Value bc_nil_value(void) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.type = 0;
    v.int_val = 0;
    return v;
}

static Value bc_copy_value(Value v) {
    Value out = v;
    if (v.type == 2 && v.string_val) out.string_val = strdup(v.string_val);
    return out;
}

static int bc_truthy(Value v) {
    switch (v.type) {
        case 0: return v.int_val != 0;
        case 1: return v.float_val != 0.0;
        case 2: return v.string_val && v.string_val[0] != '\0';
        case 3: return v.bool_val != 0;
        case 8: return v.array_val.count > 0;
        case VALUE_TYPE_DICT: return v.dict_val.count > 0;
        default: return 1;
    }
}

static ASTNode* bc_value_to_literal(Value v) {
    switch (v.type) {
        case 0: return create_number_node(v.int_val);
        case 1: return create_float_node(v.float_val);
        case 2: return create_string_node(v.string_val ? v.string_val : "");
        case 3: return create_bool_node(v.bool_val);
        default: return create_nil_node();
    }
}

static Value bc_apply_binary(Value left, Value right, BCOpCode op) {
    Value result = bc_nil_value();

    if ((left.type == 0 || left.type == 1) && (right.type == 0 || right.type == 1)) {
        double a = (left.type == 1) ? left.float_val : (double)left.int_val;
        double b = (right.type == 1) ? right.float_val : (double)right.int_val;
        int is_float = (left.type == 1 || right.type == 1);

        switch (op) {
            case BC_ADD: result.type = is_float ? 1 : 0; if (is_float) result.float_val = a + b; else result.int_val = (int)(a + b); break;
            case BC_SUB: result.type = is_float ? 1 : 0; if (is_float) result.float_val = a - b; else result.int_val = (int)(a - b); break;
            case BC_MUL: result.type = is_float ? 1 : 0; if (is_float) result.float_val = a * b; else result.int_val = (int)(a * b); break;
            case BC_DIV: result.type = 1; result.float_val = b == 0 ? 0.0 : a / b; break;
            case BC_MOD: result.type = 0; result.int_val = (int)a % (int)b; break;
            case BC_EQ: result.type = 3; result.bool_val = a == b; break;
            case BC_NEQ: result.type = 3; result.bool_val = a != b; break;
            case BC_LT: result.type = 3; result.bool_val = a < b; break;
            case BC_LTE: result.type = 3; result.bool_val = a <= b; break;
            case BC_GT: result.type = 3; result.bool_val = a > b; break;
            case BC_GTE: result.type = 3; result.bool_val = a >= b; break;
            default: break;
        }
        return result;
    }

    if (op == BC_ADD && left.type == 2 && right.type == 2) {
        size_t len = strlen(left.string_val ? left.string_val : "") + strlen(right.string_val ? right.string_val : "") + 1;
        result.type = 2;
        result.string_val = (char*)malloc(len);
        snprintf(result.string_val, len, "%s%s", left.string_val ? left.string_val : "", right.string_val ? right.string_val : "");
        return result;
    }

    switch (op) {
        case BC_AND: result.type = 3; result.bool_val = bc_truthy(left) && bc_truthy(right); break;
        case BC_OR: result.type = 3; result.bool_val = bc_truthy(left) || bc_truthy(right); break;
        case BC_EQ: result.type = 3; result.bool_val = (left.type == right.type); break;
        case BC_NEQ: result.type = 3; result.bool_val = (left.type != right.type); break;
        default: break;
    }
    return result;
}

static Value bc_call_ast_function(ASTNode* node, Environment* closure, Value* args, int arg_count);

static Value bc_call_value(Value callee, Value* args, int arg_count) {
    Value result = bc_nil_value();

    if (callee.type == 5) {
        call_c_function(&callee, args, arg_count, &result);
        return result;
    }

    if (callee.type == 4) {
        return bc_call_ast_function(callee.func_val.node, callee.func_val.closure, args, arg_count);
    }

    if (callee.type == 9) {
        return bc_call_ast_function(callee.lambda_val.node, callee.lambda_val.closure, args, arg_count);
    }

    return result;
}

// ------------------------------------------------------------
// Compiler
// ------------------------------------------------------------

typedef struct {
    BCChunk* chunk;
} BCCompiler;

static BCChunk* bc_compile_statement_list(ASTNodeList* list, const char* name);
static void bc_compile_stmt(BCCompiler* c, ASTNode* node);
static void bc_compile_expr(BCCompiler* c, ASTNode* node);

static BCInstruction bc_ins(BCOpCode op) {
    BCInstruction ins;
    memset(&ins, 0, sizeof(ins));
    ins.op = op;
    return ins;
}

static BCChunk* bc_compile_statement_list(ASTNodeList* list, const char* name) {
    BCChunk* chunk = bc_chunk_new(name);
    BCCompiler c = { .chunk = chunk };
    if (list) {
        for (int i = 0; i < list->count; i++) {
            bc_compile_stmt(&c, list->nodes[i]);
        }
    }
    bc_chunk_emit(chunk, bc_ins(BC_HALT));
    return chunk;
}

static BCChunk* bc_compile_expr_chunk(ASTNode* expr, const char* name) {
    BCChunk* chunk = bc_chunk_new(name);
    BCCompiler c = { .chunk = chunk };
    bc_compile_expr(&c, expr);
    bc_chunk_emit(chunk, bc_ins(BC_HALT));
    return chunk;
}

static void bc_emit_eval_expr(BCCompiler* c, ASTNode* node) {
    BCInstruction ins = bc_ins(BC_EVAL_EXPR);
    ins.node = node;
    bc_chunk_emit(c->chunk, ins);
}

static void bc_emit_eval_stmt(BCCompiler* c, ASTNode* node) {
    BCInstruction ins = bc_ins(BC_EVAL_STMT);
    ins.node = node;
    bc_chunk_emit(c->chunk, ins);
}

static int bc_is_ident(ASTNode* node) {
    return node && node->type == NODE_IDENTIFIER;
}

static void bc_compile_dict_entries(BCCompiler* c, ASTNodeList* entries) {
    if (!entries) return;
    for (int i = 0; i < entries->count; i++) {
        ASTNode* pair = entries->nodes[i];
        if (pair && pair->type == NODE_BINARY_OP && pair->binary.op == OP_ASSIGN) {
            bc_compile_expr(c, pair->binary.left);
            bc_compile_expr(c, pair->binary.right);
        } else {
            bc_compile_expr(c, pair);
            bc_chunk_emit(c->chunk, bc_ins(BC_PUSH_NIL));
        }
    }
}

static void bc_compile_expr(BCCompiler* c, ASTNode* node) {
    if (!node) {
        bc_chunk_emit(c->chunk, bc_ins(BC_PUSH_NIL));
        return;
    }

    switch (node->type) {
        case NODE_NUMBER: {
            BCInstruction ins = bc_ins(BC_PUSH_INT);
            ins.a = node->number.value;
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_FLOAT: {
            BCInstruction ins = bc_ins(BC_PUSH_FLOAT);
            ins.num = node->float_val.value;
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_STRING: {
            BCInstruction ins = bc_ins(BC_PUSH_STRING);
            ins.str = bc_strdup0(node->string_val.value);
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_BOOL: {
            BCInstruction ins = bc_ins(BC_PUSH_BOOL);
            ins.a = node->bool_val.value;
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_NIL:
            bc_chunk_emit(c->chunk, bc_ins(BC_PUSH_NIL));
            break;
        case NODE_IDENTIFIER: {
            BCInstruction ins = bc_ins(BC_LOAD_NAME);
            ins.str = bc_strdup0(node->identifier.name);
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_UNARY_OP: {
            bc_compile_expr(c, node->unary.operand);
            switch (node->unary.op) {
                case OP_NOT: bc_chunk_emit(c->chunk, bc_ins(BC_NOT)); break;
                case OP_NEG: bc_chunk_emit(c->chunk, bc_ins(BC_NEG)); break;
                default: bc_emit_eval_expr(c, node); break;
            }
            break;
        }
        case NODE_BINARY_OP: {
            if (node->binary.op == OP_ASSIGN && bc_is_ident(node->binary.left)) {
                bc_compile_expr(c, node->binary.right);
                BCInstruction dup = bc_ins(BC_DUP);
                bc_chunk_emit(c->chunk, dup);
                BCInstruction st = bc_ins(BC_STORE_NAME);
                st.a = 0;
                st.str = bc_strdup0(node->binary.left->identifier.name);
                bc_chunk_emit(c->chunk, st);
                break;
            }
            if ((node->binary.op == OP_ADD_ASSIGN || node->binary.op == OP_SUB_ASSIGN ||
                 node->binary.op == OP_MUL_ASSIGN || node->binary.op == OP_DIV_ASSIGN ||
                 node->binary.op == OP_MOD_ASSIGN) && bc_is_ident(node->binary.left)) {
                BCInstruction ld = bc_ins(BC_LOAD_NAME);
                ld.str = bc_strdup0(node->binary.left->identifier.name);
                bc_chunk_emit(c->chunk, ld);
                bc_compile_expr(c, node->binary.right);
                switch (node->binary.op) {
                    case OP_ADD_ASSIGN: bc_chunk_emit(c->chunk, bc_ins(BC_ADD)); break;
                    case OP_SUB_ASSIGN: bc_chunk_emit(c->chunk, bc_ins(BC_SUB)); break;
                    case OP_MUL_ASSIGN: bc_chunk_emit(c->chunk, bc_ins(BC_MUL)); break;
                    case OP_DIV_ASSIGN: bc_chunk_emit(c->chunk, bc_ins(BC_DIV)); break;
                    case OP_MOD_ASSIGN: bc_chunk_emit(c->chunk, bc_ins(BC_MOD)); break;
                    default: break;
                }
                BCInstruction dup = bc_ins(BC_DUP);
                bc_chunk_emit(c->chunk, dup);
                BCInstruction st = bc_ins(BC_STORE_NAME);
                st.a = 0;
                st.str = bc_strdup0(node->binary.left->identifier.name);
                bc_chunk_emit(c->chunk, st);
                break;
            }
            bc_compile_expr(c, node->binary.left);
            bc_compile_expr(c, node->binary.right);
            switch (node->binary.op) {
                case OP_ADD: bc_chunk_emit(c->chunk, bc_ins(BC_ADD)); break;
                case OP_SUB: bc_chunk_emit(c->chunk, bc_ins(BC_SUB)); break;
                case OP_MUL: bc_chunk_emit(c->chunk, bc_ins(BC_MUL)); break;
                case OP_DIV: bc_chunk_emit(c->chunk, bc_ins(BC_DIV)); break;
                case OP_MOD: bc_chunk_emit(c->chunk, bc_ins(BC_MOD)); break;
                case OP_EQ: bc_chunk_emit(c->chunk, bc_ins(BC_EQ)); break;
                case OP_NEQ: bc_chunk_emit(c->chunk, bc_ins(BC_NEQ)); break;
                case OP_LT: bc_chunk_emit(c->chunk, bc_ins(BC_LT)); break;
                case OP_LTE: bc_chunk_emit(c->chunk, bc_ins(BC_LTE)); break;
                case OP_GT: bc_chunk_emit(c->chunk, bc_ins(BC_GT)); break;
                case OP_GTE: bc_chunk_emit(c->chunk, bc_ins(BC_GTE)); break;
                case OP_AND: bc_chunk_emit(c->chunk, bc_ins(BC_AND)); break;
                case OP_OR: bc_chunk_emit(c->chunk, bc_ins(BC_OR)); break;
                default: bc_emit_eval_expr(c, node); break;
            }
            break;
        }
        case NODE_ARRAY: {
            if (node->array.elements) {
                for (int i = 0; i < node->array.elements->count; i++) {
                    bc_compile_expr(c, node->array.elements->nodes[i]);
                }
                BCInstruction ins = bc_ins(BC_BUILD_ARRAY);
                ins.a = node->array.elements->count;
                bc_chunk_emit(c->chunk, ins);
            } else {
                BCInstruction ins = bc_ins(BC_BUILD_ARRAY);
                ins.a = 0;
                bc_chunk_emit(c->chunk, ins);
            }
            break;
        }
        case NODE_DICT: {
            bc_compile_dict_entries(c, node->dict.entries);
            BCInstruction ins = bc_ins(BC_BUILD_DICT);
            ins.a = node->dict.entries ? node->dict.entries->count : 0;
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_CALL: {
            bc_compile_expr(c, node->call.callee);
            if (node->call.args) {
                for (int i = 0; i < node->call.args->count; i++) {
                    bc_compile_expr(c, node->call.args->nodes[i]);
                }
            }
            BCInstruction ins = bc_ins(BC_CALL);
            ins.a = node->call.args ? node->call.args->count : 0;
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_TERNARY: {
            BCInstruction ins = bc_ins(BC_IF);
            ins.a = 1; // expression mode
            ins.chunk_a = bc_compile_expr_chunk(node->ternary.condition, "ternary_cond");
            ins.chunk_b = bc_compile_expr_chunk(node->ternary.true_expr, "ternary_then");
            ins.chunk_c = bc_compile_expr_chunk(node->ternary.false_expr, "ternary_else");
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        default:
            bc_emit_eval_expr(c, node);
            break;
    }
}

static void bc_compile_stmt(BCCompiler* c, ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            if (node->program.statements) {
                for (int i = 0; i < node->program.statements->count; i++) {
                    bc_compile_stmt(c, node->program.statements->nodes[i]);
                }
            }
            break;
        case NODE_LET:
        case NODE_CONST:
        case NODE_MUTS:
            bc_compile_expr(c, node->type == NODE_MUTS ? node->muts_decl.value : node->var_decl.value);
            {
                BCInstruction st = bc_ins(BC_STORE_NAME);
                st.a = 0;
                st.str = bc_strdup0(node->type == NODE_MUTS ? node->muts_decl.name : node->var_decl.name);
                bc_chunk_emit(c->chunk, st);
            }
            break;
        case NODE_EXPR_STMT:
            bc_compile_expr(c, node->expr_stmt.expr);
            bc_chunk_emit(c->chunk, bc_ins(BC_POP));
            break;
        case NODE_RETURN:
            if (node->return_stmt.value) bc_compile_expr(c, node->return_stmt.value);
            else bc_chunk_emit(c->chunk, bc_ins(BC_PUSH_NIL));
            bc_chunk_emit(c->chunk, bc_ins(BC_RETURN));
            break;
        case NODE_BREAK:
            bc_chunk_emit(c->chunk, bc_ins(BC_BREAK));
            break;
        case NODE_CONTINUE:
            bc_chunk_emit(c->chunk, bc_ins(BC_CONTINUE));
            break;
        case NODE_IF: {
            BCInstruction ins = bc_ins(BC_IF);
            ins.a = 0;
            ins.chunk_a = bc_compile_expr_chunk(node->if_stmt.condition, "if_cond");
            ins.chunk_b = bc_compile_statement_list(node->if_stmt.then_branch, "if_then");
            ins.chunk_c = bc_compile_statement_list(node->if_stmt.else_branch, "if_else");
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_WHILE: {
            BCInstruction ins = bc_ins(BC_WHILE);
            ins.chunk_a = bc_compile_expr_chunk(node->while_stmt.condition, "while_cond");
            ins.chunk_b = bc_compile_statement_list(node->while_stmt.body, "while_body");
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_LOOP: {
            BCInstruction ins = bc_ins(BC_LOOP);
            ins.chunk_a = bc_compile_statement_list(node->loop_stmt.body, "loop_body");
            bc_chunk_emit(c->chunk, ins);
            break;
        }
        case NODE_FUNCTION:
        case NODE_PUBLIC_FUNCTION:
        case NODE_ASYNC_FUNCTION:
        case NODE_STRUCT:
        case NODE_STRUCT_EXTENDS:
        case NODE_ENUM:
        case NODE_IMPL:
        case NODE_IMPORT:
        case NODE_EXPORT:
        case NODE_USE:
        case NODE_PACKET:
        case NODE_MODULE:
            bc_chunk_emit(c->chunk, bc_ins(BC_NOP));
            break;
        case NODE_NNL:
        case NODE_JMP:
        case NODE_TRY:
        case NODE_THROW:
        case NODE_MATCH:
        case NODE_FOR:
        case NODE_FOR_IN:
        case NODE_FOR_RANGE:
        case NODE_AWAIT:
        case NODE_AWAIT_BLOCK:
        case NODE_SPAWN:
        case NODE_SYSF:
        case NODE_SH:
        case NODE_LAMBDA:
        case NODE_METHOD_CALL:
        case NODE_MEMBER_ACCESS:
        case NODE_STATIC_ACCESS:
        case NODE_ARRAY_ACCESS:
        case NODE_DICT_ACCESS:
        case NODE_STRUCT_INIT:
        case NODE_F_STRING:
        case NODE_PATTERN_ARRAY:
        case NODE_PATTERN_BINDING:
        case NODE_PATTERN_NUMBER:
        case NODE_PATTERN_STRING:
        case NODE_PATTERN_IDENT:
        case NODE_PATTERN_WILDCARD:
        case NODE_TYPE_DEF:
        case NODE_OPTIONAL_TYPE:
        case NODE_ARRAY_TYPE:
        case NODE_DICT_TYPE:
        case NODE_RETURN_STRUCT_FIELD:
        case NODE_MATCH_CASE:
            bc_emit_eval_stmt(c, node);
            break;
        case NODE_BINARY_OP:
        case NODE_UNARY_OP:
        case NODE_NUMBER:
        case NODE_FLOAT:
        case NODE_STRING:
        case NODE_BOOL:
        case NODE_NIL:
        case NODE_IDENTIFIER:
        case NODE_ARRAY:
        case NODE_DICT:
        case NODE_TERNARY:
            bc_compile_expr(c, node);
            bc_chunk_emit(c->chunk, bc_ins(BC_POP));
            break;
        default:
            bc_emit_eval_stmt(c, node);
            break;
    }
}

// ------------------------------------------------------------
// VM
// ------------------------------------------------------------

typedef struct {
    Value* data;
    int count;
    int capacity;
} ValueStack;

static void stack_push(ValueStack* st, Value v) {
    if (st->count >= st->capacity) {
        st->capacity = st->capacity == 0 ? 32 : st->capacity * 2;
        st->data = (Value*)realloc(st->data, st->capacity * sizeof(Value));
    }
    st->data[st->count++] = v;
}

static Value stack_pop(ValueStack* st) {
    if (st->count <= 0) return bc_nil_value();
    return st->data[--st->count];
}

static Value stack_peek(ValueStack* st) {
    if (st->count <= 0) return bc_nil_value();
    return st->data[st->count - 1];
}

static Value bc_run_chunk(BCChunk* chunk, Environment* env, int* control);

static Value bc_call_ast_function(ASTNode* node, Environment* closure, Value* args, int arg_count) {
    Environment* fn_env = create_env(closure);

    ASTNodeList* params = NULL;
    ASTNodeList* body = NULL;

    if (node->type == NODE_FUNCTION || node->type == NODE_PUBLIC_FUNCTION || node->type == NODE_ASYNC_FUNCTION) {
        params = node->function.params;
        body = node->function.body;
    } else if (node->type == NODE_LAMBDA) {
        params = node->lambda.params;
        body = node->lambda.body;
    }

    for (int i = 0; params && i < params->count; i++) {
        ASTNode* param = params->nodes[i];
        const char* pname = NULL;
        ASTNode* default_value = NULL;
        if (param->type == NODE_PARAM) {
            pname = param->param.name;
            default_value = param->param.default_value;
        } else if (param->type == NODE_IDENTIFIER) {
            pname = param->identifier.name;
        }
        if (!pname) continue;

        if (i < arg_count) {
            env_set(fn_env, (char*)pname, bc_copy_value(args[i]));
        } else if (default_value) {
            env_set(fn_env, (char*)pname, evaluate_expr(default_value, fn_env));
        } else {
            env_set(fn_env, (char*)pname, bc_nil_value());
        }
    }

    BCChunk* body_chunk = bc_compile_statement_list(body, "fn_body");
    int control = 0;
    Value ret = bc_run_chunk(body_chunk, fn_env, &control);
    bc_chunk_free(body_chunk);
    free(fn_env);
    if (control == 1) return ret;
    return ret;
}

static Value bc_run_chunk(BCChunk* chunk, Environment* env, int* control) {
    ValueStack st = {0};
    if (control) *control = 0;

    for (int ip = 0; ip < chunk->count; ip++) {
        BCInstruction* ins = &chunk->code[ip];
        switch (ins->op) {
            case BC_NOP:
                break;
            case BC_PUSH_INT: {
                Value v = bc_nil_value();
                v.type = 0; v.int_val = ins->a;
                stack_push(&st, v);
                break;
            }
            case BC_PUSH_FLOAT: {
                Value v = bc_nil_value();
                v.type = 1; v.float_val = ins->num;
                stack_push(&st, v);
                break;
            }
            case BC_PUSH_STRING: {
                Value v = bc_nil_value();
                v.type = 2; v.string_val = bc_strdup0(ins->str ? ins->str : "");
                stack_push(&st, v);
                break;
            }
            case BC_PUSH_BOOL: {
                Value v = bc_nil_value();
                v.type = 3; v.bool_val = ins->a;
                stack_push(&st, v);
                break;
            }
            case BC_PUSH_NIL:
                stack_push(&st, bc_nil_value());
                break;
            case BC_LOAD_NAME: {
                Value* found = env_get(env, ins->str);
                if (!found) {
                    fprintf(stderr, "Bytecode error: undefined name '%s'\n", ins->str ? ins->str : "<null>");
                    stack_push(&st, bc_nil_value());
                } else {
                    stack_push(&st, bc_copy_value(*found));
                }
                break;
            }
            case BC_STORE_NAME: {
                Value v = stack_pop(&st);
                env_set(env, ins->str, v);
                if (ins->a) stack_push(&st, v);
                break;
            }
            case BC_POP:
                (void)stack_pop(&st);
                break;
            case BC_DUP: {
                Value v = stack_peek(&st);
                stack_push(&st, bc_copy_value(v));
                break;
            }
            case BC_ADD:
            case BC_SUB:
            case BC_MUL:
            case BC_DIV:
            case BC_MOD:
            case BC_EQ:
            case BC_NEQ:
            case BC_LT:
            case BC_LTE:
            case BC_GT:
            case BC_GTE:
            case BC_AND:
            case BC_OR: {
                Value right = stack_pop(&st);
                Value left = stack_pop(&st);
                stack_push(&st, bc_apply_binary(left, right, ins->op));
                break;
            }
            case BC_NOT: {
                Value v = stack_pop(&st);
                Value out = bc_nil_value();
                out.type = 3;
                out.bool_val = !bc_truthy(v);
                stack_push(&st, out);
                break;
            }
            case BC_NEG: {
                Value v = stack_pop(&st);
                Value out = bc_nil_value();
                if (v.type == 1) { out.type = 1; out.float_val = -v.float_val; }
                else { out.type = 0; out.int_val = -v.int_val; }
                stack_push(&st, out);
                break;
            }
            case BC_ASSIGN:
            case BC_ADD_ASSIGN:
            case BC_SUB_ASSIGN:
            case BC_MUL_ASSIGN:
            case BC_DIV_ASSIGN:
            case BC_MOD_ASSIGN:
                break;
            case BC_BUILD_ARRAY: {
                int count = ins->a;
                ASTNodeList* list = create_node_list();
                Value* tmp = NULL;
                if (count > 0) tmp = (Value*)malloc(count * sizeof(Value));
                for (int i = count - 1; i >= 0; i--) {
                    tmp[i] = stack_pop(&st);
                }
                for (int i = 0; i < count; i++) {
                    add_to_node_list(list, bc_value_to_literal(tmp[i]));
                }
                free(tmp);
                Value arr = bc_nil_value();
                arr.type = 8;
                arr.array_val.elements = list;
                arr.array_val.count = count;
                stack_push(&st, arr);
                break;
            }
            case BC_BUILD_DICT: {
                int pairs = ins->a;
                Value dict = bc_nil_value();
                dict.type = VALUE_TYPE_DICT;
                dict.dict_val.entries = NULL;
                dict.dict_val.count = 0;
                dict.dict_val.capacity = 0;
                for (int i = 0; i < pairs; i++) {
                    Value val = stack_pop(&st);
                    Value key = stack_pop(&st);
                    if (dict.dict_val.count >= dict.dict_val.capacity) {
                        dict.dict_val.capacity = dict.dict_val.capacity == 0 ? 8 : dict.dict_val.capacity * 2;
                        dict.dict_val.entries = realloc(dict.dict_val.entries, dict.dict_val.capacity * sizeof(*dict.dict_val.entries));
                    }
                    dict.dict_val.entries[dict.dict_val.count].key = (Value*)malloc(sizeof(Value));
                    dict.dict_val.entries[dict.dict_val.count].value = (Value*)malloc(sizeof(Value));
                    *dict.dict_val.entries[dict.dict_val.count].key = bc_copy_value(key);
                    *dict.dict_val.entries[dict.dict_val.count].value = bc_copy_value(val);
                    dict.dict_val.count++;
                }
                stack_push(&st, dict);
                break;
            }
            case BC_CALL: {
                int argc = ins->a;
                Value* args = NULL;
                if (argc > 0) args = (Value*)malloc(argc * sizeof(Value));
                for (int i = argc - 1; i >= 0; i--) args[i] = stack_pop(&st);
                Value callee = stack_pop(&st);
                Value ret = bc_call_value(callee, args, argc);
                free(args);
                stack_push(&st, ret);
                break;
            }
            case BC_EVAL_EXPR:
                stack_push(&st, evaluate_expr(ins->node, env));
                break;
            case BC_EVAL_STMT: {
                int rc = evaluate_statement(ins->node, env, NULL);
                if (rc == 1 || rc == 2 || rc == 3) {
                    Value out = stack_peek(&st);
                    if (control) *control = rc;
                    free(st.data);
                    return out;
                }
                break;
            }
            case BC_IF: {
                int cond_control = 0;
                Value cond = bc_run_chunk(ins->chunk_a, env, &cond_control);
                if (cond_control != 0) {
                    if (control) *control = cond_control;
                    free(st.data);
                    return cond;
                }
                if (bc_truthy(cond)) {
                    if (ins->chunk_b) {
                        int branch_control = 0;
                        Value branch = bc_run_chunk(ins->chunk_b, env, &branch_control);
                        if (branch_control != 0) {
                            if (control) *control = branch_control;
                            free(st.data);
                            return branch;
                        }
                        if (ins->a) stack_push(&st, branch);
                    } else if (ins->a) {
                        stack_push(&st, bc_nil_value());
                    }
                } else {
                    if (ins->chunk_c) {
                        int branch_control = 0;
                        Value branch = bc_run_chunk(ins->chunk_c, env, &branch_control);
                        if (branch_control != 0) {
                            if (control) *control = branch_control;
                            free(st.data);
                            return branch;
                        }
                        if (ins->a) stack_push(&st, branch);
                    } else if (ins->a) {
                        stack_push(&st, bc_nil_value());
                    }
                }
                break;
            }
            case BC_WHILE: {
                while (1) {
                    int cond_control = 0;
                    Value cond = bc_run_chunk(ins->chunk_a, env, &cond_control);
                    if (cond_control != 0) {
                        Value out = stack_peek(&st);
                        if (control) *control = cond_control;
                        free(st.data);
                        return out;
                    }
                    if (!bc_truthy(cond)) break;

                    int body_control = 0;
                    Value body = bc_run_chunk(ins->chunk_b, env, &body_control);
                    (void)body;
                    if (body_control == 1) {
                        if (control) *control = 1;
                        free(st.data);
                        return body;
                    }
                    if (body_control == 2) break;
                    if (body_control == 3) continue;
                }
                break;
            }
            case BC_LOOP: {
                while (1) {
                    int body_control = 0;
                    Value body = bc_run_chunk(ins->chunk_a, env, &body_control);
                    (void)body;
                    if (body_control == 1) { if (control) *control = 1; free(st.data); return body; }
                    if (body_control == 2) break;
                    if (body_control == 3) continue;
                }
                break;
            }
            case BC_RETURN: {
                Value ret = st.count ? stack_pop(&st) : bc_nil_value();
                if (control) *control = 1;
                free(st.data);
                return ret;
            }
            case BC_BREAK: {
                Value out = stack_peek(&st);
                if (control) *control = 2;
                free(st.data);
                return out;
            }
            case BC_CONTINUE: {
                Value out = stack_peek(&st);
                if (control) *control = 3;
                free(st.data);
                return out;
            }
            case BC_HALT:
                if (control) *control = 0;
                goto done;
            default:
                break;
        }
    }

done:
    if (st.count > 0) {
        Value out = stack_pop(&st);
        free(st.data);
        return out;
    }
    free(st.data);
    return bc_nil_value();
}

// ------------------------------------------------------------
// Program runner
// ------------------------------------------------------------

static void bc_setup_globals(Environment* global, ASTNode* program) {
    init_interpreter();
    register_native_c_functions(global);

    ModuleRegistry* reg = get_module_registry();
    char* builtin_path = resolve_module_path(NULL, "__builtin__");
    if (!builtin_path) builtin_path = resolve_module_path(NULL, "./lib/__builtin__");
    if (builtin_path) {
        LoadedModule* builtin = load_module(reg, global, builtin_path, "__builtin__", NULL, NULL);
        if (builtin && builtin->env) {
            for (int i = 0; i < builtin->env->var_count; i++) {
                env_set(global, builtin->env->vars[i].name, builtin->env->vars[i].value);
            }
        }
        free(builtin_path);
    }

    Value argv_val;
    memset(&argv_val, 0, sizeof(argv_val));
    argv_val.type = 8;
    argv_val.array_val.count = goscript_argc;
    if (goscript_argc > 0) {
        ASTNodeList* args_list = create_node_list();
        for (int i = 0; i < goscript_argc; i++) {
            add_to_node_list(args_list, create_string_node(goscript_argv[i]));
        }
        argv_val.array_val.elements = args_list;
    } else {
        argv_val.array_val.elements = NULL;
    }
    env_set(global, "ARGV", argv_val);

    if (program && program->type == NODE_PROGRAM && program->program.statements) {
        // 1) Fonctions
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION || stmt->type == NODE_ASYNC_FUNCTION) {
                Value func_val;
                memset(&func_val, 0, sizeof(func_val));
                func_val.type = 4;
                func_val.func_val.node = stmt;
                func_val.func_val.closure = global;
                env_set(global, stmt->function.name, func_val);
            }
        }

        // 2) Structures
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt->type == NODE_STRUCT) {
                Value struct_val;
                memset(&struct_val, 0, sizeof(struct_val));
                struct_val.type = 6;
                struct_val.struct_val.struct_name = strdup(stmt->struct_def.name);
                struct_val.struct_val.fields = NULL;
                struct_val.struct_val.field_count = 0;
                env_set(global, stmt->struct_def.name, struct_val);
            }
        }

        // 3) Implémentations
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt->type == NODE_IMPL) {
                register_impl(stmt->impl.name, stmt);
            }
        }

        // 4) Imports
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            if (stmt->type == NODE_IMPORT) {
                evaluate_statement(stmt, global, NULL);
            }
        }
    }
}

void interpret_program_bytecode(ASTNode* program, int dump_bytecode) {
    Environment* global = create_env(NULL);
    bc_setup_globals(global, program);

    Value* main_val = env_get(global, "main");
    if (main_val && (main_val->type == 4 || main_val->type == 9)) {
        ASTNode* main_node = (main_val->type == 4) ? main_val->func_val.node : main_val->lambda_val.node;
        ASTNodeList* main_body = NULL;
        if (main_node && main_node->type == NODE_FUNCTION) main_body = main_node->function.body;
        else if (main_node && main_node->type == NODE_PUBLIC_FUNCTION) main_body = main_node->function.body;
        else if (main_node && main_node->type == NODE_ASYNC_FUNCTION) main_body = main_node->function.body;
        else if (main_node && main_node->type == NODE_LAMBDA) main_body = main_node->lambda.body;

        if (dump_bytecode && main_body) {
            BCChunk* main_chunk = bc_compile_statement_list(main_body, "main");
            bc_chunk_dump(main_chunk);
            bc_chunk_free(main_chunk);
        }
        (void)bc_call_value(*main_val, NULL, 0);
    } else {
        BCChunk* program_chunk = bc_compile_statement_list(program ? program->program.statements : NULL, "program");
        if (dump_bytecode) {
            bc_chunk_dump(program_chunk);
        }

        int control = 0;
        (void)bc_run_chunk(program_chunk, global, &control);
        bc_chunk_free(program_chunk);
    }

    free(global);
}
