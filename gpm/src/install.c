#include "gpm.h"

/* ================================================================
 * INSTALLER UN PACKAGE - VERSION AMÉLIORÉE
 * Style pip : installation dans /usr/local/lib/goscript
 * + cache rapide dans gpm_modules
 * ================================================================ */

int gpm_install_package(const char* name, const char* version) {
    char pkg_name[256] = {0};
    char pkg_version[64] = {0};
    
    // Parser name@version
    char* at = strchr(name, '@');
    if (at) {
        size_t len = at - name;
        strncpy(pkg_name, name, len);
        pkg_name[len] = '\0';
        strncpy(pkg_version, at + 1, sizeof(pkg_version) - 1);
    } else {
        strncpy(pkg_name, name, sizeof(pkg_name) - 1);
        pkg_version[0] = '\0';
    }
    
    // Si pas de version, chercher la dernière
    if (!pkg_version[0]) {
        Dependency dep = {0};
        strncpy(dep.name, pkg_name, sizeof(dep.name) - 1);
        dep.type = VER_LATEST;
        
        char* resolved = gpm_resolve_version(&dep);
        if (!resolved) {
            LOG_ERROR("Package '%s' introuvable sur le registre", pkg_name);
            LOG_INFO("Vérifiez: gpm search %s", pkg_name);
            return -1;
        }
        strncpy(pkg_version, resolved, sizeof(pkg_version) - 1);
    }
    
    LOG_STEP("Installation de %s@%s", pkg_name, pkg_version);
    
    // 1. TÉLÉCHARGER LE PACKAGE
    char archive_path[PATH_MAX];
    snprintf(archive_path, sizeof(archive_path), 
             "%s/%s-%s-%s%s",
             GPM_TEMP_DIR, pkg_name, pkg_version, 
             gpm_config.arch, GPM_PACKAGE_EXT);
    
    // URL de téléchargement
    char download_url[1024];
    snprintf(download_url, sizeof(download_url),
             "%s/package/download/%s/%s/%s/r0/%s",
             gpm_config.registry_url,
             gpm_config.scope,
             pkg_name, pkg_version, gpm_config.arch);
    
    LOG_INFO("Téléchargement: %s", download_url);
    
    gpm_mkdir_p(GPM_TEMP_DIR);
    
    if (gpm_network_download(download_url, archive_path) != 0) {
        LOG_ERROR("Échec du téléchargement de %s", pkg_name);
        return -1;
    }
    
    // 2. EXTRAIRE DANS UN RÉPERTOIRE TEMPORAIRE
    char extract_dir[PATH_MAX];
    snprintf(extract_dir, sizeof(extract_dir), 
             "%s/extract_%s_%d", GPM_TEMP_DIR, pkg_name, getpid());
    
    gpm_mkdir_p(extract_dir);
    
    // Extraire l'archive
    char cmd[2048];
    snprintf(cmd, sizeof(cmd), 
             "cd '%s' && tar -xzf '%s' 2>/dev/null",
             extract_dir, archive_path);
    
    if (system(cmd) != 0) {
        // Essayer sans le .tar.bool (l'archive pourrait être un .gz simple)
        snprintf(cmd, sizeof(cmd),
                 "cd '%s' && gunzip -c '%s' | tar -xf - 2>/dev/null",
                 extract_dir, archive_path);
        if (system(cmd) != 0) {
            LOG_ERROR("Échec de l'extraction du package");
            rmdir(extract_dir);
            unlink(archive_path);
            return -1;
        }
    }
    
    // 3. INSTALLER DANS /usr/local/lib/goscript/ (STYLE PIP)
    char goscript_lib[PATH_MAX];
    snprintf(goscript_lib, sizeof(goscript_lib), 
             "%s/%s", GPM_LIB_DIR, pkg_name);
    
    gpm_mkdir_p(goscript_lib);
    
    // Copier TOUS les fichiers .gjs et la structure
    snprintf(cmd, sizeof(cmd),
             "cd '%s' && find . -name '*.gjs' -o -name '*.so' -o -name '*.a' "
             "-o -name 'Manifest.toml' -o -name 'install.sh' "
             "| while read f; do "
             "  mkdir -p '%s/$(dirname \"$f\")' 2>/dev/null; "
             "  cp \"$f\" '%s/$f' 2>/dev/null; "
             "done",
             extract_dir, goscript_lib, goscript_lib);
    system(cmd);
    
    // Copier aussi les fichiers à la racine
    snprintf(cmd, sizeof(cmd),
             "cp '%s'/*.gjs '%s/' 2>/dev/null; "
             "cp '%s'/Manifest.toml '%s/' 2>/dev/null",
             extract_dir, goscript_lib, extract_dir, goscript_lib);
    system(cmd);
    
    LOG_INFO("Installé dans: %s", goscript_lib);
    
    // 4. CRÉER LE CACHE RAPIDE DANS gpm_modules
    char gpm_modules_path[PATH_MAX];
    snprintf(gpm_modules_path, sizeof(gpm_modules_path), 
             "gpm_modules/%s", pkg_name);
    
    gpm_mkdir_p("gpm_modules");
    
    // Supprimer l'ancien lien si existe
    if (gpm_file_exists(gpm_modules_path)) {
        rmdir(gpm_modules_path);
        unlink(gpm_modules_path);
    }
    
    // Créer un lien symbolique vers /usr/local/lib/goscript/pkg
    snprintf(cmd, sizeof(cmd), 
             "ln -sf '%s' '%s' 2>/dev/null || cp -r '%s' '%s'",
             goscript_lib, gpm_modules_path, goscript_lib, gpm_modules_path);
    system(cmd);
    
    LOG_INFO("Cache rapide: %s -> %s", gpm_modules_path, goscript_lib);
    
    // 5. LIRE ET GÉRER LES DÉPENDANCES
    Manifest pkg_manifest = {0};
    char saved_dir[PATH_MAX];
    getcwd(saved_dir, sizeof(saved_dir));
    
    // Chercher le Manifest.toml dans le package extrait
    char manifest_path[PATH_MAX];
    snprintf(manifest_path, sizeof(manifest_path), 
             "%s/Manifest.toml", extract_dir);
    
    if (gpm_file_exists(manifest_path)) {
        chdir(extract_dir);
        
        if (gpm_manifest_read(&pkg_manifest) == 0) {
            LOG_INFO("Dépendances trouvées: %d", pkg_manifest.dep_count);
            
            // Installer chaque dépendance
            for (int i = 0; i < pkg_manifest.dep_count; i++) {
                Dependency* dep = &pkg_manifest.dependencies[i];
                
                // Vérifier si déjà installé
                char dep_path[PATH_MAX];
                snprintf(dep_path, sizeof(dep_path), 
                         "%s/%s", GPM_LIB_DIR, dep->name);
                
                if (!gpm_file_exists(dep_path)) {
                    LOG_INFO("  Installation de la dépendance: %s", dep->name);
                    
                    // Résoudre la version
                    char* dep_version = gpm_resolve_version(dep);
                    if (dep_version) {
                        gpm_install_package(dep->name, dep_version);
                    } else {
                        LOG_WARN("  Dépendance non trouvée: %s", dep->name);
                    }
                } else {
                    LOG_INFO("  Dépendance déjà installée: %s", dep->name);
                }
            }
        }
        chdir(saved_dir);
    } else {
        LOG_WARN("Aucun Manifest.toml dans le package (les dépendances ne seront pas installées)");
    }
    
    // 6. EXÉCUTER LE SCRIPT D'INSTALLATION SI PRÉSENT
    char install_script[PATH_MAX];
    snprintf(install_script, sizeof(install_script), 
             "%s/install.sh", extract_dir);
    
    if (gpm_file_exists(install_script)) {
        LOG_INFO("Exécution du script d'installation...");
        chdir(extract_dir);
        system("chmod +x install.sh && ./install.sh");
        chdir(saved_dir);
    }
    
    // 7. NETTOYER
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'", extract_dir);
    system(cmd);
    unlink(archive_path);
    
    // 8. VÉRIFICATION FINALE
    if (gpm_file_exists(goscript_lib)) {
        LOG_SUCCESS("Package %s@%s installé avec succès !", pkg_name, pkg_version);
        LOG_INFO("  📁 Bibliothèque: %s", goscript_lib);
        LOG_INFO("  ⚡ Cache: gpm_modules/%s", pkg_name);
        
        // Lister les fichiers installés
        snprintf(cmd, sizeof(cmd), 
                 "ls -1 '%s'/*.gjs 2>/dev/null | head -5 | sed 's/^/      /'",
                 goscript_lib);
        system(cmd);
        
        return 0;
    }
    
    LOG_ERROR("Échec de l'installation");
    return -1;
}

int gpm_run_script(const char* script) {
    if (!script || !script[0]) {
        LOG_WARN("Aucun script à exécuter");
        return 0;
    }
    
    LOG_STEP("Exécution du script");
    printf("  > %s\n", script);
    
    int ret = system(script);
    
    if (ret == 0) {
        LOG_SUCCESS("Script terminé");
    } else {
        LOG_WARN("Script terminé avec le code %d", WEXITSTATUS(ret));
    }
    
    return ret;
}
/* ================================================================
 * INSTALLER DEPUIS Manifest.toml (gpm install sans argument)
 * ================================================================ */

int gpm_install_from_manifest(void) {
    Manifest manifest;
    if (gpm_manifest_read(&manifest) != 0) {
        LOG_ERROR("Aucun Manifest.toml trouvé");
        LOG_INFO("Exécutez 'gpm init' pour créer un nouveau projet");
        return -1;
    }
    
    LOG_STEP("Installation des dépendances depuis Manifest.toml");
    
    // 1. Résoudre l'arbre
    DepNode* tree = gpm_resolve_tree(&manifest);
    if (!tree) {
        LOG_ERROR("Échec de la résolution des dépendances");
        return -1;
    }
    
    // 2. Hoisting
    gpm_hoist_dependencies(tree);
    
    // 3. Afficher l'arbre
    printf("\n");
    LOG_INFO("Arbre de dépendances :");
    gpm_print_tree(tree, 0);
    printf("\n");
    
    // 4. Aplatir et installer
    DepNode** flat = NULL;
    int flat_count = 0;
    gpm_flatten_tree_to_list(tree, &flat, &flat_count);
    
    int success = 0;
    int failed = 0;
    int skipped = 0;
    
    for (int i = 0; i < flat_count; i++) {
        DepNode* node = flat[i];
        if (node->depth == 0) continue;
        if (node->hoisted) { skipped++; continue; }
        
        if (gpm_install_package(node->name, node->version) == 0) {
            success++;
        } else {
            failed++;
        }
    }
    
    // 5. Générer le lockfile
    gpm_lockfile_generate(tree);
    
    // 6. Résumé
    printf("\n");
    LOG_SUCCESS("Installation terminée !");
    LOG_INFO("  ✅ %d packages installés", success);
    if (skipped > 0) LOG_INFO("  ⏭️  %d packages ignorés (hoisted)", skipped);
    if (failed > 0) LOG_WARN("  ❌ %d packages en erreur", failed);
    
    free(flat);
    gpm_free_dep_tree(tree);
    
    return failed > 0 ? -1 : 0;
}

/* ================================================================
 * INITIALISER UN NOUVEAU PROJET
 * ================================================================ */

int gpm_init_project(const char* name, const char* version) {
    printf("\n");
    printf(COLOR_CYAN COLOR_BOLD);
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║     GPM v%s - Initialisation de projet           ║\n", GPM_VERSION);
    printf("╚══════════════════════════════════════════════════╝\n");
    printf(COLOR_RESET "\n");
    
    Manifest manifest = {0};
    char input[256];
    
    printf("package name: (%s) ", name ? name : "my-project");
    fflush(stdout);
    if (fgets(input, sizeof(input), stdin)) input[strcspn(input, "\n")] = '\0';
    strncpy(manifest.name, (*input && strcmp(input, "") != 0) ? input : (name ? name : "my-project"), sizeof(manifest.name) - 1);
    
    printf("version: (1.0.0) ");
    fflush(stdout);
    if (fgets(input, sizeof(input), stdin)) input[strcspn(input, "\n")] = '\0';
    strncpy(manifest.version, (*input && strcmp(input, "") != 0) ? input : (version ? version : "1.0.0"), sizeof(manifest.version) - 1);
    
    printf("description: ");
    fflush(stdout);
    if (fgets(manifest.description, sizeof(manifest.description), stdin))
        manifest.description[strcspn(manifest.description, "\n")] = '\0';
    
    printf("entry point: (main.gjs) ");
    fflush(stdout);
    if (fgets(manifest.main, sizeof(manifest.main), stdin))
        manifest.main[strcspn(manifest.main, "\n")] = '\0';
    if (!manifest.main[0]) strcpy(manifest.main, "main.gjs");
    
    printf("author: ");
    fflush(stdout);
    if (fgets(manifest.author, sizeof(manifest.author), stdin))
        manifest.author[strcspn(manifest.author, "\n")] = '\0';
    
    printf("license: (MIT) ");
    fflush(stdout);
    if (fgets(manifest.license, sizeof(manifest.license), stdin))
        manifest.license[strcspn(manifest.license, "\n")] = '\0';
    if (!manifest.license[0]) strcpy(manifest.license, "MIT");
    
    strcpy(manifest.release, "r0");
    strcpy(manifest.arch, gpm_config.arch[0] ? gpm_config.arch : "x86_64");
    
    if (gpm_manifest_write(&manifest) == 0) {
        printf("\n");
        LOG_SUCCESS("Projet initialisé !");
        LOG_INFO("  Manifest: %s", GPM_MANIFEST_FILE);
        LOG_INFO("  Package: %s@%s", manifest.name, manifest.version);
        LOG_INFO("  Exécutez 'gpm install' pour installer les dépendances");
        return 0;
    }
    
    return -1;
}

/* ================================================================
 * DÉSINSTALLER UN PACKAGE
 * ================================================================ */

int gpm_uninstall_package(const char* name) {
    LOG_STEP("Désinstallation de %s", name);
    
    char pkg_path[PATH_MAX];
    snprintf(pkg_path, sizeof(pkg_path), "%s/%s", GPM_LIB_DIR, name);
    
    if (!gpm_file_exists(pkg_path)) {
        LOG_ERROR("%s n'est pas installé", name);
        return -1;
    }
    
    // Supprimer le répertoire de la lib
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'", pkg_path);
    system(cmd);
    
    // Supprimer le lien dans gpm_modules
    snprintf(cmd, sizeof(cmd), "rm -rf 'gpm_modules/%s'", name);
    system(cmd);
    
    LOG_SUCCESS("%s désinstallé", name);
    return 0;
}

/* ================================================================
 * MISE À JOUR D'UN PACKAGE
 * ================================================================ */

int gpm_update_package(const char* name) {
    LOG_STEP("Mise à jour de %s", name);
    
    // Désinstaller l'ancienne version
    gpm_uninstall_package(name);
    
    // Installer la dernière version
    return gpm_install_package(name, "latest");
}
