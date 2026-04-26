#include "gpm.h"

/* ================================================================
 * CRÉATION D'UN PACKAGE .tar.bool
 * ================================================================ */

int package_create(const char* source_dir, const char* output_path) {
    LOG_INFO("Creating package: %s", output_path);
    
    struct archive* a = archive_write_new();
    if (!a) {
        LOG_ERROR("Failed to create archive");
        return 1;
    }
    
    // Configuration du format
    archive_write_set_format_pax_restricted(a);
    archive_write_add_filter_gzip(a);
    
    // Ouvrir le fichier de sortie
    if (archive_write_open_filename(a, output_path) != ARCHIVE_OK) {
        LOG_ERROR("Cannot open output file: %s", archive_error_string(a));
        archive_write_free(a);
        return 1;
    }
    
    // Parcourir le répertoire source
    DIR* dir = opendir(source_dir);
    if (!dir) {
        LOG_ERROR("Cannot open source directory: %s", source_dir);
        archive_write_close(a);
        archive_write_free(a);
        return 1;
    }
    
    // Ajouter les fichiers
    char base_path[PATH_MAX];
    realpath(source_dir, base_path);
    size_t base_len = strlen(base_path);
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", source_dir, entry->d_name);
        
        struct stat st;
        if (stat(full_path, &st) != 0) continue;
        
        struct archive_entry* ae = archive_entry_new();
        
        // Chemin relatif dans l'archive
        char* relative_path = full_path + base_len + 1;
        archive_entry_set_pathname(ae, relative_path);
        archive_entry_set_size(ae, st.st_size);
        archive_entry_set_filetype(ae, AE_IFREG);
        archive_entry_set_perm(ae, st.st_mode);
        archive_entry_set_mtime(ae, st.st_mtime, 0);
        
        archive_write_header(a, ae);
        
        // Écrire le contenu
        FILE* f = fopen(full_path, "rb");
        if (f) {
            char buf[8192];
            size_t n;
            while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
                archive_write_data(a, buf, n);
            }
            fclose(f);
        }
        
        archive_entry_free(ae);
    }
    closedir(dir);
    
    // Finaliser
    archive_write_close(a);
    archive_write_free(a);
    
    LOG_SUCCESS("Package created: %s", output_path);
    return 0;
}

/* ================================================================
 * EXTRACTION D'UN PACKAGE
 * ================================================================ */

int package_extract(const char* package_path, const char* dest_dir) {
    LOG_INFO("Extracting: %s -> %s", package_path, dest_dir);
    
    struct archive* a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    
    if (archive_read_open_filename(a, package_path, 10240) != ARCHIVE_OK) {
        LOG_ERROR("Cannot open package: %s", archive_error_string(a));
        archive_read_free(a);
        return 1;
    }
    
    // Créer le répertoire de destination
    dir_create(dest_dir);
    
    struct archive_entry* entry;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* pathname = archive_entry_pathname(entry);
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_dir, pathname);
        
        // Créer les répertoires parents
        char* parent = path_dirname(full_path);
        dir_create(parent);
        free(parent);
        
        // Extraire le fichier
        if (archive_entry_filetype(entry) == AE_IFREG) {
            FILE* f = fopen(full_path, "wb");
            if (f) {
                const void* buff;
                size_t size;
                la_int64_t offset;
                
                while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                    fwrite(buff, 1, size, f);
                }
                fclose(f);
            }
        }
        
        // Restaurer les permissions
        chmod(full_path, archive_entry_perm(entry));
    }
    
    archive_read_close(a);
    archive_read_free(a);
    
    LOG_SUCCESS("Package extracted");
    return 0;
}

/* ================================================================
 * VÉRIFICATION DE L'INTÉGRITÉ
 * ================================================================ */

int package_verify(const char* package_path, const char* expected_hash) {
    char* hash = package_compute_hash(package_path);
    
    if (expected_hash && strcmp(hash, expected_hash) != 0) {
        LOG_ERROR("Hash mismatch!");
        LOG_ERROR("  Expected: %s", expected_hash);
        LOG_ERROR("  Got:      %s", hash);
        free(hash);
        return 0;
    }
    
    free(hash);
    return 1;
}

/* ================================================================
 * CALCUL DU HASH SHA256
 * ================================================================ */

char* package_compute_hash(const char* file_path) {
    FILE* f = fopen(file_path, "rb");
    if (!f) return NULL;
    
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    
    unsigned char buf[GPM_BUFFER_SIZE];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        SHA256_Update(&ctx, buf, n);
    }
    fclose(f);
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &ctx);
    
    char* hex = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex + i * 2, "%02x", hash[i]);
    }
    hex[SHA256_DIGEST_LENGTH * 2] = '\0';
    
    return hex;
}

/* ================================================================
 * SIGNATURE DU PACKAGE
 * ================================================================ */

int package_sign(const char* package_path, const char* key_path) {
    // Lire la clé privée
    FILE* key_file = fopen(key_path, "r");
    if (!key_file) {
        LOG_ERROR("Cannot open private key: %s", key_path);
        return 1;
    }
    
    EVP_PKEY* pkey = PEM_read_PrivateKey(key_file, NULL, NULL, NULL);
    fclose(key_file);
    
    if (!pkey) {
        LOG_ERROR("Failed to read private key");
        return 1;
    }
    
    // Calculer le hash du fichier
    char* hash_str = package_compute_hash(package_path);
    if (!hash_str) {
        EVP_PKEY_free(pkey);
        return 1;
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sscanf(hash_str + i * 2, "%02hhx", &hash[i]);
    }
    
    // Signer
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    EVP_SignInit(md_ctx, EVP_sha256());
    EVP_SignUpdate(md_ctx, hash, SHA256_DIGEST_LENGTH);
    
    unsigned char* sig = malloc(EVP_PKEY_size(pkey));
    unsigned int sig_len;
    EVP_SignFinal(md_ctx, sig, &sig_len, pkey);
    
    // Écrire la signature
    char sig_path[1024];
    snprintf(sig_path, sizeof(sig_path), "%s.sig", package_path);
    
    char* sig_b64 = base64_encode(sig, sig_len);
    file_write(sig_path, sig_b64);
    
    free(hash_str);
    free(sig);
    free(sig_b64);
    EVP_MD_CTX_free(md_ctx);
    EVP_PKEY_free(pkey);
    
    LOG_SUCCESS("Package signed: %s", sig_path);
    return 0;
}

int package_verify_signature(const char* package_path, const char* pubkey_path) {
    // Lire la clé publique
    FILE* key_file = fopen(pubkey_path, "r");
    if (!key_file) return 1;
    
    EVP_PKEY* pkey = PEM_read_PUBKEY(key_file, NULL, NULL, NULL);
    fclose(key_file);
    
    if (!pkey) return 1;
    
    // Lire la signature
    char sig_path[1024];
    snprintf(sig_path, sizeof(sig_path), "%s.sig", package_path);
    
    char* sig_b64 = file_read(sig_path);
    if (!sig_b64) {
        EVP_PKEY_free(pkey);
        return 1;
    }
    
    size_t sig_len;
    unsigned char* sig = base64_decode(sig_b64, &sig_len);
    free(sig_b64);
    
    if (!sig) {
        EVP_PKEY_free(pkey);
        return 1;
    }
    
    // Calculer le hash du fichier
    char* hash_str = package_compute_hash(package_path);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sscanf(hash_str + i * 2, "%02hhx", &hash[i]);
    }
    free(hash_str);
    
    // Vérifier
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    EVP_VerifyInit(md_ctx, EVP_sha256());
    EVP_VerifyUpdate(md_ctx, hash, SHA256_DIGEST_LENGTH);
    
    int result = EVP_VerifyFinal(md_ctx, sig, sig_len, pkey);
    
    free(sig);
    EVP_MD_CTX_free(md_ctx);
    EVP_PKEY_free(pkey);
    
    return result == 1 ? 0 : 1;
}

/* ================================================================
 * GESTION DES MÉTADONNÉES
 * ================================================================ */

PackageMeta* package_read_meta(const char* package_path) {
    // Extraire temporairement le package.json
    char temp_dir[1024];
    snprintf(temp_dir, sizeof(temp_dir), "%s/gpm-meta-XXXXXX", "/tmp");
    mkdtemp(temp_dir);
    
    if (package_extract(package_path, temp_dir) != 0) {
        dir_remove(temp_dir);
        return NULL;
    }
    
    char meta_path[1024];
    snprintf(meta_path, sizeof(meta_path), "%s/package.json", temp_dir);
    
    if (!file_exists(meta_path)) {
        // Chercher dans un sous-dossier
        DIR* dir = opendir(temp_dir);
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
    if (val) meta->name = strdup(json_string_value(val));
    
    val = json_object_get(root, "version");
    if (val) meta->version = strdup(json_string_value(val));
    
    val = json_object_get(root, "author");
    if (val) meta->author = strdup(json_string_value(val));
    
    val = json_object_get(root, "description");
    if (val) meta->description = strdup(json_string_value(val));
    
    val = json_object_get(root, "license");
    if (val) meta->license = strdup(json_string_value(val));
    
    val = json_object_get(root, "sha256");
    if (val) meta->sha256 = strdup(json_string_value(val));
    
    val = json_object_get(root, "size");
    if (val) meta->size = json_integer_value(val);
    
    // Dependencies
    json_t* deps = json_object_get(root, "dependencies");
    if (deps && json_is_array(deps)) {
        meta->dep_count = json_array_size(deps);
        meta->dependencies = calloc(meta->dep_count, sizeof(char*));
        for (int i = 0; i < meta->dep_count; i++) {
            meta->dependencies[i] = strdup(json_string_value(json_array_get(deps, i)));
        }
    }
    
    json_decref(root);
    return meta;
}

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
 * INSTALLATION / DÉSINSTALLATION DES FICHIERS
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
 * RÉSOLUTION DES DÉPENDANCES
 * ================================================================ */

int package_resolve_deps(PackageMeta* meta) {
    for (int i = 0; i < meta->dep_count; i++) {
        if (!package_is_installed(meta->dependencies[i], NULL)) {
            LOG_INFO("Installing dependency: %s", meta->dependencies[i]);
            if (gpm_install(meta->dependencies[i], NULL) != 0) {
                LOG_ERROR("Failed to install dependency: %s", meta->dependencies[i]);
                return 1;
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
 * GESTION DES PACKAGES INSTALLÉS
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
        
        bool match = strcmp(meta->version, version) == 0;
        package_meta_free(meta);
        return match;
    }
    
    return true;
}

char* package_find_in_cache(const char* name, const char* version, const char* arch) {
    char cache_name[256];
    snprintf(cache_name, sizeof(cache_name), "%s-%s-%s" GPM_PACKAGE_EXT, 
             name, version ? version : "*", arch ? arch : "*");
    
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
    strcpy(dst, src);
    return dst;
}

char* str_concat(const char* s1, const char* s2) {
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char* result = malloc(len1 + len2 + 1);
    if (s1) strcpy(result, s1);
    if (s2) strcpy(result + len1, s2);
    return result;
}

char* str_replace(const char* str, const char* old, const char* new) {
    char* result;
    int i, cnt = 0;
    size_t newlen = strlen(new);
    size_t oldlen = strlen(old);
    
    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], old) == &str[i]) {
            cnt++;
            i += oldlen - 1;
        }
    }
    
    result = malloc(i + cnt * (newlen - oldlen) + 1);
    i = 0;
    while (*str) {
        if (strstr(str, old) == str) {
            strcpy(&result[i], new);
            i += newlen;
            str += oldlen;
        } else {
            result[i++] = *str++;
        }
    }
    result[i] = '\0';
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
    for (char* p = str; *p; p++) *p = toupper(*p);
    return str;
}

char* str_lower(char* str) {
    for (char* p = str; *p; p++) *p = tolower(*p);
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
    char* last_slash = strrchr(copy, '/');
    if (last_slash) {
        *last_slash = '\0';
        return copy;
    }
    free(copy);
    return strdup(".");
}

char* path_basename(const char* path) {
    char* last_slash = strrchr(path, '/');
    return last_slash ? strdup(last_slash + 1) : strdup(path);
}

char* path_extension(const char* path) {
    char* dot = strrchr(path, '.');
    return dot ? strdup(dot) : strdup("");
}

bool file_exists(const char* path) {
    return access(path, F_OK) == 0;
}

bool dir_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

int dir_create(const char* path) {
    char tmp[PATH_MAX];
    snprintf(tmp, sizeof(tmp), "mkdir -p %s", path);
    return system(tmp);
}

int dir_remove(const char* path) {
    char tmp[PATH_MAX];
    snprintf(tmp, sizeof(tmp), "rm -rf %s", path);
    return system(tmp);
}

size_t file_size(const char* path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return st.st_size;
}

char* file_read(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* content = malloc(size + 1);
    fread(content, 1, size, f);
    content[size] = '\0';
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
    char* home = getenv("HOME");
    if (home) return strdup(home);
    
    struct passwd* pw = getpwuid(getuid());
    return pw ? strdup(pw->pw_dir) : strdup("/root");
}

char* get_current_dir(void) {
    char* cwd = getcwd(NULL, 0);
    return cwd ? cwd : strdup(".");
}

char* get_temp_dir(void) {
    char* tmp = getenv("TMPDIR");
    if (!tmp) tmp = getenv("TMP");
    if (!tmp) tmp = getenv("TEMP");
    return tmp ? strdup(tmp) : strdup("/tmp");
}

char* get_os_name(void) {
    #ifdef __linux__
    return strdup("Linux");
    #elif __APPLE__
    return strdup("macOS");
    #else
    struct utsname buf;
    uname(&buf);
    return strdup(buf.sysname);
    #endif
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
    char* user = getenv("USER");
    if (user) return strdup(user);
    
    struct passwd* pw = getpwuid(getuid());
    return pw ? strdup(pw->pw_name) : strdup("unknown");
}

ArchType get_cpu_arch(void) {
    struct utsname buf;
    uname(&buf);
    
    if (strcmp(buf.machine, "x86_64") == 0) return ARCH_X86_64;
    if (strcmp(buf.machine, "i686") == 0) return ARCH_I686;
    if (strcmp(buf.machine, "aarch64") == 0) return ARCH_AARCH64;
    if (strcmp(buf.machine, "armv7l") == 0) return ARCH_ARMV7L;
    if (strcmp(buf.machine, "riscv64") == 0) return ARCH_RISCV64;
    
    return ARCH_UNKNOWN;
}

int get_cpu_count(void) {
    return sysconf(_SC_NPROCESSORS_ONLN);
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
        return time(NULL) - info.uptime;
    }
    return 0;
}

char* generate_uuid(void) {
    unsigned char buf[16];
    FILE* f = fopen("/dev/urandom", "rb");
    if (!f) return NULL;
    fread(buf, 1, 16, f);
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
    BIO_write(bio, data, len);
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
    *out_len = BIO_read(bio, buf, strlen(data));
    
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
        result = realloc(result, result_size + len + 1);
        memcpy(result + result_size, buffer, len + 1);
        result_size += len;
    }
    
    int status = pclose(pipe);
    if (exit_code) *exit_code = WEXITSTATUS(status);
    if (output) *output = result;
    else free(result);
    
    return 0;
}

int run_command_async(const char* cmd) {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        exit(1);
    }
    return pid;
}

int wait_for_process(pid_t pid, int* exit_code) {
    int status;
    waitpid(pid, &status, 0);
    if (exit_code) *exit_code = WEXITSTATUS(status);
    return 0;
}

void set_process_name(const char* name) {
    #ifdef __linux__
    prctl(PR_SET_NAME, name, 0, 0, 0);
    #endif
}

int daemonize(void) {
    pid_t pid = fork();
    if (pid < 0) return 1;
    if (pid > 0) exit(0);
    
    if (setsid() < 0) return 1;
    
    signal(SIGHUP, SIG_IGN);
    
    pid = fork();
    if (pid < 0) return 1;
    if (pid > 0) exit(0);
    
    chdir("/");
    umask(0);
    
    for (int i = 0; i < 3; i++) close(i);
    
    int devnull = open("/dev/null", O_RDWR);
    dup2(devnull, STDIN_FILENO);
    dup2(devnull, STDOUT_FILENO);
    dup2(devnull, STDERR_FILENO);
    close(devnull);
    
    return 0;
}
