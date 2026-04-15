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
// ============================================
// RÉSOLUTION DE CHEMIN INTELLIGENTE
// ============================================

char* resolve_module_path(char* current_file, char* import_path) {
    char resolved[PATH_MAX];
    
    // 1. Import relatif avec points
    if (import_path[0] == '.') {
        int levels = 0;
        char* ptr = import_path;
        while (*ptr == '.') {
            levels++;
            ptr++;
        }
        
        char base[PATH_MAX];
        if (current_file && current_file[0]) {
            strcpy(base, current_file);
            char* dir = dirname(base);
            
            // Remonter de 'levels' dossiers
            for (int i = 0; i < levels; i++) {
                char* parent = dirname(dir);
                if (strcmp(parent, dir) == 0) break;
                strcpy(dir, parent);
            }
            
            if (*ptr) {
                snprintf(resolved, PATH_MAX, "%s/%s", dir, ptr);
            } else {
                snprintf(resolved, PATH_MAX, "%s", dir);
            }
        }
        
        return resolve_directory_or_file(resolved);
    }
    
    // 2. Import standard (chercher dans les chemins système)
    const char* search_paths[] = {
        "/usr/local/lib/goscript/modules",
        "/usr/local/lib/goscript/lib",
        "./lib",
        "./modules",
        ".",
        NULL
    };
    
    for (int i = 0; search_paths[i]; i++) {
        snprintf(resolved, PATH_MAX, "%s/%s", search_paths[i], import_path);
        
        // Essayer comme dossier
        char* result = resolve_directory_or_file(resolved);
        if (result) return result;
    }
    
    return NULL;
}

// ============================================
// DÉTECTE SI C'EST UN DOSSIER OU UN FICHIER
// ============================================

char* resolve_directory_or_file(char* path) {
    char resolved[PATH_MAX];
    
    // 1. Essayer comme dossier avec __self__.gjs
    snprintf(resolved, PATH_MAX, "%s/__self__.gjs", path);
    if (access(resolved, F_OK) == 0) {
        if (realpath(resolved, resolved)) {
            return strdup(resolved);
        }
    }
    
    // 2. Essayer comme dossier avec index.gjs
    snprintf(resolved, PATH_MAX, "%s/index.gjs", path);
    if (access(resolved, F_OK) == 0) {
        if (realpath(resolved, resolved)) {
            return strdup(resolved);
        }
    }
    
    // 3. Essayer comme fichier .gjs
    snprintf(resolved, PATH_MAX, "%s.gjs", path);
    if (access(resolved, F_OK) == 0) {
        if (realpath(resolved, resolved)) {
            return strdup(resolved);
        }
    }
    
    // 4. Essayer comme dossier (charger tous les fichiers)
    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        // C'est un dossier, on va charger tous les .gjs
        return strdup(path);  // Marqueur spécial pour dossier
    }
    
    return NULL;
}

// ============================================
// CHARGER UN DOSSIER ENTIER
// ============================================

LoadedModule* load_directory(char* dir_path, char* module_name, Environment* env) {
    LoadedModule* dir_module = create_module(dir_path, module_name, NULL);
    dir_module->env = create_env(NULL);
    
    // Ouvrir le dossier
    DIR* dir = opendir(dir_path);
    if (!dir) {
        dir_module->status = MODULE_STATUS_ERROR;
        return dir_module;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Ignorer . et ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Construire le chemin complet
        char full_path[PATH_MAX];
        snprintf(full_path, PATH_MAX, "%s/%s", dir_path, entry->d_name);
        
        // Vérifier si c'est un fichier .gjs
        if (strstr(entry->d_name, ".gjs") != NULL) {
            // Extraire le nom du sous-module
            char sub_name[256];
            strncpy(sub_name, entry->d_name, strlen(entry->d_name) - 4);
            sub_name[strlen(entry->d_name) - 4] = '\0';
            
            // Charger le sous-module
            LoadedModule* sub = load_module_from_file(full_path, sub_name, dir_module->env);
            if (sub) {
                // Exporter les symboles publics du sous-module
                export_all_public_symbols(sub, dir_module);
            }
        }
        // Vérifier si c'est un sous-dossier
        else {
            struct stat st;
            if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
                // Charger récursivement
                LoadedModule* sub = load_directory(full_path, entry->d_name, dir_module->env);
                if (sub) {
                    export_all_public_symbols(sub, dir_module);
                }
            }
        }
    }
    
    closedir(dir);
    dir_module->status = MODULE_STATUS_LOADED;
    return dir_module;
}

// ============================================
// EXPORTER TOUS LES SYMBOLES PUBLICS
// ============================================

void export_all_public_symbols(LoadedModule* src, LoadedModule* dst) {
    for (int i = 0; i < src->env->var_count; i++) {
        char* name = src->env->vars[i].name;
        Value val = src->env->vars[i].value;
        
        // Vérifier si c'est public (commence par majuscule ou est dans la liste d'export)
        if (isupper(name[0]) || is_exported(src, name)) {
            env_set(dst->env, name, val);
        }
    }
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
