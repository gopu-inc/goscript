#include "gpm.h"

/* ================================================================
 * STRUCTURE POUR LA RÉPONSE CURL
 * ================================================================ */

struct MemoryResponse {
    char* data;
    size_t size;
};

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryResponse* mem = (struct MemoryResponse*)userp;
    
    char* ptr = realloc(mem->data, mem->size + realsize + 1);
    if (!ptr) return 0;
    
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = '\0';
    
    return realsize;
}

/* ================================================================
 * AUTHENTIFICATION (LOGIN)
 * ================================================================ */

int gpm_login(const char* username, const char* password) {
    LOG_STEP("Authentification de %s...", username);
    
    CURL* curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("Échec d'initialisation de libcurl");
        return -1;
    }
    
    // URL d'authentification
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/login",
             gpm_config.registry_url, GPM_API_VERSION);
    
    LOG_DEBUG("URL: %s", url);
    
    // Créer le JSON de la requête
    char post_data[1024];
    snprintf(post_data, sizeof(post_data),
             "{\"username\":\"%s\",\"password\":\"%s\"}",
             username, password);
    
    LOG_DEBUG("Données: %s", post_data);
    
    // Configuration de la requête
    struct MemoryResponse response = {0};
    response.data = malloc(1);
    response.size = 0;
    
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Accept: application/json");
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(post_data));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, GPM_USER_AGENT);
    
    if (!gpm_config.verify_ssl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    
    // Envoyer la requête
    CURLcode res = curl_easy_perform(curl);
    
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    
    // Traiter la réponse
    if (res != CURLE_OK) {
        LOG_ERROR("Erreur réseau: %s", curl_easy_strerror(res));
        free(response.data);
        return -1;
    }
    
    LOG_DEBUG("HTTP %ld", http_code);
    LOG_DEBUG("Réponse: %s", response.data ? response.data : "(vide)");
    
    if (http_code == 200 && response.data) {
        // Parser le JSON
        json_error_t error;
        json_t* root = json_loads(response.data, 0, &error);
        
        if (root) {
            json_t* success = json_object_get(root, "success");
            json_t* token = json_object_get(root, "token");
            json_t* err_msg = json_object_get(root, "error");
            
            if (json_is_true(success) && token && json_is_string(token)) {
                // Sauvegarder le token
                strncpy(gpm_config.token, json_string_value(token), 
                        sizeof(gpm_config.token) - 1);
                strncpy(gpm_config.username, username, 
                        sizeof(gpm_config.username) - 1);
                gpm_config.authenticated = true;
                
                gpm_config_save();
                
                LOG_SUCCESS("Authentifié en tant que %s", username);
                LOG_INFO("Token sauvegardé dans ~/%s/%s", 
                         gpm_config.home_dir, GPM_CONFIG_FILE);
                
                json_decref(root);
                free(response.data);
                return 0;
            }
            
            if (err_msg && json_is_string(err_msg)) {
                LOG_ERROR("Erreur: %s", json_string_value(err_msg));
            } else {
                LOG_ERROR("Réponse inattendue du serveur");
            }
            
            json_decref(root);
        } else {
            LOG_ERROR("Réponse JSON invalide: %s", error.text);
        }
    } else if (http_code == 401) {
        LOG_ERROR("Identifiants invalides");
    } else if (http_code == 404) {
        LOG_ERROR("Endpoint d'authentification introuvable");
    } else {
        LOG_ERROR("Erreur HTTP %ld", http_code);
    }
    
    free(response.data);
    return -1;
}

/* ================================================================
 * DÉCONNEXION (LOGOUT)
 * ================================================================ */

int gpm_logout(void) {
    gpm_config.authenticated = false;
    memset(gpm_config.token, 0, sizeof(gpm_config.token));
    memset(gpm_config.username, 0, sizeof(gpm_config.username));
    gpm_config_save();
    LOG_SUCCESS("Déconnecté");
    return 0;
}

/* ================================================================
 * PUBLICATION D'UN PACKAGE
 * ================================================================ */

int gpm_publish(void) {
    LOG_STEP("Publication du package");
    
    // Vérifier l'authentification
    if (!gpm_config.authenticated || !gpm_config.token[0]) {
        LOG_ERROR("Non authentifié. Exécutez 'gpm login' d'abord");
        return -1;
    }
    
    // Lire le manifest
    Manifest manifest;
    if (gpm_manifest_read(&manifest) != 0) {
        LOG_ERROR("Pas de Manifest.toml trouvé. Exécutez 'gpm init' d'abord");
        return -1;
    }
    
    // Vérifier que le package existe ou le construire
    char archive_name[512];
    snprintf(archive_name, sizeof(archive_name),
             "build/%s-%s-%s.%s%s",
             manifest.name, manifest.version, 
             manifest.release, manifest.arch, GPM_PACKAGE_EXT);
    
    if (!gpm_file_exists(archive_name)) {
        LOG_INFO("Archive non trouvée, construction automatique...");
        if (gpm_build_package() != 0) {
            LOG_ERROR("Échec de la construction");
            return -1;
        }
    }
    
    // Calculer le SHA256
    char* sha256 = gpm_sha256_file(archive_name);
    if (sha256) {
        strncpy(manifest.sha256, sha256, sizeof(manifest.sha256) - 1);
    }
    
    // URL d'upload
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/package/upload/%s/%s",
             gpm_config.registry_url, GPM_API_VERSION,
             gpm_config.scope, manifest.name);
    
    LOG_INFO("Upload vers %s...", url);
    LOG_INFO("  Package: %s@%s", manifest.name, manifest.version);
    LOG_INFO("  Archive: %s", archive_name);
    if (sha256) LOG_INFO("  SHA256: %s", sha256);
    
    // Uploader
    if (gpm_network_upload(url, archive_name, gpm_config.token) == 0) {
        LOG_SUCCESS("Package publié avec succès !");
        LOG_INFO("  📦 %s@%s", manifest.name, manifest.version);
        LOG_INFO("  🔗 %s/package/%s", gpm_config.registry_url, manifest.name);
        return 0;
    }
    
    LOG_ERROR("Échec de la publication");
    return -1;
}
