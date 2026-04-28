// gpm_core.c - Implémentation du nouveau cœur
#include "gpm.h"
#include <libgen.h>
#include <dirent.h>
#include <sys/wait.h>

// ============================================================================
// VARIABLES GLOBALES
// ============================================================================

static gpm_config_t g_config;
static sqlite3* g_db = NULL;
static pthread_mutex_t g_db_mutex = PTHREAD_MUTEX_INITIALIZER;
static CURL* g_curl = NULL;

// ============================================================================
// INITIALISATION (comme npm init)
// ============================================================================

int gpm_init_project(const char* name, const char* version) {
    printf("\n╔══════════════════════════════════════════════════╗\n");
    printf("║     GPM v%s - Package Initialization            ║\n", GPM_VERSION);
    printf("╚══════════════════════════════════════════════════╝\n\n");
    
    manifest_t manifest = {0};
    
    // Questions interactives
    char input[256];
    
    printf("package name: (%s) ", name ? name : "my-project");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    strcpy(manifest.name, input[0] ? input : (name ? name : "my-project"));
    
    printf("version: (1.0.0) ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    strcpy(manifest.version, input[0] ? input : (version ? version : "1.0.0"));
    
    printf("description: ");
    fgets(manifest.description, sizeof(manifest.description), stdin);
    manifest.description[strcspn(manifest.description, "\n")] = 0;
    
    printf("entry point: (main.gjs) ");
    fgets(manifest.main, sizeof(manifest.main), stdin);
    manifest.main[strcspn(manifest.main, "\n")] = 0;
    if (!manifest.main[0]) strcpy(manifest.main, "main.gjs");
    
    printf("author: ");
    fgets(manifest.author, sizeof(manifest.author), stdin);
    manifest.author[strcspn(manifest.author, "\n")] = 0;
    
    printf("license: (MIT) ");
    fgets(manifest.license, sizeof(manifest.license), stdin);
    manifest.license[strcspn(manifest.license, "\n")] = 0;
    if (!manifest.license[0]) strcpy(manifest.license, "MIT");
    
    // Défauts
    strcpy(manifest.release, "r0");
    strcpy(manifest.arch, "x86_64");
    
    // Générer le manifest
    return gpm_write_manifest(&manifest);
}

// ============================================================================
// RÉSOLUTION DE DÉPENDANCES (ALGORITHME INSPIRÉ DE NPM)
// ============================================================================

dep_node_t* gpm_resolve_tree(manifest_t* manifest) {
    printf("[GPM] * Resolving dependency tree...\n");
    
    dep_node_t* root = calloc(1, sizeof(dep_node_t));
    strcpy(root->name, manifest->name);
    strcpy(root->version, manifest->version);
    root->depth = 0;
    
    // Résoudre les dépendances de production
    for (int i = 0; i < manifest->dep_count; i++) {
        dependency_t* dep = &manifest->dependencies[i];
        
        // Trouver la meilleure version
        char* best_version = gpm_resolve_version(dep);
        if (!best_version) {
            printf("[GPM] [!]  Could not resolve %s\n", dep->name);
            continue;
        }
        
        // Ajouter au nœud
        dep_node_t* child = calloc(1, sizeof(dep_node_t));
        strcpy(child->name, dep->name);
        strcpy(child->version, best_version);
        child->depth = 1;
        child->is_dev = false;
        
        // Résoudre récursivement les dépendances de l'enfant
        manifest_t* child_manifest = gpm_fetch_manifest(dep->name, best_version);
        if (child_manifest) {
            dep_node_t* grandchild = gpm_resolve_tree(child_manifest);
            // Ajouter les petits-enfants
            if (grandchild->child_count > 0) {
                child->children = grandchild->children;
                child->child_count = grandchild->child_count;
            }
            gpm_free_manifest(child_manifest);
        }
        
        root->children = realloc(root->children, (root->child_count + 1) * sizeof(dep_node_t*));
        root->children[root->child_count++] = child;
        
        free(best_version);
    }
    
    // Hoisting (remonter les dépendances communes)
    gpm_hoist_dependencies(root);
    
    return root;
}

// Algorithme de hoisting comme npm
int gpm_hoist_dependencies(dep_node_t* root) {
    // Parcourir l'arbre et remonter les dépendances communes
    for (int i = 0; i < root->child_count; i++) {
        dep_node_t* child = root->children[i];
        
        // Chercher si cette dépendance existe déjà à un niveau supérieur
        dep_node_t* existing = gpm_find_in_tree(root, child->name, child->depth - 1);
        
        if (existing) {
            // Vérifier compatibilité de version
            if (gpm_version_compatible(existing->version, child->version)) {
                child->hoisted = true;
                continue;
            }
        }
        
        // Hoisting récursif
        if (child->child_count > 0) {
            gpm_hoist_dependencies(child);
        }
    }
    
    return 0;
}

// ============================================================================
// INSTALLATION AVEC NODE_MODULES (comme npm)
// ============================================================================

int gpm_install_with_deps(manifest_t* manifest) {
    printf("[GPM] {pkg} Installing dependencies...\n\n");
    
    // 1. Résoudre l'arbre
    dep_node_t* tree = gpm_resolve_tree(manifest);
    if (!tree) return -1;
    
    // 2. Aplatir (résoudre les conflits)
    gpm_flatten_tree(tree);
    
    // 3. Générer lockfile
    gpm_generate_lockfile(tree);
    
    // 4. Télécharger et installer chaque package
    dep_node_t* flat_list[1024];
    int flat_count = 0;
    gpm_flatten_to_list(tree, flat_list, &flat_count);
    
    // Créer node_modules (ou gpm_modules)
    mkdir("gpm_modules", 0755);
    
    for (int i = 0; i < flat_count; i++) {
        dep_node_t* node = flat_list[i];
        
        if (node->hoisted) continue;
        
        printf("[GPM] Installing %s@%s", node->name, node->version);
        
        char dest_path[1024];
        snprintf(dest_path, sizeof(dest_path), "gpm_modules/%s", node->name);
        
        // Télécharger
        char archive_path[512];
        snprintf(archive_path, sizeof(archive_path), "/tmp/gpm-%s-%s.tar.bool", 
                 node->name, node->version);
        
        if (gpm_download_package(node->name, node->version, archive_path) == 0) {
            // Extraire
            mkdir(dest_path, 0755);
            gpm_extract_package(archive_path, dest_path);
            unlink(archive_path);
            
            // Exécuter les scripts lifecycle
            gpm_run_lifecycle("preinstall", dest_path);
            gpm_run_lifecycle("install", dest_path);
            gpm_run_lifecycle("postinstall", dest_path);
            
            // Lier les binaires
            gpm_link_binaries(dest_path);
            
            printf(" ++\n");
        } else {
            printf(" x Failed\n");
        }
    }
    
    // 5. Créer les symlinks pour les dépendances peer
    gpm_link_peer_dependencies(tree);
    
    // 6. Vérifier l'intégrité
    gpm_verify_integrity(tree);
    
    printf("\n[GPM] ++ Installation complete!\n");
    gpm_print_summary(tree);
    
    return 0;
}

// ============================================================================
// GÉNÉRATION DE LOCKFILE (comme package-lock.json)
// ============================================================================

int gpm_generate_lockfile(dep_node_t* tree) {
    printf("[GPM] < % > Generating lockfile...\n");
    
    FILE* f = fopen(GPM_LOCKFILE, "w");
    if (!f) return -1;
    
    fprintf(f, "# GPM Lockfile v2\n");
    fprintf(f, "# Generated by GPM v%s\n", GPM_VERSION);
    fprintf(f, "# DO NOT EDIT MANUALLY\n\n");
    
    fprintf(f, "[metadata]\n");
    fprintf(f, "lockfile_version = \"2.0\"\n");
    fprintf(f, "\n");
    
    // Aplatir l'arbre
    dep_node_t* flat_list[1024];
    int flat_count = 0;
    gpm_flatten_to_list(tree, flat_list, &flat_count);
    
    for (int i = 0; i < flat_count; i++) {
        dep_node_t* node = flat_list[i];
        
        fprintf(f, "[[package]]\n");
        fprintf(f, "name = \"%s\"\n", node->name);
        fprintf(f, "version = \"%s\"\n", node->version);
        
        // URL résolue
        char url[512];
        gpm_get_package_url(node->name, node->version, url, sizeof(url));
        fprintf(f, "resolved = \"%s\"\n", url);
        
        // Intégrité (SHA512)
        char integrity[256];
        gpm_compute_integrity(node->name, node->version, integrity);
        fprintf(f, "integrity = \"%s\"\n", integrity);
        
        // Dépendances
        if (node->child_count > 0) {
            fprintf(f, "dependencies = [\n");
            for (int j = 0; j < node->child_count; j++) {
                fprintf(f, "  \"%s\",\n", node->children[j]->name);
            }
            fprintf(f, "]\n");
        }
        
        fprintf(f, "\n");
    }
    
    fclose(f);
    printf("[GPM] ++ Lockfile written to %s\n", GPM_LOCKFILE);
    return 0;
}

// ============================================================================
// PUBLICATION (comme npm publish + apsm)
// ============================================================================

int gpm_publish() {
    printf("[GPM] Preparing to publish...\n");
    
    // 1. Vérifier le manifest
    manifest_t manifest;
    if (gpm_read_manifest(&manifest) != 0) {
        printf("[GPM] No Manifest.toml found. Run 'gpm init' first.\n");
        return -1;
    }
    
    // 2. Vérifier l'authentification
    if (!g_config.authenticated) {
        printf("[GPM] Not authenticated. Run 'gpm login' first.\n");
        return -1;
    }
    
    // 3. Exécuter le script prepublish
    gpm_run_script("prepublish");
    
    // 4. Builder si nécessaire
    if (gpm_file_exists(GPM_BUILD_FILE)) {
        printf("[GPM] Building package...\n");
        gpm_build();
    }
    
    // 5. Créer l'archive (.tar.bool)
    printf("[GPM] Creating package archive...\n");
    
    char archive_name[512];
    snprintf(archive_name, sizeof(archive_name), 
             "build/%s-%s-%s.%s" GPM_PACKAGE_EXT,
             manifest.name, manifest.version, manifest.release, manifest.arch);
    
    // Créer le répertoire build si nécessaire
    mkdir("build", 0755);
    
    // Exclure les fichiers inutiles
    char cmd[2048];
    snprintf(cmd, sizeof(cmd),
             "tar --exclude='gpm_modules' --exclude='.git' --exclude='build' "
             "--exclude='.gpm' --exclude='*.tar.bool' "
             "-czf '%s' .",
             archive_name);
    
    if (system(cmd) != 0) {
        printf("[GPM] Failed to create archive\n");
        return -1;
    }
    
    // 6. Calculer SHA256
    char sha256[128];
    gpm_compute_sha256(archive_name, sha256);
    
    // 7. Uploader vers Zarch Hub
    printf("[GPM] $ Uploading to Zarch Hub...\n");
    
    char url[512];
    snprintf(url, sizeof(url), "%s/%s/package/upload/%s/%s",
             g_config.registry_url, GPM_API_VERSION, 
             g_config.scope, manifest.name);
    
    if (gpm_upload_package(url, archive_name, &manifest, g_config.auth_token) == 0) {
        printf("[GPM] ++ Package published successfully!\n");
        printf("[GPM] 📦 %s@%s\n", manifest.name, manifest.version);
        printf("[GPM] 🔗 %s/package/%s\n", g_config.registry_url, manifest.name);
        return 0;
    }
    
    printf("[GPM Publication failed\n");
    return -1;
}

// ============================================================================
// BUILD SYSTEM (intégration bool)
// ============================================================================

int gpm_build() {
    printf("[GPM] Building package...\n");
    
    // Chercher APKMBUILD ou Manifest.toml
    manifest_t manifest;
    if (gpm_read_manifest(&manifest) != 0) {
        printf("[GPM] No manifest found\n");
        return -1;
    }
    
    // Créer la structure de build
    char build_dir[512];
    snprintf(build_dir, sizeof(build_dir), "build/pkg-%s", manifest.name);
    mkdir(build_dir, 0755);
    
    // Structure standard
    char path[1024];
    snprintf(path, sizeof(path), "%s/usr/bin", build_dir);
    mkdir(path, 0755);
    
    snprintf(path, sizeof(path), "%s/usr/lib", build_dir);
    mkdir(path, 0755);
    
    // Exécuter le script de build
    if (manifest.build_cmd[0]) {
        printf("[GPM] Running build command: %s\n", manifest.build_cmd);
        if (system(manifest.build_cmd) != 0) {
            printf("[GPM] Build failed\n");
            return -1;
        }
    }
    
    // Copier les fichiers
    if (manifest.files_count > 0) {
        for (int i = 0; i < manifest.files_count; i++) {
            char src[512], dst[512];
            snprintf(src, sizeof(src), "%s", manifest.files_to_include[i]);
            snprintf(dst, sizeof(dst), "%s/%s", build_dir, manifest.files_to_include[i]);
            
            char cp_cmd[1024];
            snprintf(cp_cmd, sizeof(cp_cmd), "cp '%s' '%s'", src, dst);
            system(cp_cmd);
        }
    }
    
    // Créer l'archive
    char archive_name[512];
    snprintf(archive_name, sizeof(archive_name), 
             "build/%s-%s-%s.%s" GPM_PACKAGE_EXT,
             manifest.name, manifest.version, manifest.release, manifest.arch);
    
    char tar_cmd[2048];
    snprintf(tar_cmd, sizeof(tar_cmd), "cd '%s' && tar -czf '../%s-%s-%s.%s.tar.bool' *",
             build_dir, manifest.name, manifest.version, manifest.release, manifest.arch);
    
    system(tar_cmd);
    
    printf("[GPM]  Build complete: %s\n", archive_name);
    return 0;
}

// ============================================================================
// SCRIPTS LIFECYCLE (comme npm scripts)
// ============================================================================

int gpm_run_script(const char* script_name) {
    manifest_t manifest;
    if (gpm_read_manifest(&manifest) != 0) return -1;
    
    char* script = NULL;
    
    if (strcmp(script_name, "build") == 0) script = manifest.scripts_build;
    else if (strcmp(script_name, "test") == 0) script = manifest.scripts_test;
    else if (strcmp(script_name, "preinstall") == 0) script = manifest.scripts_preinstall;
    else if (strcmp(script_name, "install") == 0) script = manifest.scripts_install;
    else if (strcmp(script_name, "postinstall") == 0) script = manifest.scripts_postinstall;
    else if (strcmp(script_name, "prepublish") == 0) script = manifest.scripts_prepublish;
    
    if (!script || !script[0]) return 0;
    
    printf("[GPM] Running script '%s'...\n", script_name);
    printf("[GPM] > %s\n", script);
    
    return system(script);
}

// ============================================================================
// COMMANDES PRINCIPALES
// ============================================================================

int gpm_main(int argc, char** argv) {
    if (argc < 2) {
        gpm_print_help();
        return 0;
    }
    
    char* command = argv[1];
    
    if (strcmp(command, "init") == 0) {
        return gpm_init_project(argc > 2 ? argv[2] : NULL, NULL);
    }
    else if (strcmp(command, "install") == 0 || strcmp(command, "i") == 0) {
        if (argc > 2) {
            // Installer un package spécifique
            return gpm_install(argv[2], argc > 3 ? argv[3] : NULL);
        } else {
            // Installer depuis le manifest
            manifest_t manifest;
            if (gpm_read_manifest(&manifest) == 0) {
                return gpm_install_with_deps(&manifest);
            }
        }
    }
    else if (strcmp(command, "uninstall") == 0 || strcmp(command, "rm") == 0) {
        return gpm_uninstall(argv[2]);
    }
    else if (strcmp(command, "update") == 0) {
        return gpm_update(argv[2]);
    }
    else if (strcmp(command, "publish") == 0) {
        return gpm_publish();
    }
    else if (strcmp(command, "build") == 0) {
        return gpm_build();
    }
    else if (strcmp(command, "login") == 0) {
        return gpm_login(argv[2], argv[3]);
    }
    else if (strcmp(command, "search") == 0) {
        return gpm_search(argv[2]);
    }
    else if (strcmp(command, "list") == 0 || strcmp(command, "ls") == 0) {
        return gpm_list(argv[2]);
    }
    else if (strcmp(command, "run") == 0) {
        return gpm_run_script(argv[2]);
    }
    else if (strcmp(command, "doctor") == 0) {
        return gpm_doctor();
    }
    else {
        printf("[GPM] Unknown command: %s\n", command);
        gpm_print_help();
        return 1;
    }
    
    return 0;
}

// ============================================================================
// AIDE
// ============================================================================

void gpm_print_help() {
    printf("\n╔═════════════════════════════════════════════╗\n");
    printf("║     GPM v%s - Goscript Package Manager        ║\n", GPM_VERSION);
    printf("║     (npm-compatible package manager)          ║\n");
    printf("╚═══════════════════════════════════════════════╝\n\n");
    
    printf("Usage: gpm <command> [options]\n\n");
    
    printf("Commands:\n");
    printf("  init                    Create a new package\n");
    printf("  install [pkg]          Install packages\n");
    printf("  uninstall <pkg>        Remove a package\n");
    printf("  update [pkg]           Update packages\n");
    printf("  publish                Publish to Zarch Hub\n");
    printf("  build                  Build package\n");
    printf("  login <user> <pass>    Authenticate\n");
    printf("  search <query>         Search packages\n");
    printf("  list                   List installed packages\n");
    printf("  run <script>           Run lifecycle script\n");
    printf("  doctor                 Check installation\n");
    printf("  help                   Show this help\n\n");
    
    printf("Options:\n");
    printf("  --global, -g           Global install\n");
    printf("  --save, -S             Save to dependencies\n");
    printf("  --save-dev, -D         Save to devDependencies\n");
    printf("  --production           Install production only\n");
    printf("  --force, -f            Force operation\n");
    printf("  --verbose, -v          Verbose output\n");
    printf("  --debug                Debug mode\n\n");
    
    printf("Examples:\n");
    printf("  gpm init my-project\n");
    printf("  gpm install http\n");
    printf("  gpm install http@1.2.3\n");
    printf("  gpm install --save-dev fs\n");
    printf("  gpm publish\n");
    printf("  gpm build\n\n");
}

// ============================================================================
// MAIN ENTRY POINT
// ============================================================================

int main(int argc, char** argv) {
    // Initialisation
    gpm_init();
    gpm_load_config();
    
    // Parse arguments
    int result = gpm_main(argc, argv);
    
    // Cleanup
    gpm_cleanup();
    
    return result;
}
