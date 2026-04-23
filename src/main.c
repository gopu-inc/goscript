// main.c - Version améliorée avec support CLI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"

extern ASTNode* program_root;
extern FILE* yyin;
extern int yyparse(void);
extern void interpret_program(ASTNode* program);

// ========== NOUVEAU: GESTION DES ARGUMENTS CLI ==========

// Variable globale pour stocker les arguments du script
int goscript_argc = 0;
char** goscript_argv = NULL;

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
void free_script_args() {
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
    int debug_mode;      // -d, --debug
    int repl_mode;       // -i, --interactive
    int show_help;       // -h, --help
    int show_version;    // -v, --version
    char* filename;      // Fichier à exécuter
    int script_args_start; // Index où commencent les arguments du script
} GoscriptOptions;

/**
 * Parse les options de ligne de commande
 */
GoscriptOptions parse_options(int argc, char** argv) {
    GoscriptOptions opts = {0};
    opts.filename = NULL;
    opts.script_args_start = argc; // Par défaut, pas d'arguments script
    
    int i = 1;
    while (i < argc) {
        // Flags de l'interpréteur (préfixés par -)
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            opts.debug_mode = 1;
            i++;
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interactive") == 0) {
            opts.repl_mode = 1;
            i++;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            opts.show_help = 1;
            i++;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            opts.show_version = 1;
            i++;
        }
        // Séparateur explicite: -- indique la fin des flags GD et le début des args script
        else if (strcmp(argv[i], "--") == 0) {
            opts.script_args_start = i + 1;
            break;
        }
        // Premier argument non-flag = nom du fichier
        else if (argv[i][0] != '-' && opts.filename == NULL) {
            opts.filename = argv[i];
            opts.script_args_start = i + 1; // Le reste sont des args pour le script
            i++;
        }
        // Si on a déjà le filename, le reste est pour le script
        else if (opts.filename != NULL) {
            opts.script_args_start = i;
            break;
        }
        else {
            i++;
        }
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
    printf("  -d, --debug       Show AST before execution\n");
    printf("  -i, --interactive Start REPL mode\n");
    printf("  -h, --help        Show this help message\n");
    printf("  -v, --version     Show version information\n");
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
void show_version() {
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
    
    // Ouvrir le fichier
    yyin = fopen(opts.filename, "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open '%s'\n", opts.filename);
        free_script_args();
        return 1;
    }
    
    // Parser
    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result != 0 || !program_root) {
        fprintf(stderr, "Error: Parsing failed\n");
        free_script_args();
        return 1;
    }
    
    // Mode debug: afficher l'AST
    if (opts.debug_mode) {
        printf("\n===( AST )===\n");
        print_ast(program_root, 0);
        printf("\n");
    }
    
    // Exécuter le programme
    interpret_program(program_root);
    
    // Nettoyage
    free_ast(program_root);
    free_script_args();
    
    return 0;
}
