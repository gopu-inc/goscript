#include "interpreter.h"
#include <libgen.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern ASTNode* program_root;
extern int yyparse(void);
extern FILE* yyin;
extern void free_ast(ASTNode* node);
extern void evaluate_statement(ASTNode* node, Environment* env);
extern Value evaluate_expr(ASTNode* node, Environment* env);

// ==================== RÉSOLVEUR DE CHEMIN ====================

char* resolve_module_path(char* current_file, char* import_path) {
    char* result = NULL;
    
    // Chemin absolu ?
    if (import_path[0] == '/') {
        result = strdup(import_path);
    }
    // Chemin relatif (commence par . ou ..)
    else if (import_path[0] == '.') {
        char* dir = strdup(current_file);
        char* dirname_ptr = dirname(dir);
        
        char full_path[1024];
        if (import_path[1] == '/') {
            // ./module
            snprintf(full_path, sizeof(full_path), "%s/%s", dirname_ptr, import_path + 2);
        } else if (import_path[1] == '.' && import_path[2] == '/') {
            // ../module
            char* parent = dirname(dirname_ptr);
            snprintf(full_path, sizeof(full_path), "%s/%s", parent, import_path + 3);
        } else {
            snprintf(full_path, sizeof(full_path), "%s/%s", dirname_ptr, import_path);
        }
        
        result = strdup(full_path);
        free(dir);
    }
    // Module standard
    else {
        char* paths[] = {
            "/usr/local/lib/goscript/granul/packages/",
            "/usr/lib/goscript/",
            "./modules/"
        };
        
        for (int i = 0; i < 3; i++) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s%s", paths[i], import_path);
            
            // Vérifier si c'est un dossier avec __self__.gjs
            char self_path[1024];
            snprintf(self_path, sizeof(self_path), "%s/__self__.gjs", full_path);
            if (access(self_path, F_OK) == 0) {
                result = strdup(self_path);
                break;
            }
            
            // Vérifier si c'est un fichier .gjs
            snprintf(self_path, sizeof(self_path), "%s.gjs", full_path);
            if (access(self_path, F_OK) == 0) {
                result = strdup(self_path);
                break;
            }
        }
    }
    
    return result;
}

// ==================== GESTION DE LA TABLE DES MODULES ====================

ModuleRegistry* init_module_registry(void) {
    ModuleRegistry* reg = malloc(sizeof(ModuleRegistry));
    reg->modules = NULL;
    reg->count = 0;
    reg->capacity = 0;
    return reg;
}

void register_module(ModuleRegistry* reg, LoadedModule* mod) {
    if (reg->count >= reg->capacity) {
        reg->capacity = reg->capacity == 0 ? 10 : reg->capacity * 2;
        reg->modules = realloc(reg->modules, reg->capacity * sizeof(LoadedModule*));
    }
    reg->modules[reg->count++] = mod;
}

LoadedModule* find_module(ModuleRegistry* reg, char* path) {
    for (int i = 0; i < reg->count; i++) {
        if (strcmp(reg->modules[i]->module_path, path) == 0) {
            return reg->modules[i];
        }
    }
    return NULL;
}

void free_module_registry(ModuleRegistry* reg) {
    if (!reg) return;
    for (int i = 0; i < reg->count; i++) {
        if (reg->modules[i]) {
            free(reg->modules[i]->module_path);
            free(reg->modules[i]->module_name);
            if (reg->modules[i]->constraints.allowed_names) {
                for (int j = 0; j < reg->modules[i]->constraints.allowed_count; j++) {
                    free(reg->modules[i]->constraints.allowed_names[j]);
                }
                free(reg->modules[i]->constraints.allowed_names);
            }
            free(reg->modules[i]);
        }
    }
    free(reg->modules);
    free(reg);
}

// ==================== TRAITEMENT DES CONTRAINTES ====================

void process_constraints(LoadedModule* module, ASTNode* constraints) {
    if (!constraints) return;
    
    if (constraints->type == NODE_CONSTRAINT) {
        if (strcmp(constraints->constraint.constraint_type, "only") == 0) {
            if (constraints->constraint.list) {
                module->constraints.allowed_count = constraints->constraint.list->count;
                module->constraints.allowed_names = malloc(module->constraints.allowed_count * sizeof(char*));
                for (int i = 0; i < module->constraints.allowed_count; i++) {
                    ASTNode* name_node = constraints->constraint.list->nodes[i];
                    if (name_node->type == NODE_IDENTIFIER) {
                        module->constraints.allowed_names[i] = strdup(name_node->identifier.name);
                    }
                }
            }
        } else if (strcmp(constraints->constraint.constraint_type, "timeout") == 0) {
            module->constraints.timeout_ms = constraints->constraint.int_value;
        } else if (strcmp(constraints->constraint.constraint_type, "sandbox") == 0) {
            module->constraints.sandbox = 1;
        } else if (strcmp(constraints->constraint.constraint_type, "allow_ffi") == 0) {
            module->constraints.allow_ffi = constraints->constraint.int_value;
        }
    } else if (constraints->type == NODE_CONSTRAINT_LIST) {
        process_constraints(module, constraints->constraint_list.a);
        process_constraints(module, constraints->constraint_list.b);
    }
}

// ==================== CHARGEMENT D'UN MODULE ====================

LoadedModule* load_module(ModuleRegistry* reg, Environment* parent_env,
                          char* current_file, char* import_path, 
                          char* alias, ASTNode* constraints) {
    // 1. Résoudre le chemin du module
    char* module_path = resolve_module_path(current_file, import_path);
    if (!module_path) {
        fprintf(stderr, "Module not found: %s\n", import_path);
        return NULL;
    }
    
    // 2. Vérifier si le module est déjà chargé
    LoadedModule* existing = find_module(reg, module_path);
    if (existing) {
        existing->ref_count++;
        free(module_path);
        return existing;
    }
    
    // 3. Créer un nouvel environnement isolé pour le module
    Environment* module_env = create_env(NULL);
    
    // 4. Ouvrir et parser le fichier du module
    FILE* f = fopen(module_path, "r");
    if (!f) {
        fprintf(stderr, "Cannot open module file: %s\n", module_path);
        free(module_path);
        free(module_env);
        return NULL;
    }
    
    // Sauvegarder l'ancien yyin
    FILE* old_yyin = yyin;
    yyin = f;
    
    // Parser le fichier du module
    int parse_result = yyparse();
    
    fclose(f);
    yyin = old_yyin;
    
    if (parse_result != 0 || !program_root) {
        fprintf(stderr, "Parse error in module: %s\n", module_path);
        free(module_path);
        free(module_env);
        return NULL;
    }
    
    // 5. Créer la structure du module
    LoadedModule* module = malloc(sizeof(LoadedModule));
    module->module_path = module_path;
    module->module_name = alias ? strdup(alias) : strdup(import_path);
    module->env = module_env;
    module->status = 1;
    module->ref_count = 1;
    
    // 6. Initialiser les contraintes par défaut
    module->constraints.allowed_names = NULL;
    module->constraints.allowed_count = 0;
    module->constraints.timeout_ms = 0;
    module->constraints.sandbox = 0;
    module->constraints.allow_ffi = 1;
    
    // 7. Traiter les contraintes si présentes
    if (constraints) {
        process_constraints(module, constraints);
    }
    
    // 8. Enregistrer toutes les fonctions du module
    for (int i = 0; i < program_root->program.statements->count; i++) {
        ASTNode* stmt = program_root->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION) {
            Value func_val;
            func_val.type = 4;  // Type FUNCTION
            func_val.func_val.node = stmt;
            func_val.func_val.closure = module_env;
            env_set(module_env, stmt->function.name, func_val);
        }
    }
    
    // 9. Enregistrer les constantes du module
    for (int i = 0; i < program_root->program.statements->count; i++) {
        ASTNode* stmt = program_root->program.statements->nodes[i];
        if (stmt->type == NODE_CONST) {
            Value const_val = evaluate_expr(stmt->var_decl.value, module_env);
            env_set(module_env, stmt->var_decl.name, const_val);
        }
    }
    
    // 10. Enregistrer les structures du module
    for (int i = 0; i < program_root->program.statements->count; i++) {
        ASTNode* stmt = program_root->program.statements->nodes[i];
        if (stmt->type == NODE_STRUCT) {
            Value struct_val;
            struct_val.type = 6;  // Type STRUCT
            struct_val.struct_val.struct_name = strdup(stmt->struct_def.name);
            struct_val.struct_val.fields = NULL;
            struct_val.struct_val.field_count = 0;
            env_set(module_env, stmt->struct_def.name, struct_val);
        }
    }
    
    // 11. Enregistrer les implémentations du module
    for (int i = 0; i < program_root->program.statements->count; i++) {
        ASTNode* stmt = program_root->program.statements->nodes[i];
        if (stmt->type == NODE_IMPL) {
            register_impl(stmt->impl.name, stmt);
            
            // Enregistrer les méthodes
            for (int j = 0; j < stmt->impl.methods->count; j++) {
                ASTNode* method = stmt->impl.methods->nodes[j];
                if (method->type == NODE_FUNCTION) {
                    char method_full_name[256];
                    snprintf(method_full_name, sizeof(method_full_name), "%s::%s", 
                             stmt->impl.name, method->function.name);
                    Value func_val;
                    func_val.type = 4;
                    func_val.func_val.node = method;
                    func_val.func_val.closure = module_env;
                    env_set(module_env, method_full_name, func_val);
                }
            }
        }
    }
    
    // 12. Exporter les symboles publics (pub)
    for (int i = 0; i < program_root->program.statements->count; i++) {
        ASTNode* stmt = program_root->program.statements->nodes[i];
        if (stmt->type == NODE_EXPORT) {
            Value* exported = env_get(module_env, stmt->export.name);
            if (exported) {
                env_set(module_env, stmt->export.name, *exported);
            }
        }
    }
    
    // 13. Exécuter le module (si des expressions à la racine)
    for (int i = 0; i < program_root->program.statements->count; i++) {
        ASTNode* stmt = program_root->program.statements->nodes[i];
        if (stmt->type == NODE_EXPR_STMT) {
            evaluate_statement(stmt, module_env);
        }
    }
    
    // 14. Enregistrer le module dans le registre
    register_module(reg, module);
    
    // 15. CRUCIAL: Lier le module à l'environnement parent avec son alias
    Value module_val;
    module_val.type = 7;  // Type MODULE
    module_val.int_val = (int)module;
    if (parent_env) {
        env_set(parent_env, module->module_name, module_val);
    }
    
    // 16. Nettoyer le programme_root temporaire
    free_ast(program_root);
    program_root = NULL;
    
    return module;
}

// ==================== VÉRIFICATION DES PERMISSIONS ====================

int is_name_allowed(LoadedModule* module, char* name) {
    if (!module) return 1;
    if (module->constraints.allowed_count == 0) return 1;
    
    for (int i = 0; i < module->constraints.allowed_count; i++) {
        if (strcmp(module->constraints.allowed_names[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_ffi_allowed(LoadedModule* module) {
    if (!module) return 1;
    return module->constraints.allow_ffi;
}

// ==================== ENREGISTREMENT DES IMPLÉMENTATIONS ====================

static ImplEntry* impl_table = NULL;
static int impl_count = 0;
static int impl_capacity = 0;

void register_impl(char* struct_name, ASTNode* impl_node) {
    if (impl_count >= impl_capacity) {
        impl_capacity = impl_capacity == 0 ? 10 : impl_capacity * 2;
        impl_table = realloc(impl_table, impl_capacity * sizeof(ImplEntry));
    }
    impl_table[impl_count].struct_name = strdup(struct_name);
    impl_table[impl_count].impl_node = impl_node;
    impl_count++;
}

ASTNode* find_impl(char* struct_name) {
    for (int i = 0; i < impl_count; i++) {
        if (strcmp(impl_table[i].struct_name, struct_name) == 0) {
            return impl_table[i].impl_node;
        }
    }
    return NULL;
}

ASTNode* find_method(ASTNode* impl_node, char* method_name) {
    if (!impl_node || impl_node->type != NODE_IMPL) return NULL;
    
    for (int i = 0; i < impl_node->impl.methods->count; i++) {
        ASTNode* method = impl_node->impl.methods->nodes[i];
        if (method->type == NODE_FUNCTION && 
            strcmp(method->function.name, method_name) == 0) {
            return method;
        }
    }
    return NULL;
}

void free_impl_table(void) {
    for (int i = 0; i < impl_count; i++) {
        free(impl_table[i].struct_name);
    }
    free(impl_table);
    impl_table = NULL;
    impl_count = 0;
    impl_capacity = 0;
}
