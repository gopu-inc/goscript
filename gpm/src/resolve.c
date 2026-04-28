// src/resolve.c
#include "gpm.h"

/* ================================================================
 * CRÉER UN NOUVEAU NŒUD DE L'ARBRE
 * ================================================================ */

static DepNode* create_dep_node(const char* name, const char* version, int depth) {
    DepNode* node = calloc(1, sizeof(DepNode));
    if (!node) return NULL;
    
    strncpy(node->name, name, sizeof(node->name) - 1);
    strncpy(node->version, version, sizeof(node->version) - 1);
    node->depth = depth;
    node->resolved = false;
    node->hoisted = false;
    
    return node;
}

/* ================================================================
 * RÉSOUDRE LA MEILLEURE VERSION POUR UNE DÉPENDANCE
 * ================================================================ */

char* gpm_resolve_version(Dependency* dep) {
    static char version[64];
    
    LOG_DEBUG("Résolution de %s...", dep->name);
    
    // Chercher dans le registre
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/package/%s",
             gpm_config.registry_url, GPM_API_VERSION, dep->name);
    
    long status = 0;
    char* response = gpm_network_get(url, &status);
    
    if (status != 200 || !response) {
        LOG_WARN("Package %s non trouvé dans le registre", dep->name);
        return NULL;
    }
    
    json_error_t error;
    json_t* root = json_loads(response, 0, &error);
    free(response);
    
    if (!root) return NULL;
    
    json_t* pkg = json_object_get(root, "package");
    if (!pkg) {
        json_decref(root);
        return NULL;
    }
    
    // Trouver la meilleure version qui satisfait la contrainte
    json_t* versions = json_object_get(pkg, "versions");
    char* best = NULL;
    SemVer best_ver = {0};
    
    if (versions && json_is_array(versions)) {
        size_t count = json_array_size(versions);
        for (size_t i = 0; i < count; i++) {
            json_t* v = json_array_get(versions, i);
            const char* ver_str = json_string_value(v);
            
            if (ver_str) {
                SemVer current = gpm_semver_parse(ver_str);
                if (gpm_semver_satisfies(current, *dep)) {
                    if (!best || gpm_semver_compare(current, best_ver) > 0) {
                        best_ver = current;
                        best = (char*)ver_str;
                    }
                }
            }
        }
    }
    
    // Fallback: utiliser la version principale
    if (!best) {
        json_t* ver_json = json_object_get(pkg, "version");
        if (ver_json && json_is_string(ver_json)) {
            best = (char*)json_string_value(ver_json);
        }
    }
    
    if (best) {
        strncpy(version, best, sizeof(version) - 1);
        json_decref(root);
        LOG_DEBUG("  Résolu: %s@%s", dep->name, version);
        return version;
    }
    
    json_decref(root);
    return NULL;
}

/* ================================================================
 * CONSTRUIRE L'ARBRE DE DÉPENDANCES (RÉCURSIF)
 * ================================================================ */

DepNode* gpm_resolve_tree(Manifest* manifest) {
    LOG_STEP("Construction de l'arbre de dépendances");
    
    // Nœud racine
    DepNode* root = create_dep_node(manifest->name, manifest->version, 0);
    if (!root) return NULL;
    
    int total_deps = manifest->dep_count;
    if (!gpm_config.production) {
        total_deps += manifest->dev_dep_count;
    }
    
    LOG_INFO("Résolution de %d dépendances...", total_deps);
    
    // Résoudre les dépendances de production
    for (int i = 0; i < manifest->dep_count; i++) {
        Dependency* dep = &manifest->dependencies[i];
        
        char* version = gpm_resolve_version(dep);
        if (!version) {
            LOG_WARN("  Impossible de résoudre %s", dep->name);
            continue;
        }
        
        DepNode* child = create_dep_node(dep->name, version, 1);
        child->is_dev = false;
        
        // Résoudre récursivement (profondeur max 10)
        if (root->child_count < 256) {
            root->children = realloc(root->children, 
                (root->child_count + 1) * sizeof(DepNode*));
            root->children[root->child_count++] = child;
            child->parent = root;
            child->resolved = true;
            LOG_DEBUG("  ✓ %s@%s", dep->name, version);
        }
    }
    
    // Résoudre les dépendances de développement
    if (!gpm_config.production) {
        for (int i = 0; i < manifest->dev_dep_count; i++) {
            Dependency* dep = &manifest->dev_dependencies[i];
            
            char* version = gpm_resolve_version(dep);
            if (!version) continue;
            
            DepNode* child = create_dep_node(dep->name, version, 1);
            child->is_dev = true;
            
            if (root->child_count < 256) {
                root->children = realloc(root->children,
                    (root->child_count + 1) * sizeof(DepNode*));
                root->children[root->child_count++] = child;
                child->parent = root;
                child->resolved = true;
                LOG_DEBUG("  ✓ %s@%s (dev)", dep->name, version);
            }
        }
    }
    
    LOG_SUCCESS("Arbre résolu: %d dépendances", root->child_count);
    return root;
}

/* ================================================================
 * HOISTING (REMOUNTER LES DÉPENDANCES COMMUNES)
 * ================================================================ */

int gpm_hoist_dependencies(DepNode* root) {
    LOG_DEBUG("Hoisting des dépendances...");
    
    for (int i = 0; i < root->child_count; i++) {
        DepNode* child = root->children[i];
        
        // Chercher si ce package existe déjà dans les parents
        DepNode* parent = root->parent;
        while (parent) {
            for (int j = 0; j < parent->child_count; j++) {
                DepNode* sibling = parent->children[j];
                if (sibling != child && strcmp(sibling->name, child->name) == 0) {
                    // Vérifier compatibilité de version
                    if (strcmp(sibling->version, child->version) == 0) {
                        child->hoisted = true;
                        LOG_DEBUG("  Hoisted: %s@%s", child->name, child->version);
                        break;
                    }
                }
            }
            if (child->hoisted) break;
            parent = parent->parent;
        }
    }
    
    return 0;
}

/* ================================================================
 * APLATIR L'ARBRE EN LISTE
 * ================================================================ */

void gpm_flatten_tree_to_list(DepNode* node, DepNode*** list, int* count) {
    if (!node || node->hoisted) return;
    
    // Ajouter ce nœud
    *list = realloc(*list, (*count + 1) * sizeof(DepNode*));
    (*list)[(*count)++] = node;
    
    // Ajouter les enfants
    for (int i = 0; i < node->child_count; i++) {
        gpm_flatten_tree_to_list(node->children[i], list, count);
    }
}

/* ================================================================
 * LIBÉRER L'ARBRE
 * ================================================================ */

void gpm_free_dep_tree(DepNode* node) {
    if (!node) return;
    
    for (int i = 0; i < node->child_count; i++) {
        gpm_free_dep_tree(node->children[i]);
    }
    
    free(node->children);
    free(node);
}

/* ================================================================
 * AFFICHER L'ARBRE
 * ================================================================ */

void gpm_print_tree(DepNode* node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++) {
        printf(i == depth - 1 ? "├── " : "│   ");
    }
    
    const char* icon = node->hoisted ? "↑" : "•";
    printf("%s %s@%s\n", icon, node->name, node->version);
    
    for (int i = 0; i < node->child_count; i++) {
        if (!node->children[i]->hoisted) {
            gpm_print_tree(node->children[i], depth + 1);
        }
    }
}
