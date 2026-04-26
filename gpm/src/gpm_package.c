#include "gpm.h"
#include <signal.h>
#include <ctype.h>
#include <limits.h>  // Pour PATH_MAX

/* ================================================================
 * DÉCLARATIONS FORWARD
 * ================================================================ */

extern int gpm_install(const char* package, const char* version);
extern int gpm_uninstall(const char* package);
extern int gpm_verify(const char* package);

/* ================================================================
 * CRÉATION D'UN PACKAGE .tar.bool (version system tar)
 * ================================================================ */

int package_create(const char* source_dir, const char* output_path) {
    LOG_INFO("Creating package: %s", output_path);
    
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), 
             "cd '%s' && tar -czf '%s' . 2>/dev/null",
             source_dir, output_path);
    
    int exit_code;
    char* output;
    if (run_command(cmd, &output, &exit_code) != 0 || exit_code != 0) {
        LOG_ERROR("Failed to create archive: %s", output ? output : "unknown error");
        free(output);
        return 1;
    }
    free(output);
    
    if (!file_exists(output_path)) {
        LOG_ERROR("Archive not created");
        return 1;
    }
    
    LOG_SUCCESS("Package created: %s (%zu bytes)", output_path, file_size(output_path));
    return 0;
}

/* ================================================================
 * EXTRACTION D'UN PACKAGE
 * ================================================================ */

int package_extract(const char* package_path, const char* dest_dir) {
    LOG_INFO("Extracting: %s -> %s", package_path, dest_dir);
    
    if (!file_exists(package_path)) {
        LOG_ERROR("Package not found: %s", package_path);
        return 1;
    }
    
    dir_create(dest_dir);
    
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), 
             "mkdir -p '%s' && cd '%s' && tar -xzf '%s' 2>/dev/null",
             dest_dir, dest_dir, package_path);
    
    int exit_code;
    char* output;
    if (run_command(cmd, &output, &exit_code) != 0 || exit_code != 0) {
        LOG_ERROR("Failed to extract archive: %s", output ? output : "unknown error");
        free(output);
        return 1;
    }
    free(output);
    
    LOG_SUCCESS("Package extracted to %s", dest_dir);
    return 0;
}

/* ================================================================
 * VÉRIFICATION
 * ================================================================ */

int package_verify(const char* package_path, const char* expected_hash) {
    if (!file_exists(package_path)) {
        LOG_ERROR("File not found: %s", package_path);
        return 0;
    }
    
    char* hash = package_compute_hash(package_path);
    if (!hash) return 0;
    
    LOG_INFO("SHA256: %s", hash);
    
    if (expected_hash) {
        if (strcmp(hash, expected_hash) != 0) {
            LOG_ERROR("Hash mismatch!");
            LOG_ERROR("  Expected: %s", expected_hash);
            LOG_ERROR("  Got:      %s", hash);
            free(hash);
            return 0;
        }
        LOG_SUCCESS("Hash verified");
    }
    
    free(hash);
    return 1;
}

/* ================================================================
 * CALCUL DU HASH
 * ================================================================ */

char* package_compute_hash(const char* file_path) {
    if (!file_exists(file_path)) return NULL;
    
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "sha256sum '%s' 2>/dev/null | awk '{print $1}'", file_path);
    
    char* output;
    int exit_code;
    if (run_command(cmd, &output, &exit_code) != 0 || exit_code != 0 || !output) {
        return NULL;
    }
    
    char* trimmed = str_trim(output);
    char* result = strdup(trimmed);
    free(output);
    
    return result;
}

/* ================================================================
 * SIGNATURE
 * ================================================================ */

int package_sign(const char* package_path, const char* key_path) {
    if (!file_exists(package_path) || !file_exists(key_path)) return 1;
    
    char sig_path[1024];
    snprintf(sig_path, sizeof(sig_path), "%s.sig", package_path);
    
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), 
             "openssl dgst -sha256 -sign '%s' -out '%s' '%s' 2>/dev/null",
             key_path, sig_path, package_path);
    
    int exit_code;
    if (run_command(cmd, NULL, &exit_code) != 0 || exit_code != 0) {
        LOG_ERROR("Failed to sign package");
        return 1;
    }
    
    LOG_SUCCESS("Package signed: %s", sig_path);
    return 0;
}

int package_verify_signature(const char* package_path, const char* pubkey_path) {
    if (!file_exists(package_path) || !file_exists(pubkey_path)) return 1;
    
    char sig_path[1024];
    snprintf(sig_path, sizeof(sig_path), "%s.sig", package_path);
    
    if (!file_exists(sig_path)) {
        LOG_ERROR("Signature file not found: %s", sig_path);
        return 1;
    }
    
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), 
             "openssl dgst -sha256 -verify '%s' -signature '%s' '%s' 2>/dev/null",
             pubkey_path, sig_path, package_path);
    
    char* output;
    int exit_code;
    run_command(cmd, &output, &exit_code);
    
    if (exit_code == 0 && output && strstr(output, "Verified OK")) {
        free(output);
        return 0;
    }
    
    free(output);
    return 1;
}

/* ================================================================
 * LECTURE DES MÉTADONNÉES
 * ================================================================ */

PackageMeta* package_read_meta(const char* package_path) {
    if (!file_exists(package_path)) return NULL;
    
    char temp_dir[] = "/tmp/gpm-meta-XXXXXX";
    if (!mkdtemp(temp_dir)) return NULL;
    
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), 
             "cd '%s' && tar -xzf '%s' 'package.json' '*/package.json' 2>/dev/null",
             temp_dir, package_path);
    
    int exit_code;
    run_command(cmd, NULL, &exit_code);
    
    char meta_path[1024];
    snprintf(meta_path, sizeof(meta_path), "%s/package.json", temp_dir);
    
    if (!file_exists(meta_path)) {
        DIR* dir = opendir(temp_dir);
        if (!dir) {
            dir_remove(temp_dir);
            return NULL;
        }
        
        struct dirent* entry;
        bool found = false;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && 
                strcmp(entry->d_name, "..") != 0) {
                snprintf(meta_path, sizeof(meta_path), "%s/%s/package.json", 
                         temp_dir, entry->d_name);
                if (file_exists(meta_path)) {
                    found = true;
                    break;
                }
            }
        }
        closedir(dir);
        
        if (!found) {
            dir_remove(temp_dir);
            return NULL;
        }
    }
    
    char* json_str = file_read(meta_path);
    dir_remove(temp_dir);
    
    if (!json_str) return NULL;
    
    json_error_t error;
    json_t* root = json_loads(json_str, 0, &error);
    free(json_str);
    
    if (!root) return NULL;
    
    PackageMeta* meta = calloc(1, sizeof(PackageMeta));
    
    json_t* val;
    val = json_object_get(root, "name");
    if (val && json_is_string(val)) meta->name = strdup(json_string_value(val));
    
    val = json_object_get(root, "version");
    if (val && json_is_string(val)) meta->version = strdup(json_string_value(val));
    
    val = json_object_get(root, "release");
    if (val && json_is_string(val)) meta->release = strdup(json_string_value(val));
    else meta->release = strdup("r0");
    
    val = json_object_get(root, "author");
    if (val && json_is_string(val)) meta->author = strdup(json_string_value(val));
    
    val = json_object_get(root, "description");
    if (val && json_is_string(val)) meta->description = strdup(json_string_value(val));
    
    val = json_object_get(root, "license");
    if (val && json_is_string(val)) meta->license = strdup(json_string_value(val));
    
    val = json_object_get(root, "homepage");
    if (val && json_is_string(val)) meta->homepage = strdup(json_string_value(val));
    
    val = json_object_get(root, "repository");
    if (val && json_is_string(val)) meta->repository = strdup(json_string_value(val));
    
    val = json_object_get(root, "sha256");
    if (val && json_is_string(val)) meta->sha256 = strdup(json_string_value(val));
    
    val = json_object_get(root, "size");
    if (val) meta->size = (size_t)json_integer_value(val);
    
    val = json_object_get(root, "scope");
    if (val && json_is_string(val)) {
        if (strcmp(json_string_value(val), "private") == 0) 
            meta->scope = PKG_SCOPE_PRIVATE;
        else if (strcmp(json_string_value(val), "unlisted") == 0)
            meta->scope = PKG_SCOPE_UNLISTED;
        else
            meta->scope = PKG_SCOPE_PUBLIC;
    }
    
    val = json_object_get(root, "created_at");
    if (val && json_is_string(val)) {
        struct tm tm = {0};
        strptime(json_string_value(val), "%Y-%m-%dT%H:%M:%S", &tm);
        meta->created_at = mktime(&tm);
    }
    
    val = json_object_get(root, "downloads");
    if (val) meta->downloads = (int)json_integer_value(val);
    
    json_t* deps = json_object_get(root, "dependencies");
    if (deps && json_is_array(deps)) {
        meta->dep_count = (int)json_array_size(deps);
        if (meta->dep_count > 0) {
            meta->dependencies = calloc(meta->dep_count, sizeof(char*));
            for (size_t i = 0; i < json_array_size(deps); i++) {
                json_t* dep = json_array_get(deps, i);
                if (json_is_string(dep)) {
                    meta->dependencies[i] = strdup(json_string_value(dep));
                }
            }
        }
    }
    
    json_t* keywords = json_object_get(root, "keywords");
    if (keywords && json_is_array(keywords)) {
        meta->keyword_count = (int)json_array_size(keywords);
        if (meta->keyword_count > 0) {
            meta->keywords = calloc(meta->keyword_count, sizeof(char*));
            for (size_t i = 0; i < json_array_size(keywords); i++) {
                json_t* kw = json_array_get(keywords, i);
                if (json_is_string(kw)) {
                    meta->keywords[i] = strdup(json_string_value(kw));
                }
            }
        }
    }
    
    json_t* conflicts = json_object_get(root, "conflicts");
    if (conflicts && json_is_array(conflicts)) {
        meta->conflict_count = (int)json_array_size(conflicts);
        if (meta->conflict_count > 0) {
            meta->conflicts = calloc(meta->conflict_count, sizeof(char*));
            for (size_t i = 0; i < json_array_size(conflicts); i++) {
                json_t* conf = json_array_get(conflicts, i);
                if (json_is_string(conf)) {
                    meta->conflicts[i] = strdup(json_string_value(conf));
                }
            }
        }
    }
    
    json_decref(root);
    return meta;
}

/* ================================================================
 * LIBÉRATION MÉMOIRE
 * ================================================================ */

void package_meta_free(PackageMeta* meta) {
    if (!meta) return;
    free(meta->name);
    free(meta->version);
    free(meta->release);
    free(meta->author);
    free(meta->description);
    free(meta->license);
    free(meta->homepage);
    free(meta->repository);
    free(meta->sha256);
    free(meta->signature);
    
    for (int i = 0; i < meta->dep_count; i++) free(meta->dependencies[i]);
    free(meta->dependencies);
    
    for (int i = 0; i < meta->keyword_count; i++) free(meta->keywords[i]);
    free(meta->keywords);
    
    for (int i = 0; i < meta->conflict_count; i++) free(meta->conflicts[i]);
    free(meta->conflicts);
    
    free(meta);
}

/* ================================================================
 * INSTALLATION / DÉSINSTALLATION
 * ================================================================ */

int package_install_file(const char* package_path) {
    return package_extract(package_path, g_config.lib_dir);
}

int package_uninstall_files(PackageMeta* meta) {
    char pkg_dir[1024];
    snprintf(pkg_dir, sizeof(pkg_dir), "%s/%s", g_config.lib_dir, meta->name);
    return dir_remove(pkg_dir);
}

/* ================================================================
 * DÉPENDANCES
 * ================================================================ */

int package_resolve_deps(PackageMeta* meta) {
    for (int i = 0; i < meta->dep_count; i++) {
        if (!package_is_installed(meta->dependencies[i], NULL)) {
            LOG_INFO("Installing dependency: %s", meta->dependencies[i]);
            if (gpm_install(meta->dependencies[i], NULL) != 0) {
                LOG_WARN("Failed to install dependency: %s", meta->dependencies[i]);
            }
        }
    }
    return 0;
}

int package_check_conflicts(PackageMeta* meta) {
    for (int i = 0; i < meta->conflict_count; i++) {
        if (package_is_installed(meta->conflicts[i], NULL)) {
            LOG_ERROR("Conflicting package installed: %s", meta->conflicts[i]);
            return 1;
        }
    }
    return 0;
}

/* ================================================================
 * PACKAGES INSTALLÉS
 * ================================================================ */

PackageList* package_get_installed(void) {
    PackageList* list = calloc(1, sizeof(PackageList));
    list->capacity = 16;
    list->packages = calloc(list->capacity, sizeof(char*));
    list->count = 0;
    
    DIR* dir = opendir(g_config.lib_dir);
    if (!dir) return list;
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (entry->d_name[0] == '.') continue;
        
        char meta_path[1024];
        snprintf(meta_path, sizeof(meta_path), "%s/%s/package.json", 
                 g_config.lib_dir, entry->d_name);
        
        if (file_exists(meta_path)) {
            if (list->count >= list->capacity) {
                list->capacity *= 2;
                list->packages = realloc(list->packages, 
                                        list->capacity * sizeof(char*));
            }
            list->packages[list->count++] = strdup(entry->d_name);
        }
    }
    closedir(dir);
    
    return list;
}

void package_list_free(PackageList* list) {
    if (!list) return;
    for (int i = 0; i < list->count; i++) free(list->packages[i]);
    free(list->packages);
    free(list);
}

bool package_is_installed(const char* name, const char* version) {
    char meta_path[1024];
    snprintf(meta_path, sizeof(meta_path), "%s/%s/package.json", 
             g_config.lib_dir, name);
    
    if (!file_exists(meta_path)) return false;
    
    if (version) {
        PackageMeta* meta = package_read_meta(meta_path);
        if (!meta) return false;
        
        bool match = meta->version && strcmp(meta->version, version) == 0;
        package_meta_free(meta);
        return match;
    }
    
    return true;
}

char* package_find_in_cache(const char* name, const char* version, const char* arch) {
    DIR* dir = opendir(g_config.cache_dir);
    if (!dir) return NULL;
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, name) && str_endswith(entry->d_name, GPM_PACKAGE_EXT)) {
            if (version && !strstr(entry->d_name, version)) continue;
            if (arch && !strstr(entry->d_name, arch)) continue;
            
            char* full_path = malloc(PATH_MAX);
            snprintf(full_path, PATH_MAX, "%s/%s", g_config.cache_dir, entry->d_name);
            closedir(dir);
            return full_path;
        }
    }
    
    closedir(dir);
    return NULL;
}

/* ================================================================
 * UTILITAIRES
 * ================================================================ */

char* str_duplicate(const char* src) {
    if (!src) return NULL;
    char* dst = malloc(strlen(src) + 1);
    if (dst) strcpy(dst, src);
    return dst;
}

char* str_concat(const char* s1, const char* s2) {
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char* result = malloc(len1 + len2 + 1);
    if (!result) return NULL;
    if (s1) strcpy(result, s1);
    if (s2) strcpy(result + len1, s2);
    return result;
}

bool str_startswith(const char* str, const char* prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool str_endswith(const char* str, const char* suffix) {
    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);
    if (len_suffix > len_str) return false;
    return strcmp(str + len_str - len_suffix, suffix) == 0;
}

char* str_trim(char* str) {
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char* str_upper(char* str) {
    for (char* p = str; *p; p++) *p = (char)toupper((unsigned char)*p);
    return str;
}

char* str_lower(char* str) {
    for (char* p = str; *p; p++) *p = (char)tolower((unsigned char)*p);
    return str;
}

char* path_join(const char* path1, const char* path2) {
    size_t len1 = strlen(path1);
    bool has_slash = path1[len1 - 1] == '/';
    
    char* result = malloc(len1 + strlen(path2) + 2);
    strcpy(result, path1);
    if (!has_slash) strcat(result, "/");
    strcat(result, path2);
    return result;
}

char* path_dirname(const char* path) {
    char* copy = strdup(path);
    if (!copy) return NULL;
    char* last_slash = strrchr(copy, '/');
    if (last_slash) {
        *last_slash = '\0';
        return copy;
    }
    free(copy);
    return strdup(".");
}

char* path_basename(const char* path) {
    const char* last_slash = strrchr(path, '/');
    return strdup(last_slash ? last_slash + 1 : path);
}

char* path_extension(const char* path) {
    const char* dot = strrchr(path, '.');
    return strdup(dot ? dot : "");
}

bool file_exists(const char* path) {
    return access(path, F_OK) == 0;
}

bool dir_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

int dir_create(const char* path) {
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "mkdir -p '%s'", path);
    return system(cmd);
}

int dir_remove(const char* path) {
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "rm -rf '%s'", path);
    return system(cmd);
}

size_t file_size(const char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (size_t)st.st_size;
}

char* file_read(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* content = malloc((size_t)size + 1);
    if (!content) {
        fclose(f);
        return NULL;
    }
    size_t n = fread(content, 1, (size_t)size, f);
    content[n] = '\0';
    fclose(f);
    
    return content;
}

int file_write(const char* path, const char* content) {
    FILE* f = fopen(path, "w");
    if (!f) return 1;
    fprintf(f, "%s", content);
    fclose(f);
    return 0;
}

char* get_home_dir(void) {
    const char* home = getenv("HOME");
    if (home) return strdup(home);
    
    struct passwd* pw = getpwuid(getuid());
    return strdup(pw ? pw->pw_dir : "/root");
}

char* get_current_dir(void) {
    char* cwd = getcwd(NULL, 0);
    return cwd ? cwd : strdup(".");
}

char* get_temp_dir(void) {
    const char* tmp = getenv("TMPDIR");
    if (!tmp) tmp = getenv("TMP");
    if (!tmp) tmp = getenv("TEMP");
    return strdup(tmp ? tmp : "/tmp");
}

char* get_os_name(void) {
    return strdup("Linux");
}

char* get_os_version(void) {
    struct utsname buf;
    uname(&buf);
    return strdup(buf.release);
}

char* get_kernel_version(void) {
    struct utsname buf;
    uname(&buf);
    return strdup(buf.release);
}

char* get_hostname(void) {
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    return strdup(hostname);
}

char* get_username(void) {
    const char* user = getenv("USER");
    if (user) return strdup(user);
    
    struct passwd* pw = getpwuid(getuid());
    return strdup(pw ? pw->pw_name : "unknown");
}

ArchType get_cpu_arch(void) {
    struct utsname buf;
    uname(&buf);
    
    if (strcmp(buf.machine, "x86_64") == 0) return ARCH_X86_64;
    if (strcmp(buf.machine, "i686") == 0) return ARCH_I686;
    if (strcmp(buf.machine, "aarch64") == 0) return ARCH_AARCH64;
    if (strcmp(buf.machine, "armv7l") == 0) return ARCH_ARMV7L;
    if (strcmp(buf.machine, "riscv64") == 0) return ARCH_RISCV64;
    
    return ARCH_X86_64; // fallback
}

int get_cpu_count(void) {
    return (int)sysconf(_SC_NPROCESSORS_ONLN);
}

long get_total_ram(void) {
    return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
}

long get_free_ram(void) {
    return sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE);
}

time_t get_boot_time(void) {
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        return time(NULL) - (time_t)info.uptime;
    }
    return 0;
}

char* generate_uuid(void) {
    unsigned char buf[16];
    FILE* f = fopen("/dev/urandom", "rb");
    if (!f) return NULL;
    if (fread(buf, 1, 16, f) != 16) {
        fclose(f);
        return NULL;
    }
    fclose(f);
    
    buf[6] = (buf[6] & 0x0f) | 0x40;
    buf[8] = (buf[8] & 0x3f) | 0x80;
    
    char* uuid = malloc(37);
    snprintf(uuid, 37, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             buf[0], buf[1], buf[2], buf[3],
             buf[4], buf[5],
             buf[6], buf[7],
             buf[8], buf[9],
             buf[10], buf[11], buf[12], buf[13], buf[14], buf[15]);
    return uuid;
}

char* base64_encode(const unsigned char* data, size_t len) {
    BIO* bio = BIO_new(BIO_s_mem());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data, (int)len);
    BIO_flush(bio);
    
    BUF_MEM* buf;
    BIO_get_mem_ptr(bio, &buf);
    
    char* result = malloc(buf->length + 1);
    memcpy(result, buf->data, buf->length);
    result[buf->length] = '\0';
    
    BIO_free_all(bio);
    return result;
}

unsigned char* base64_decode(const char* data, size_t* out_len) {
    BIO* bio = BIO_new_mem_buf(data, -1);
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    
    unsigned char* buf = malloc(strlen(data));
    *out_len = BIO_read(bio, buf, (int)strlen(data));
    
    BIO_free_all(bio);
    return buf;
}

char* url_encode(const char* str) {
    CURL* curl = curl_easy_init();
    if (!curl) return strdup(str);
    
    char* encoded = curl_easy_escape(curl, str, 0);
    curl_easy_cleanup(curl);
    
    return encoded ? encoded : strdup(str);
}

char* url_decode(const char* str) {
    CURL* curl = curl_easy_init();
    if (!curl) return strdup(str);
    
    int len;
    char* decoded = curl_easy_unescape(curl, str, 0, &len);
    curl_easy_cleanup(curl);
    
    return decoded ? decoded : strdup(str);
}

int run_command(const char* cmd, char** output, int* exit_code) {
    char buffer[256];
    char* result = NULL;
    size_t result_size = 0;
    
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return 1;
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t len = strlen(buffer);
        char* tmp = realloc(result, result_size + len + 1);
        if (!tmp) {
            free(result);
            pclose(pipe);
            return 1;
        }
        result = tmp;
        memcpy(result + result_size, buffer, len + 1);
        result_size += len;
    }
    
    int status = pclose(pipe);
    if (exit_code) *exit_code = WEXITSTATUS(status);
    if (output) *output = result;
    else free(result);
    
    return 0;
}
