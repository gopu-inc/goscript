#ifndef GPM_H
#define GPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <jansson.h>
#include <sqlite3.h>
#include <yaml.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <pthread.h>

// ============================================================================
// CONSTANTES GLOBALES
// ============================================================================

#define GPM_VERSION "3.0.0"
#define GPM_LOCKFILE "gpm.lock"
#define GPM_MANIFEST "Manifest.toml"
#define GPM_BUILD_FILE "APKMBUILD"
#define GPM_PACKAGE_EXT ".tar.bool"

// Chemins
#define GPM_HOME_DIR ".gpm"
#define GPM_CONFIG_FILE ".gpmrc"
#define GPM_CACHE_DIR ".gpm/cache"
#define GPM_GLOBAL_DIR "/usr/local/lib/gpm"
#define GPM_MODULES_DIR "/usr/local/lib/gpm/modules"
#define GPM_BIN_DIR "/usr/local/bin"
#define GPM_TEMP_DIR "/tmp/gpm"

#define GPM_REGISTRY_URL "https://gsql-badge.onrender.com"
#define GPM_API_VERSION "v5.2"

// ============================================================================
// TYPES DE DONNÉES AMÉLIORÉS
// ============================================================================

// Version sémantique
typedef struct {
    int major;
    int minor;
    int patch;
    char prerelease[32];
    char build[32];
} semver_t;

// Contrainte de version (comme npm)
typedef enum {
    CONSTRAINT_EXACT,     // 1.2.3
    CONSTRAINT_GTE,       // >=1.2.3  
    CONSTRAINT_LTE,       // <=1.2.3
    CONSTRAINT_GT,        // >1.2.3
    CONSTRAINT_LT,        // <1.2.3
    CONSTRAINT_CARET,     // ^1.2.3 (compatible)
    CONSTRAINT_TILDE,     // ~1.2.3 (patch)
    CONSTRAINT_RANGE,     // 1.2.3 - 2.0.0
    CONSTRAINT_ANY        // *
} version_constraint_t;

typedef struct {
    char name[256];
    version_constraint_t type;
    semver_t version_min;
    semver_t version_max;
} dependency_t;

// Arbre de dépendances
typedef struct dep_node {
    char name[256];
    char version[64];
    bool resolved;
    bool is_dev;
    struct dep_node** children;
    int child_count;
    int depth;
    bool hoisted;
} dep_node_t;

// Manifest complet (comme package.json)
typedef struct {
    char name[256];
    char version[64];
    char release[16];
    char arch[32];
    char description[1024];
    char author[256];
    char license[64];
    char homepage[256];
    char repository[256];
    
    // Dépendances
    dependency_t* dependencies;
    int dep_count;
    dependency_t* dev_dependencies;
    int dev_dep_count;
    dependency_t* peer_dependencies;
    int peer_dep_count;
    dependency_t* optional_dependencies;
    int opt_dep_count;
    
    // Scripts lifecycle
    char scripts_preinstall[1024];
    char scripts_install[1024];
    char scripts_postinstall[1024];
    char scripts_preuninstall[1024];
    char scripts_uninstall[1024];
    char scripts_postuninstall[1024];
    char scripts_build[1024];
    char scripts_test[1024];
    char scripts_prepublish[1024];
    
    // Métadonnées
    char main[256];       // Point d'entrée
    char* keywords[32];
    int keyword_count;
    char* files_to_include[256];
    int files_count;
    
    // Bool build info
    char build_cmd[1024];
    char install_cmd[1024];
    char check_cmd[1024];
    char build_deps[1024];
    
    // Signature
    char sha256[128];
    char signature[256];
    time_t build_date;
    char build_host[128];
    
    // Zarch Hub
    char hub_auth_token[512];
    bool hub_published;
    char hub_url[512];
} manifest_t;

// Lockfile entry (comme package-lock.json)
typedef struct {
    char name[256];
    char version[64];
    char resolved_url[512];
    char integrity[128];  // SHA512
    bool is_dev;
    int depth;
    char* dependencies[32];
    int dep_count;
} lock_entry_t;

typedef struct {
    char name[256];
    char version[64];
    char lockfile_version[16];
    lock_entry_t* packages;
    int package_count;
} lockfile_t;

// GPM Configuration complète
typedef struct {
    // Chemins
    char home_dir[512];
    char config_path[512];
    char cache_dir[512];
    char global_dir[512];
    char registry_url[256];
    
    // Authentification
    char auth_token[512];
    char username[256];
    bool authenticated;
    
    // Comportement
    bool save_exact;
    bool save_dev;
    bool save_optional;
    bool production;
    bool force;
    bool global;
    bool verbose;
    bool debug;
    
    // Cache
    int cache_max_age;    // secondes
    int cache_max_size;   // MB
    
    // Proxy
    char proxy_url[256];
    bool verify_ssl;
    
    // Registry
    char scope[16];       // public/private
    char default_arch[32];
    
    // Build
    char build_dir[256];
    bool auto_build;
} gpm_config_t;

// État de l'installation
typedef enum {
    PKG_NOT_INSTALLED,
    PKG_INSTALLED,
    PKG_UPDATING,
    PKG_BUILDING,
    PKG_ERROR,
    PKG_QUEUED
} package_state_t;

// Package dans le registre local
typedef struct {
    char name[256];
    char version[64];
    char real_path[1024];
    char node_modules_path[1024];
    package_state_t state;
    manifest_t* manifest;
    dep_node_t* dep_tree;
    bool is_linked;
    bool is_global;
} installed_pkg_t;

// ============================================================================
// API PRINCIPALE DE GPM
// ============================================================================

// Initialisation
int gpm_init();
int gpm_init_project(const char* name, const char* version);
int gpm_load_config();
int gpm_save_config();

// Gestion des dépendances (comme npm)
int gpm_install(const char* package, const char* version);
int gpm_install_from_manifest();
int gpm_uninstall(const char* package);
int gpm_update(const char* package);
int gpm_update_all();
int gpm_dedupe();
int gpm_prune();
int gpm_outdated();

// Résolution intelligente
dep_node_t* gpm_resolve_tree(manifest_t* manifest);
int gpm_flatten_tree(dep_node_t* root);
int gpm_detect_conflicts(dep_node_t* root);
int gpm_hoist_dependencies(dep_node_t* root);
int gpm_generate_lockfile(dep_node_t* tree);

// Installation physique
int gpm_download_package(const char* name, const char* version, const char* output);
int gpm_extract_package(const char* archive, const char* dest);
int gpm_run_lifecycle(const char* script_name, const char* pkg_path);
int gpm_link_binaries(const char* pkg_path);
int gpm_create_symlinks();

// Publication (comme npm publish)
int gpm_publish();
int gpm_pack();
int gpm_login(const char* username, const char* password);
int gpm_logout();
int gpm_whoami();

// Build (comme bool)
int gpm_build();
int gpm_run_build_script();
int gpm_test();

// Gestion du cache
int gpm_cache_add(const char* name, const char* version, const char* archive);
int gpm_cache_get(const char* name, const char* version, char* path);
int gpm_cache_clean();
int gpm_cache_verify();
int gpm_cache_size();

// Recherche et info
int gpm_search(const char* query);
int gpm_info(const char* package);
int gpm_list(const char* filter);
int gpm_audit();
int gpm_doctor();

// Configuration
int gpm_config_set(const char* key, const char* value);
char* gpm_config_get(const char* key);
int gpm_config_list();
int gpm_config_delete(const char* key);

// Workspaces
int gpm_workspace_init();
int gpm_workspace_add(const char* package);
int gpm_workspace_remove(const char* package);

// Scripts
int gpm_run_script(const char* script_name);
int gpm_run(const char* command);

// Utilitaires
char* gpm_resolve_path(const char* relative);
int gpm_file_exists(const char* path);
semver_t gpm_parse_version(const char* version);
int gpm_compare_versions(semver_t a, semver_t b);
bool gpm_version_satisfies(semver_t version, dependency_t constraint);
char* gpm_get_latest_version(const char* name);

// Base de données locale
int gpm_db_init();
int gpm_db_add_package(installed_pkg_t* pkg);
int gpm_db_remove_package(const char* name);
installed_pkg_t* gpm_db_get_package(const char* name);
installed_pkg_t** gpm_db_list_packages(int* count);
int gpm_db_search(const char* query, installed_pkg_t** results, int max);

// Hooks et événements
typedef int (*gpm_hook_fn)(const char* event, void* data);
int gpm_register_hook(const char* event, gpm_hook_fn callback);
int gpm_emit_event(const char* event, void* data);

#endif // GPM_H
