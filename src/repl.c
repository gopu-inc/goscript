#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ast.h"

extern ASTNode* program_root;
extern FILE* yyin;
extern int yyparse(void);
extern void interpret_program(ASTNode* program);
extern void free_ast(ASTNode* node);

// Couleurs ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Mots-clés pour coloration
const char* keywords[] = {
    "fn", "lt", "cn", "ret", "if", "else", "for", "while", 
    "loop", "break", "import", "true", "false", "nil", NULL
};

char* colorize(const char* line) {
    static char buffer[8192];
    buffer[0] = '\0';
    char word[256];
    int i = 0, j;
    
    while (line[i] != '\0') {
        // Chaînes
        if (line[i] == '"') {
            strcat(buffer, GREEN);
            strcat(buffer, "\"");
            i++;
            while (line[i] != '"' && line[i] != '\0') {
                char c[2] = {line[i], '\0'};
                strcat(buffer, c);
                i++;
            }
            if (line[i] == '"') {
                strcat(buffer, "\"");
                i++;
            }
            strcat(buffer, RESET);
            continue;
        }
        
        // Commentaires
        if (line[i] == '/' && line[i+1] == '/') {
            strcat(buffer, CYAN);
            while (line[i] != '\0') {
                char c[2] = {line[i], '\0'};
                strcat(buffer, c);
                i++;
            }
            strcat(buffer, RESET);
            break;
        }
        
        // Mots (identifiants, mots-clés)
        if ((line[i] >= 'a' && line[i] <= 'z') || 
            (line[i] >= 'A' && line[i] <= 'Z') || 
            line[i] == '_') {
            j = 0;
            while ((line[i] >= 'a' && line[i] <= 'z') ||
                   (line[i] >= 'A' && line[i] <= 'Z') ||
                   (line[i] >= '0' && line[i] <= '9') ||
                   line[i] == '_') {
                word[j++] = line[i++];
            }
            word[j] = '\0';
            
            int is_keyword = 0;
            for (int k = 0; keywords[k] != NULL; k++) {
                if (strcmp(word, keywords[k]) == 0) {
                    strcat(buffer, BOLD MAGENTA);
                    strcat(buffer, word);
                    strcat(buffer, RESET);
                    is_keyword = 1;
                    break;
                }
            }
            
            if (!is_keyword) {
                strcat(buffer, word);
            }
            continue;
        }
        
        // Nombres
        if (line[i] >= '0' && line[i] <= '9') {
            strcat(buffer, YELLOW);
            while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') {
                char c[2] = {line[i], '\0'};
                strcat(buffer, c);
                i++;
            }
            strcat(buffer, RESET);
            continue;
        }
        
        // Opérateurs
        if (strchr("+-*/=<>!&|%", line[i])) {
            strcat(buffer, BLUE);
            char c[2] = {line[i], '\0'};
            strcat(buffer, c);
            strcat(buffer, RESET);
            i++;
            continue;
        }
        
        // Parenthèses, accolades
        if (strchr("(){}[];,", line[i])) {
            strcat(buffer, RED);
            char c[2] = {line[i], '\0'};
            strcat(buffer, c);
            strcat(buffer, RESET);
            i++;
            continue;
        }
        
        // Caractères normaux
        char c[2] = {line[i], '\0'};
        strcat(buffer, c);
        i++;
    }
    
    return buffer;
}

int evaluate_line(const char* line) {
    if (strlen(line) == 0) return 0;
    
    char temp_file[] = "/tmp/goscript_XXXXXX";
    int fd = mkstemp(temp_file);
    if (fd == -1) {
        printf("Error: Cannot create temp file\n");
        return 1;
    }
    
    write(fd, line, strlen(line));
    write(fd, "\n", 1);
    close(fd);
    
    yyin = fopen(temp_file, "r");
    if (!yyin) {
        unlink(temp_file);
        return 1;
    }
    
    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result == 0 && program_root) {
        interpret_program(program_root);
        free_ast(program_root);
        program_root = NULL;
    } else if (parse_result != 0) {
        printf("%sError: Parsing failed%s\n", RED, RESET);
    }
    
    unlink(temp_file);
    return 0;
}

void show_help() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║  Goscript REPL - Interactive Mode                ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Commands:                                       ║\n");
    printf("║    .exit    - Exit REPL                          ║\n");
    printf("║    .help    - Show this help                     ║\n");
    printf("║    .clear   - Clear screen                       ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Features:                                       ║\n");
    printf("║    • Syntax highlighting                         ║\n");
    printf("║    • Command history (↑/↓ arrows)                ║\n");
    printf("║    • Multi-line input (use \\ at end)             ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Examples:                                       ║\n");
    printf("║    >>> lt a = 10                                 ║\n");
    printf("║    >>> lt b = 20                                 ║\n");
    printf("║    >>> println(a + b)                            ║\n");
    printf("║    30                                            ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");
    printf("\n");
}

int repl_main() {
    printf("\n");
    printf("%s╔══════════════════════════════════════════════════╗%s\n", BOLD CYAN, RESET);
    printf("%s║       Goscript REPL v1.0                        ║%s\n", BOLD CYAN, RESET);
    printf("%s║       Type .help for help                       ║%s\n", BOLD CYAN, RESET);
    printf("%s╚══════════════════════════════════════════════════╝%s\n", BOLD CYAN, RESET);
    printf("\n");
    
    char* input;
    char* multiline_buffer = NULL;
    
    while (1) {
        char* prompt = get_prompt();
        input = readline(prompt);
        
        if (!input) {
            printf("\n");
            break;
        }
        
        if (strlen(input) > 0) {
            add_history(input);
        }
        
        // Commandes
        if (strcmp(input, ".exit") == 0) {
            free(input);
            break;
        } else if (strcmp(input, ".help") == 0) {
            show_help();
            free(input);
            continue;
        } else if (strcmp(input, ".clear") == 0) {
            printf("\033[2J\033[H");
            free(input);
            continue;
        }
        
        // Multi-line
        if (strlen(input) > 0 && input[strlen(input)-1] == '\\') {
            if (multiline_buffer == NULL) {
                multiline_buffer = malloc(1);
                multiline_buffer[0] = '\0';
            }
            size_t len = strlen(multiline_buffer) + strlen(input);
            multiline_buffer = realloc(multiline_buffer, len + 1);
            strcat(multiline_buffer, input);
            multiline_buffer[len-1] = ' ';
            free(input);
            continue;
        }
        
        if (multiline_buffer) {
            size_t len = strlen(multiline_buffer) + strlen(input) + 1;
            multiline_buffer = realloc(multiline_buffer, len);
            strcat(multiline_buffer, input);
            free(input);
            evaluate_line(multiline_buffer);
            free(multiline_buffer);
            multiline_buffer = NULL;
        } else {
            evaluate_line(input);
            free(input);
        }
        printf("\n");
    }
    
    printf("%sGoodbye!%s\n", GREEN, RESET);
    return 0;
}
