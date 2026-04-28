// include/gpm.h
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
#include <pwd.h>
#include <curl/curl.h>
#include <jansson.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <libgen.h>
#include <fcntl.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/* ================================================================
 * CONSTANTES GPM
 * ================================================================ */

#define GPM_VERSION             "3.0.0"
#define GPM_BUILD_DATE          __DATE__ " " __TIME__
#define GPM_USER_AGENT          "GPM/" GPM_VERSION " Goscript-PM"

// Chemins standards
#define GPM_HOME               ".gpm"
#define GPM_CONFIG_FILE        ".gpmrc"
#define GPM_LOCK_FILE          "gpm.lock"
#define GPM_MANIFEST_FILE      "Manifest.toml"
#define GPM_BUILD_FILE         "APKMBUILD"
#define GPM_PACKAGE_EXT        ".tar.bool"

// Répertoires système
#define GPM_CONFIG_DIR         "/etc/gpm"
#define GPM_CACHE_DIR          "/var/cache/gpm"
#define GPM_LIB_DIR            "/usr/local/lib/goscript"
#define GPM_MODULES_DIR        "/usr/local/lib/goscript/modules"
#define GPM_BIN_DIR            "/usr/local/bin"
#define GPM_TEMP_DIR           "/tmp/gpm"

// Registry
#define GPM_REGISTRY_URL       "https://gsql-badge.onrender.com"
#define GPM_API_VERSION        "v5.2"
#define GPM_DEFAULT_SCOPE      "public"

// Timeouts et limites
#define GPM_TIMEOUT            30
#define GPM_RETRY_COUNT        3
#define GPM_RETRY_DELAY        2
#define GPM_MAX_PARALLEL       4
#define GPM_CACHE_TTL          86400  // 24 heures

/* ================================================================
 * COULEURS ANSI POUR L'AFFICHAGE
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

// Macros de logging
#define LOG_INFO(fmt, ...)    printf(COLOR_BLUE   "ℹ " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_SUCCESS(fmt, ...) printf(COLOR_GREEN  "✓ " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)    printf(COLOR_YELLOW "⚠ " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   fprintf(stderr, COLOR_RED "✗ " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)   if(gpm_config.debug) printf(COLOR_MAGENTA "… " COLOR_RESET fmt "\n", ##__VA_ARGS__)
#define LOG_STEP(fmt, ...)    printf(COLOR_CYAN   "▶ " COLOR_RESET fmt "...\n", ##__VA_ARGS__)

/* ================================================================
 * TYPES FONDAMENTAUX
 * ================================================================ */

// Version sémantique
typedef struct {
    int major;
    int minor;
    int patch;
    char prerelease[32];
    char build[32];
} SemVer;

// Contrainte de version
typedef enum {
    VER_EXACT,      // =1.2.3
    VER_ANY,        // *
    VER_GTE,        // >=1.2.3
    VER_LTE,        // <=1.2.3
    VER_GT,         // >1.2.3
    VER_LT,         // <1.2.3
    VER_CARET,      // ^1.2.3 (compatible)
    VER_TILDE,      // ~1.2.3 (approximative)
    VER_RANGE,      // 1.2.3 - 2.0.0
    VER_LATEST      // latest
} VerConstraint;

typedef struct {
    char name[256];
    VerConstraint type;
    SemVer version;
    SemVer version_max;  // Pour les ranges
} Dependency;

// Manifest du package
typedef struct {
    char name[256];
    char version[64];
    char release[16];
    char arch[32];
    char description[1024];
    char author[256];
    char license[64];
    char homepage[256];
    
    // Dépendances
    Dependency* dependencies;
    int dep_count;
    Dependency* dev_dependencies;
    int dev_dep_count;
    
    // Scripts npm-like
    char scripts_preinstall[1024];
    char scripts_install[1024];
    char scripts_postinstall[1024];
    char scripts_build[1024];
    char scripts_test[1024];
    char scripts_prepublish[1024];
    
    // Build
    char build_cmd[1024];
    char install_cmd[1024];
    
    // Fichiers
    char* files[256];
    int files_count;
    char main[256];
    
    // Métadonnées
    char sha256[128];
    time_t created_at;
} Manifest;

// Configuration GPM
typedef struct {
    // Chemins
    char home_dir[512];
    char cache_dir[512];
    char global_dir[512];
    char registry_url[256];
    
    // Auth
    char token[512];
    char username[256];
    bool authenticated;
    
    // Comportement
    bool debug;
    bool force;
    bool global;
    bool production;
    bool save_dev;
    bool offline;
    bool verify_ssl;
    
    // Registry
    char scope[16];
    char arch[32];
    
    // Cache
    int cache_ttl;
    int max_parallel;
    int timeout;
} GPMConfig;

// Noeud de l'arbre de dépendances
typedef struct DepNode {
    char name[256];
    char version[64];
    bool resolved;
    bool hoisted;
    bool is_dev;
    int depth;
    struct DepNode** children;
    int child_count;
    struct DepNode* parent;
} DepNode;

// Entrée du lockfile
typedef struct {
    char name[256];
    char version[64];
    char url[512];
    char integrity[128];  // SHA512
    bool is_dev;
    int depth;
} LockEntry;

typedef struct {
    char version[16];
    LockEntry* entries;
    int entry_count;
} Lockfile;

// Package installé
typedef struct {
    char name[256];
    char version[64];
    char path[1024];
    Manifest* manifest;
    time_t install_date;
} InstalledPackage;

/* ================================================================
 * VARIABLE GLOBALE DE CONFIGURATION
 * ================================================================ */

extern GPMConfig gpm_config;

/* ================================================================
 * FONCTIONS PRINCIPALES
 * ================================================================ */

// Configuration
int gpm_config_init(void);
int gpm_config_load(void);
int gpm_config_save(void);
int gpm_config_set(const char* key, const char* value);
char* gpm_config_get(const char* key);

// Manifest
int gpm_manifest_read(Manifest* manifest);
int gpm_manifest_write(Manifest* manifest);
int gpm_manifest_validate(Manifest* manifest);

// Version
SemVer gpm_semver_parse(const char* version);
int gpm_semver_compare(SemVer a, SemVer b);
bool gpm_semver_satisfies(SemVer version, Dependency dep);
char* gpm_semver_to_string(SemVer ver);

// Résolution
DepNode* gpm_resolve_tree(Manifest* manifest);
int gpm_flatten_tree(DepNode* root);
int gpm_hoist_dependencies(DepNode* root);
void gpm_free_dep_tree(DepNode* node);

// Dépendances
Dependency gpm_dependency_parse(const char* name, const char* constraint);
char* gpm_resolve_version(Dependency* dep);

// Arbre
void gpm_print_tree(DepNode* node, int depth);
void gpm_flatten_tree_to_list(DepNode* node, DepNode*** list, int* count);

// Lockfile
int gpm_compute_integrity(const char* name, const char* version, char* output);

// Installation
int gpm_init_project(const char* name, const char* version);

// Publication
int gpm_publish(void);

// Authentification
int gpm_login(const char* username, const char* password);
int gpm_logout(void);

// Build
int gpm_build_package(void);

// Lockfile
int gpm_lockfile_read(Lockfile* lock);
int gpm_lockfile_write(Lockfile* lock);
int gpm_lockfile_generate(DepNode* tree);

// Réseau
int gpm_network_init(void);
char* gpm_network_get(const char* url, long* status);
int gpm_network_download(const char* url, const char* output);
int gpm_network_upload(const char* url, const char* file, const char* token);
bool gpm_network_check(void);

// Installation
int gpm_install_package(const char* name, const char* version);
int gpm_install_from_manifest(void);
int gpm_uninstall_package(const char* name);
int gpm_update_package(const char* name);

// Build
int gpm_build_package(void);
int gpm_run_script(const char* script);

// Utilitaires
char* gpm_strdup(const char* src);
char* gpm_path_join(const char* p1, const char* p2);
bool gpm_file_exists(const char* path);
int gpm_mkdir_p(const char* path);
char* gpm_sha256_file(const char* path);

#endif // GPM_H
