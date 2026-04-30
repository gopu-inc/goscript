// src/build.c - VERSION AMÉLIORÉE
#include "gpm.h"

/* ================================================================
 * VÉRIFIER SI UN FICHIER EST IGNORÉ PAR .gpmignore
 * ================================================================ */

static bool is_ignored(const char* filepath, char** ignore_patterns, int pattern_count) {
    if (!ignore_patterns || pattern_count == 0) return false;
    
    const char* filename = strrchr(filepath, '/');
    if (filename) filename++;
    else filename = filepath;
    
    for (int i = 0; i < pattern_count; i++) {
        const char* pattern = ignore_patterns[i];
        
        // Match exact
        if (strcmp(filename, pattern) == 0) return true;
        if (strcmp(filepath, pattern) == 0) return true;
        
        // Match wildcard (*.ext)
        if (pattern[0] == '*' && pattern[1] == '.') {
            const char* ext = pattern + 1;
            const char* file_ext = strrchr(filename, '.');
            if (file_ext && strcmp(file_ext, ext) == 0) return true;
        }
        
        // Match directory (dir/)
        size_t pattern_len = strlen(pattern);
        if (pattern[pattern_len - 1] == '/') {
            if (strncmp(filepath, pattern, pattern_len) == 0) return true;
        }
        
        // Match extension (*.ext)
        if (pattern[0] == '*' && pattern[1] == '.') {
            const char* ext = pattern + 1;
            size_t file_len = strlen(filename);
            size_t ext_len = strlen(ext);
            if (file_len > ext_len && strcmp(filename + file_len - ext_len, ext) == 0) return true;
        }
    }
    
    return false;
}

/* ================================================================
 * CHARGER LES PATTERNS .gpmignore
 * ================================================================ */

static char** load_gpmignore(int* count) {
    *count = 0;
    
    const char* ignore_paths[] = {
        ".gpmignore",
        ".gitignore",
        NULL
    };
    
    const char* ignore_path = NULL;
    for (int i = 0; ignore_paths[i]; i++) {
        if (gpm_file_exists(ignore_paths[i])) {
            ignore_path = ignore_paths[i];
            break;
        }
    }
    
    if (!ignore_path) {
        LOG_DEBUG("Aucun fichier .gpmignore trouvé");
        return NULL;
    }
    
    LOG_DEBUG("Chargement de %s", ignore_path);
    
    FILE* f = fopen(ignore_path, "r");
    if (!f) return NULL;
    
    char** patterns = NULL;
    int capacity = 0;
    
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        // Nettoyer la ligne
        line[strcspn(line, "\n")] = '\0';
        line[strcspn(line, "\r")] = '\0';
        
        // Ignorer commentaires et lignes vides
        char* trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
        if (trimmed[0] == '#' || trimmed[0] == '\0') continue;
        
        // Allouer plus d'espace si nécessaire
        if (*count >= capacity) {
            capacity = capacity == 0 ? 16 : capacity * 2;
            patterns = realloc(patterns, capacity * sizeof(char*));
        }
        
        patterns[*count] = strdup(trimmed);
        LOG_DEBUG("  Pattern ignore: %s", patterns[*count]);
        (*count)++;
    }
    
    fclose(f);
    
    // Ajouter des patterns par défaut
    const char* default_ignores[] = {
        ".gpm/",
        ".git/",
        ".gitignore",
        ".gpmignore",
        "build/",
        "gpm_modules/",
        "node_modules/",
        "*.tar.bool",
        "*.tar.gz",
        "*.o",
        "*.a",
        "*.so",
        ".DS_Store",
        "Thumbs.db",
        NULL
    };
    
    for (int i = 0; default_ignores[i]; i++) {
        // Vérifier si déjà présent
        bool already = false;
        for (int j = 0; j < *count; j++) {
            if (strcmp(patterns[j], default_ignores[i]) == 0) {
                already = true;
                break;
            }
        }
        
        if (!already) {
            if (*count >= capacity) {
                capacity *= 2;
                patterns = realloc(patterns, capacity * sizeof(char*));
            }
            patterns[*count] = strdup(default_ignores[i]);
            (*count)++;
        }
    }
    
    LOG_DEBUG("%d patterns d'ignore chargés", *count);
    return patterns;
}

/* ================================================================
 * LIBÉRER LES PATTERNS
 * ================================================================ */

static void free_gpmignore(char** patterns, int count) {
    if (!patterns) return;
    for (int i = 0; i < count; i++) {
        free(patterns[i]);
    }
    free(patterns);
}

/* ================================================================
 * COPIER UN FICHIER EN CRÉANT LE RÉPERTOIRE PARENT
 * ================================================================ */

static int copy_file_with_parent(const char* src, const char* dst) {
    // Créer le répertoire parent
    char* dst_copy = strdup(dst);
    char* parent = dirname(dst_copy);
    gpm_mkdir_p(parent);
    free(dst_copy);
    
    // Copier le fichier
    char cmd[2048];
    snprintf(cmd, sizeof(cmd), "cp -f '%s' '%s' 2>/dev/null", src, dst);
    int ret = system(cmd);
    
    if (ret == 0) {
        LOG_DEBUG("    Copié: %s -> %s", src, dst);
    }
    
    return ret;
}

/* ================================================================
 * TROUVER ET COPIER LE README (toutes les variantes)
 * ================================================================ */

static void copy_readme_files(const char* src_dir, const char* dst_dir, 
                               char** ignore_patterns, int pattern_count) {
    const char* readme_variants[] = {
        "README.md",
        "README.MD",
        "Readme.md",
        "readme.md",
        "README.txt",
        "README",
        "readme",
        "README.rst",
        "README.markdown",
        "README.mdown",
        "README.org",
        NULL
    };
    
    int copied = 0;
    for (int i = 0; readme_variants[i]; i++) {
        char src_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, readme_variants[i]);
        
        if (gpm_file_exists(src_path)) {
            if (is_ignored(readme_variants[i], ignore_patterns, pattern_count)) {
                LOG_DEBUG("  README ignoré: %s", readme_variants[i]);
                continue;
            }
            
            char dst_path[1024];
            snprintf(dst_path, sizeof(dst_path), "%s/%s", dst_dir, readme_variants[i]);
            
            if (copy_file_with_parent(src_path, dst_path) == 0) {
                copied++;
            }
        }
    }
    
    // Chercher aussi dans docs/
    char docs_readme[1024];
    snprintf(docs_readme, sizeof(docs_readme), "%s/docs", src_dir);
    
    if (gpm_file_exists(docs_readme)) {
        for (int i = 0; readme_variants[i]; i++) {
            char src_path[1024];
            snprintf(src_path, sizeof(src_path), "%s/docs/%s", src_dir, readme_variants[i]);
            
            if (gpm_file_exists(src_path)) {
                if (is_ignored(readme_variants[i], ignore_patterns, pattern_count)) {
                    continue;
                }
                
                char dst_path[1024];
                snprintf(dst_path, sizeof(dst_path), "%s/docs/%s", dst_dir, readme_variants[i]);
                
                if (copy_file_with_parent(src_path, dst_path) == 0) {
                    copied++;
                }
            }
        }
    }
    
    if (copied > 0) {
        LOG_INFO("  📄 %d README(s) copié(s)", copied);
    } else {
        LOG_WARN("  ⚠️ Aucun README trouvé");
    }
}

/* ================================================================
 * COPIER LES FICHIERS LISTÉS DANS Manifest.toml
 * ================================================================ */

static int copy_manifest_files(Manifest* manifest, const char* src_dir, 
                                const char* dst_dir, char** ignore_patterns, 
                                int pattern_count) {
    int copied = 0;
    
    // 1. Copier le fichier main (entry point)
    if (manifest->main[0]) {
        char src_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, manifest->main);
        
        if (gpm_file_exists(src_path)) {
            if (!is_ignored(manifest->main, ignore_patterns, pattern_count)) {
                char dst_path[1024];
                snprintf(dst_path, sizeof(dst_path), "%s/%s", dst_dir, manifest->main);
                if (copy_file_with_parent(src_path, dst_path) == 0) copied++;
            }
        } else {
            LOG_WARN("  ⚠️ Fichier main introuvable: %s", manifest->main);
        }
    }
    
    // 2. Copier les fichiers listés dans files[]
    if (manifest->files_count > 0) {
        LOG_INFO("  📁 Copie de %d fichiers listés dans Manifest.toml...", manifest->files_count);
        
        for (int i = 0; i < manifest->files_count; i++) {
            const char* file = manifest->files[i];
            
            if (is_ignored(file, ignore_patterns, pattern_count)) {
                LOG_DEBUG("    Ignoré: %s", file);
                continue;
            }
            
            char src_path[1024];
            snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, file);
            
            if (gpm_file_exists(src_path)) {
                char dst_path[1024];
                snprintf(dst_path, sizeof(dst_path), "%s/%s", dst_dir, file);
                if (copy_file_with_parent(src_path, dst_path) == 0) copied++;
            } else {
                LOG_WARN("    ⚠️ Fichier introuvable: %s", file);
            }
        }
    }
    
    // 3. Copier tous les .gjs si aucun fichier n'est listé
    if (manifest->files_count == 0) {
        LOG_INFO("  📁 Aucun fichier listé, copie automatique de tous les .gjs...");
        
        char cmd[2048];
        snprintf(cmd, sizeof(cmd),
                 "cd '%s' && find . -name '*.gjs' -type f 2>/dev/null | while read f; do "
                 "  echo \"$f\"; "
                 "done",
                 src_dir);
        
        FILE* fp = popen(cmd, "r");
        if (fp) {
            char filepath[1024];
            while (fgets(filepath, sizeof(filepath), fp)) {
                filepath[strcspn(filepath, "\n")] = '\0';
                
                // Enlever le ./ du début
                const char* rel_path = filepath;
                if (rel_path[0] == '.' && rel_path[1] == '/') rel_path += 2;
                
                if (is_ignored(rel_path, ignore_patterns, pattern_count)) {
                    LOG_DEBUG("    Ignoré: %s", rel_path);
                    continue;
                }
                
                char dst_path[1024];
                snprintf(dst_path, sizeof(dst_path), "%s/%s", dst_dir, rel_path);
                
                char src_full[1024];
                snprintf(src_full, sizeof(src_full), "%s/%s", src_dir, rel_path);
                
                if (copy_file_with_parent(src_full, dst_path) == 0) copied++;
            }
            pclose(fp);
        }
    }
    
    // 4. Copier les .so et .a (bibliothèques compilées)
    char cmd_libs[2048];
    snprintf(cmd_libs, sizeof(cmd_libs),
             "cd '%s' && find . \\( -name '*.so' -o -name '*.so.*' -o -name '*.a' \\) -type f 2>/dev/null | while read f; do "
             "  echo \"$f\"; "
             "done",
             src_dir);
    
    FILE* fp2 = popen(cmd_libs, "r");
    if (fp2) {
        char filepath[1024];
        while (fgets(filepath, sizeof(filepath), fp2)) {
            filepath[strcspn(filepath, "\n")] = '\0';
            
            const char* rel_path = filepath;
            if (rel_path[0] == '.' && rel_path[1] == '/') rel_path += 2;
            
            if (is_ignored(rel_path, ignore_patterns, pattern_count)) {
                continue;
            }
            
            char dst_path[1024];
            snprintf(dst_path, sizeof(dst_path), "%s/%s", dst_dir, rel_path);
            
            char src_full[1024];
            snprintf(src_full, sizeof(src_full), "%s/%s", src_dir, rel_path);
            
            copy_file_with_parent(src_full, dst_path);
        }
        pclose(fp2);
    }
    
    return copied;
}

/* ================================================================
 * COPIER LES DÉPENDANCES RÉSOLUES DANS L'ARCHIVE
 * ================================================================ */

static int copy_dependencies_to_build(const char* build_dir, Manifest* manifest) {
    if (manifest->dep_count == 0) {
        LOG_DEBUG("  Aucune dépendance à copier");
        return 0;
    }
    
    LOG_STEP("Résolution et copie des dépendances...");
    
    char vendor_dir[1024];
    snprintf(vendor_dir, sizeof(vendor_dir), "%s/gpm_modules", build_dir);
    gpm_mkdir_p(vendor_dir);
    
    // Résoudre l'arbre de dépendances
    DepNode* tree = gpm_resolve_tree(manifest);
    if (!tree) {
        LOG_WARN("  Impossible de résoudre les dépendances");
        return 0;
    }
    
    // Aplatir l'arbre
    DepNode** flat = NULL;
    int flat_count = 0;
    gpm_flatten_tree_to_list(tree, &flat, &flat_count);
    
    int copied = 0;
    
    for (int i = 0; i < flat_count; i++) {
        DepNode* node = flat[i];
        if (node->depth == 0) continue;
        if (node->hoisted) continue;
        
        char dep_src[PATH_MAX];
        snprintf(dep_src, sizeof(dep_src), "%s/%s", GPM_LIB_DIR, node->name);
        
        if (!gpm_file_exists(dep_src)) {
            LOG_WARN("  ⚠️ Dépendance non installée: %s@%s", node->name, node->version);
            
            // Essayer de l'installer automatiquement
            LOG_INFO("  📥 Installation automatique de %s@%s...", node->name, node->version);
            if (gpm_install_package(node->name, node->version) == 0) {
                LOG_SUCCESS("  ✅ %s@%s installé", node->name, node->version);
            } else {
                LOG_ERROR("  ❌ Échec de l'installation de %s@%s", node->name, node->version);
                continue;
            }
        }
        
        char dep_dst[PATH_MAX];
        snprintf(dep_dst, sizeof(dep_dst), "%s/%s", vendor_dir, node->name);
        
        char cmd[2048];
        snprintf(cmd, sizeof(cmd), "cp -rL '%s' '%s' 2>/dev/null", dep_src, dep_dst);
        
        if (system(cmd) == 0 && gpm_file_exists(dep_dst)) {
            LOG_SUCCESS("  📦 %s@%s copié dans vendor", node->name, node->version);
            copied++;
        } else {
            LOG_WARN("  ⚠️ Échec de copie de %s@%s", node->name, node->version);
        }
    }
    
    free(flat);
    gpm_free_dep_tree(tree);
    
    LOG_INFO("  📊 %d dépendance(s) incluse(s) dans l'archive", copied);
    return copied;
}

/* ================================================================
 * CONSTRUCTION DU PACKAGE (VERSION AMÉLIORÉE)
 * ================================================================ */

int gpm_build_package(void) {
    LOG_STEP("Construction du package");
    
    // 1. Lire le manifest
    Manifest manifest = {0};
    if (gpm_manifest_read(&manifest) != 0) {
        LOG_ERROR("Pas de Manifest.toml trouvé");
        LOG_INFO("Exécutez 'gpm init' pour créer un nouveau projet");
        return -1;
    }
    
    // Valider le manifest
    if (gpm_manifest_validate(&manifest) != 0) {
        LOG_ERROR("Manifest.toml invalide");
        return -1;
    }
    
    LOG_INFO("  Package: %s@%s", manifest.name, manifest.version);
    LOG_INFO("  Release: %s", manifest.release);
    LOG_INFO("  Architecture: %s", manifest.arch);
    
    // 2. Charger .gpmignore
    int ignore_count = 0;
    char** ignore_patterns = load_gpmignore(&ignore_count);
    
    // 3. Créer le répertoire de build
    char build_dir[512];
    snprintf(build_dir, sizeof(build_dir), "build/pkg-%s", manifest.name);
    
    // Nettoyer l'ancien build
    if (gpm_file_exists(build_dir)) {
        char cmd_clean[1024];
        snprintf(cmd_clean, sizeof(cmd_clean), "rm -rf '%s'", build_dir);
        system(cmd_clean);
    }
    
    gpm_mkdir_p(build_dir);
    
    // Structure standard
    char path[1024];
    snprintf(path, sizeof(path), "%s/usr/bin", build_dir);
    gpm_mkdir_p(path);
    snprintf(path, sizeof(path), "%s/usr/lib", build_dir);
    gpm_mkdir_p(path);
    
    // 4. Exécuter le script de build si présent
    if (manifest.scripts_build[0]) {
        LOG_STEP("Exécution du script de build...");
        LOG_INFO("  > %s", manifest.scripts_build);
        
        int ret = system(manifest.scripts_build);
        if (ret != 0) {
            LOG_ERROR("Build échoué (code %d)", WEXITSTATUS(ret));
            free_gpmignore(ignore_patterns, ignore_count);
            return -1;
        }
        LOG_SUCCESS("Build terminé");
    }
    
    // 5. Copier le Manifest.toml
    LOG_STEP("Copie des fichiers...");
    
    char cmd_manifest[1024];
    snprintf(cmd_manifest, sizeof(cmd_manifest), "cp '%s' '%s/'", GPM_MANIFEST_FILE, build_dir);
    system(cmd_manifest);
    LOG_DEBUG("  ✅ Manifest.toml copié");
    
    // 6. Copier les fichiers listés dans Manifest.toml
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    
    int files_copied = copy_manifest_files(&manifest, cwd, build_dir, 
                                            ignore_patterns, ignore_count);
    LOG_INFO("  📁 %d fichiers copiés dans le build", files_copied);
    
    // 7. Copier le(s) README
    copy_readme_files(cwd, build_dir, ignore_patterns, ignore_count);
    
    // 8. Copier le CHANGELOG si présent
    const char* changelog_variants[] = {
        "CHANGELOG.md", "CHANGELOG.txt", "CHANGELOG",
        "CHANGES.md", "CHANGES.txt", "CHANGES",
        "HISTORY.md", "HISTORY.txt",
        NULL
    };
    
    for (int i = 0; changelog_variants[i]; i++) {
        char cl_path[1024];
        snprintf(cl_path, sizeof(cl_path), "%s/%s", cwd, changelog_variants[i]);
        
        if (gpm_file_exists(cl_path)) {
            if (!is_ignored(changelog_variants[i], ignore_patterns, ignore_count)) {
                char dst_cl[1024];
                snprintf(dst_cl, sizeof(dst_cl), "%s/%s", build_dir, changelog_variants[i]);
                copy_file_with_parent(cl_path, dst_cl);
                LOG_DEBUG("  📋 %s copié", changelog_variants[i]);
            }
            break;
        }
    }
    
    // 9. Copier le LICENSE si présent
    const char* license_variants[] = {
        "LICENSE", "LICENSE.md", "LICENSE.txt",
        "LICENCE", "LICENCE.md",
        "COPYING", "COPYING.txt",
        NULL
    };
    
    for (int i = 0; license_variants[i]; i++) {
        char lic_path[1024];
        snprintf(lic_path, sizeof(lic_path), "%s/%s", cwd, license_variants[i]);
        
        if (gpm_file_exists(lic_path)) {
            if (!is_ignored(license_variants[i], ignore_patterns, ignore_count)) {
                char dst_lic[1024];
                snprintf(dst_lic, sizeof(dst_lic), "%s/%s", build_dir, license_variants[i]);
                copy_file_with_parent(lic_path, dst_lic);
                LOG_DEBUG("  📜 %s copié", license_variants[i]);
            }
            break;
        }
    }
    
    // 10. Copier les dépendances résolues dans gpm_modules/
    copy_dependencies_to_build(build_dir, &manifest);
    
    // 11. Copier le script d'installation si présent
    char install_script[1024];
    snprintf(install_script, sizeof(install_script), "%s/install.sh", cwd);
    
    if (gpm_file_exists(install_script)) {
        if (!is_ignored("install.sh", ignore_patterns, ignore_count)) {
            char dst_install[1024];
            snprintf(dst_install, sizeof(dst_install), "%s/install.sh", build_dir);
            copy_file_with_parent(install_script, dst_install);
            LOG_DEBUG("  🔧 install.sh copié");
        }
    }
    
    // 12. Créer l'archive .tar.bool
    LOG_STEP("Création de l'archive...");
    
    char archive_name[512];
    snprintf(archive_name, sizeof(archive_name),
             "build/%s-%s-%s.%s%s",
             manifest.name, manifest.version, manifest.release,
             manifest.arch, GPM_PACKAGE_EXT);
    
    // Supprimer l'ancienne archive si elle existe
    if (gpm_file_exists(archive_name)) {
        unlink(archive_name);
    }
    
    char cmd[2048];
    snprintf(cmd, sizeof(cmd),
             "cd '%s' && tar -czf '../%s-%s-%s.%s%s' . 2>/dev/null",
             build_dir, manifest.name, manifest.version, 
             manifest.release, manifest.arch, GPM_PACKAGE_EXT);
    
    if (system(cmd) != 0) {
        LOG_ERROR("Échec de la création de l'archive");
        free_gpmignore(ignore_patterns, ignore_count);
        return -1;
    }
    
    // 13. Calculer SHA256
    char* sha = gpm_sha256_file(archive_name);
    if (sha) {
        strncpy(manifest.sha256, sha, sizeof(manifest.sha256) - 1);
    }
    
    // 14. Obtenir la taille
    struct stat st;
    stat(archive_name, &st);
    
    // 15. Afficher le résumé
    printf("\n");
    LOG_SUCCESS("Build terminé !");
    printf("  ┌─────────────────────────────────────────────┐\n");
    printf("  │  📦 Archive: %-31s │\n", archive_name + 6);  // Skip "build/"
    printf("  │  📏 Taille:  %-31s │\n", 
           st.st_size > 1024 * 1024 
               ? gpm_format_size(st.st_size) 
               : gpm_format_size(st.st_size));
    if (sha) {
        printf("  │  🔐 SHA256:  %-31s │\n", sha);
    }
    printf("  │  📁 Fichiers: %-29d │\n", files_copied);
    if (manifest.dep_count > 0) {
        printf("  │  📦 Déps:    %-29d │\n", manifest.dep_count);
    }
    printf("  └─────────────────────────────────────────────┘\n");
    printf("\n");
    
    // 16. Nettoyer le répertoire de build temporaire
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'", build_dir);
    system(cmd);
    
    // 16. Libérer les patterns
    free_gpmignore(ignore_patterns, ignore_count);
    
    return 0;
}

/* ================================================================
 * FORMATER LA TAILLE POUR L'AFFICHAGE
 * ================================================================ */

char* gpm_format_size(size_t bytes) {
    static char buffer[32];
    
    if (bytes < 1024) {
        snprintf(buffer, sizeof(buffer), "%zu B", bytes);
    } else if (bytes < 1024 * 1024) {
        snprintf(buffer, sizeof(buffer), "%.1f KB", bytes / 1024.0);
    } else if (bytes < 1024 * 1024 * 1024) {
        snprintf(buffer, sizeof(buffer), "%.1f MB", bytes / (1024.0 * 1024.0));
    } else {
        snprintf(buffer, sizeof(buffer), "%.2f GB", bytes / (1024.0 * 1024.0 * 1024.0));
    }
    
    return buffer;
}
