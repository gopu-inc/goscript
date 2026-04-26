/* ================================================================
 * gpm_network.c - Gestion réseau, authentification, téléchargement
 * ================================================================ */

#include "gpm.h"

/* ================================================================
 * VARIABLES STATIQUES
 * ================================================================ */

static CURL* curl = NULL;
static bool curl_initialized = false;

/* ================================================================
 * STRUCTURE POUR LES DONNÉES DE RÉPONSE
 * ================================================================ */

struct MemoryStruct {
    char* memory;
    size_t size;
};

/* ================================================================
 * CALLBACKS CURL
 * ================================================================ */

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;
    
    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        LOG_ERROR("Out of memory in write callback");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

static size_t write_file_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
    return written;
}

static int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow,
                             curl_off_t ultotal, curl_off_t ulnow) {
    (void)clientp;
    (void)ultotal;
    (void)ulnow;
    
    if (dltotal > 0) {
        int percent = (int)((dlnow * 100) / dltotal);
        fprintf(stderr, "\r  " COLOR_CYAN "Downloading: %d%%" COLOR_RESET, percent);
        fflush(stderr);
        if (dlnow == dltotal) fprintf(stderr, "\n");
    }
    return 0;
}

/* ================================================================
 * INITIALISATION / NETTOYAGE
 * ================================================================ */

int network_init(void) {
    if (curl_initialized) return 0;
    
    curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("Failed to initialize CURL");
        return 1;
    }
    
    // Configuration de base
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, (long)g_config.timeout);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, GPM_USER_AGENT);
    
    // Keep-alive
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
    
    // Encodage
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");
    
    // Redirections POST
    curl_easy_setopt(curl, CURLOPT_POSTREDIR, CURL_REDIR_POST_ALL);
    
    // Cache DNS
    curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 3600L);
    
    // SSL
    if (!g_config.verify_ssl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    
    // Proxy
    if (g_config.proxy) {
        curl_easy_setopt(curl, CURLOPT_PROXY, g_config.proxy);
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
    }
    
    curl_initialized = true;
    LOG_DEBUG("CURL initialized (timeout=%ds)", g_config.timeout);
    return 0;
}

void network_cleanup(void) {
    if (curl) {
        curl_easy_cleanup(curl);
        curl = NULL;
    }
    curl_initialized = false;
}

/* ================================================================
 * USER AGENT COMPLET
 * ================================================================ */

char* network_get_user_agent(void) {
    static char ua[1024];
    struct utsname sys_info;
    uname(&sys_info);
    
    struct sysinfo mem_info;
    sysinfo(&mem_info);
    
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    
    char* username = get_username();
    ArchType arch = get_cpu_arch();
    const char* arch_str = "unknown";
    switch (arch) {
        case ARCH_X86_64:  arch_str = "x86_64"; break;
        case ARCH_I686:    arch_str = "i686"; break;
        case ARCH_AARCH64: arch_str = "aarch64"; break;
        case ARCH_ARMV7L:  arch_str = "armv7l"; break;
        case ARCH_RISCV64: arch_str = "riscv64"; break;
        default: break;
    }
    
    snprintf(ua, sizeof(ua),
             "GPM/%s (Goscript-PM; %s %s; %s; %s; %ldMB RAM; %d CPUs; %s@%s) "
             "libcurl/%s OpenSSL/%s",
             GPM_VERSION,
             sys_info.sysname,
             sys_info.release,
             arch_str,
             sys_info.machine,
             mem_info.totalram / (1024 * 1024),
             get_nprocs(),
             username ? username : "unknown",
             hostname,
             curl_version_info(CURLVERSION_NOW)->version,
             OpenSSL_version(OPENSSL_VERSION));
    
    free(username);
    return ua;
}

char* network_get_system_info(void) {
    static char info[2048];
    struct utsname sys_info;
    uname(&sys_info);
    
    struct sysinfo mem_info;
    sysinfo(&mem_info);
    
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    
    char* username = get_username();
    char* os_name = get_os_name();
    char* os_version = get_os_version();
    
    snprintf(info, sizeof(info),
             "{\n"
             "  \"os\": \"%s\",\n"
             "  \"os_version\": \"%s\",\n"
             "  \"kernel\": \"%s\",\n"
             "  \"arch\": \"%s\",\n"
             "  \"hostname\": \"%s\",\n"
             "  \"username\": \"%s\",\n"
             "  \"cpus\": %d,\n"
             "  \"ram_mb\": %ld,\n"
             "  \"boot_time\": %lld,\n"
             "  \"gpm_version\": \"%s\"\n"
             "}",
             os_name ? os_name : sys_info.sysname,
             os_version ? os_version : sys_info.release,
             sys_info.release,
             sys_info.machine,
             hostname,
             username ? username : "unknown",
             get_nprocs(),
             mem_info.totalram / (1024 * 1024),
             (long long)get_boot_time(),
             GPM_VERSION);
    
    free(os_name);
    free(os_version);
    free(username);
    
    return info;
}

/* ================================================================
 * REQUÊTES HTTP
 * ================================================================ */

char* network_get(const char* url, long* status_code) {
    if (!curl_initialized) network_init();
    
    struct MemoryStruct chunk = {0};
    chunk.memory = malloc(1);
    if (!chunk.memory) return NULL;
    chunk.size = 0;
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, (long)g_config.timeout);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    
    // Headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
    headers = curl_slist_append(headers, "Cache-Control: no-cache");
    
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    LOG_DEBUG("GET %s", url);
    
    CURLcode res = curl_easy_perform(curl);
    
    if (status_code) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, status_code);
    }
    
    curl_slist_free_all(headers);
    
    if (res != CURLE_OK) {
        if (g_config.debug) {
            LOG_ERROR("GET %s failed: %s", url, curl_easy_strerror(res));
        }
        free(chunk.memory);
        return NULL;
    }
    
    return chunk.memory;
}

char* network_post(const char* url, const char* data, const char* content_type) {
    if (!curl_initialized) network_init();
    
    struct MemoryStruct chunk = {0};
    chunk.memory = malloc(1);
    if (!chunk.memory) return NULL;
    chunk.size = 0;
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(data));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, (long)g_config.timeout);
    
    // Headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
    
    if (content_type) {
        char ct[512];
        snprintf(ct, sizeof(ct), "Content-Type: %s", content_type);
        headers = curl_slist_append(headers, ct);
    }
    
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    LOG_DEBUG("POST %s", url);
    
    CURLcode res = curl_easy_perform(curl);
    
    curl_slist_free_all(headers);
    
    if (res != CURLE_OK) {
        if (g_config.debug) {
            LOG_ERROR("POST %s failed: %s", url, curl_easy_strerror(res));
        }
        free(chunk.memory);
        return NULL;
    }
    
    return chunk.memory;
}

/* ================================================================
 * TÉLÉCHARGEMENT DE FICHIER
 * ================================================================ */

int network_download(const char* url, const char* output_path) {
    if (!curl_initialized) network_init();
    
    LOG_DEBUG("Downloading: %s -> %s", url, output_path);
    
    // Créer le répertoire parent si nécessaire
    char* parent_dir = path_dirname(output_path);
    if (parent_dir) {
        dir_create(parent_dir);
        free(parent_dir);
    }
    
    FILE* fp = fopen(output_path, "wb");
    if (!fp) {
        LOG_ERROR("Cannot open file for writing: %s", output_path);
        return 1;
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, (long)g_config.timeout);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30L);
    
    // Headers pour le téléchargement
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/octet-stream, application/gzip");
    headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
    
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    // Retry avec délai progressif
    CURLcode res = CURLE_OK;
    long http_code = 0;
    
    for (int attempt = 0; attempt < g_config.retry_count; attempt++) {
        if (attempt > 0) {
            int delay = GPM_RETRY_DELAY * (attempt + 1);
            LOG_INFO("Retry %d/%d in %ds...", attempt + 1, g_config.retry_count, delay);
            sleep(delay);
            
            // Réouvrir le fichier (truncate)
            fclose(fp);
            fp = fopen(output_path, "wb");
            if (!fp) return 1;
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        }
        
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        
        if (res == CURLE_OK && http_code == 200) {
            break;  // Succès
        }
        
        if (res == CURLE_OPERATION_TIMEDOUT) {
            LOG_WARN("Timeout - server may be waking up (cold start)");
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, (long)(g_config.timeout * 2));
        }
    }
    
    curl_slist_free_all(headers);
    fclose(fp);
    
    if (res != CURLE_OK || http_code != 200) {
        LOG_ERROR("Download failed after %d attempts: HTTP %ld, %s", 
                  g_config.retry_count, http_code,
                  res != CURLE_OK ? curl_easy_strerror(res) : "OK");
        unlink(output_path);
        return 1;
    }
    
    LOG_DEBUG("Download complete: %s", output_path);
    return 0;
}

/* ================================================================
 * UPLOAD DE FICHIER
 * ================================================================ */

int network_upload(const char* url, const char* file_path) {
    if (!curl_initialized) network_init();
    
    FILE* fp = fopen(file_path, "rb");
    if (!fp) {
        LOG_ERROR("Cannot open file: %s", file_path);
        return 1;
    }
    
    // Créer le formulaire multipart
    curl_mime* mime = curl_mime_init(curl);
    if (!mime) {
        fclose(fp);
        return 1;
    }
    
    curl_mimepart* part = curl_mime_addpart(mime);
    curl_mime_name(part, "file");
    curl_mime_filedata(part, file_path);
    
    char* basename = path_basename(file_path);
    curl_mime_filename(part, basename);
    free(basename);
    
    // Ajouter les champs de métadonnées
    if (g_config.default_scope) {
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "scope");
        curl_mime_data(part, g_config.default_scope, CURL_ZERO_TERMINATED);
    }
    
    if (g_config.default_arch) {
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "arch");
        curl_mime_data(part, g_config.default_arch, CURL_ZERO_TERMINATED);
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, (long)(g_config.timeout * 2));  // Upload plus long
    
    // Headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    LOG_DEBUG("Uploading: %s -> %s", file_path, url);
    
    CURLcode res = curl_easy_perform(curl);
    
    curl_mime_free(mime);
    curl_slist_free_all(headers);
    fclose(fp);
    
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    if (res != CURLE_OK || (http_code != 200 && http_code != 201)) {
        LOG_ERROR("Upload failed: HTTP %ld, %s", http_code,
                  res != CURLE_OK ? curl_easy_strerror(res) : "OK");
        return 1;
    }
    
    LOG_DEBUG("Upload complete");
    return 0;
}

/* ================================================================
 * VÉRIFICATION DE CONNECTIVITÉ
 * ================================================================ */

bool network_check_connectivity(void) {
    if (!curl_initialized) network_init();
    
    // Tester le registre principal
    char url[1024];
    snprintf(url, sizeof(url), "%s/status", g_config.registry_url);
    
    long status = 0;
    char* response = network_get(url, &status);
    
    if (status == 200 && response) {
        free(response);
        LOG_DEBUG("Connectivity OK: %s", g_config.registry_url);
        return true;
    }
    free(response);
    
    // Essayer les miroirs
    const char* mirrors[] = {
        GPM_MIRROR_REGISTRY,
        GPM_FALLBACK_REGISTRY,
        "https://google.com",
        NULL
    };
    
    for (int i = 0; mirrors[i]; i++) {
        snprintf(url, sizeof(url), "%s/status", mirrors[i]);
        response = network_get(url, &status);
        if (status == 200 && response) {
            free(response);
            LOG_DEBUG("Connectivity OK via mirror: %s", mirrors[i]);
            return true;
        }
        free(response);
    }
    
    LOG_WARN("No connectivity detected");
    return false;
}

/* ================================================================
 * AUTHENTIFICATION
 * ================================================================ */

int network_auth_login(const char* username, const char* password) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/login", 
             g_config.registry_url, GPM_API_VERSION);
    
    // Créer le JSON de la requête
    json_t* data = json_object();
    json_object_set_new(data, "username", json_string(username));
    json_object_set_new(data, "password", json_string(password));
    
    char* json_str = json_dumps(data, 0);
    json_decref(data);
    
    LOG_DEBUG("Login request to %s", url);
    
    char* response = network_post(url, json_str, "application/json");
    free(json_str);
    
    if (!response) {
        LOG_ERROR("No response from server");
        return 1;
    }
    
    json_error_t error;
    json_t* root = json_loads(response, 0, &error);
    free(response);
    
    if (!root) {
        LOG_ERROR("Failed to parse server response");
        return 1;
    }
    
    // Vérifier le succès
    json_t* success = json_object_get(root, "success");
    json_t* token = json_object_get(root, "token");
    json_t* err = json_object_get(root, "error");
    
    if (json_is_true(success) && token && json_is_string(token)) {
        // Stocker le token
        free(g_auth.token);
        g_auth.token = strdup(json_string_value(token));
        
        free(g_auth.username);
        g_auth.username = strdup(username);
        
        g_auth.authenticated = true;
        g_auth.auth_method = AUTH_TOKEN;
        g_auth.token_expiry = time(NULL) + 604800;  // 7 jours
        
        LOG_SUCCESS("Authenticated as %s", username);
        json_decref(root);
        return 0;
    }
    
    if (err && json_is_string(err)) {
        LOG_ERROR("Login failed: %s", json_string_value(err));
    } else {
        LOG_ERROR("Login failed: unknown error");
    }
    
    json_decref(root);
    return 1;
}

int network_auth_verify(void) {
    if (!g_auth.token) {
        g_auth.authenticated = false;
        return 1;
    }
    
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/verify", 
             g_config.registry_url, GPM_API_VERSION);
    
    long status = 0;
    char* response = network_get(url, &status);
    
    if (status == 200 && response) {
        json_error_t error;
        json_t* root = json_loads(response, 0, &error);
        free(response);
        
        if (root) {
            json_t* valid = json_object_get(root, "valid");
            if (json_is_true(valid)) {
                json_t* user = json_object_get(root, "user");
                if (user) {
                    json_t* username_json = json_object_get(user, "username");
                    if (username_json && json_is_string(username_json)) {
                        free(g_auth.username);
                        g_auth.username = strdup(json_string_value(username_json));
                    }
                }
                g_auth.authenticated = true;
                LOG_DEBUG("Token verified for %s", g_auth.username);
                json_decref(root);
                return 0;
            }
            json_decref(root);
        }
    } else {
        free(response);
    }
    
    g_auth.authenticated = false;
    LOG_DEBUG("Token verification failed");
    return 1;
}

int network_auth_refresh(void) {
    if (!g_auth.refresh_token) {
        LOG_DEBUG("No refresh token available");
        return 1;
    }
    
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/refresh", 
             g_config.registry_url, GPM_API_VERSION);
    
    json_t* data = json_object();
    json_object_set_new(data, "refresh_token", json_string(g_auth.refresh_token));
    
    char* json_str = json_dumps(data, 0);
    json_decref(data);
    
    char* response = network_post(url, json_str, "application/json");
    free(json_str);
    
    if (!response) return 1;
    
    json_error_t error;
    json_t* root = json_loads(response, 0, &error);
    free(response);
    
    if (!root) return 1;
    
    json_t* token = json_object_get(root, "token");
    if (token && json_is_string(token)) {
        free(g_auth.token);
        g_auth.token = strdup(json_string_value(token));
        g_auth.token_expiry = time(NULL) + 604800;
        g_auth.authenticated = true;
        
        LOG_DEBUG("Token refreshed");
        json_decref(root);
        return 0;
    }
    
    json_decref(root);
    return 1;
}

/* ================================================================
 * SSL / PROXY
 * ================================================================ */

int network_setup_ssl(void) {
    if (!curl_initialized) network_init();
    
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, g_config.verify_ssl ? 1L : 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, g_config.verify_ssl ? 2L : 0L);
    
    LOG_DEBUG("SSL verification: %s", g_config.verify_ssl ? "enabled" : "disabled");
    return 0;
}

int network_proxy_setup(const char* proxy) {
    if (!curl_initialized) network_init();
    
    curl_easy_setopt(curl, CURLOPT_PROXY, proxy);
    curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
    
    LOG_DEBUG("Proxy set: %s", proxy);
    return 0;
}
