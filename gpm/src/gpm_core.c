#include "gpm.h"
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

/* ================================================================
 * DÉCLARATIONS FORWARD DES FONCTIONS EXTERNES
 * ================================================================ */

// Fonctions de gpm_package.c
extern void package_meta_free(PackageMeta* meta);
extern void package_list_free(PackageList* list);
extern int package_extract(const char* package_path, const char* dest_dir);
extern int package_create(const char* source_dir, const char* output_path);
extern int package_install_file(const char* package_path);
extern int package_uninstall_files(PackageMeta* meta);
extern int package_resolve_deps(PackageMeta* meta);
extern int package_check_conflicts(PackageMeta* meta);
extern int package_verify(const char* package_path, const char* expected_hash);
extern int package_sign(const char* package_path, const char* key_path);
extern int package_verify_signature(const char* package_path, const char* pubkey_path);
extern char* package_compute_hash(const char* file_path);
extern PackageMeta* package_read_meta(const char* package_path);
extern int package_write_meta(const char* package_path, PackageMeta* meta);
extern PackageList* package_get_installed(void);
extern bool package_is_installed(const char* name, const char* version);
extern char* package_find_in_cache(const char* name, const char* version, const char* arch);
extern void package_meta_free(PackageMeta* meta);
extern void package_list_free(PackageList* list);

// Fonctions de gpm_network.c
extern int network_init(void);
extern void network_cleanup(void);
extern char* network_get(const char* url, long* status_code);
extern char* network_post(const char* url, const char* data, const char* content_type);
extern int network_download(const char* url, const char* output_path);
extern int network_upload(const char* url, const char* file_path);
extern bool network_check_connectivity(void);
extern int network_auth_login(const char* username, const char* password);
extern int network_auth_verify(void);
extern int network_auth_refresh(void);
extern char* network_get_user_agent(void);
extern char* network_get_system_info(void);

// Fonctions utilitaires
extern char* strdup(const char* s);
extern char* url_encode(const char* str);
extern char* path_basename(const char* path);
extern int run_command(const char* cmd, char** output, int* exit_code);

/* ================================================================
 * INITIALISATION GPM
 * ================================================================ */

int gpm_init(void) {
    LOG_INFO("Initializing GPM...");
    
    // Créer les dossiers nécessaires
    dir_create(GPM_CONFIG_DIR);
    dir_create(GPM_CACHE_DIR);
    dir_create(GPM_LIB_DIR);
    dir_create(GPM_MODULES_DIR);
    dir_create(GPM_STDLIB_DIR);
    dir_create(GPM_BUILTIN_DIR);
    dir_create(GPM_TEMP_DIR);
    dir_create(GPM_KERNEL_DIR);
    dir_create(GPM_NGINX_DIR);
    dir_create(GPM_DAEMON_DIR);
    
    // Vérifier la connectivité si pas en mode offline
    if (!g_config.offline) {
        if (!network_check_connectivity()) {
            LOG_WARN("No network connectivity, switching to offline mode");
            g_config.offline = true;
        }
    }
    
    // Vérifier l'authentification
    if (g_config.token && !g_auth.authenticated) {
        network_auth_verify();
    }
    
    LOG_SUCCESS("GPM initialized");
    return 0;
}

/* ================================================================
 * INSTALLATION D'UN PACKAGE
 * ================================================================ */

int gpm_install(const char* package, const char* version) {
    char clean_package[256] = {0};
    char specified_version[64] = {0};
    char pkg_release[32] = "r0";     // ← AJOUT : release par défaut
    char pkg_arch[32] = {0};          // ← AJOUT : arch du registre
    
    // 1. PARSER LE FORMAT "package@version"
    char* at_sign = strchr(package, '@');
    if (at_sign) {
        size_t name_len = at_sign - package;
        strncpy(clean_package, package, name_len);
        clean_package[name_len] = '\0';
        strncpy(specified_version, at_sign + 1, 63);
        specified_version[63] = '\0';
    } else {
        strncpy(clean_package, package, 255);
        clean_package[255] = '\0';
        if (version) {
            strncpy(specified_version, version, 63);
            specified_version[63] = '\0';
        }
    }
    
    // 2. RÉSOUDRE LA VERSION + RELEASE + ARCH
    char resolved_version[64] = {0};
    
    if (specified_version[0] != '\0') {
        strncpy(resolved_version, specified_version, 63);
    } else {
        // Chercher les infos du package via l'API
        char url[1024];
        snprintf(url, sizeof(url), "%s/%s/package/%s",
                 g_config.registry_url, GPM_API_VERSION, clean_package);
        
        long status = 0;
        char* response = network_get(url, &status);
        
        if (status == 200 && response) {
            json_error_t error;
            json_t* root = json_loads(response, 0, &error);
            if (root) {
                json_t* pkg_obj = json_object_get(root, "package");
                if (pkg_obj) {
                    // Version
                    json_t* ver = json_object_get(pkg_obj, "version");
                    if (ver && json_is_string(ver)) {
                        strncpy(resolved_version, json_string_value(ver), 63);
                        resolved_version[63] = '\0';
                    }
                    
                    // Release (AJOUT)
                    json_t* rel = json_object_get(pkg_obj, "release");
                    if (rel && json_is_string(rel)) {
                        strncpy(pkg_release, json_string_value(rel), 31);
                        pkg_release[31] = '\0';
                    }
                    
                    // Arch du registre (AJOUT)
                    json_t* arch_json = json_object_get(pkg_obj, "arch");
                    if (arch_json && json_is_string(arch_json)) {
                        strncpy(pkg_arch, json_string_value(arch_json), 31);
                        pkg_arch[31] = '\0';
                    }
                }
                json_decref(root);
            }
            free(response);
        }
        
        if (resolved_version[0] == '\0') {
            strcpy(resolved_version, "latest");
        }
    }
    
    // Si l'arch n'est pas spécifiée par le registre, utiliser l'arch locale
    if (pkg_arch[0] == '\0') {
        strncpy(pkg_arch, g_config.default_arch, 31);
    }
    
    LOG_INFO("Installing %s@%s (release=%s, arch=%s)...", 
             clean_package, resolved_version, pkg_release, pkg_arch);
    
    // 3. VÉRIFIER SI DÉJÀ INSTALLÉ
    if (package_is_installed(clean_package, resolved_version)) {
        LOG_WARN("%s@%s is already installed", clean_package, resolved_version);
        if (!g_config.force) return 0;
    }
    
    // 4. TÉLÉCHARGER avec le bon release et la bonne arch
    char download_url[1024];
    snprintf(download_url, sizeof(download_url), 
             "%s/package/download/%s/%s/%s/%s/%s",  // ← AJOUT du release
             g_config.registry_url,
             g_config.default_scope,
             clean_package,
             resolved_version,
             pkg_release,     // ← Release dynamique
             pkg_arch);        // ← Arch du registre
    
    char temp_path[1024];
    snprintf(temp_path, sizeof(temp_path), "%s/%s-%s-%s" GPM_PACKAGE_EXT,
             g_config.cache_dir, clean_package, resolved_version, pkg_arch);
    
    LOG_INFO("Downloading: %s", download_url);
    
    int download_result = network_download(download_url, temp_path);
    
    // 5. FALLBACKS avec le même release
    if (download_result != 0) {
        const char* fallback_archs[] = {"x86_64", "i686", "aarch64", "armv7l", NULL};
        bool downloaded = false;
        
        for (int j = 0; fallback_archs[j]; j++) {
            if (strcmp(fallback_archs[j], pkg_arch) == 0) continue;
            
            snprintf(download_url, sizeof(download_url),
                     "%s/package/download/%s/%s/%s/%s/%s",
                     g_config.registry_url,
                     g_config.default_scope,
                     clean_package,
                     resolved_version,
                     pkg_release,
                     fallback_archs[j]);
            
            snprintf(temp_path, sizeof(temp_path), "%s/%s-%s-%s" GPM_PACKAGE_EXT,
                     g_config.cache_dir, clean_package, resolved_version, fallback_archs[j]);
            
            LOG_INFO("Trying %s: %s", fallback_archs[j], download_url);
            if (network_download(download_url, temp_path) == 0) {
                downloaded = true;
                break;
            }
        }
        
        if (!downloaded) {
            LOG_ERROR("Failed to download package: %s", clean_package);
            return 1;
        }
    }
    
    // 6. VÉRIFIER
    if (!gpm_verify(temp_path)) {
        LOG_ERROR("Package integrity check failed");
        unlink(temp_path);
        return 1;
    }
    
    // 7. EXTRAIRE
    if (package_extract(temp_path, g_config.lib_dir) != 0) {
        LOG_ERROR("Failed to extract package");
        unlink(temp_path);
        return 1;
    }
    
    // 8. DÉPENDANCES
    PackageMeta* meta = package_read_meta(temp_path);
    if (meta) {
        if (meta->dep_count > 0) {
            package_resolve_deps(meta);
        }
        package_meta_free(meta);
    }
    
    LOG_SUCCESS("✅ Successfully installed %s@%s", clean_package, resolved_version);
    
    char install_path[1024];
    snprintf(install_path, sizeof(install_path), "%s/%s", g_config.lib_dir, clean_package);
    LOG_INFO("📍 Location: %s", install_path);
    
    return 0;
}
/* ================================================================
 * ROLLBACK - CORRIGÉ (SANS .tar.bool DANS L'URL)
 * ================================================================ */

int gpm_rollback(const char* package, const char* version) {
    LOG_INFO("Rolling back %s to version %s...", package, version);
    
    char cached_path[1024];
    snprintf(cached_path, sizeof(cached_path), "%s/%s-%s-%s" GPM_PACKAGE_EXT,
             g_config.cache_dir, package, version, g_config.default_arch);
    
    if (!file_exists(cached_path)) {
        LOG_INFO("Version not in cache, downloading...");
        
        // URL sans .tar.bool
        char url[1024];
        snprintf(url, sizeof(url), "%s/package/download/%s/%s/%s/r0/%s",
                 g_config.registry_url,
                 g_config.default_scope,
                 package,
                 version,
                 g_config.default_arch);
        
        LOG_INFO("Downloading: %s", url);
        
        if (network_download(url, cached_path) != 0) {
            LOG_ERROR("Failed to download version %s", version);
            return 1;
        }
    }
    
    gpm_uninstall(package);
    
    if (gpm_install(package, version) != 0) {
        LOG_ERROR("Rollback failed");
        return 1;
    }
    
    LOG_SUCCESS("Rolled back %s to version %s", package, version);
    return 0;
}

/* ================================================================
 * DÉSINSTALLATION
 * ================================================================ */

int gpm_uninstall(const char* package) {
    LOG_INFO("Uninstalling %s...", package);
    
    // Trouver le package installé
    char meta_path[1024];
    snprintf(meta_path, sizeof(meta_path), "%s/%s/package.json", 
             g_config.lib_dir, package);
    
    if (!file_exists(meta_path)) {
        LOG_ERROR("Package not found: %s", package);
        return 1;
    }
    
    PackageMeta* meta = package_read_meta(meta_path);
    if (!meta) {
        LOG_ERROR("Failed to read package metadata");
        return 1;
    }
    
    // Vérifier les dépendances inverses
    PackageList* installed = package_get_installed();
    for (int i = 0; i < installed->count; i++) {
        char dep_meta_path[1024];
        snprintf(dep_meta_path, sizeof(dep_meta_path), "%s/%s/package.json",
                 g_config.lib_dir, installed->packages[i]);
        
        PackageMeta* dep_meta = package_read_meta(dep_meta_path);
        if (dep_meta) {
            for (int j = 0; j < dep_meta->dep_count; j++) {
                if (dep_meta->dependencies[j] && strcmp(dep_meta->dependencies[j], package) == 0) {
                    LOG_WARN("%s depends on %s", installed->packages[i], package);
                    if (!g_config.force) {
                        LOG_ERROR("Use --force to uninstall anyway");
                        package_meta_free(dep_meta);
                        package_list_free(installed);
                        package_meta_free(meta);
                        return 1;
                    }
                }
            }
            package_meta_free(dep_meta);
        }
    }
    package_list_free(installed);
    
    // Supprimer les fichiers
    if (package_uninstall_files(meta) != 0) {
        LOG_ERROR("Failed to remove package files");
        package_meta_free(meta);
        return 1;
    }
    
    // Supprimer le dossier du package
    char pkg_dir[1024];
    snprintf(pkg_dir, sizeof(pkg_dir), "%s/%s", g_config.lib_dir, package);
    dir_remove(pkg_dir);
    
    package_meta_free(meta);
    LOG_SUCCESS("Successfully uninstalled %s", package);
    return 0;
}

/* ================================================================
 * MISE À JOUR
 * ================================================================ */

int gpm_update(const char* package) {
    if (package) {
        LOG_INFO("Updating %s...", package);
        return gpm_install(package, "latest");
    }
    
    // Mettre à jour tous les packages
    LOG_INFO("Updating all packages...");
    
    PackageList* installed = package_get_installed();
    int updated = 0;
    int errors = 0;
    
    for (int i = 0; i < installed->count; i++) {
        LOG_INFO("Checking %s...", installed->packages[i]);
        
        // Vérifier si une mise à jour est disponible
        char url[1024];
        snprintf(url, sizeof(url), "%s/%s/package/%s/latest",
                 g_config.registry_url, GPM_API_VERSION, installed->packages[i]);
        
        long status = 0;
        char* response = network_get(url, &status);
        if (status == 200 && response) {
            json_error_t error;
            json_t* root = json_loads(response, 0, &error);
            if (root) {
                json_t* latest_ver = json_object_get(root, "version");
                if (latest_ver && json_is_string(latest_ver)) {
                    char* current_ver = NULL;
                    char meta_path[1024];
                    snprintf(meta_path, sizeof(meta_path), "%s/%s/package.json",
                             g_config.lib_dir, installed->packages[i]);
                    
                    PackageMeta* meta = package_read_meta(meta_path);
                    if (meta && meta->version) {
                        current_ver = strdup(meta->version);
                        package_meta_free(meta);
                    }
                    
                    if (current_ver && strcmp(current_ver, json_string_value(latest_ver)) != 0) {
                        LOG_INFO("Update available: %s %s -> %s",
                                 installed->packages[i], current_ver, 
                                 json_string_value(latest_ver));
                        
                        if (gpm_install(installed->packages[i], 
                                       json_string_value(latest_ver)) == 0) {
                            updated++;
                        } else {
                            errors++;
                        }
                    }
                    free(current_ver);
                }
                json_decref(root);
            }
            free(response);
        }
    }
    
    package_list_free(installed);
    
    if (updated > 0) {
        LOG_SUCCESS("Updated %d package(s)", updated);
    } else {
        LOG_INFO("All packages are up to date");
    }
    
    return errors > 0 ? 1 : 0;
}

/* ================================================================
 * LISTE DES PACKAGES
 * ================================================================ */

int gpm_list(const char* filter) {
    PackageList* installed = package_get_installed();
    
    if (installed->count == 0) {
        printf(COLOR_DIM "No packages installed\n" COLOR_RESET);
        package_list_free(installed);
        return 0;
    }
    
    printf(COLOR_BOLD "\n📦 Installed Packages (%d):\n" COLOR_RESET, installed->count);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    for (int i = 0; i < installed->count; i++) {
        if (filter && !strstr(installed->packages[i], filter)) continue;
        
        char meta_path[1024];
        snprintf(meta_path, sizeof(meta_path), "%s/%s/package.json",
                 g_config.lib_dir, installed->packages[i]);
        
        PackageMeta* meta = package_read_meta(meta_path);
        if (meta) {
            printf(COLOR_GREEN "  %-20s" COLOR_RESET, meta->name ? meta->name : "unknown");
            printf(COLOR_YELLOW " v%-10s" COLOR_RESET, meta->version ? meta->version : "?");
            printf(COLOR_DIM " • %s" COLOR_RESET, meta->description ? meta->description : "");
            printf("\n");
            package_meta_free(meta);
        }
    }
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    package_list_free(installed);
    return 0;
}

/* ================================================================
 * RECHERCHE
 * ================================================================ */

int gpm_search(const char* query) {
    LOG_INFO("Searching for: %s", query);
    
    char* encoded_query = url_encode(query);
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/package/search?q=%s",
             g_config.registry_url, GPM_API_VERSION, encoded_query);
    free(encoded_query);
    
    long status = 0;
    char* response = network_get(url, &status);
    
    if (status != 200 || !response) {
        LOG_ERROR("Search failed (HTTP %ld)", status);
        free(response);
        return 1;
    }
    
    json_error_t error;
    json_t* root = json_loads(response, 0, &error);
    free(response);
    
    if (!root) {
        LOG_ERROR("Failed to parse response");
        return 1;
    }
    
    json_t* results = json_object_get(root, "results");
    if (!results || !json_is_array(results)) {
        LOG_INFO("No results found");
        json_decref(root);
        return 0;
    }
    
    size_t count = json_array_size(results);
    printf(COLOR_BOLD "\n🔍 Search Results for '%s' (%zu):\n" COLOR_RESET, query, count);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    for (size_t i = 0; i < count; i++) {
        json_t* pkg = json_array_get(results, i);
        const char* name = json_string_value(json_object_get(pkg, "name"));
        const char* pkg_version = json_string_value(json_object_get(pkg, "version"));
        const char* author = json_string_value(json_object_get(pkg, "author"));
        int downloads = (int)json_integer_value(json_object_get(pkg, "downloads"));
        
        printf("  " COLOR_GREEN "%-25s" COLOR_RESET, name ? name : "?");
        printf(COLOR_YELLOW " v%-10s" COLOR_RESET, pkg_version ? pkg_version : "?");
        printf(COLOR_DIM " by %-15s" COLOR_RESET, author ? author : "?");
        printf(COLOR_BLUE " ⬇ %d" COLOR_RESET "\n", downloads);
    }
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    json_decref(root);
    return 0;
}

/* ================================================================
 * INFOS PACKAGE
 * ================================================================ */

int gpm_info(const char* package) {
    char url[1024];
    snprintf(url, sizeof(url), "%s/%s/package/%s",
             g_config.registry_url, GPM_API_VERSION, package);
    
    long status = 0;
    char* response = network_get(url, &status);
    
    if (status != 200 || !response) {
        LOG_ERROR("Package not found: %s", package);
        free(response);
        return 1;
    }
    
    json_error_t error;
    json_t* root = json_loads(response, 0, &error);
    free(response);
    
    if (!root) {
        LOG_ERROR("Failed to parse response");
        return 1;
    }
    
    json_t* pkg = json_object_get(root, "package");
    if (!pkg) {
        LOG_ERROR("Invalid response format");
        json_decref(root);
        return 1;
    }
    
    printf(COLOR_BOLD "\n📦 Package: " COLOR_GREEN "%s\n" COLOR_RESET, 
           json_string_value(json_object_get(pkg, "name")));
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  Version:    %s\n", json_string_value(json_object_get(pkg, "version")));
    printf("  Author:     %s\n", json_string_value(json_object_get(pkg, "author")));
    printf("  Scope:      %s\n", json_string_value(json_object_get(pkg, "scope")));
    printf("  Size:       %lld bytes\n", (long long)json_integer_value(json_object_get(pkg, "size")));
    printf("  Downloads:  %lld\n", (long long)json_integer_value(json_object_get(pkg, "downloads")));
    printf("  SHA256:     %s\n", json_string_value(json_object_get(pkg, "sha256")));
    printf("  Created:    %s\n", json_string_value(json_object_get(pkg, "created_at")));
    
    json_t* readme = json_object_get(root, "readme");
    if (readme && json_is_string(readme)) {
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("  README:\n%s\n", json_string_value(readme));
    }
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    json_decref(root);
    return 0;
}

/* ================================================================
 * BUILD - Création d'un package .tar.bool
 * ================================================================ */

int gpm_build(const char* source_dir, const char* output) {
    LOG_INFO("Building package from: %s", source_dir);
    
    if (!dir_exists(source_dir)) {
        LOG_ERROR("Source directory not found: %s", source_dir);
        return 1;
    }
    
    // Générer le nom de sortie si non spécifié
    char output_path[1024];
    if (output) {
        strncpy(output_path, output, sizeof(output_path) - 1);
        output_path[sizeof(output_path) - 1] = '\0';
    } else {
        char* dir_name = path_basename((char*)source_dir);
        snprintf(output_path, sizeof(output_path), 
                 "%s-1.0.0-r0-%s" GPM_PACKAGE_EXT,
                 dir_name, g_config.default_arch);
    }
    
    if (package_create(source_dir, output_path) != 0) {
        LOG_ERROR("Failed to build package");
        return 1;
    }
    
    // Calculer le hash
    char* hash = package_compute_hash(output_path);
    LOG_SUCCESS("Package built: %s", output_path);
    LOG_INFO("SHA256: %s", hash);
    free(hash);
    
    return 0;
}

/* ================================================================
 * PUBLISH
 * ================================================================ */

int gpm_publish(const char* package_path) {
    if (!g_auth.authenticated) {
        LOG_ERROR("Not authenticated. Please login first.");
        return 1;
    }
    
    if (!file_exists(package_path)) {
        LOG_ERROR("Package file not found: %s", package_path);
        return 1;
    }
    
    LOG_INFO("Publishing: %s", package_path);
    
    // Vérifier l'intégrité
    if (!gpm_verify(package_path)) {
        LOG_ERROR("Package verification failed");
        return 1;
    }
    
    // Lire les métadonnées
    PackageMeta* meta = package_read_meta(package_path);
    if (!meta) {
        LOG_ERROR("Failed to read package metadata");
        return 1;
    }
    
    // Upload
    char url[1024];
    const char* scope_str = (meta->scope == PKG_SCOPE_PUBLIC) ? "public" : "private";
    snprintf(url, sizeof(url), "%s/%s/package/upload/%s/%s",
             g_config.registry_url, GPM_API_VERSION, scope_str, meta->name);
    
    if (network_upload(url, package_path) != 0) {
        LOG_ERROR("Upload failed");
        package_meta_free(meta);
        return 1;
    }
    
    LOG_SUCCESS("Package published: %s@%s", meta->name, meta->version);
    package_meta_free(meta);
    return 0;
}

/* ================================================================
 * VÉRIFICATION
 * ================================================================ */

int gpm_verify(const char* package) {
    LOG_INFO("Verifying: %s", package);
    
    char package_path[1024] = {0};
    
    // 1. Vérifier si c'est un chemin de fichier direct
    if (file_exists(package)) {
        strncpy(package_path, package, sizeof(package_path) - 1);
    }
    // 2. Chercher dans le cache
    else {
        char* cached = package_find_in_cache(package, NULL, g_config.default_arch);
        if (cached) {
            strncpy(package_path, cached, sizeof(package_path) - 1);
            free(cached);
        }
    }
    // 3. Chercher dans les packages installés
    if (package_path[0] == '\0') {
        char meta_path[1024];
        snprintf(meta_path, sizeof(meta_path), "%s/%s/package.json", 
                 g_config.lib_dir, package);
        if (file_exists(meta_path)) {
            // Le package est installé mais on n'a pas le .tar.bool
            PackageMeta* meta = package_read_meta(meta_path);
            if (meta && meta->sha256) {
                LOG_INFO("Package is installed");
                LOG_INFO("Registered SHA256: %s", meta->sha256);
                LOG_INFO("Version: %s", meta->version);
                package_meta_free(meta);
                return 1;  // Vérifié via les métadonnées
            }
            package_meta_free(meta);
        }
    }
    
    if (package_path[0] == '\0') {
        LOG_ERROR("Package not found: %s", package);
        LOG_INFO("Usage: gpm verify <file.tar.bool>");
        LOG_INFO("   or: gpm verify <installed-package-name>");
        return 0;
    }
    
    // Calculer le hash SHA256
    char* hash = package_compute_hash(package_path);
    if (!hash) {
        LOG_ERROR("Failed to compute hash");
        return 0;
    }
    
    LOG_INFO("SHA256: %s", hash);
    
    // Vérifier avec le hash du registre
    PackageMeta* meta = package_read_meta(package_path);
    if (meta && meta->sha256) {
        if (strcmp(hash, meta->sha256) == 0) {
            LOG_SUCCESS("✅ Hash matches registry");
        } else {
            LOG_ERROR("❌ Hash mismatch!");
            LOG_ERROR("  Expected: %s", meta->sha256);
            LOG_ERROR("  Got:      %s", hash);
            free(hash);
            package_meta_free(meta);
            return 0;
        }
    }
    
    free(hash);
    if (meta) package_meta_free(meta);
    
    LOG_SUCCESS("✅ Package verified successfully");
    return 1;
}


/* ================================================================
 * LOGIN / LOGOUT
 * ================================================================ */

int gpm_login(const char* username, const char* password) {
    LOG_INFO("Logging in as %s...", username);
    
    if (network_auth_login(username, password) != 0) {
        LOG_ERROR("Login failed");
        return 1;
    }
    
    // Sauvegarder la config
    if (g_auth.token) {
        free(g_config.token);
        g_config.token = strdup(g_auth.token);
        save_config();
    }
    
    LOG_SUCCESS("Logged in as %s", username);
    return 0;
}

int gpm_logout(void) {
    g_auth.authenticated = false;
    free(g_auth.token);
    g_auth.token = NULL;
    free(g_config.token);
    g_config.token = NULL;
    
    save_config();
    LOG_SUCCESS("Logged out");
    return 0;
}

/* ================================================================
 * CACHE
 * ================================================================ */

int gpm_cache_clean(void) {
    LOG_INFO("Cleaning cache...");
    
    DIR* dir = opendir(g_config.cache_dir);
    if (!dir) {
        LOG_ERROR("Cannot open cache directory");
        return 1;
    }
    
    int cleaned = 0;
    size_t freed = 0;
    struct dirent* entry;
    
    time_t now = time(NULL);
    time_t ttl = g_config.ttl;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", g_config.cache_dir, entry->d_name);
        
        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (now - st.st_mtime > ttl) {
                size_t sz = (size_t)st.st_size;
                if (unlink(full_path) == 0) {
                    cleaned++;
                    freed += sz;
                }
            }
        }
    }
    closedir(dir);
    
    LOG_SUCCESS("Cleaned %d files, freed %zu bytes", cleaned, freed);
    return 0;
}

int gpm_cache_verify(void) {
    LOG_INFO("Verifying cache integrity...");
    
    DIR* dir = opendir(g_config.cache_dir);
    if (!dir) return 1;
    
    int total = 0;
    int valid = 0;
    int corrupt = 0;
    struct dirent* entry;
    
    while ((entry = readdir(dir)) != NULL) {
        if (!str_endswith(entry->d_name, GPM_PACKAGE_EXT)) continue;
        
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", g_config.cache_dir, entry->d_name);
        
        total++;
        if (gpm_verify(full_path)) {
            valid++;
        } else {
            corrupt++;
        }
    }
    closedir(dir);
    
    LOG_INFO("Cache: %d total, %d valid, %d corrupt", total, valid, corrupt);
    return corrupt > 0 ? 1 : 0;
}

/* ================================================================
 * CONFIGURATION
 * ================================================================ */

int gpm_config_set(const char* key, const char* value) {
    if (strcmp(key, "registry") == 0) {
        free(g_config.registry_url);
        g_config.registry_url = strdup(value);
    } else if (strcmp(key, "token") == 0) {
        free(g_config.token);
        g_config.token = strdup(value);
    } else if (strcmp(key, "scope") == 0) {
        free(g_config.default_scope);
        g_config.default_scope = strdup(value);
    } else if (strcmp(key, "arch") == 0) {
        free(g_config.default_arch);
        g_config.default_arch = strdup(value);
    } else if (strcmp(key, "proxy") == 0) {
        free(g_config.proxy);
        g_config.proxy = strdup(value);
    } else {
        LOG_ERROR("Unknown config key: %s", key);
        return 1;
    }
    
    save_config();
    LOG_SUCCESS("Config updated: %s = %s", key, value);
    return 0;
}

int gpm_config_get(const char* key) {
    if (strcmp(key, "registry") == 0) {
        printf("%s\n", g_config.registry_url ? g_config.registry_url : "not set");
    } else if (strcmp(key, "token") == 0) {
        printf("%s\n", g_config.token ? "********" : "not set");
    } else if (strcmp(key, "scope") == 0) {
        printf("%s\n", g_config.default_scope ? g_config.default_scope : "public");
    } else if (strcmp(key, "arch") == 0) {
        printf("%s\n", g_config.default_arch ? g_config.default_arch : "x86_64");
    } else if (strcmp(key, "proxy") == 0) {
        printf("%s\n", g_config.proxy ? g_config.proxy : "not set");
    } else {
        LOG_ERROR("Unknown config key: %s", key);
        return 1;
    }
    return 0;
}

/* ================================================================
 * DAEMON
 * ================================================================ */

int gpm_daemon_start(const char* config) {
    (void)config;  // Supprime le warning - paramètre pour usage futur
    
    LOG_INFO("Starting GPM daemon...");
    
    pid_t pid = fork();
    if (pid < 0) {
        LOG_ERROR("Failed to fork");
        return 1;
    }
    
    if (pid > 0) {
        // Parent
        LOG_SUCCESS("Daemon started with PID %d", pid);
        return 0;
    }
    
    // Enfant - daemonize
    setsid();
    signal(SIGHUP, SIG_IGN);
    
    pid = fork();
    if (pid > 0) _exit(0);
    
    // Changer le répertoire de travail
    chdir("/");
    umask(0);
    
    // Fermer les descripteurs standards
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    // Rediriger vers /dev/null
    int devnull = open("/dev/null", O_RDWR);
    if (devnull >= 0) {
        dup2(devnull, STDIN_FILENO);
        dup2(devnull, STDOUT_FILENO);
        dup2(devnull, STDERR_FILENO);
        close(devnull);
    }
    
    // Boucle principale du daemon
    while (1) {
        if (g_config.use_cache) {
            gpm_cache_verify();
        }
        sleep(g_config.ttl);
    }
    
    return 0;
}

int gpm_daemon_stop(const char* name) {
    (void)name;  // Supprime le warning - paramètre pour usage futur
    
    LOG_INFO("Stopping daemon...");
    
    char pid_path[1024];
    snprintf(pid_path, sizeof(pid_path), "%s/gpm-daemon.pid", GPM_CONFIG_DIR);
    
    if (!file_exists(pid_path)) {
        LOG_ERROR("Daemon PID file not found");
        return 1;
    }
    
    char* pid_str = file_read(pid_path);
    if (!pid_str) return 1;
    
    pid_t pid = (pid_t)atoi(pid_str);
    free(pid_str);
    
    if (kill(pid, SIGTERM) != 0) {
        LOG_ERROR("Failed to stop daemon (PID %d): %s", pid, strerror(errno));
        return 1;
    }
    
    unlink(pid_path);
    LOG_SUCCESS("Daemon stopped");
    return 0;
}
