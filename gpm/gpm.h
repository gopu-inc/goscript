#ifndef GPM_H
#define GPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <curl/curl.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <jansson.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>

// ============================================================================
// VERSION ET IDENTITÉ
// ============================================================================
#define GPM_VERSION           "5.2.0"
#define GPM_CODENAME          "NovaCore"
#define GPM_API_VERSION       "v5.2"
#define GPM_USER_AGENT_BASE   "GPM-Goscript/5.2"

// ============================================================================
// CHEMINS STANDARD
// ============================================================================
#define GPM_ROOT              "/usr/local/lib/goscript"
#define GPM_LIB_DIR           GPM_ROOT "/lib"
#define GPM_BIN_DIR           GPM_ROOT "/bin"
#define GPM_CACHE_DIR         GPM_ROOT "/cache"
#define GPM_CONFIG_DIR        GPM_ROOT "/config"
#define GPM_MODULES_DIR       GPM_ROOT "/modules"
#define GPM_PACKAGES_DIR      GPM_ROOT "/packages"
#define GPM_REGISTRY_FILE     GPM_ROOT "/registry.json"
#define GPM_LOCK_FILE         GPM_ROOT "/gpm.lock"
#define GPM_LOG_FILE          GPM_ROOT "/gpm.log"
#define GPM_TEMP_DIR          GPM_ROOT "/tmp"
#define GPM_CREDENTIALS_FILE  GPM_ROOT "/credentials.gpg"
#define GPM_CONFIG_FILE       GPM_ROOT "/gpm.conf"
#define GPM_INDEX_CACHE       GPM_CACHE_DIR "/index.json"

// ============================================================================
// API ENDPOINTS
// ============================================================================
#define API_BASE_URL          "https://gsql-badge.onrender.com"
#define API_LOGIN             API_BASE_URL "/v5.2/auth/login"
#define API_REGISTER          API_BASE_URL "/v5.2/auth/register"
#define API_SEARCH            API_BASE_URL "/v5.2/package/search"
#define API_PACKAGE_INFO      API_BASE_URL "/v5.2/package"
#define API_PUBLISH           API_BASE_URL "/v5.2/package/upload"
#define API_DOWNLOAD          API_BASE_URL "/package/download"

// ============================================================================
// CONSTANTES
// ============================================================================
#define MAX_PATH              4096
#define MAX_CMD               8192
#define MAX_USERNAME          256
#define MAX_PASSWORD          512
#define MAX_TOKEN             2048
#define MAX_PACKAGE_NAME      256
#define MAX_VERSION           64
#define MAX_URL               4096
#define MAX_RESPONSE          (16 * 1024 * 1024)  // 16MB
#define MAX_HEADERS           1024
#define TIMEOUT_CONNECT       30L
#define TIMEOUT_TRANSFER      300L
#define MAX_RETRIES           5
#define RETRY_DELAY           2
#define MAX_CONCURRENT_DL     8
#define CACHE_TTL             3600
#define INDEX_REFRESH_INTERVAL 1800

// ============================================================================
// STRUCTURES DE DONNÉES
// ============================================================================

typedef struct {
    char name[MAX_PACKAGE_NAME];
    char version[MAX_VERSION];
    char release[16];
    char arch[32];
    char scope[16];
    char author[MAX_USERNAME];
    char sha256[65];
    char description[1024];
    size_t size;
    int downloads;
    char created_at[32];
    char updated_at[32];
    char* readme;
    char* dependencies;
    char* checksums;
} PackageInfo;

typedef struct {
    char system[64];
    char release[64];
    char machine[64];
    char version[64];
    char hostname[256];
    char kernel[128];
    char processor[64];
    char model[256];
    char board[256];
    long total_ram;
    long free_ram;
    int cpu_cores;
    char cpu_flags[512];
    char libc_version[64];
    char gcc_version[64];
    char goscript_version[64];
    char shell[256];
    char user[256];
    char home[512];
    char lang[64];
    char timezone[128];
    int is_docker;
    int is_wsl;
    int is_vm;
    char ip_address[64];
    char mac_address[24];
} SystemInfo;

typedef struct {
    char token[MAX_TOKEN];
    char username[MAX_USERNAME];
    char role[32];
    time_t expires_at;
    char refresh_token[MAX_TOKEN];
} AuthCredentials;

typedef struct {
    int verbose;
    int quiet;
    int force;
    int dry_run;
    int no_cache;
    int offline;
    int debug;
    char proxy[MAX_URL];
    char registry_url[MAX_URL];
    int parallel_downloads;
    int retry_count;
    int timeout;
    char arch_override[32];
    char target_dir[MAX_PATH];
    int install_deps;
    int verify_signatures;
    int use_sandbox;
} GPMConfig;

typedef struct {
    char url[MAX_URL];
    char dest[MAX_PATH];
    char sha256[65];
    size_t size;
    int retries;
    int status;
} DownloadTask;

typedef struct {
    PackageInfo** packages;
    int count;
    int capacity;
    time_t last_updated;
    char index_file[MAX_PATH];
} PackageIndex;

typedef struct {
    char** paths;
    int count;
    int capacity;
} PathList;

// ============================================================================
// STRUCTURE DE MÉMOIRE POUR LES RÉPONSES CURL
// ============================================================================
typedef struct {
    char* data;
    size_t size;
    size_t capacity;
} MemoryBuffer;

// ============================================================================
// FONCTIONS GLOBALES
// ============================================================================

// === KERNEL (kernel.c) ===
int gpm_init(GPMConfig* config);
int gpm_shutdown(void);
int gpm_run_command(int argc, char** argv);
void gpm_signal_handler(int sig);
int gpm_acquire_lock(void);
void gpm_release_lock(void);

// === SYSTEM INFO (stdlib.c) ===
SystemInfo* get_system_info(void);
char* generate_user_agent(void);
char* generate_request_headers(AuthCredentials* auth);
void free_system_info(SystemInfo* info);
void print_system_info(SystemInfo* info);

// === UTILITIES (utils.c) ===
char* str_dup(const char* src);
char* str_concat(const char* s1, const char* s2);
char* str_path_join(const char* base, const char* path);
int str_starts_with(const char* str, const char* prefix);
int str_ends_with(const char* str, const char* suffix);
char* str_replace(const char* str, const char* old, const char* new);
char** str_split(const char* str, char delim, int* count);
char* str_trim(char* str);
int mkdir_p(const char* path);
int file_exists(const char* path);
int dir_exists(const char* path);
long file_size(const char* path);
char* file_read(const char* path);
int file_write(const char* path, const char* data, size_t len);
int file_append(const char* path, const char* data);
int file_delete(const char* path);
int file_copy(const char* src, const char* dst);
char* get_home_dir(void);
char* get_current_dir(void);
char* get_temp_dir(void);
void print_colored(const char* color, const char* fmt, ...);
void print_success(const char* fmt, ...);
void print_error(const char* fmt, ...);
void print_warning(const char* fmt, ...);
void print_info(const char* fmt, ...);
void print_debug(const char* fmt, ...);
void print_banner(const char* title);
void print_progress_bar(int percent, int width);

// === CONFIG (config.c) ===
GPMConfig* config_load(const char* path);
int config_save(GPMConfig* config, const char* path);
GPMConfig* config_init_default(void);
void config_free(GPMConfig* config);
int config_parse_args(GPMConfig* config, int argc, char** argv);

// === SECURITY (security.c) ===
int sha256_file(const char* path, char output[65]);
int sha256_string(const char* data, char output[65]);
int verify_signature(const char* data, const char* signature);
int encrypt_data(const char* plain, char* encrypted);
int decrypt_data(const char* encrypted, char* plain);
char* generate_token(int length);
int hash_password(const char* password, char* hash);

// === AUTHENTICATION (login.c) ===
AuthCredentials* auth_load(void);
int auth_save(AuthCredentials* auth);
int auth_login(const char* username, const char* password);
int auth_logout(void);
int auth_is_valid(AuthCredentials* auth);
int auth_refresh_token(AuthCredentials* auth);
AuthCredentials* auth_init_default(void);
void auth_free(AuthCredentials* auth);

// === DOWNLOAD (download.c) ===
int download_init(void);
void download_cleanup(void);
int download_file(const char* url, const char* dest, AuthCredentials* auth);
int download_parallel(DownloadTask* tasks, int task_count, AuthCredentials* auth);
size_t download_write_callback(void* ptr, size_t size, size_t nmemb, void* userdata);
int download_with_progress(const char* url, const char* dest, AuthCredentials* auth);
int download_to_memory(const char* url, char** data, size_t* size, AuthCredentials* auth);

// === PARSER (parser.c) ===
PackageInfo* parse_package_json(const char* json);
PackageIndex* parse_index_json(const char* json);
char* package_to_json(PackageInfo* pkg);
char* index_to_json(PackageIndex* index);
int parse_package_filename(const char* filename, char* name, char* version, 
                          char* release, char* arch);
int parse_version(const char* version, int* major, int* minor, int* patch);
int compare_versions(const char* v1, const char* v2);

// === CACHE (cache.c) ===
int cache_init(void);
int cache_clean(int max_age);
int cache_has(const char* key);
int cache_get(const char* key, char** data, size_t* size);
int cache_set(const char* key, const char* data, size_t size);
int cache_delete(const char* key);
int cache_clear(void);
char* cache_get_path(const char* key);

// === INSTALL (install.c) ===
int install_package(const char* name, const char* version, AuthCredentials* auth, GPMConfig* config);
int install_from_url(const char* url, const char* dest, GPMConfig* config);
int install_dependencies(PackageInfo* pkg, AuthCredentials* auth, GPMConfig* config);
int uninstall_package(const char* name, GPMConfig* config);
int update_package(const char* name, const char* version, AuthCredentials* auth, GPMConfig* config);
int list_installed_packages(void);
int extract_archive(const char* archive_path, const char* dest_dir);
int verify_installation(const char* name, const char* version);

// === VERIFY (verify.c) ===
int verify_package_integrity(const char* archive_path, const char* expected_hash);
int verify_package_signature(const char* archive_path, const char* signature);
int verify_checksums(PackageInfo* pkg);
int verify_compatibility(PackageInfo* pkg);
int verify_disk_space(size_t required);
int verify_permissions(const char* path);

// === ROLLBACK (rollback.c) ===
int rollback_init(const char* name);
int rollback_package(const char* name, const char* version);
int rollback_list(const char* name);
int rollback_commit(const char* name);
int rollback_cleanup(const char* name, int keep_versions);

// === PROTOCOL (protocol.c) ===
int protocol_init(void);
void protocol_cleanup(void);
char* protocol_api_get(const char* endpoint, AuthCredentials* auth);
char* protocol_api_post(const char* endpoint, const char* data, AuthCredentials* auth);
char* protocol_api_upload(const char* endpoint, const char* filepath, 
                         AuthCredentials* auth, const char* metadata);
int protocol_api_download(const char* endpoint, const char* dest, AuthCredentials* auth);
int protocol_search(const char* query, PackageIndex** results, AuthCredentials* auth);
int protocol_publish(const char* package_path, const char* metadata, AuthCredentials* auth);

// === PUBLISH (publish.c) ===
int publish_package(const char* source_dir, const char* metadata_file, AuthCredentials* auth);
int package_create_archive(const char* source_dir, const char* dest);
int package_generate_metadata(const char* source_dir, char** metadata);
int package_validate(const char* archive_path);

// === LINKER (linker.c) ===
int linker_create_symlink(const char* target, const char* link_path);
int linker_remove_symlink(const char* link_path);
int linker_update_links(const char* package_name, const char* version);
int linker_get_target(const char* link_path, char* target, size_t size);
PathList* linker_list_links(const char* package_name);

// === DAEMON (daemon.c) ===
int daemon_start(GPMConfig* config);
int daemon_stop(void);
int daemon_status(void);
int daemon_reload(void);
void daemon_signal_handler(int sig);
int daemon_write_pid(const char* pidfile);
int daemon_check_running(const char* pidfile);

// === RELEASE (release.c) ===
int release_compare_architectures(const char* arch1, const char* arch2);
char* release_get_latest(const char* name, AuthCredentials* auth);
char** release_list_versions(const char* name, int* count, AuthCredentials* auth);
int release_check_update(const char* name, const char* current_version, 
                        char* latest_version, AuthCredentials* auth);
char* release_get_download_url(const char* name, const char* version, 
                              const char* release, const char* arch);

// === MACRO (macro.c) ===
#define GPM_OK                         0
#define GPM_ERROR                     -1
#define GPM_ERROR_NETWORK             -2
#define GPM_ERROR_AUTH                -3
#define GPM_ERROR_PACKAGE_NOT_FOUND    -4
#define GPM_ERROR_VERSION_NOT_FOUND    -5
#define GPM_ERROR_CHECKSUM            -6
#define GPM_ERROR_DISK_FULL           -7
#define GPM_ERROR_PERMISSION          -8
#define GPM_ERROR_LOCK                -9
#define GPM_ERROR_ALREADY_INSTALLED   -10
#define GPM_ERROR_DEPENDENCY          -11
#define GPM_ERROR_INVALID_ARCHIVE     -12

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_BOLD    "\033[1m"

// === SHULTIN (shultin.c) ===
int sh_exec(const char* fmt, ...);
char* sh_exec_capture(const char* fmt, ...);
int sh_exists(const char* path);
int sh_is_file(const char* path);
int sh_is_dir(const char* path);
int sh_mkdir(const char* path);
int sh_rm(const char* path);
char* sh_ls(const char* path);
char* sh_cat(const char* path);
int sh_cp(const char* src, const char* dst);
int sh_mv(const char* src, const char* dst);
char* sh_which(const char* cmd);
char* sh_env(const char* name);
char* sh_hostname(void);
char* sh_pwd(void);
int sh_chmod(const char* path, mode_t mode);
int sh_chown(const char* path, uid_t uid, gid_t gid);

// === NGINX (nginx.c) ===
int nginx_generate_config(const char* domain, const char* root_dir, int port);
int nginx_enable_site(const char* config_name);
int nginx_disable_site(const char* config_name);
int nginx_reload(void);
int nginx_test_config(void);
int nginx_get_status(void);
char* nginx_get_version(void);

#endif /* GPM_H */
