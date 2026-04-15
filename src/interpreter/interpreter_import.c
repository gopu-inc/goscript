#include "interpreter.h"
#include <libgen.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern ASTNode* program_root;
extern int yyparse(void);
extern FILE* yyin;
extern void free_ast(ASTNode* node);
extern int evaluate_statement(ASTNode* node, Environment* env, char* current_file);
extern Value evaluate_expr(ASTNode* node, Environment* env);
extern void interpret_program(ASTNode* program);
extern void register_impl(char* struct_name, ASTNode* impl_node);
extern void env_set(Environment* env, char* name, Value value);
extern Environment* create_env(Environment* parent);
extern int yylineno;
extern void register_native_c_functions(Environment* env);

// ==================== CONSTANTES ====================

#define MODULE_STATUS_UNLOADED 0
#define MODULE_STATUS_LOADING 1
#define MODULE_STATUS_LOADED 2
#define MODULE_STATUS_ERROR 3

// ==================== GESTION DU CACHE ====================

static LoadedModule* modules[1024];
static int module_count = 0;
static int module_capacity = 1024;

static LoadedModule* find_module_by_path(const char* path) {
    for (int i = 0; i < module_count; i++) {
        if (modules[i] && modules[i]->module_path && 
            strcmp(modules[i]->module_path, path) == 0) {
            return modules[i];
        }
    }
    return NULL;
}

static LoadedModule* find_module_by_name(const char* name) {
    for (int i = 0; i < module_count; i++) {
        if (modules[i] && modules[i]->module_name && 
            strcmp(modules[i]->module_name, name) == 0) {
            return modules[i];
        }
    }
    return NULL;
}

static LoadedModule* create_module(const char* path, const char* name, const char* alias) {
    if (module_count >= module_capacity) {
        fprintf(stderr, "Module registry full\n");
        return NULL;
    }
    
    LoadedModule* mod = malloc(sizeof(LoadedModule));
    if (!mod) return NULL;
    
    mod->module_path = path ? strdup(path) : NULL;
    mod->module_name = name ? strdup(name) : NULL;
    mod->alias = alias ? strdup(alias) : NULL;
    mod->status = MODULE_STATUS_LOADING;
    mod->env = create_env(NULL);
    mod->ref_count = 1;
    
    mod->constraints.allowed_names = NULL;
    mod->constraints.allowed_count = 0;
    mod->constraints.timeout_ms = 0;
    mod->constraints.sandbox = 0;
    mod->constraints.allow_ffi = 1;
    
    modules[module_count++] = mod;
    return mod;
}

static void free_module(LoadedModule* mod) {
    if (!mod) return;
    
    if (mod->module_path) free(mod->module_path);
    if (mod->module_name) free(mod->module_name);
    if (mod->alias) free(mod->alias);
    if (mod->env) free(mod->env);
    
    if (mod->constraints.allowed_names) {
        for (int i = 0; i < mod->constraints.allowed_count; i++) {
            if (mod->constraints.allowed_names[i]) free(mod->constraints.allowed_names[i]);
        }
        free(mod->constraints.allowed_names);
    }
    
    free(mod);
}

static void register_export(LoadedModule* mod, const char* symbol, const char* alias) {
    if (!mod || !symbol) return;
    
    if (!mod->constraints.allowed_names) {
        mod->constraints.allowed_names = malloc(32 * sizeof(char*));
        mod->constraints.allowed_count = 0;
    }
    
    // Vérifier si déjà exporté
    for (int i = 0; i < mod->constraints.allowed_count; i++) {
        if (mod->constraints.allowed_names[i] && 
            strcmp(mod->constraints.allowed_names[i], symbol) == 0) {
            return;
        }
    }
    
    const char* export_name = alias ? alias : symbol;
    mod->constraints.allowed_names[mod->constraints.allowed_count] = strdup(export_name);
    mod->constraints.allowed_count++;
}

// ==================== RÉSOLUTION DE CHEMIN ====================
char* resolve_module_path(char* current_file, char* import_path) {
    char resolved[PATH_MAX];
    
    // Chemins de recherche pour les modules
    const char* search_paths[] = {
        "./modules",                      // modules/__builtin__.gjs
        "./lib",                          // lib/__builtin__.gjs
        "./lib/std",
        "./src",                          // src/__builtin__.gjs
        "/usr/local/lib/goscript/protocole",       // Chemin spécial pour le builtin
        "/usr/local/lib/goscript",
        "/usr/local/lib/goscript/std",
        "/usr/lib/goscript",
        "./",                             // ./__builtin__.gjs
        NULL
    };
    
    // Cas spécial: __builtin__ (module intégré)
    if (strcmp(import_path, "__builtin__") == 0) {
        // Vérifier d'abord dans le chemin spécial
        char special_path[PATH_MAX];
        snprintf(special_path, PATH_MAX, "/usr/local/lib/goscript/protocole/__builtin__.gjs");
        if (access(special_path, F_OK) == 0) {
            if (realpath(special_path, resolved)) {
                return strdup(resolved);
            }
        }
        
        // Sinon chercher dans tous les chemins
        for (int i = 0; search_paths[i]; i++) {
            char with_ext[PATH_MAX];
            snprintf(with_ext, PATH_MAX, "%s/__builtin__.gjs", search_paths[i]);
            if (access(with_ext, F_OK) == 0) {
                char real_path[PATH_MAX];
                if (realpath(with_ext, real_path)) {
                    return strdup(real_path);
                }
            }
        }
        
        // Dernier recours: chercher dans le répertoire courant
        if (access("__builtin__.gjs", F_OK) == 0) {
            if (realpath("__builtin__.gjs", resolved)) {
                return strdup(resolved);
            }
        }
        
        fprintf(stderr, "Warning: __builtin__.gjs not found in any search path\n");
        return NULL;
    }
    
    // 1. Chemin absolu
    if (import_path[0] == '/') {
        snprintf(resolved, PATH_MAX, "%s", import_path);
        
        char with_ext[PATH_MAX];
        snprintf(with_ext, PATH_MAX, "%s.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            if (realpath(with_ext, resolved)) {
                return strdup(resolved);
            }
        }
        
        snprintf(with_ext, PATH_MAX, "%s/__self__.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            if (realpath(with_ext, resolved)) {
                return strdup(resolved);
            }
        }
        
        if (access(resolved, F_OK) == 0) {
            if (realpath(resolved, resolved)) {
                return strdup(resolved);
            }
        }
    }
    
    // 2. Chemin relatif
    if (import_path[0] == '.') {
        char base[PATH_MAX];
        
        if (current_file && current_file[0] && strcmp(current_file, "REPL") != 0) {
            strcpy(base, current_file);
            char* dir = dirname(base);
            snprintf(resolved, PATH_MAX, "%s/%s", dir, import_path);
        } else {
            if (getcwd(resolved, PATH_MAX) == NULL) {
                return NULL;
            }
            strcat(resolved, "/");
            strcat(resolved, import_path);
        }
        
        char clean_path[PATH_MAX];
        if (realpath(resolved, clean_path)) {
            strcpy(resolved, clean_path);
        }
        
        char with_ext[PATH_MAX];
        snprintf(with_ext, PATH_MAX, "%s.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            if (realpath(with_ext, resolved)) {
                return strdup(resolved);
            }
        }
        
        snprintf(with_ext, PATH_MAX, "%s/__self__.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            if (realpath(with_ext, resolved)) {
                return strdup(resolved);
            }
        }
        
        if (access(resolved, F_OK) == 0) {
            if (realpath(resolved, resolved)) {
                return strdup(resolved);
            }
        }
    }
    
    // 3. Recherche dans les chemins standards
    for (int i = 0; search_paths[i]; i++) {
        char with_ext[PATH_MAX];
        snprintf(with_ext, PATH_MAX, "%s/%s.gjs", search_paths[i], import_path);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        snprintf(with_ext, PATH_MAX, "%s/%s/__self__.gjs", search_paths[i], import_path);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        snprintf(with_ext, PATH_MAX, "%s/%s", search_paths[i], import_path);
        if (access(with_ext, F_OK) == 0) {
            struct stat path_stat;
            if (stat(with_ext, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode)) {
                char real_path[PATH_MAX];
                if (realpath(with_ext, real_path)) {
                    return strdup(real_path);
                }
            }
        }
    }
    
    return NULL;
}

// ==================== TRAITEMENT DES CONTRAINTES ====================

void process_constraints(LoadedModule* module, ASTNode* constraints) {
    (void)module;
    (void)constraints;
}

int is_name_allowed(LoadedModule* module, char* name) {
    (void)module;
    (void)name;
    return 1;
}

int is_ffi_allowed(LoadedModule* module) {
    (void)module;
    return 1;
}

// ==================== CHARGEMENT DE MODULE ===================

LoadedModule* load_module(ModuleRegistry* reg, Environment* parent_env,
                          char* current_file, char* import_path, 
                          char* alias, ASTNode* constraints) {
    (void)reg;
    (void)constraints;
    
    // 1. Résoudre le chemin
    char* full_path = resolve_module_path(current_file, import_path);
    if (!full_path) {
        fprintf(stderr, "Module not found: %s\n", import_path);
        return NULL;
    }
    
    // 2. Vérifier le cache
    LoadedModule* existing = find_module_by_path(full_path);
    if (existing) {
        if (existing->status == MODULE_STATUS_LOADING) {
            fprintf(stderr, "Circular import detected: %s\n", import_path);
            free(full_path);
            return NULL;
        }
        
        existing->ref_count++;
        
        Value module_val;
        module_val.type = 7;
        module_val.int_val = (int)existing;
        env_set(parent_env, alias ? alias : existing->module_name, module_val);
        
        free(full_path);
        return existing;
    }
    
    // 3. Créer le module
    LoadedModule* mod = create_module(full_path, import_path, alias);
    free(full_path);
    
    if (!mod) return NULL;
    
    // 4. Lire le fichier
    FILE* f = fopen(mod->module_path, "r");
    if (!f) {
        mod->status = MODULE_STATUS_ERROR;
        return NULL;
    }
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* source = malloc(size + 1);
    if (!source) {
        fclose(f);
        mod->status = MODULE_STATUS_ERROR;
        return NULL;
    }
    
    fread(source, 1, size, f);
    source[size] = '\0';
    fclose(f);
    
    // 5. Parser le module
    FILE* old_yyin = yyin;
    int old_lineno = yylineno;
    
    yyin = fmemopen(source, size, "r");
    if (!yyin) {
        free(source);
        mod->status = MODULE_STATUS_ERROR;
        return NULL;
    }
    
    yylineno = 1;
    
    int parse_result = yyparse();
    fclose(yyin);
    yyin = old_yyin;
    yylineno = old_lineno;
    
    if (parse_result != 0 || !program_root) {
        mod->status = MODULE_STATUS_ERROR;
        free(source);
        return NULL;
    }
    
    // 6. Enregistrer les fonctions natives dans l'environnement du module
    register_native_c_functions((Environment*)mod->env);
    
    // 7. Évaluer le contenu du module pour remplir son environnement
    if (program_root && program_root->type == NODE_PROGRAM) {
        for (int i = 0; i < program_root->program.statements->count; i++) {
            ASTNode* stmt = program_root->program.statements->nodes[i];
            
            switch (stmt->type) {
                case NODE_MODULE:
                    // Ignorer la déclaration module
                    break;
                    
                case NODE_CONST:
                case NODE_LET:
                    {
                        Value val = evaluate_expr(stmt->var_decl.value, (Environment*)mod->env);
                        env_set((Environment*)mod->env, stmt->var_decl.name, val);
                        if (stmt->var_decl.is_public) {
                            register_export(mod, stmt->var_decl.name, NULL);
                        }
                    }
                    break;
                    
                case NODE_FUNCTION:
                case NODE_PUBLIC_FUNCTION:
                    {
                        Value func_val;
                        func_val.type = 4;
                        func_val.func_val.node = stmt;
                        func_val.func_val.closure = (Environment*)mod->env;
                        env_set((Environment*)mod->env, stmt->function.name, func_val);
                        if (stmt->type == NODE_PUBLIC_FUNCTION || stmt->function.is_public) {
                            register_export(mod, stmt->function.name, NULL);
                        }
                    }
                    break;
                    
                case NODE_STRUCT:
                    {
                        Value struct_val;
                        struct_val.type = 6;
                        struct_val.struct_val.struct_name = strdup(stmt->struct_def.name);
                        struct_val.struct_val.fields = NULL;
                        struct_val.struct_val.field_count = 0;
                        env_set((Environment*)mod->env, stmt->struct_def.name, struct_val);
                        if (stmt->struct_def.is_public) {
                            register_export(mod, stmt->struct_def.name, NULL);
                        }
                    }
                    break;
                    
                case NODE_IMPL:
                    register_impl(stmt->impl.name, stmt);
                    break;
                    
                case NODE_EXPORT:
                    register_export(mod, stmt->export.name, NULL);
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    // 8. Marquer comme chargé
    mod->status = MODULE_STATUS_LOADED;
    
    // 9. Lier le module à l'environnement parent
    Value module_val;
    module_val.type = 7;
    module_val.int_val = (int)mod;
    env_set(parent_env, alias ? alias : mod->module_name, module_val);
    
    // 10. Nettoyage
    free_ast(program_root);
    program_root = NULL;
    free(source);
    
    return mod;
}

// ==================== FONCTIONS D'ACCÈS ====================

ModuleRegistry* init_module_registry(void) {
    return NULL;
}

void register_module(ModuleRegistry* reg, LoadedModule* mod) {
    (void)reg;
    (void)mod;
}

LoadedModule* find_module(ModuleRegistry* reg, char* path) {
    (void)reg;
    return find_module_by_path(path);
}

void free_module_registry(ModuleRegistry* reg) {
    (void)reg;
    for (int i = 0; i < module_count; i++) {
        free_module(modules[i]);
        modules[i] = NULL;
    }
    module_count = 0;
}

void dump_modules(void) {
    printf("\n=== MODULE REGISTRY ===\n");
    for (int i = 0; i < module_count; i++) {
        LoadedModule* mod = modules[i];
        printf("Module %d:\n", i);
        printf("  Path: %s\n", mod->module_path ? mod->module_path : "(null)");
        printf("  Name: %s\n", mod->module_name ? mod->module_name : "(null)");
        printf("  Alias: %s\n", mod->alias ? mod->alias : "(null)");
        printf("  Status: %d\n", mod->status);
        printf("  RefCount: %d\n", mod->ref_count);
        printf("  Exports: %d\n", mod->constraints.allowed_count);
        printf("\n");
    }
    printf("Total modules: %d\n", module_count);
    printf("========================\n");
}
