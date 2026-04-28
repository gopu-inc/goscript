// src/install.c
#include "gpm.h"

/* ================================================================
 * TÉLÉCHARGER UN PACKAGE DEPUIS LE REGISTRE
 * ================================================================ */

static int download_package(const char* name, const char* version, char* output_path) {
    // Construire l'URL de téléchargement
    char url[1024];
    snprintf(url, sizeof(url),
             "%s/package/download/%s/%s/%s/r0/%s",
             gpm_config.registry_url,
             gpm_config.scope,
             name, version, gpm_config.arch);
    
    snprintf(output_path, PATH_MAX, "%s/%s-%s-%s%s",
             GPM_TEMP_DIR, name, version, gpm_config.arch, GPM_PACKAGE_EXT);
    
    return gpm_network_download(url, output_path);
}

/* ================================================================
 * EXTRAIRE UN PACKAGE
 * ================================================================ */

static int extract_package(const char* archive_path, const char* dest_dir) {
    gpm_mkdir_p(dest_dir);
    
    char cmd[2048];
    snprintf(cmd, sizeof(cmd),
             "cd '%s' && tar -xzf '%s' 2>/dev/null",
             dest_dir, archive_path);
    
    if (system(cmd) != 0) {
        LOG_ERROR("Échec de l'extraction");
        return -1;
    }
    
    // Vérifier que des fichiers ont été extraits
    char check[1024];
    snprintf(check, sizeof(check), "ls -A '%s' | wc -l", dest_dir);
    
    FILE* fp = popen(check, "r");
    if (fp) {
        int count = 0;
        fscanf(fp, "%d", &count);
        pclose(fp);
        if (count > 0) return 0;
    }
    
    LOG_ERROR("Aucun fichier extrait");
    return -1;
}

/* ================================================================
 * EXÉCUTER UN SCRIPT DE CYCLE DE VIE
 * ================================================================ */

int gpm_run_script(const char* script) {
    if (!script || !script[0]) return 0;
    
    LOG_STEP("Exécution du script");
    printf("  > %s\n", script);
    
    int ret = system(script);
    
    if (ret != 0) {
        LOG_WARN("Script terminé avec le code %d", WEXITSTATUS(ret));
    }
    
    return ret;
}

/* ================================================================
 * INSTALLER UN PACKAGE SPÉCIFIQUE
 * ================================================================ */

int gpm_install_package(const char* name, const char* version) {
    char pkg_name[256];
    char pkg_version[64];
    
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
    
    // Si pas de version spécifiée, résoudre la dernière
    if (!pkg_version[0]) {
        Dependency dep = {0};
        strncpy(dep.name, pkg_name, sizeof(dep.name) - 1);
        dep.type = VER_LATEST;
        
        char* resolved = gpm_resolve_version(&dep);
        if (!resolved) {
            LOG_ERROR("Package %s introuvable", pkg_name);
            return -1;
        }
        strncpy(pkg_version, resolved, sizeof(pkg_version) - 1);
    }
    
    LOG_STEP("Installation de %s@%s", pkg_name, pkg_version);
    
    // Déterminer le répertoire d'installation
    char install_dir[PATH_MAX];
    if (gpm_config.global) {
        snprintf(install_dir, sizeof(install_dir), "%s/%s",
                 gpm_config.global_dir, pkg_name);
    } else {
        snprintf(install_dir, sizeof(install_dir), "gpm_modules/%s", pkg_name);
    }
    
    // Vérifier si déjà installé
    if (gpm_file_exists(install_dir)) {
        if (!gpm_config.force) {
            LOG_WARN("%s est déjà installé", pkg_name);
            LOG_INFO("Utilisez --force pour réinstaller");
            return 0;
        }
        // Supprimer l'ancienne version
        char rm_cmd[1024];
        snprintf(rm_cmd, sizeof(rm_cmd), "rm -rf '%s'", install_dir);
        system(rm_cmd);
    }
    
    // 1. Télécharger
    char archive_path[PATH_MAX];
    if (download_package(pkg_name, pkg_version, archive_path) != 0) {
        return -1;
    }
    
    // 2. Extraire
    if (extract_package(archive_path, install_dir) != 0) {
        unlink(archive_path);
        return -1;
    }
    unlink(archive_path);
    
    // 3. Lire le manifest du package installé
    Manifest pkg_manifest;
    char saved_dir[PATH_MAX];
    getcwd(saved_dir, sizeof(saved_dir));
    chdir(install_dir);
    
    if (gpm_manifest_read(&pkg_manifest) == 0) {
        // 4. Exécuter les scripts de cycle de vie
        gpm_run_script(pkg_manifest.scripts_preinstall);
        gpm_run_script(pkg_manifest.scripts_install);
        gpm_run_script(pkg_manifest.scripts_postinstall);
        
        // 5. Installer les dépendances du package
        if (pkg_manifest.dep_count > 0) {
            LOG_INFO("Installation des dépendances de %s...", pkg_name);
            for (int i = 0; i < pkg_manifest.dep_count; i++) {
                Dependency* dep = &pkg_manifest.dependencies[i];
                gpm_install_package(dep->name, gpm_semver_to_string(dep->version));
            }
        }
    }
    
    chdir(saved_dir);
    
    LOG_SUCCESS("%s@%s installé avec succès", pkg_name, pkg_version);
    return 0;
}

/* ================================================================
 * INSTALLER DEPUIS LE MANIFEST (gpm install)
 * ================================================================ */

int gpm_install_from_manifest(void) {
    Manifest manifest;
    if (gpm_manifest_read(&manifest) != 0) {
        LOG_ERROR("Exécutez 'gpm init' d'abord");
        return -1;
    }
    
    LOG_STEP("Installation depuis Manifest.toml");
    
    // Vérifier le lockfile
    Lockfile lock;
    bool use_lock = (gpm_lockfile_read(&lock) == 0);
    
    // 1. Résoudre l'arbre de dépendances
    DepNode* tree = gpm_resolve_tree(&manifest);
    if (!tree) {
        LOG_ERROR("Échec de la résolution des dépendances");
        return -1;
    }
    
    // 2. Hoisting
    gpm_hoist_dependencies(tree);
    
    // 3. Afficher l'arbre
    LOG_INFO("Arbre de dépendances:");
    gpm_print_tree(tree, 0);
    printf("\n");
    
    // 4. Aplatir et installer
    DepNode** flat = NULL;
    int flat_count = 0;
    gpm_flatten_tree_to_list(tree, &flat, &flat_count);
    
    LOG_INFO("Installation de %d packages...", flat_count);
    
    int success = 0;
    int failed = 0;
    
    for (int i = 0; i < flat_count; i++) {
        DepNode* node = flat[i];
        if (node->depth == 0) continue;  // Skip root
        
        if (!node->hoisted) {
            if (gpm_install_package(node->name, node->version) == 0) {
                success++;
            } else {
                failed++;
            }
        }
    }
    
    // 5. Générer le lockfile
    gpm_lockfile_generate(tree);
    
    // 6. Résumé
    printf("\n");
    if (failed == 0) {
        LOG_SUCCESS("Installation terminée: %d packages", success);
    } else {
        LOG_WARN("Installation terminée avec %d erreurs", failed);
    }
    
    free(flat);
    gpm_free_dep_tree(tree);
    
    return failed > 0 ? -1 : 0;
}

/* ================================================================
 * DÉSINSTALLER UN PACKAGE
 * ================================================================ */

int gpm_uninstall_package(const char* name) {
    LOG_STEP("Désinstallation de %s", name);
    
    char pkg_dir[PATH_MAX];
    if (gpm_config.global) {
        snprintf(pkg_dir, sizeof(pkg_dir), "%s/%s", gpm_config.global_dir, name);
    } else {
        snprintf(pkg_dir, sizeof(pkg_dir), "gpm_modules/%s", name);
    }
    
    if (!gpm_file_exists(pkg_dir)) {
        LOG_ERROR("%s n'est pas installé", name);
        return -1;
    }
    
    // Exécuter le script de preuninstall si disponible
    Manifest manifest;
    char saved_dir[PATH_MAX];
    getcwd(saved_dir, sizeof(saved_dir));
    chdir(pkg_dir);
    
    if (gpm_manifest_read(&manifest) == 0) {
        // Chercher un script de désinstallation
        if (gpm_file_exists("uninstall.sh")) {
            system("./uninstall.sh");
        }
    }
    
    chdir(saved_dir);
    
    // Supprimer le répertoire
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'", pkg_dir);
    system(cmd);
    
    LOG_SUCCESS("%s désinstallé", name);
    return 0;
}

/* ================================================================
 * MISE À JOUR
 * ================================================================ */

int gpm_update_package(const char* name) {
    LOG_STEP("Mise à jour de %s", name);
    
    // Désinstaller l'ancienne version
    gpm_uninstall_package(name);
    
    // Installer la dernière version
    return gpm_install_package(name, "latest");
}
