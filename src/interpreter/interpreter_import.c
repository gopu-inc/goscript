#include "interpreter.h"
#include <libgen.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>

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

// ==================== TYPES DE MODULES ====================

// ==================== REGISTRY GLOBAL ====================

static LoadedModule* modules[1024];
static int module_count = 0;
static int module_capacity = 1024;

// ==================== UTILITAIRES DE NOMS ====================

/**
 * Transforme "time.ft" en "time/ft"
 */
static void module_name_to_path(const char* name, char* path_out) {
    const char* p = name;
    char* out = path_out;
    
    // 1. Gérer les préfixes relatifs
    if (*p == '.') {
        if (*(p+1) == '.') { 
            // ".." devient "../"
            *out++ = '.'; *out++ = '.'; *out++ = '/';
            p += 2;
        } else { 
            // "." devient "./"
            *out++ = '.'; *out++ = '/';
            p += 1;
        }
    }
    
    // 2. Remplacer le reste des points par des slashes
    while (*p) {
        if (*p == '.') *out++ = '/';
        else *out++ = *p;
        p++;
    }
    *out = '\0';
}

/**
 * Extrait le dernier composant du nom (ex: "time.ft" -> "ft")
 */
static const char* get_last_component(const char* name) {
    const char* last = strrchr(name, '.');
    return last ? last + 1 : name;
}

/**
 * Extrait le parent (ex: "time.ft" -> "time", retourne NULL si pas de parent)
 */
static char* get_parent_name(const char* name) {
    char* dot = strrchr(name, '.');
    if (!dot) return NULL;
    
    int len = dot - name;
    char* parent = malloc(len + 1);
    strncpy(parent, name, len);
    parent[len] = '\0';
    return parent;
}

// ==================== RECHERCHE DANS LE CACHE ====================

static LoadedModule* find_module_by_path(const char* path) {
    if (!path) return NULL;
    for (int i = 0; i < module_count; i++) {
        if (modules[i] && modules[i]->module_path && 
            strcmp(modules[i]->module_path, path) == 0) {
            return modules[i];
        }
    }
    return NULL;
}

static LoadedModule* find_module_by_name(const char* name) {
    if (!name) return NULL;
    for (int i = 0; i < module_count; i++) {
        if (modules[i] && modules[i]->module_name && 
            strcmp(modules[i]->module_name, name) == 0) {
            return modules[i];
        }
    }
    return NULL;
}

// ==================== CRÉATION / DESTRUCTION ====================

static LoadedModule* create_module(const char* path, const char* name, 
                                   const char* alias, ModuleType type) {
    if (module_count >= module_capacity) {
        fprintf(stderr, "[Goscript] Module registry full\n");
        return NULL;
    }
    
    LoadedModule* mod = malloc(sizeof(LoadedModule));
    if (!mod) return NULL;
    
    mod->module_path = path ? strdup(path) : NULL;
    mod->module_name = name ? strdup(name) : NULL;
    mod->alias = alias ? strdup(alias) : NULL;
    mod->type = type;
    mod->parent = NULL;
    mod->submodules.list = NULL;
    mod->submodules.count = 0;
    mod->submodules.capacity = 0;
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
    
    if (mod->submodules.list) {
        free(mod->submodules.list);
    }
    
    if (mod->constraints.allowed_names) {
        for (int i = 0; i < mod->constraints.allowed_count; i++) {
            if (mod->constraints.allowed_names[i]) free(mod->constraints.allowed_names[i]);
        }
        free(mod->constraints.allowed_names);
    }
    
    free(mod);
}

// ==================== GESTION DES SOUS-MODULES ====================

/**
 * Ajoute un sous-module au parent (pour l'API "parent::child::func")
 */
static void add_submodule(LoadedModule* parent, LoadedModule* child) {
    if (!parent || parent->type != MODULE_TYPE_PACKAGE) return;
    if (!child) return;
    
    // Éviter les doublons
    for (int i = 0; i < parent->submodules.count; i++) {
        if (parent->submodules.list[i] == child) return;
    }
    
    if (parent->submodules.count >= parent->submodules.capacity) {
        parent->submodules.capacity = parent->submodules.capacity == 0 ? 4 : parent->submodules.capacity * 2;
        parent->submodules.list = realloc(parent->submodules.list, 
                                          parent->submodules.capacity * sizeof(LoadedModule*));
    }
    
    child->parent = parent;
    parent->submodules.list[parent->submodules.count++] = child;
    
    // Rendre le sous-module accessible dans l'environnement du parent
    const char* short_name = get_last_component(child->module_name);
    
    Value mod_val;
    mod_val.type = 7;
    mod_val.int_val = (int)child;
    
    env_set(parent->env, short_name, mod_val);
}

// ==================== ENREGISTREMENT DES EXPORTS ====================

static void register_export(LoadedModule* mod, const char* symbol, const char* alias) {
    if (!mod || !symbol) return;
    
    if (!mod->constraints.allowed_names) {
        mod->constraints.allowed_names = malloc(32 * sizeof(char*));
        mod->constraints.allowed_count = 0;
    }
    
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
    char module_path[PATH_MAX];
    
    // Convertit "time.ft" en "time/ft", ".client" en "./client"
    module_name_to_path(import_path, module_path);

    // Chemins de recherche standards
    const char* search_paths[] = {
        "./modules",
        "./lib",
        "../lib",
        "../modules",
        "../../lib",
        "../../modules",
        "./lib/std",
        "./src",
        "/usr/local/lib/goscript",
        "/usr/local/lib/goscript/std",
        "/usr/lib/goscript",
        ".",
        "..",
        "../..",
        "../../..",
        "../../../..",
        "../../../../..",
        NULL
    };

    // Cas spécial: __builtin__
    if (strcmp(import_path, "__builtin__") == 0) {
        char special_path[PATH_MAX];
        snprintf(special_path, PATH_MAX, "/usr/local/lib/goscript/__builtin__.gjs");
        if (access(special_path, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(special_path, real_path)) {
                return strdup(real_path);
            }
        }
        
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
        
        if (access("__builtin__.gjs", F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath("__builtin__.gjs", real_path)) {
                return strdup(real_path);
            }
        }
        
        fprintf(stderr, "[Goscript] Warning: __builtin__.gjs not found\n");
        return NULL;
    }
    
    // 1. Chemin absolu
    if (import_path[0] == '/') {
        snprintf(resolved, PATH_MAX, "%s", import_path);
        
        char with_ext[PATH_MAX];
        snprintf(with_ext, PATH_MAX, "%s.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        snprintf(with_ext, PATH_MAX, "%s/__self__.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        if (access(resolved, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(resolved, real_path)) {
                return strdup(real_path);
            }
        }
    }
    
    // 2. Chemin relatif (CORRIGÉ ICI)
    if (import_path[0] == '.') {
        char base[PATH_MAX];
        if (current_file && current_file[0] && strcmp(current_file, "REPL") != 0) {
            strcpy(base, current_file);
            char* dir = dirname(base);
            // CRITIQUE : Utilisation de module_path (ex: "./client") au lieu de import_path (".client")
            snprintf(resolved, PATH_MAX, "%s/%s", dir, module_path);
        } else {
            if (getcwd(resolved, PATH_MAX) == NULL) {
                return NULL;
            }
            strcat(resolved, "/");
            // CRITIQUE : Utilisation de module_path ici aussi
            strcat(resolved, module_path);
        }
        
        char clean_path[PATH_MAX];
        if (realpath(resolved, clean_path)) {
            strcpy(resolved, clean_path);
        }
        
        char with_ext[PATH_MAX];
        snprintf(with_ext, PATH_MAX, "%s.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        snprintf(with_ext, PATH_MAX, "%s/__self__.gjs", resolved);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        struct stat st;
        if (stat(resolved, &st) == 0 && S_ISDIR(st.st_mode)) {
            char real_path[PATH_MAX];
            if (realpath(resolved, real_path)) {
                return strdup(real_path);
            }
        }
    }
    
    // 3. Recherche dans les chemins standards
    for (int i = 0; search_paths[i]; i++) {
        char with_ext[PATH_MAX];
        
        // Fichier .gjs direct
        snprintf(with_ext, PATH_MAX, "%s/%s.gjs", search_paths[i], module_path);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        // Dossier avec __self__.gjs
        snprintf(with_ext, PATH_MAX, "%s/%s/__self__.gjs", search_paths[i], module_path);
        if (access(with_ext, F_OK) == 0) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
        
        // Dossier (package)
        snprintf(with_ext, PATH_MAX, "%s/%s", search_paths[i], module_path);
        struct stat st;
        if (stat(with_ext, &st) == 0 && S_ISDIR(st.st_mode)) {
            char real_path[PATH_MAX];
            if (realpath(with_ext, real_path)) {
                return strdup(real_path);
            }
        }
    }
    
    return NULL;
}


// ==================== CHARGEMENT D'UN FICHIER ====================

static LoadedModule* load_file_module(const char* full_path, const char* module_name, 
                                      const char* alias) {
    // Vérifier le cache
    LoadedModule* existing = find_module_by_path(full_path);
    if (existing) {
        if (existing->status == MODULE_STATUS_LOADING) {
            fprintf(stderr, "[Goscript] Circular import detected: %s\n", module_name);
            return NULL;
        }
        existing->ref_count++;
        return existing;
    }
    
    // Créer le module
    LoadedModule* mod = create_module(full_path, module_name, alias, MODULE_TYPE_FILE);
    if (!mod) return NULL;
    
    // Lire le fichier
    FILE* f = fopen(full_path, "r");
    if (!f) {
        fprintf(stderr, "[Goscript] Cannot open file: %s\n", full_path);
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
    
    // Parser
    FILE* old_yyin = yyin;
    int old_lineno = yylineno;
    ASTNode* old_program_root = program_root;  // <-- SAUVEGARDER L'AST PRINCIPAL
    
    yyin = fmemopen(source, size, "r");
    if (!yyin) {
        free(source);
        mod->status = MODULE_STATUS_ERROR;
        return NULL;
    }
    
    yylineno = 1;
    program_root = NULL;  // <-- RÉINITIALISER POUR LE PARSER
    int parse_result = yyparse();
    fclose(yyin);
    
    yyin = old_yyin;
    yylineno = old_lineno;
    
    if (parse_result != 0 || !program_root) {
        fprintf(stderr, "[Goscript] Parse error in module: %s\n", module_name);
        mod->status = MODULE_STATUS_ERROR;
        program_root = old_program_root;  // <-- RESTAURER
        free(source);
        return NULL;
    }
    
    // Enregistrer les fonctions natives
    register_native_c_functions(mod->env);
    
    // Évaluer le contenu du module (remplit mod->env)
    ASTNode* module_ast = program_root;  // <-- GARDER UNE RÉFÉRENCE
    
    if (module_ast && module_ast->type == NODE_PROGRAM) {
        for (int i = 0; i < module_ast->program.statements->count; i++) {
            ASTNode* stmt = module_ast->program.statements->nodes[i];
            
            switch (stmt->type) {
                case NODE_MODULE:
                    break;
                    
                case NODE_CONST:
                case NODE_LET: {
                    Value val = evaluate_expr(stmt->var_decl.value, mod->env);
                    env_set(mod->env, stmt->var_decl.name, val);
                    if (stmt->var_decl.is_public) {
                        register_export(mod, stmt->var_decl.name, NULL);
                    }
                    break;
                }
                
                case NODE_MUTS: {
                    Value val = evaluate_expr(stmt->muts_decl.value, mod->env);
                    env_set(mod->env, stmt->muts_decl.name, val);
                    if (stmt->muts_decl.is_public) {
                        register_export(mod, stmt->muts_decl.name, NULL);
                    }
                    break;
                }
                
                case NODE_FUNCTION:
                case NODE_PUBLIC_FUNCTION:
                case NODE_ASYNC_FUNCTION: {
                    Value func_val;
                    func_val.type = 4;
                    func_val.func_val.node = stmt;  // <-- POINTE VERS L'AST DU MODULE
                    func_val.func_val.closure = mod->env;
                    env_set(mod->env, stmt->function.name, func_val);
                    if (stmt->type == NODE_PUBLIC_FUNCTION || stmt->function.is_public) {
                        register_export(mod, stmt->function.name, NULL);
                    }
                    break;
                }
                
                case NODE_STRUCT: {
                    Value struct_val;
                    struct_val.type = 6;
                    struct_val.struct_val.struct_name = strdup(stmt->struct_def.name);
                    struct_val.struct_val.fields = NULL;
                    struct_val.struct_val.field_count = 0;
                    env_set(mod->env, stmt->struct_def.name, struct_val);
                    if (stmt->struct_def.is_public) {
                        register_export(mod, stmt->struct_def.name, NULL);
                    }
                    break;
                }
                
                case NODE_STRUCT_EXTENDS: {
                    Value struct_val;
                    struct_val.type = 6;
                    struct_val.struct_val.struct_name = strdup(stmt->struct_extend.name);
                    struct_val.struct_val.fields = NULL;
                    struct_val.struct_val.field_count = 0;
                    env_set(mod->env, stmt->struct_extend.name, struct_val);
                    if (stmt->struct_extend.is_public) {
                        register_export(mod, stmt->struct_extend.name, NULL);
                    }
                    break;
                }
                
                case NODE_ENUM: {
                    Value enum_val;
                    enum_val.type = 6;
                    enum_val.struct_val.struct_name = strdup(stmt->enum_def.name);
                    env_set(mod->env, stmt->enum_def.name, enum_val);
                    break;
                }
                
                case NODE_IMPL:
                    register_impl(stmt->impl.name, stmt);
                    break;
                    
                case NODE_EXPORT:
                    register_export(mod, stmt->export.name, NULL);
                    break;
              
                case NODE_IMPORT:
                    evaluate_statement(stmt, mod->env, full_path);
                    break;
                // ----------------------------------------------
                    
                default:
                    break;
            }

        }
    }
    
    mod->status = MODULE_STATUS_LOADED;
    
    // NE PAS LIBÉRER L'AST DU MODULE !
    // free_ast(module_ast);  // <-- SURTOUT PAS !
    
    program_root = old_program_root;  // <-- RESTAURER L'AST PRINCIPAL
    free(source);
    
    return mod;
}

// ==================== CHARGEMENT D'UN PACKAGE ====================
static LoadedModule* load_package_module(const char* dir_path, const char* module_name, 
                                         const char* alias) {
    // Vérifier le cache
    LoadedModule* existing = find_module_by_path(dir_path);
    if (existing) {
        existing->ref_count++;
        return existing;
    }
    
    // Vérifier si __self__.gjs existe
    char self_path[PATH_MAX];
    snprintf(self_path, PATH_MAX, "%s/__self__.gjs", dir_path);
    
    LoadedModule* mod = NULL;
    
    if (access(self_path, F_OK) == 0) {
        // Charger __self__.gjs comme module principal du package
        mod = load_file_module(self_path, module_name, alias);
        if (mod) {
            mod->type = MODULE_TYPE_PACKAGE;
            // Mettre à jour le chemin pour pointer vers le dossier
            free(mod->module_path);
            mod->module_path = strdup(dir_path);
        }
    } else {
        // Pas de __self__.gjs, créer un package vide (namespace)
        mod = create_module(dir_path, module_name, alias, MODULE_TYPE_PACKAGE);
        if (mod) {
            mod->status = MODULE_STATUS_LOADED;
            register_native_c_functions(mod->env);
        }
    }
    
    return mod;
}

// ==================== CHARGEMENT PRINCIPAL ====================

LoadedModule* load_module(ModuleRegistry* reg, Environment* parent_env,
                          char* current_file, char* import_path, 
                          char* alias, ASTNode* constraints) {
    (void)reg;
    (void)constraints;
    
    if (!import_path) return NULL;
    
    // 1. Résoudre le chemin
    char* full_path = resolve_module_path(current_file, import_path);
    if (!full_path) {
        fprintf(stderr, "[Goscript] Module not found: %s\n", import_path);
        return NULL;
    }
    
    // 2. Déterminer le type et charger
    struct stat st;
    LoadedModule* mod = NULL;
    
    if (stat(full_path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            mod = load_package_module(full_path, import_path, alias);
        } else {
            mod = load_file_module(full_path, import_path, alias);
        }
    }
    
    free(full_path);
    
    if (!mod) return NULL;
    
    // 3. Lier à l'environnement parent
    if (parent_env) {
        const char* env_name = alias ? alias : get_last_component(import_path);
        
        Value module_val;
        module_val.type = 7;
        module_val.int_val = (int)mod;
        env_set(parent_env, env_name, module_val);
        
        // 4. Gérer la hiérarchie parent-enfant
        char* parent_name = get_parent_name(import_path);
        if (parent_name) {
            LoadedModule* parent_mod = find_module_by_name(parent_name);
            if (!parent_mod) {
                // Charger le parent automatiquement
                parent_mod = load_module(NULL, parent_env, current_file, parent_name, NULL, NULL);
            }
            if (parent_mod) {
                add_submodule(parent_mod, mod);
            }
            free(parent_name);
        }
    }
    
    return mod;
}

// ==================== CONTRAINTES ====================

void process_constraints(LoadedModule* module, ASTNode* constraints) {
    (void)module;
    (void)constraints;
}

int is_name_allowed(LoadedModule* module, char* name) {
    if (!module || !name) return 1;
    if (module->constraints.allowed_count == 0) return 1;
    
    for (int i = 0; i < module->constraints.allowed_count; i++) {
        if (module->constraints.allowed_names[i] && 
            strcmp(module->constraints.allowed_names[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_ffi_allowed(LoadedModule* module) {
    return module ? module->constraints.allow_ffi : 1;
}

// ==================== REGISTRY ====================

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
        if (modules[i]) {
            // Libérer l'AST du module si tu le stockes quelque part
            // Pour l'instant, on ne le fait pas car l'AST est partagé
            free_module(modules[i]);
            modules[i] = NULL;
        }
    }
    module_count = 0;
}

// ==================== DEBUG ====================

void dump_modules(void) {
    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    MODULE REGISTRY                            ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < module_count; i++) {
        LoadedModule* mod = modules[i];
        if (!mod) continue;
        
        printf("║ Module %d:\n", i);
        printf("║   Path:   %s\n", mod->module_path ? mod->module_path : "(null)");
        printf("║   Name:   %s\n", mod->module_name ? mod->module_name : "(null)");
        printf("║   Alias:  %s\n", mod->alias ? mod->alias : "(null)");
        printf("║   Type:   %s\n", mod->type == MODULE_TYPE_FILE ? "FILE" : "PACKAGE");
        printf("║   Status: %d\n", mod->status);
        printf("║   RefCount: %d\n", mod->ref_count);
        printf("║   Submodules: %d\n", mod->submodules.count);
        printf("║   Exports: %d\n", mod->constraints.allowed_count);
        
        if (mod->submodules.count > 0) {
            printf("║   Children:\n");
            for (int j = 0; j < mod->submodules.count; j++) {
                printf("║     - %s\n", mod->submodules.list[j]->module_name);
            }
        }
        
        if (i < module_count - 1) {
            printf("╟──────────────────────────────────────────────────────────────╢\n");
        }
    }
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("Total modules: %d\n\n", module_count);
}
