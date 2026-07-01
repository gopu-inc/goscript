#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>
#include "ast/ast.h"
#include "bytecode/bytecode.h"

extern ASTNode* program_root;
extern FILE* yyin;
extern int yyparse(void);
extern void interpret_program(ASTNode* program);

// ========== VARIABLES GLOBALES POUR LES ARGUMENTS CLI ==========
int goscript_argc = 0;
char** goscript_argv = NULL;
// ================================================================

// ========== PROTOTYPES ==========
void print_ast(ASTNode* node, int depth);
void init_script_args(int argc, char** argv, int start_index);
void free_script_args(void);
// ===============================

// ========== GESTION DES ARGUMENTS CLI ==========

/**
 * Initialise les arguments CLI pour le script
 */
void init_script_args(int argc, char** argv, int start_index) {
    goscript_argc = argc - start_index;
    if (goscript_argc > 0) {
        goscript_argv = malloc(goscript_argc * sizeof(char*));
        for (int i = 0; i < goscript_argc; i++) {
            goscript_argv[i] = strdup(argv[start_index + i]);
        }
    } else {
        goscript_argv = NULL;
    }
}

/**
 * Libère les arguments CLI
 */
void free_script_args(void) {
    if (goscript_argv) {
        for (int i = 0; i < goscript_argc; i++) {
            free(goscript_argv[i]);
        }
        free(goscript_argv);
        goscript_argv = NULL;
    }
    goscript_argc = 0;
}

// ========== STRUCTURE POUR LES OPTIONS ==========

typedef struct {
    int debug_mode;         // -d, --debug
    int bytecode_mode;      // --bytecode
    int dump_bytecode;      // --dump-bytecode
    int emit_gbc;           // --emit-gbc
    int emit_native_gbc;    // --emit-native-gbc / --emit-obj
    int repl_mode;          // -i, --interactive
    int show_help;          // -h, --help
    int show_version;       // -v, --version
    char* output_file;      // -o, --output
    char* filename;         // Fichier à exécuter
    int script_args_start;  // Index où commencent les arguments du script
} GoscriptOptions;

static int ends_with(const char* s, const char* suffix) {
    if (!s || !suffix) return 0;
    size_t sl = strlen(s), su = strlen(suffix);
    return sl >= su && strcmp(s + sl - su, suffix) == 0;
}

static char* read_file_text(const char* path, size_t* out_len) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size < 0) { fclose(f); return NULL; }
    char* buf = malloc((size_t)size + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)size, f);
    buf[n] = '\0';
    if (out_len) *out_len = n;
    fclose(f);
    return buf;
}

static FILE* make_tmp_source(const char* source) {
    FILE* tmp = tmpfile();
    if (!tmp) return NULL;
    fwrite(source, 1, strlen(source), tmp);
    rewind(tmp);
    return tmp;
}

typedef struct {
    char magic[4];
    uint32_t version;
    uint32_t flags;
    uint64_t source_len;
    uint64_t bytecode_len;
} GBCHeader;

static int write_gbc_file(const char* path, const char* source, const char* bytecode_dump, uint32_t flags) {
    FILE* f = fopen(path, "wb");
    if (!f) return 0;
    GBCHeader h = {{'G','B','C','1'}, 1, flags, (uint64_t)strlen(source), bytecode_dump ? (uint64_t)strlen(bytecode_dump) : 0};
    if (fwrite(&h, sizeof(h), 1, f) != 1) { fclose(f); return 0; }
    if (h.source_len && fwrite(source, 1, (size_t)h.source_len, f) != h.source_len) { fclose(f); return 0; }
    if (h.bytecode_len && fwrite(bytecode_dump, 1, (size_t)h.bytecode_len, f) != h.bytecode_len) { fclose(f); return 0; }
    fclose(f);
    return 1;
}

static void fprint_c_string(FILE* f, const char* s) {
    fputc('"', f);
    for (const unsigned char* p = (const unsigned char*)s; p && *p; p++) {
        if (*p == '\\' || *p == '"') fprintf(f, "\\%c", *p);
        else if (*p == '\n') fprintf(f, "\\n");
        else if (*p == '\r') fprintf(f, "\\r");
        else if (*p == '\t') fprintf(f, "\\t");
        else if (*p < 32 || *p > 126) fprintf(f, "\\x%02x", *p);
        else fputc(*p, f);
    }
    fputc('"', f);
}

static int emit_native_gbc_object(const char* output, const char* source, const char* runner_path) {
    char tmp_path[] = "./.goscript_gbc_XXXXXX.c";
    int fd = mkstemps(tmp_path, 2);
    if (fd < 0) return 0;
    FILE* c = fdopen(fd, "w");
    if (!c) { close(fd); return 0; }

    fprintf(c, "#include <unistd.h>\n#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\n");
    fprintf(c, "static const char goscript_runner[] = ");
    fprint_c_string(c, runner_path && runner_path[0] ? runner_path : "gd");
    fprintf(c, ";\n");
    fprintf(c, "static const unsigned char goscript_src[] = {\n");
    for (size_t i = 0; source[i]; i++) {
        fprintf(c, "0x%02x,", (unsigned char)source[i]);
        if ((i + 1) % 16 == 0) fprintf(c, "\n");
    }
    fprintf(c, "0x00};\n");
    fprintf(c,
        "int main(int argc, char** argv){\n"
        "  char path[] = \"./.goscript_exec_XXXXXX.gjs\";\n"
        "  int fd = mkstemps(path, 4); if(fd < 0){perror(\"mkstemps\"); return 1;}\n"
        "  size_t len = sizeof(goscript_src)-1; if(write(fd, goscript_src, len) != (ssize_t)len){perror(\"write\"); return 1;} close(fd);\n"
        "  char** nargv = calloc((size_t)argc + 4, sizeof(char*)); if(!nargv) return 1;\n"
        "  nargv[0] = (char*)goscript_runner; nargv[1] = \"--bytecode\"; nargv[2] = path;\n"
        "  for(int i=1;i<argc;i++) nargv[i+2] = argv[i];\n"
        "  execv(goscript_runner, nargv);\n"
        "  nargv[0] = \"./gd\"; execv(\"./gd\", nargv);\n"
        "  nargv[0] = \"gd\"; execvp(\"gd\", nargv); perror(\"exec gd\"); return 127;\n"
        "}\n");
    fclose(c);

    char cmd[2048];
    snprintf(cmd, sizeof(cmd), "cc -c -x c '%s' -o '%s'", tmp_path, output);
    int rc = system(cmd);
    unlink(tmp_path);
    return rc == 0;
}

static int read_gbc_file(const char* path, char** source_out, char** bytecode_out, uint32_t* flags_out) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;
    GBCHeader h;
    if (fread(&h, sizeof(h), 1, f) != 1) { fclose(f); return 0; }
    if (memcmp(h.magic, "GBC1", 4) != 0) { fclose(f); return 0; }
    char* source = malloc((size_t)h.source_len + 1);
    char* bc = NULL;
    if (!source) { fclose(f); return 0; }
    if (fread(source, 1, (size_t)h.source_len, f) != h.source_len) { free(source); fclose(f); return 0; }
    source[h.source_len] = '\0';
    if (h.bytecode_len > 0) {
        bc = malloc((size_t)h.bytecode_len + 1);
        if (!bc) { free(source); fclose(f); return 0; }
        if (fread(bc, 1, (size_t)h.bytecode_len, f) != h.bytecode_len) { free(source); free(bc); fclose(f); return 0; }
        bc[h.bytecode_len] = '\0';
    }
    fclose(f);
    if (source_out) *source_out = source; else free(source);
    if (bytecode_out) *bytecode_out = bc; else free(bc);
    if (flags_out) *flags_out = h.flags;
    return 1;
}

/**
 * Parse les options de ligne de commande
 */
GoscriptOptions parse_options(int argc, char** argv) {
    GoscriptOptions opts = {0};
    opts.filename = NULL;
    opts.script_args_start = argc;

    int i = 1;
    while (i < argc) {
        char* arg = argv[i];
        if (strcmp(arg, "--") == 0) { opts.script_args_start = i + 1; break; }
        if (arg[0] != '-' || strcmp(arg, "-") == 0) {
            if (!opts.filename) {
                opts.filename = arg;
                opts.script_args_start = i + 1;
            } else {
                opts.script_args_start = i;
                break;
            }
            i++;
            continue;
        }
        if (strcmp(arg, "--debug") == 0) opts.debug_mode = 1;
        else if (strcmp(arg, "--interactive") == 0) opts.repl_mode = 1;
        else if (strcmp(arg, "--bytecode") == 0) opts.bytecode_mode = 1;
        else if (strcmp(arg, "--dump-bytecode") == 0) { opts.dump_bytecode = 1; opts.bytecode_mode = 1; }
        else if (strcmp(arg, "--emit-gbc") == 0) opts.emit_gbc = 1;
        else if (strcmp(arg, "--emit-native-gbc") == 0 || strcmp(arg, "--emit-obj") == 0) opts.emit_native_gbc = 1;
        else if (strcmp(arg, "--output") == 0 || strcmp(arg, "-o") == 0) {
            if (i + 1 < argc) opts.output_file = argv[++i];
        } else if (strncmp(arg, "-o", 2) == 0 && strlen(arg) > 2) {
            opts.output_file = arg + 2;
        } else if (strcmp(arg, "-d") == 0) opts.debug_mode = 1;
        else if (strcmp(arg, "-i") == 0) opts.repl_mode = 1;
        else if (strcmp(arg, "-h") == 0) opts.show_help = 1;
        else if (strcmp(arg, "-v") == 0) opts.show_version = 1;
        else {
            for (size_t j = 1; arg[j]; j++) {
                switch (arg[j]) {
                    case 'd': opts.debug_mode = 1; break;
                    case 'i': opts.repl_mode = 1; break;
                    case 'h': opts.show_help = 1; break;
                    case 'v': opts.show_version = 1; break;
                    case 'b': opts.bytecode_mode = 1; break;
                    case 'e': opts.emit_gbc = 1; break;
                    case 'n': opts.emit_native_gbc = 1; break;
                    case 'o':
                        if (arg[j + 1]) { opts.output_file = &arg[j + 1]; j = strlen(arg) - 1; }
                        else if (i + 1 < argc) { opts.output_file = argv[++i]; }
                        break;
                    default: break;
                }
            }
        }
        i++;
    }
    return opts;
}

/**
 * Affiche l'aide
 */
void show_help(const char* program_name) {
    printf("Goscript - A modern scripting language\n");
    printf("Version: 0.2.0\n\n");
    printf("Usage: %s [options] <script.gjs> [script-args...]\n\n", program_name);
    printf("Options:\n");
    printf("  -d, --debug         Show AST before execution\n");
    printf("  -b, --bytecode       Run through the bytecode VM\n");
    printf("  -e, --emit-gbc       Emit .gbc package\n");
    printf("  -n, --emit-native-gbc Emit linkable ELF object named .gbc\n");
    printf("  -o, --output FILE    Output .gbc path\n");
    printf("      --dump-bytecode  Print generated bytecode\n");
    printf("  -i, --interactive    Start REPL mode\n");
    printf("  -h, --help           Show this help message\n");
    printf("  -v, --version        Show version information\n");
    printf("  --                 End of GD options, start of script arguments\n\n");
    printf("Examples:\n");
    printf("  %s script.gjs\n", program_name);
    printf("  %s -d script.gjs --server 8080\n", program_name);
    printf("  %s script.gjs --input file.txt --output result.txt\n", program_name);
    printf("  %s script.gjs -- --server 8080 --debug\n", program_name);
    printf("    (Le -- sépare les flags GD des flags du script)\n");
}

/**
 * Affiche la version
 */
void show_version(void) {
    printf("Goscript v0.2.0\n");
    printf("Copyright (c) 2026 Gopu.inc Team\n");
    printf("Build date: 2026-04-23\n");
}

// ========== MAIN PRINCIPAL ==========

int main(int argc, char** argv) {
    // Parser les options
    GoscriptOptions opts = parse_options(argc, argv);
    
    // Afficher l'aide
    if (opts.show_help) {
        show_help(argv[0]);
        return 0;
    }
    
    // Afficher la version
    if (opts.show_version) {
        show_version();
        return 0;
    }
    
    // Mode REPL
    if (!opts.filename || opts.repl_mode) {
        if (opts.filename) {
            printf("REPL mode with file preload: %s\n", opts.filename);
        }
        printf("REPL mode coming soon!\n");
        printf("Please provide a file: %s <file.gjs>\n", argv[0]);
        return 1;
    }

    // Initialiser les arguments du script
    init_script_args(argc, argv, opts.script_args_start);

    // Charger le fichier source ou .gbc
    char* source_text = NULL;
    char* loaded_bc_dump = NULL;
    uint32_t gbc_flags = 0;
    if (ends_with(opts.filename, ".gbc")) {
        if (!read_gbc_file(opts.filename, &source_text, &loaded_bc_dump, &gbc_flags)) {
            fprintf(stderr, "Error: Cannot open GBC '%s'\n", opts.filename);
            free_script_args();
            return 1;
        }
        opts.bytecode_mode = 1;
    } else {
        source_text = read_file_text(opts.filename, NULL);
        if (!source_text) {
            fprintf(stderr, "Error: Cannot open '%s'\n", opts.filename);
            free_script_args();
            return 1;
        }
    }

    // Parser depuis la mémoire
    yyin = make_tmp_source(source_text);
    if (!yyin) {
        fprintf(stderr, "Error: Cannot create temp source\n");
        free(source_text);
        free(loaded_bc_dump);
        free_script_args();
        return 1;
    }

    int parse_result = yyparse();
    fclose(yyin);

    if (parse_result != 0 || !program_root) {
        fprintf(stderr, "Error: Parsing failed\n");
        free(source_text);
        free(loaded_bc_dump);
        free_script_args();
        return 1;
    }

    if (opts.debug_mode) {
        printf("\n╔══════════════════════════════════════════════════════════════╗\n");
        printf("║                         AST DEBUG                           ║\n");
        printf("╚══════════════════════════════════════════════════════════════╝\n\n");
        print_ast(program_root, 0);
        printf("\n╔══════════════════════════════════════════════════════════════╗\n");
        printf("║                      END AST DEBUG                         ║\n");
        printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    }

    // Générer .gbc container si demandé
    if (opts.emit_gbc) {
        char* bc_dump = bc_program_dump(program_root);
        char* out = opts.output_file;
        char auto_out[1024];
        if (!out) {
            const char* base = strrchr(opts.filename, '/');
            base = base ? base + 1 : opts.filename;
            snprintf(auto_out, sizeof(auto_out), "%s.gbc", base);
            out = auto_out;
        }
        if (!write_gbc_file(out, source_text, bc_dump ? bc_dump : "", gbc_flags | (opts.bytecode_mode ? 1u : 0u))) {
            fprintf(stderr, "Error: Cannot write '%s'\n", out);
        } else {
            printf("Wrote %s\n", out);
        }
        free(bc_dump);
    }

    // Générer un objet ELF linkable par lld/ld si demandé.
    // Exemple: ./gd -n -o app.gbc main.gjs && cc app.gbc -o app
    if (opts.emit_native_gbc) {
        char* out = opts.output_file;
        char auto_out[1024];
        if (!out) {
            const char* base = strrchr(opts.filename, '/');
            base = base ? base + 1 : opts.filename;
            snprintf(auto_out, sizeof(auto_out), "%s.native.gbc", base);
            out = auto_out;
        }
        char runner_path[PATH_MAX];
        const char* runner = argv[0];
        if (realpath(argv[0], runner_path)) runner = runner_path;
        if (!emit_native_gbc_object(out, source_text, runner)) {
            fprintf(stderr, "Error: Cannot emit native object '%s'\n", out);
        } else {
            printf("Wrote native object %s\n", out);
            printf("Link: cc %s -o app  # ou clang -fuse-ld=lld %s -o app\n", out, out);
        }
    }

    if (opts.emit_gbc || opts.emit_native_gbc) {
        goto cleanup;
    }

    // Exécuter le programme
    if (opts.bytecode_mode) {
        interpret_program_bytecode(program_root, opts.dump_bytecode);
    } else {
        interpret_program(program_root);
    }

cleanup:
    free_ast(program_root);
    free(source_text);
    free(loaded_bc_dump);
    free_script_args();
    return 0;
}

// ========== FONCTION D'AFFICHAGE DE L'AST ==========

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
            if (node->function.is_async) printf(" (async)");
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
            
        case NODE_FOR_IN:
            printf("ForIn: %s in ", node->for_in.var);
            print_ast(node->for_in.collection, 0);
            printf("\n");
            if (node->for_in.body) {
                for (int i = 0; i < node->for_in.body->count; i++) {
                    print_ast(node->for_in.body->nodes[i], depth + 1);
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
            
        case NODE_TERNARY:
            printf("(");
            print_ast(node->ternary.condition, 0);
            printf(" ? ");
            print_ast(node->ternary.true_expr, 0);
            printf(" : ");
            print_ast(node->ternary.false_expr, 0);
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
            
        case NODE_DICT:
            printf("Dict: {");
            if (node->dict.entries) {
                for (int i = 0; i < node->dict.entries->count; i++) {
                    if (i > 0) printf(", ");
                    print_ast(node->dict.entries->nodes[i], 0);
                }
            }
            printf("}\n");
            break;
            
        case NODE_DICT_ACCESS:
            printf("DictAccess: ");
            print_ast(node->dict_access.dict, 0);
            printf("[");
            print_ast(node->dict_access.key, 0);
            printf("]\n");
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
            
        case NODE_TRY:
            printf("Try\n");
            if (node->try_stmt.try_body) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Body:\n");
                for (int i = 0; i < node->try_stmt.try_body->count; i++) {
                    print_ast(node->try_stmt.try_body->nodes[i], depth + 2);
                }
            }
            if (node->try_stmt.catch_block) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Catch:\n");
                print_ast(node->try_stmt.catch_block, depth + 2);
            }
            if (node->try_stmt.finally_block) {
                for (int i = 0; i < depth + 1; i++) printf("  ");
                printf("Finally:\n");
                print_ast(node->try_stmt.finally_block, depth + 2);
            }
            break;
            
        case NODE_THROW:
            printf("Throw: ");
            print_ast(node->throw_stmt.value, 0);
            printf("\n");
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
            
        case NODE_SYSF:
            printf("Sysf: ");
            print_ast(node->sysf.command, 0);
            printf("\n");
            break;
            
        case NODE_SH:
            printf("Sh: ");
            print_ast(node->sysf.command, 0);
            printf("\n");
            break;
            
        case NODE_AWAIT:
            printf("Await: ");
            print_ast(node->await.expr, 0);
            printf("\n");
            break;
            
        case NODE_SPAWN:
            printf("Spawn: ");
            print_ast(node->spawn.expr, 0);
            printf("\n");
            break;
            
        case NODE_USE:
            printf("Use: %s", node->use_stmt.path);
            if (node->use_stmt.symbols) {
                printf(" {");
                for (int i = 0; i < node->use_stmt.symbols->count; i++) {
                    if (i > 0) printf(", ");
                    print_ast(node->use_stmt.symbols->nodes[i], 0);
                }
                printf("}");
            }
            if (node->use_stmt.alias) {
                printf(" as %s", node->use_stmt.alias);
            }
            printf("\n");
            break;
            
        case NODE_F_STRING:
            printf("FString: \"%s\"\n", node->f_string.template);
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
            
        case NODE_PATTERN_ARRAY:
            printf("PatternArray: [");
            if (node->pattern_array.elements) {
                for (int i = 0; i < node->pattern_array.elements->count; i++) {
                    if (i > 0) printf(", ");
                    print_ast(node->pattern_array.elements->nodes[i], 0);
                }
            }
            printf("]\n");
            break;
            
        case NODE_PATTERN_BINDING:
            printf("PatternBinding: lt %s\n", node->pattern_binding.var_name);
            break;
            
        case NODE_DICT_TYPE:
            printf("DictType: <");
            print_ast(node->dict_type.key_type, 0);
            printf(", ");
            print_ast(node->dict_type.value_type, 0);
            printf(">\n");
            break;
            
        default:
            printf("Node(%d)\n", node->type);
            break;
    }
}
