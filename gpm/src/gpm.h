#ifndef GPM_H
#define GPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#include <curl/curl.h>
#include <archive.h>
#include <archive_entry.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <jansson.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/* ================================================================
 * CONSTANTES
 * ================================================================ */

#define GPM_VERSION             "1.0.0"
#define GPM_BUILD_DATE          __DATE__ " " __TIME__
#define GPM_USER_AGENT          "GPM/" GPM_VERSION " Goscript-PM"
#define GPM_CONFIG_DIR          "/etc/gpm"
#define GPM_CACHE_DIR           "/var/cache/gpm"
#define GPM_LIB_DIR             "/usr/local/lib/goscript"
#define GPM_MODULES_DIR         "/usr/local/lib/goscript/modules"
#define GPM_STDLIB_DIR          "/usr/local/lib/goscript/std"
#define GPM_BUILTIN_DIR         "/usr/local/lib/goscript/builtin"
#define GPM_KERNEL_DIR          "/usr/local/lib/goscript/kernel"
#define GPM_NGINX_DIR           "/usr/local/lib/goscript/nginx"
#define GPM_DAEMON_DIR          "/usr/local/lib/goscript/daemon"
#define GPM_TEMP_DIR            "/tmp/gpm"
#define GPM_PACKAGE_EXT         ".tar.bool"
#define GPM_LOCK_FILE           "gpm.lock"
#define GPM_CONFIG_FILE         "gpm.conf"
#define GPM_CACHE_DB            "cache.db"
#define GPM_INDEX_URL           "https://gsql-badge.onrender.com"
#define GPM_API_VERSION         "v5.2"
#define GPM_DEFAULT_REGISTRY    "https://gsql-badge.onrender.com"
#define GPM_MIRROR_REGISTRY     "https://gpm.gopu-inc.com"
#define GPM_FALLBACK_REGISTRY   "https://gpm.github.io"
#define GPM_TIMEOUT             30
#define GPM_RETRY_COUNT         3
#define GPM_RETRY_DELAY         2
#define GPM_MAX_PARALLEL        4
#define GPM_BUFFER_SIZE         8192
#define GPM_HASH_ALGO           "sha256"
#define GPM_SIG_ALGO            "RSA-SHA256"
#define GPM_TTL_DEFAULT         3600
#define GPM_CACHE_TTL           86400

/* ================================================================
 * COULEURS ANSI
 * ================================================================ */

#define COLOR_RESET     "\033[0m"
#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_BLUE      "\033[34m"
#define COLOR_MAGENTA   "\033[35m"
#define COLOR_CYAN      "\033[36m"
#define COLOR_WHITE     "\033[37m"
#define COLOR_BOLD      "\033[1m"
#define COLOR_DIM       "\033[2m"
#define COLOR_UNDERLINE "\033[4m"

#define LOG_INFO(fmt, ...)    printf(COLOR_BLUE "[INFO] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_SUCCESS(fmt, ...) printf(COLOR_GREEN "[✓] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)    printf(COLOR_YELLOW "[⚠] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   fprintf(stderr, COLOR_RED "[✗] " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)   if(g_config.debug) printf(COLOR_MAGENTA "[DEBUG] " COLOR_RESET fmt "\n", ##__VA_ARGS__)

/* ================================================================
 * TYPES ÉNUMÉRÉS
 * ================================================================ */

typedef enum {
    PKG_SCOPE_PUBLIC,
    PKG_SCOPE_PRIVATE,
    PKG_SCOPE_UNLISTED
} PackageScope;

typedef enum {
    PKG_STATUS_INSTALLED,
    PKG_STATUS_UPDATING,
    PKG_STATUS_ERROR,
    PKG_STATUS_BUILDING,
    PKG_STATUS_DOWNLOADING,
    PKG_STATUS_VERIFYING,
    PKG_STATUS_ROLLBACK
} PackageStatus;

typedef enum {
    ARCH_X86_64,
    ARCH_I686,
    ARCH_AARCH64,
    ARCH_ARMV7L,
    ARCH_RISCV64,
    ARCH_UNKNOWN
} ArchType;

typedef enum {
    AUTH_NONE,
    AUTH_TOKEN,
    AUTH_OAUTH2,
    AUTH_PGP,
    AUTH_SSH
} AuthMethod;

typedef enum {
    PROTO_HTTPS,
    PROTO_SSH,
    PROTO_GIT,
    PROTO_IPFS,
    PROTO_IPNS
} ProtocolType;

/* ================================================================
 * STRUCTURES DE DONNÉES
 * ================================================================ */

typedef struct {
    char* name;
    char* version;
    char* release;
    ArchType arch;
    PackageScope scope;
    char* author;
    char* description;
    char* license;
    char* homepage;
    char* repository;
    char** keywords;
    int keyword_count;
    char** dependencies;
    int dep_count;
    char** conflicts;
    int conflict_count;
    char* sha256;
    char* signature;
    size_t size;
    time_t created_at;
    time_t updated_at;
    int downloads;
    float rating;
} PackageMeta;

typedef struct {
    char* username;
    char* token;
    char* refresh_token;
    char* email;
    AuthMethod auth_method;
    time_t token_expiry;
    bool authenticated;
    char* ssh_key_path;
    char* pgp_key_id;
} AuthContext;

typedef struct {
    char* registry_url;
    char* cache_dir;
    char* lib_dir;
    char* token;
    char* default_scope;
    char* default_arch;
    char* proxy;
    int timeout;
    int retry_count;
    int max_parallel;
    bool verify_ssl;
    bool debug;
    bool force;
    bool yes;
    bool no_color;
    bool offline;
    bool use_cache;
    bool sandbox;
    bool daemon_mode;
    int ttl;
    char* nginx_conf;
    char* kernel_version;
    char** registries;
    int registry_count;
} GPMConfig;

typedef struct {
    char** packages;
    int count;
    int capacity;
} PackageList;

typedef struct {
    char* path;
    char* hash;
    time_t timestamp;
    size_t size;
} CacheEntry;

typedef struct {
    CacheEntry** entries;
    int count;
    int capacity;
} CacheDatabase;

typedef struct {
    pid_t pid;
    char* name;
    char* config_path;
    bool running;
} DaemonProcess;

/* ================================================================
 * VARIABLES GLOBALES
 * ================================================================ */

extern GPMConfig g_config;
extern AuthContext g_auth;

/* ================================================================
 * FONCTIONS PRINCIPALES
 * ================================================================ */

/* gpm_main.c */
void print_banner(void);
void print_help(void);
void print_version(void);
int  parse_command_line(int argc, char** argv);
void init_config(void);
void load_config(void);
void save_config(void);

/* gpm_core.c */
int  gpm_init(void);
int  gpm_install(const char* package, const char* version);
int  gpm_uninstall(const char* package);
int  gpm_update(const char* package);
int  gpm_list(const char* filter);
int  gpm_search(const char* query);
int  gpm_info(const char* package);
int  gpm_login(const char* username, const char* password);
int  gpm_logout(void);
int  gpm_publish(const char* package_path);
int  gpm_verify(const char* package);
int  gpm_rollback(const char* package, const char* version);
int  gpm_build(const char* source_dir, const char* output);
int  gpm_daemon_start(const char* config);
int  gpm_daemon_stop(const char* name);
int  gpm_cache_clean(void);
int  gpm_cache_verify(void);
int  gpm_config_set(const char* key, const char* value);
int  gpm_config_get(const char* key);

/* gpm_network.c */
int  network_init(void);
void network_cleanup(void);
char* network_get(const char* url, long* status_code);
char* network_post(const char* url, const char* data, const char* content_type);
int  network_download(const char* url, const char* output_path);
int  network_upload(const char* url, const char* file_path);
bool network_check_connectivity(void);
int  network_auth_login(const char* username, const char* password);
int  network_auth_verify(void);
int  network_auth_refresh(void);
char* network_get_user_agent(void);
char* network_get_system_info(void);
int  network_setup_ssl(void);
int  network_proxy_setup(const char* proxy);

/* gpm_package.c */
int  package_create(const char* source_dir, const char* output_path);
int  package_extract(const char* package_path, const char* dest_dir);
int  package_verify(const char* package_path, const char* expected_hash);
int  package_sign(const char* package_path, const char* key_path);
int  package_verify_signature(const char* package_path, const char* pubkey_path);
char* package_compute_hash(const char* file_path);
PackageMeta* package_read_meta(const char* package_path);
int package_write_meta(const char* package_path, PackageMeta* meta);
int  package_install_file(const char* package_path);
int  package_uninstall_files(PackageMeta* meta);
int  package_resolve_deps(PackageMeta* meta);
int  package_check_conflicts(PackageMeta* meta);
int  package_rollback_to(const char* package, const char* version);
PackageList* package_get_installed(void);
bool package_is_installed(const char* name, const char* version);
char* package_find_in_cache(const char* name, const char* version, const char* arch);

/* ================================================================
 * FONCTIONS UTILITAIRES
 * ================================================================ */

char* str_duplicate(const char* src);
char* str_concat(const char* s1, const char* s2);
char* str_replace(const char* str, const char* old, const char* new);
bool  str_startswith(const char* str, const char* prefix);
bool  str_endswith(const char* str, const char* suffix);
char* str_trim(char* str);
char* str_upper(char* str);
char* str_lower(char* str);
char* path_join(const char* path1, const char* path2);
char* path_dirname(const char* path);
char* path_basename(const char* path);
char* path_extension(const char* path);
bool  file_exists(const char* path);
bool  dir_exists(const char* path);
int   dir_create(const char* path);
int   dir_remove(const char* path);
size_t file_size(const char* path);
char* file_read(const char* path);
int   file_write(const char* path, const char* content);
char* get_home_dir(void);
char* get_current_dir(void);
char* get_temp_dir(void);
char* get_os_name(void);
char* get_os_version(void);
char* get_kernel_version(void);
char* get_hostname(void);
char* get_username(void);
ArchType get_cpu_arch(void);
int   get_cpu_count(void);
long  get_total_ram(void);
long  get_free_ram(void);
time_t get_boot_time(void);
char* generate_uuid(void);
char* base64_encode(const unsigned char* data, size_t len);
unsigned char* base64_decode(const char* data, size_t* out_len);
char* url_encode(const char* str);
char* url_decode(const char* str);
int   run_command(const char* cmd, char** output, int* exit_code);
int   run_command_async(const char* cmd);
int   wait_for_process(pid_t pid, int* exit_code);
void  set_process_name(const char* name);
int   daemonize(void);

#endif /* GPM_H */
