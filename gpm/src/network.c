// src/network.c
#include "gpm.h"

static CURL* g_curl = NULL;
static bool curl_initialized = false;

/* ================================================================
 * STRUCTURE POUR LES RÉPONSES HTTP
 * ================================================================ */

struct MemoryResponse {
    char* data;
    size_t size;
};

/* ================================================================
 * CALLBACKS CURL
 * ================================================================ */

static size_t write_memory_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryResponse* mem = (struct MemoryResponse*)userp;
    
    char* ptr = realloc(mem->data, mem->size + realsize + 1);
    if (!ptr) {
        LOG_ERROR("Out of memory in network callback");
        return 0;
    }
    
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = '\0';
    
    return realsize;
}

static size_t write_file_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

static int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow,
                              curl_off_t ultotal, curl_off_t ulnow) {
    (void)clientp;
    (void)ultotal;
    (void)ulnow;
    
    if (dltotal > 0) {
        int percent = (int)((dlnow * 100) / dltotal);
        static int last_percent = -1;
        
        if (percent != last_percent && (percent % 10 == 0 || percent == 100)) {
            printf("\r  [");
            int filled = percent / 2;
            for (int i = 0; i < 50; i++) {
                if (i < filled) printf("=");
                else if (i == filled) printf(">");
                else printf(" ");
            }
            printf("] %d%%", percent);
            fflush(stdout);
            last_percent = percent;
            
            if (percent == 100) printf("\n");
        }
    }
    return 0;
}

/* ================================================================
 * INITIALISATION DU RÉSEAU
 * ================================================================ */

int gpm_network_init(void) {
    if (curl_initialized) return 0;
    
    g_curl = curl_easy_init();
    if (!g_curl) {
        LOG_ERROR("Échec d'initialisation de libcurl");
        return -1;
    }
    
    // Configuration de base
    curl_easy_setopt(g_curl, CURLOPT_TIMEOUT, (long)gpm_config.timeout);
    curl_easy_setopt(g_curl, CURLOPT_CONNECTTIMEOUT, 15L);
    curl_easy_setopt(g_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(g_curl, CURLOPT_MAXREDIRS, 10L);
    curl_easy_setopt(g_curl, CURLOPT_USERAGENT, GPM_USER_AGENT);
    curl_easy_setopt(g_curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(g_curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");
    curl_easy_setopt(g_curl, CURLOPT_DNS_CACHE_TIMEOUT, 3600L);
    
    // SSL
    if (!gpm_config.verify_ssl) {
        curl_easy_setopt(g_curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(g_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    
    curl_initialized = true;
    LOG_DEBUG("Réseau initialisé (timeout=%ds)", gpm_config.timeout);
    return 0;
}

/* ================================================================
 * REQUÊTE GET AVEC AUTHENTIFICATION
 * ================================================================ */

char* gpm_network_get(const char* url, long* status_code) {
    gpm_network_init();
    
    struct MemoryResponse chunk = {0};
    chunk.data = malloc(1);
    if (!chunk.data) return NULL;
    chunk.size = 0;
    
    curl_easy_setopt(g_curl, CURLOPT_URL, url);
    curl_easy_setopt(g_curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(g_curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(g_curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(g_curl, CURLOPT_NOPROGRESS, 1L);
    
    // Headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Cache-Control: no-cache");
    
    // Auth token si disponible
    if (gpm_config.token[0]) {
        char auth[1024];
        snprintf(auth, sizeof(auth), "Authorization: Bearer %s", gpm_config.token);
        headers = curl_slist_append(headers, auth);
    }
    
    curl_easy_setopt(g_curl, CURLOPT_HTTPHEADER, headers);
    
    LOG_DEBUG("GET %s", url);
    
    CURLcode res = curl_easy_perform(g_curl);
    
    if (status_code) {
        curl_easy_getinfo(g_curl, CURLINFO_RESPONSE_CODE, status_code);
    }
    
    curl_slist_free_all(headers);
    
    if (res != CURLE_OK) {
        if (gpm_config.debug) {
            LOG_ERROR("GET échoué: %s", curl_easy_strerror(res));
        }
        free(chunk.data);
        return NULL;
    }
    
    return chunk.data;
}

/* ================================================================
 * TÉLÉCHARGEMENT DE FICHIER
 * ================================================================ */

int gpm_network_download(const char* url, const char* output_path) {
    gpm_network_init();
    
    LOG_DEBUG("Téléchargement: %s -> %s", url, output_path);
    
    // Créer le répertoire parent
    char* parent = strdup(output_path);
    char* dir = dirname(parent);
    gpm_mkdir_p(dir);
    free(parent);
    
    FILE* fp = fopen(output_path, "wb");
    if (!fp) {
        LOG_ERROR("Impossible d'ouvrir %s en écriture", output_path);
        return -1;
    }
    
    curl_easy_setopt(g_curl, CURLOPT_URL, url);
    curl_easy_setopt(g_curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(g_curl, CURLOPT_WRITEFUNCTION, write_file_callback);
    curl_easy_setopt(g_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(g_curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(g_curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
    curl_easy_setopt(g_curl, CURLOPT_CONNECTTIMEOUT, 30L);
    
    // Headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/octet-stream, application/gzip");
    
    if (gpm_config.token[0]) {
        char auth[1024];
        snprintf(auth, sizeof(auth), "Authorization: Bearer %s", gpm_config.token);
        headers = curl_slist_append(headers, auth);
    }
    
    curl_easy_setopt(g_curl, CURLOPT_HTTPHEADER, headers);
    
    printf("  Téléchargement: %s\n", url);
    
    CURLcode res = CURLE_OK;
    long http_code = 0;
    
    for (int attempt = 0; attempt < GPM_RETRY_COUNT; attempt++) {
        if (attempt > 0) {
            int delay = GPM_RETRY_DELAY * (attempt + 1);
            LOG_INFO("Nouvelle tentative %d/%d dans %ds...", 
                     attempt + 1, GPM_RETRY_COUNT, delay);
            sleep(delay);
            
            fclose(fp);
            fp = fopen(output_path, "wb");
            if (!fp) return -1;
            curl_easy_setopt(g_curl, CURLOPT_WRITEDATA, fp);
        }
        
        res = curl_easy_perform(g_curl);
        curl_easy_getinfo(g_curl, CURLINFO_RESPONSE_CODE, &http_code);
        
        if (res == CURLE_OK && http_code == 200) {
            break;
        }
    }
    
    curl_slist_free_all(headers);
    fclose(fp);
    
    if (res != CURLE_OK || http_code != 200) {
        LOG_ERROR("Téléchargement échoué (HTTP %ld): %s", 
                  http_code, curl_easy_strerror(res));
        unlink(output_path);
        return -1;
    }
    
    // Vérifier la taille du fichier téléchargé
    struct stat st;
    if (stat(output_path, &st) != 0 || st.st_size == 0) {
        LOG_ERROR("Fichier téléchargé vide ou inexistant");
        unlink(output_path);
        return -1;
    }
    
    LOG_DEBUG("Téléchargement terminé: %s (%ld octets)", output_path, st.st_size);
    return 0;
}

/* ================================================================
 * UPLOAD DE FICHIER
 * ================================================================ */

int gpm_network_upload(const char* url, const char* file_path, const char* token) {
    gpm_network_init();
    
    FILE* fp = fopen(file_path, "rb");
    if (!fp) {
        LOG_ERROR("Impossible d'ouvrir %s", file_path);
        return -1;
    }
    
    curl_mime* mime = curl_mime_init(g_curl);
    curl_mimepart* part = curl_mime_addpart(mime);
    curl_mime_name(part, "file");
    curl_mime_filedata(part, file_path);
    curl_mime_filename(part, basename((char*)file_path));
    
    curl_easy_setopt(g_curl, CURLOPT_URL, url);
    curl_easy_setopt(g_curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(g_curl, CURLOPT_TIMEOUT, 120L);
    
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    
    if (token && token[0]) {
        char auth[1024];
        snprintf(auth, sizeof(auth), "Authorization: Bearer %s", token);
        headers = curl_slist_append(headers, auth);
    }
    
    curl_easy_setopt(g_curl, CURLOPT_HTTPHEADER, headers);
    
    LOG_DEBUG("Upload: %s -> %s", file_path, url);
    
    CURLcode res = curl_easy_perform(g_curl);
    
    curl_mime_free(mime);
    curl_slist_free_all(headers);
    fclose(fp);
    
    long http_code = 0;
    curl_easy_getinfo(g_curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    if (res != CURLE_OK || (http_code != 200 && http_code != 201)) {
        LOG_ERROR("Upload échoué (HTTP %ld)", http_code);
        return -1;
    }
    
    LOG_DEBUG("Upload terminé");
    return 0;
}

/* ================================================================
 * VÉRIFICATION DE LA CONNECTIVITÉ
 * ================================================================ */

bool gpm_network_check(void) {
    gpm_network_init();
    
    char url[512];
    snprintf(url, sizeof(url), "%s/status", gpm_config.registry_url);
    
    long status = 0;
    char* response = gpm_network_get(url, &status);
    
    if (status == 200 && response) {
        free(response);
        LOG_DEBUG("Connectivité OK");
        return true;
    }
    
    free(response);
    LOG_WARN("Pas de connectivité réseau");
    return false;
}
