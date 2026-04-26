#include "gpm.h"

/* ================================================================
 * INITIALISATION RÉSEAU
 * ================================================================ */

static CURL* curl = NULL;

int network_init(void) {
    curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("Failed to initialize CURL");
        return 1;
    }
    
    // Configuration par défaut
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, g_config.timeout);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, GPM_USER_AGENT);
    
    if (!g_config.verify_ssl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    
    // Configuration du proxy
    if (g_config.proxy) {
        curl_easy_setopt(curl, CURLOPT_PROXY, g_config.proxy);
    }
    
    return 0;
}

void network_cleanup(void) {
    if (curl) {
        curl_easy_cleanup(curl);
        curl = NULL;
    }
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
    
    return ua;
}

// Dans network_get_system_info(), changer %ld en %lld pour boot_time
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
    char* kernel = sys_info.release;
    
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
             kernel,
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
 * CALLBACK POUR CURL
 * ================================================================ */

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;
    
    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) return 0;
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

static size_t write_file_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

static int progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow,
                             curl_off_t ultotal, curl_off_t ulnow) {
    if (dltotal > 0) {
        int percent = (int)((dlnow * 100) / dltotal);
        printf("\r  " COLOR_CYAN "Downloading: %d%%" COLOR_RESET, percent);
        fflush(stdout);
        if (dlnow == dltotal) printf("\n");
    }
    return 0;
}

/* ================================================================
 * REQUÊTES HTTP
 * ================================================================ */

char* network_get(const char* url, long* status_code) {
    if (!curl) network_init();
    
    struct MemoryStruct chunk = {0};
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    
    // Ajouter les headers d'authentification
    struct curl_slist* headers = NULL;
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "User-Agent: GPM/1.0");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    CURLcode res = curl_easy_perform(curl);
    
    if (status_code) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, status_code);
    }
    
    curl_slist_free_all(headers);
    
    if (res != CURLE_OK) {
        LOG_ERROR("GET %s failed: %s", url, curl_easy_strerror(res));
        free(chunk.memory);
        return NULL;
    }
    
    return chunk.memory;
}

char* network_post(const char* url, const char* data, const char* content_type) {
    if (!curl) network_init();
    
    struct MemoryStruct chunk = {0};
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    
    struct curl_slist* headers = NULL;
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    if (content_type) {
        char ct[512];
        snprintf(ct, sizeof(ct), "Content-Type: %s", content_type);
        headers = curl_slist_append(headers, ct);
    }
    headers = curl_slist_append(headers, "Accept: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    
    if (res != CURLE_OK) {
        LOG_ERROR("POST %s failed: %s", url, curl_easy_strerror(res));
        free(chunk.memory);
        return NULL;
    }
    
    return chunk.memory;
}

int network_download(const char* url, const char* output_path) {
    if (!curl) network_init();
    
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
    
    struct curl_slist* headers = NULL;
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    // Retry logic
    CURLcode res;
    for (int attempt = 0; attempt < g_config.retry_count; attempt++) {
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) break;
        
        LOG_WARN("Download attempt %d failed: %s", attempt + 1, curl_easy_strerror(res));
        if (attempt < g_config.retry_count - 1) {
            sleep(GPM_RETRY_DELAY);
        }
    }
    
    curl_slist_free_all(headers);
    fclose(fp);
    
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    if (res != CURLE_OK || http_code != 200) {
        LOG_ERROR("Download failed: HTTP %ld, %s", http_code, 
                  res != CURLE_OK ? curl_easy_strerror(res) : "OK");
        unlink(output_path);
        return 1;
    }
    
    return 0;
}

int network_upload(const char* url, const char* file_path) {
    if (!curl) network_init();
    
    FILE* fp = fopen(file_path, "rb");
    if (!fp) {
        LOG_ERROR("Cannot open file: %s", file_path);
        return 1;
    }
    
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    curl_mime* mime = curl_mime_init(curl);
    curl_mimepart* part = curl_mime_addpart(mime);
    curl_mime_name(part, "file");
    curl_mime_filedata(part, file_path);
    curl_mime_filename(part, path_basename((char*)file_path));
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_READDATA, fp);
    
    struct curl_slist* headers = NULL;
    if (g_auth.token) {
        char auth_header[1024];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", g_auth.token);
        headers = curl_slist_append(headers, auth_header);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    CURLcode res = curl_easy_perform(curl);
    
    curl_mime_free(mime);
    curl_slist_free_all(headers);
    fclose(fp);
    
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    if (res != CURLE_OK || (http_code != 200 && http_code != 201)) {
        LOG_ERROR("Upload failed: HTTP %ld", http_code);
        return 1;
    }
    
    return 0;
}

/* ================================================================
 * VÉRIFICATION DE CONNECTIVITÉ
 * ================================================================ */

bool network_check_connectivity(void) {
    char* response = network_get("https://gsql-badge.onrender.com/status", NULL);
    if (response) {
        free(response);
        return true;
    }
    
    // Essayer les miroirs
    response = network_get("https://gpm.gopu-inc.com/status", NULL);
    if (response) {
        free(response);
        return true;
    }
    
    return false;
}

/* ================================================================
 * AUTHENTIFICATION
 * ================================================================ */

int network_auth_login(const char* username, const char* password) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/login", 
             g_config.registry_url, GPM_API_VERSION);
    
    json_t* data = json_object();
    json_object_set_new(data, "username", json_string(username));
    json_object_set_new(data, "password", json_string(password));
    
    char* json_str = json_dumps(data, 0);
    json_decref(data);
    
    char* response = network_post(url, json_str, "application/json");
    free(json_str);
    
    if (!response) return 1;
    
    json_error_t error;
    json_t* root = json_loads(response, 0, &error);
    free(response);
    
    if (!root) return 1;
    
    json_t* success = json_object_get(root, "success");
    json_t* token = json_object_get(root, "token");
    
    if (json_is_true(success) && token && json_is_string(token)) {
        g_auth.token = strdup(json_string_value(token));
        g_auth.username = strdup(username);
        g_auth.authenticated = true;
        g_auth.auth_method = AUTH_TOKEN;
        g_auth.token_expiry = time(NULL) + 604800; // 7 jours
        
        json_decref(root);
        return 0;
    }
    
    json_t* err = json_object_get(root, "error");
    if (err) {
        LOG_ERROR("Login failed: %s", json_string_value(err));
    }
    
    json_decref(root);
    return 1;
}

int network_auth_verify(void) {
    if (!g_auth.token) return 1;
    
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/verify", 
             g_config.registry_url, GPM_API_VERSION);
    
    long status;
    char* response = network_get(url, &status);
    
    if (status == 200 && response) {
        json_error_t error;
        json_t* root = json_loads(response, 0, &error);
        if (root) {
            json_t* valid = json_object_get(root, "valid");
            if (json_is_true(valid)) {
                json_t* user = json_object_get(root, "user");
                if (user) {
                    json_t* username = json_object_get(user, "username");
                    if (username) {
                        free(g_auth.username);
                        g_auth.username = strdup(json_string_value(username));
                    }
                }
                g_auth.authenticated = true;
                json_decref(root);
                free(response);
                return 0;
            }
            json_decref(root);
        }
        free(response);
    }
    
    g_auth.authenticated = false;
    return 1;
}

int network_auth_refresh(void) {
    if (!g_auth.refresh_token) return 1;
    
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/auth/refresh", 
             g_config.registry_url, GPM_API_VERSION);
    
    json_t* data = json_object();
    json_object_set_new(data, "refresh_token", json_string(g_auth.refresh_token));
    
    char* json_str = json_dumps(data, 0);
    char* response = network_post(url, json_str, "application/json");
    
    json_decref(data);
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
    if (!curl) network_init();
    
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, g_config.verify_ssl ? 1L : 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, g_config.verify_ssl ? 2L : 0L);
    
    return 0;
}

int network_proxy_setup(const char* proxy) {
    if (!curl) network_init();
    
    curl_easy_setopt(curl, CURLOPT_PROXY, proxy);
    curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
    
    return 0;
}
