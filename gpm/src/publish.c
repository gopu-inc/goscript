// src/publish.c - NOUVEAU FICHIER
#include "gpm.h"

int gpm_publish(void) {
    LOG_STEP("Publication du package");
    
    // Lire le manifest
    Manifest manifest;
    if (gpm_manifest_read(&manifest) != 0) {
        LOG_ERROR("Pas de Manifest.toml trouvé");
        return -1;
    }
    
    // Vérifier l'authentification
    if (!gpm_config.authenticated || !gpm_config.token[0]) {
        LOG_ERROR("Non authentifié. Exécutez 'gpm login' d'abord");
        return -1;
    }
    
    // Construire le nom de l'archive
    char archive_name[512];
    snprintf(archive_name, sizeof(archive_name),
             "build/%s-%s-%s.%s%s",
             manifest.name, manifest.version, manifest.release, 
             manifest.arch, GPM_PACKAGE_EXT);
    
    // Vérifier si l'archive existe
    if (!gpm_file_exists(archive_name)) {
        LOG_INFO("Archive non trouvée, construction...");
        if (gpm_build_package() != 0) {
            return -1;
        }
    }
    
    // URL d'upload
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/package/upload/%s/%s",
             gpm_config.registry_url, GPM_API_VERSION,
             gpm_config.scope, manifest.name);
    
    // Uploader
    LOG_INFO("Upload vers %s...", url);
    
    if (gpm_network_upload(url, archive_name, gpm_config.token) == 0) {
        LOG_SUCCESS("Package publié avec succès !");
        LOG_INFO("  %s@%s", manifest.name, manifest.version);
        LOG_INFO("  %s/package/%s", gpm_config.registry_url, manifest.name);
        return 0;
    }
    
    LOG_ERROR("Échec de la publication");
    return -1;
}

int gpm_login(const char* username, const char* password) {
    LOG_STEP("Authentification de %s...", username);
    
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/login",
             gpm_config.registry_url, GPM_API_VERSION);
    
    // Créer le JSON
    char post_data[1024];
    snprintf(post_data, sizeof(post_data),
             "{\"username\":\"%s\",\"password\":\"%s\"}",
             username, password);
    
    // Envoyer la requête
    CURL* curl = curl_easy_init();
    if (!curl) return -1;
    
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    char* response = NULL;
    
    // ... (utiliser les callbacks réseau habituels)
    
    curl_easy_cleanup(curl);
    
    // Sauvegarder le token si succès
    if (response) {
        // Parser la réponse JSON pour extraire le token
        // Simplifié pour l'exemple
        strncpy(gpm_config.token, "demo-token", sizeof(gpm_config.token) - 1);
        strncpy(gpm_config.username, username, sizeof(gpm_config.username) - 1);
        gpm_config.authenticated = true;
        
        gpm_config_save();
        LOG_SUCCESS("Authentifié en tant que %s", username);
        return 0;
    }
    
    LOG_ERROR("Échec de l'authentification");
    return -1;
}

int gpm_logout(void) {
    gpm_config.authenticated = false;
    gpm_config.token[0] = '\0';
    gpm_config.username[0] = '\0';
    gpm_config_save();
    LOG_SUCCESS("Déconnecté");
    return 0;
}
