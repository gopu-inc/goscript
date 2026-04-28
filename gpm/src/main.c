#include "gpm.h"

/* ================================================================
 * AFFICHAGE DE LA BANNIÈRE
 * ================================================================ */

static void print_banner(void) {
    printf("\n");
    printf(COLOR_CYAN COLOR_BOLD);
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║   GPM v%s - Goscript Package Manager             ║\n", GPM_VERSION);
    printf("║   (npm-compatible package manager)              ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");
    printf(COLOR_RESET "\n");
}

static void print_help(void) {
    print_banner();
    printf(COLOR_BOLD "USAGE:\n" COLOR_RESET);
    printf("  gpm <command> [options] [arguments]\n\n");
    
    printf(COLOR_BOLD "COMMANDS:\n" COLOR_RESET);
    printf("  " COLOR_GREEN "init" COLOR_RESET "                    Initialize a new package\n");
    printf("  " COLOR_GREEN "install, i" COLOR_RESET "   [pkg]    Install packages\n");
    printf("  " COLOR_GREEN "uninstall, rm" COLOR_RESET " <pkg>   Remove a package\n");
    printf("  " COLOR_GREEN "update, up" COLOR_RESET "   [pkg]    Update packages\n");
    printf("  " COLOR_GREEN "list, ls" COLOR_RESET "              List installed packages\n");
    printf("  " COLOR_GREEN "search, s" COLOR_RESET "   <query>   Search packages\n");
    printf("  " COLOR_GREEN "publish" COLOR_RESET "                 Publish to registry\n");
    printf("  " COLOR_GREEN "build" COLOR_RESET "                   Build package\n");
    printf("  " COLOR_GREEN "login" COLOR_RESET "        <user> <pass>  Authenticate\n");
    printf("  " COLOR_GREEN "run" COLOR_RESET "          <script> Execute script\n");
    printf("  " COLOR_GREEN "doctor" COLOR_RESET "                 Check installation\n");
    printf("  " COLOR_GREEN "help" COLOR_RESET "                   Show this help\n\n");
    
    printf(COLOR_BOLD "OPTIONS:\n" COLOR_RESET);
    printf("  --global, -g          Global install\n");
    printf("  --save-dev, -D        Save as dev dependency\n");
    printf("  --production          Production only (no dev deps)\n");
    printf("  --force, -f           Force operation\n");
    printf("  --debug, -d           Debug mode\n\n");
    
    printf(COLOR_BOLD "EXAMPLES:\n" COLOR_RESET);
    printf("  gpm init my-project\n");
    printf("  gpm install\n");
    printf("  gpm install http\n");
    printf("  gpm install http@1.2.3\n");
    printf("  gpm install --save-dev fs\n");
    printf("  gpm publish\n");
    printf("  gpm run build\n\n");
}

/* ================================================================
 * POINT D'ENTRÉE PRINCIPAL
 * ================================================================ */

int main(int argc, char** argv) {
    // Initialiser la configuration
    gpm_config_init();
    gpm_config_load();
    
    // Pas d'arguments = aide
    if (argc < 2) {
        print_help();
        return 0;
    }
    
    // Parser les options globales
    int arg_idx = 1;
    while (arg_idx < argc && argv[arg_idx][0] == '-') {
        if (strcmp(argv[arg_idx], "--debug") == 0 || strcmp(argv[arg_idx], "-d") == 0) {
            gpm_config.debug = true;
        } else if (strcmp(argv[arg_idx], "--force") == 0 || strcmp(argv[arg_idx], "-f") == 0) {
            gpm_config.force = true;
        } else if (strcmp(argv[arg_idx], "--global") == 0 || strcmp(argv[arg_idx], "-g") == 0) {
            gpm_config.global = true;
        } else if (strcmp(argv[arg_idx], "--save-dev") == 0 || strcmp(argv[arg_idx], "-D") == 0) {
            gpm_config.save_dev = true;
        } else if (strcmp(argv[arg_idx], "--production") == 0) {
            gpm_config.production = true;
        } else if (strcmp(argv[arg_idx], "--help") == 0 || strcmp(argv[arg_idx], "-h") == 0) {
            print_help();
            return 0;
        }
        arg_idx++;
    }
    
    // Plus d'arguments après les flags ?
    if (arg_idx >= argc) {
        print_help();
        return 0;
    }
    
    char* command = argv[arg_idx++];
    int result = 0;
    
    // Initialiser curl
    curl_global_init(CURL_GLOBAL_ALL);
    
    // Exécuter la commande
    if (strcmp(command, "init") == 0) {
        char* name = (arg_idx < argc) ? argv[arg_idx++] : NULL;
        char* version = (arg_idx < argc) ? argv[arg_idx++] : NULL;
        result = gpm_init_project(name, version);
    }
    else if (strcmp(command, "install") == 0 || strcmp(command, "i") == 0) {
        if (arg_idx < argc && argv[arg_idx][0] != '-') {
            char* pkg = argv[arg_idx++];
            char* ver = (arg_idx < argc && argv[arg_idx][0] != '-') ? argv[arg_idx++] : NULL;
            result = gpm_install_package(pkg, ver);
        } else {
            result = gpm_install_from_manifest();
        }
    }
    else if (strcmp(command, "uninstall") == 0 || strcmp(command, "rm") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Nom du package requis");
            result = 1;
        } else {
            result = gpm_uninstall_package(argv[arg_idx++]);
        }
    }
    else if (strcmp(command, "update") == 0 || strcmp(command, "up") == 0) {
        if (arg_idx < argc && argv[arg_idx][0] != '-') {
            result = gpm_update_package(argv[arg_idx++]);
        }
    }
    else if (strcmp(command, "list") == 0 || strcmp(command, "ls") == 0) {
        // Lister les packages installés
        printf(COLOR_BOLD "\n📦 Packages installés dans gpm_modules:\n" COLOR_RESET);
        system("ls -la gpm_modules/ 2>/dev/null || echo '  (aucun)'");
        printf("\n");
    }
    else if (strcmp(command, "search") == 0 || strcmp(command, "s") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Terme de recherche requis");
            result = 1;
        } else {
            LOG_INFO("Recherche de '%s'...", argv[arg_idx]);
            printf("  (fonctionnalité à implémenter)\n");
        }
    }
    else if (strcmp(command, "publish") == 0) {
        result = gpm_publish();
    }
    else if (strcmp(command, "build") == 0) {
        result = gpm_build_package();
    }
    else if (strcmp(command, "login") == 0) {
        if (arg_idx + 1 >= argc) {
            LOG_ERROR("Utilisateur et mot de passe requis");
            result = 1;
        } else {
            result = gpm_login(argv[arg_idx], argv[arg_idx + 1]);
        }
    }
    else if (strcmp(command, "run") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Nom du script requis");
            result = 1;
        } else {
            result = gpm_run_script(argv[arg_idx]);
        }
    }
    else if (strcmp(command, "doctor") == 0) {
        printf(COLOR_BOLD "\n🩺 GPM Doctor\n" COLOR_RESET);
        printf("───────────────────────────────────────────\n");
        printf("Version: " COLOR_GREEN "v%s" COLOR_RESET "\n", GPM_VERSION);
        printf("Registry: %s\n", gpm_config.registry_url);
        printf("Cache: %s\n", gpm_config.cache_dir);
        printf("Global dir: %s\n", gpm_config.global_dir);
        printf("Connectivité: ");
        if (gpm_network_check()) {
            printf(COLOR_GREEN "OK" COLOR_RESET "\n");
        } else {
            printf(COLOR_RED "Échec" COLOR_RESET "\n");
        }
        printf("───────────────────────────────────────────\n\n");
    }
    else {
        LOG_ERROR("Commande inconnue: %s", command);
        print_help();
        result = 1;
    }
    
    // Sauvegarder la configuration
    gpm_config_save();
    
    // Nettoyer
    curl_global_cleanup();
    
    return result;
}
