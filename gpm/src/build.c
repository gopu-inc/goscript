// src/build.c - NOUVEAU FICHIER
#include "gpm.h"

int gpm_build_package(void) {
    LOG_STEP("Construction du package");
    
    // Lire le manifest
    Manifest manifest;
    if (gpm_manifest_read(&manifest) != 0) {
        LOG_ERROR("Pas de Manifest.toml trouvé");
        return -1;
    }
    
    // Créer le répertoire de build
    gpm_mkdir_p("build");
    
    char build_dir[512];
    snprintf(build_dir, sizeof(build_dir), "build/pkg-%s", manifest.name);
    gpm_mkdir_p(build_dir);
    
    // Structure standard
    char path[1024];
    snprintf(path, sizeof(path), "%s/usr/bin", build_dir);
    gpm_mkdir_p(path);
    
    snprintf(path, sizeof(path), "%s/usr/lib", build_dir);
    gpm_mkdir_p(path);
    
    // Exécuter le script de build si présent
    if (manifest.scripts_build[0]) {
        LOG_INFO("Exécution du script de build...");
        int ret = system(manifest.scripts_build);
        if (ret != 0) {
            LOG_ERROR("Build échoué (code %d)", WEXITSTATUS(ret));
            return -1;
        }
    }
    
    // Copier les fichiers spécifiés
    if (manifest.files_count > 0) {
        for (int i = 0; i < manifest.files_count; i++) {
            char dst[1024];
            snprintf(dst, sizeof(dst), "%s/%s", build_dir, manifest.files[i]);
            
            // Créer le répertoire parent
            char* parent = strdup(dst);
            char* dir = dirname(parent);
            gpm_mkdir_p(dir);
            free(parent);
            
            // Copier
            char cmd[2048];
            snprintf(cmd, sizeof(cmd), "cp '%s' '%s'", manifest.files[i], dst);
            system(cmd);
        }
    }
    
    // Créer l'archive .tar.bool
    char archive_name[512];
    snprintf(archive_name, sizeof(archive_name),
             "build/%s-%s-%s.%s%s",
             manifest.name, manifest.version, manifest.release,
             manifest.arch, GPM_PACKAGE_EXT);
    
    char cmd[2048];
    snprintf(cmd, sizeof(cmd),
             "cd '%s' && tar -czf '../%s-%s-%s.%s%s' * 2>/dev/null",
             build_dir, manifest.name, manifest.version, 
             manifest.release, manifest.arch, GPM_PACKAGE_EXT);
    
    if (system(cmd) == 0) {
        // Calculer SHA256
        char* sha = gpm_sha256_file(archive_name);
        if (sha) {
            strncpy(manifest.sha256, sha, sizeof(manifest.sha256) - 1);
        }
        
        struct stat st;
        stat(archive_name, &st);
        
        LOG_SUCCESS("Build terminé !");
        LOG_INFO("  Archive: %s", archive_name);
        LOG_INFO("  Taille: %.2f KB", st.st_size / 1024.0);
        if (sha) LOG_INFO("  SHA256: %s", sha);
        
        // Nettoyer
        snprintf(cmd, sizeof(cmd), "rm -rf '%s'", build_dir);
        system(cmd);
        
        return 0;
    }
    
    LOG_ERROR("Échec de la création de l'archive");
    return -1;
}
