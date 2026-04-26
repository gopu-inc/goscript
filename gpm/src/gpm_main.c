/* ================================================================
 * gpm_main.c - Point d'entrée principal de GPM
 * ================================================================ */

#include "gpm.h"

/* ================================================================
 * VARIABLES GLOBALES
 * ================================================================ */

GPMConfig g_config = {0};
AuthContext g_auth = {0};

/* ================================================================
 * DÉCLARATIONS FORWARD
 * ================================================================ */

extern void package_meta_free(PackageMeta* meta);
extern void package_list_free(PackageList* list);
extern char* strdup(const char* s);

/* ================================================================
 * INITIALISATION DE LA CONFIGURATION
 * ================================================================ */

void init_config(void) {
    g_config.registry_url = strdup(GPM_DEFAULT_REGISTRY);
    g_config.cache_dir = strdup(GPM_CACHE_DIR);
    g_config.lib_dir = strdup(GPM_LIB_DIR);
    g_config.default_scope = strdup("public");
    g_config.default_arch = NULL;
    g_config.token = NULL;
    g_config.proxy = NULL;
    g_config.timeout = GPM_TIMEOUT;
    g_config.retry_count = GPM_RETRY_COUNT;
    g_config.max_parallel = GPM_MAX_PARALLEL;
    g_config.verify_ssl = true;
    g_config.debug = false;
    g_config.force = false;
    g_config.yes = false;
    g_config.no_color = false;
    g_config.offline = false;
    g_config.use_cache = true;
    g_config.sandbox = false;
    g_config.daemon_mode = false;
    g_config.ttl = GPM_TTL_DEFAULT;
    g_config.nginx_conf = NULL;
    g_config.kernel_version = NULL;
    g_config.registries = NULL;
    g_config.registry_count = 0;
    
    // Déterminer l'architecture par défaut
    ArchType arch = get_cpu_arch();
    switch (arch) {
        case ARCH_X86_64:  g_config.default_arch = strdup("x86_64"); break;
        case ARCH_I686:    g_config.default_arch = strdup("i686"); break;
        case ARCH_AARCH64: g_config.default_arch = strdup("aarch64"); break;
        case ARCH_ARMV7L:  g_config.default_arch = strdup("armv7l"); break;
        case ARCH_RISCV64: g_config.default_arch = strdup("riscv64"); break;
        default:           g_config.default_arch = strdup("x86_64"); break;
    }
    
    // Initialiser l'authentification
    g_auth.username = NULL;
    g_auth.token = NULL;
    g_auth.refresh_token = NULL;
    g_auth.email = NULL;
    g_auth.auth_method = AUTH_NONE;
    g_auth.token_expiry = 0;
    g_auth.authenticated = false;
    g_auth.ssh_key_path = NULL;
    g_auth.pgp_key_id = NULL;
}

/* ================================================================
 * CHARGEMENT DE LA CONFIGURATION
 * ================================================================ */

void load_config(void) {
    char config_path[1024];
    const char* home = getenv("HOME");
    if (home) {
        snprintf(config_path, sizeof(config_path), "%s/.gpmrc", home);
    } else {
        snprintf(config_path, sizeof(config_path), "/root/.gpmrc");
    }
    
    if (!file_exists(config_path)) {
        snprintf(config_path, sizeof(config_path), "%s/%s", 
                 GPM_CONFIG_DIR, GPM_CONFIG_FILE);
    }
    
    if (!file_exists(config_path)) return;
    
    FILE* f = fopen(config_path, "r");
    if (!f) return;
    
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        char* trimmed = str_trim(line);
        if (trimmed[0] == '#' || trimmed[0] == '\0') continue;
        
        char* equals = strchr(trimmed, '=');
        if (!equals) continue;
        
        *equals = '\0';
        char* key = str_trim(trimmed);
        char* value = str_trim(equals + 1);
        
        // Enlever les guillemets si présents
        size_t vlen = strlen(value);
        if (vlen >= 2 && (value[0] == '"' || value[0] == '\'')) {
            value[vlen - 1] = '\0';
            value++;
        }
        
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
        } else if (strcmp(key, "verify_ssl") == 0) {
            g_config.verify_ssl = strcmp(value, "true") == 0;
        } else if (strcmp(key, "timeout") == 0) {
            g_config.timeout = atoi(value);
        }
    }
    fclose(f);
}

/* ================================================================
 * SAUVEGARDE DE LA CONFIGURATION
 * ================================================================ */

void save_config(void) {
    char config_path[1024];
    const char* home = getenv("HOME");
    if (home) {
        snprintf(config_path, sizeof(config_path), "%s/.gpmrc", home);
    } else {
        snprintf(config_path, sizeof(config_path), "/root/.gpmrc");
    }
    
    FILE* f = fopen(config_path, "w");
    if (!f) return;
    
    time_t now = time(NULL);
    fprintf(f, "# GPM Configuration\n");
    fprintf(f, "# Generated: %s\n\n", ctime(&now));
    
    if (g_config.registry_url) 
        fprintf(f, "registry = \"%s\"\n", g_config.registry_url);
    if (g_config.token) 
        fprintf(f, "token = \"%s\"\n", g_config.token);
    if (g_config.default_scope) 
        fprintf(f, "scope = \"%s\"\n", g_config.default_scope);
    if (g_config.default_arch) 
        fprintf(f, "arch = \"%s\"\n", g_config.default_arch);
    if (g_config.proxy) 
        fprintf(f, "proxy = \"%s\"\n", g_config.proxy);
    fprintf(f, "verify_ssl = %s\n", g_config.verify_ssl ? "true" : "false");
    fprintf(f, "timeout = %d\n", g_config.timeout);
    
    fclose(f);
    LOG_SUCCESS("Configuration saved to %s", config_path);
}

/* ================================================================
 * AFFICHAGE
 * ================================================================ */

void print_banner(void) {
    printf(COLOR_CYAN COLOR_BOLD);
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                                                              ║\n");
    printf("║   ██████╗ ██████╗ ███╗   ███╗                               ║\n");
    printf("║  ██╔════╝ ██╔══██╗████╗ ████║                               ║\n");
    printf("║  ██║  ███╗██████╔╝██╔████╔██║                               ║\n");
    printf("║  ██║   ██║██╔═══╝ ██║╚██╔╝██║                               ║\n");
    printf("║  ╚██████╔╝██║     ██║ ╚═╝ ██║                               ║\n");
    printf("║   ╚═════╝ ╚═╝     ╚═╝     ╚═╝                               ║\n");
    printf("║                                                              ║\n");
    printf("║        GOSCRIPT PACKAGE MANAGER v%s                        ║\n", GPM_VERSION);
    printf("║        Build: %s                                ║\n", GPM_BUILD_DATE);
    printf("║                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf(COLOR_RESET "\n");
}

void print_help(void) {
    print_banner();
    printf(COLOR_BOLD "USAGE:\n" COLOR_RESET);
    printf("  gpm <command> [options] [arguments]\n\n");
    
    printf(COLOR_BOLD "COMMANDS:\n" COLOR_RESET);
    printf("  " COLOR_GREEN "install, i" COLOR_RESET "    <package> [version]  Install a package\n");
    printf("  " COLOR_GREEN "uninstall, rm" COLOR_RESET "  <package>             Uninstall a package\n");
    printf("  " COLOR_GREEN "update, up" COLOR_RESET "    [package]             Update packages\n");
    printf("  " COLOR_GREEN "search, s" COLOR_RESET "    <query>               Search packages\n");
    printf("  " COLOR_GREEN "list, ls" COLOR_RESET "     [filter]              List installed packages\n");
    printf("  " COLOR_GREEN "info, show" COLOR_RESET "   <package>             Show package info\n");
    printf("  " COLOR_GREEN "build, b" COLOR_RESET "     <source> [output]    Build a package\n");
    printf("  " COLOR_GREEN "publish, p" COLOR_RESET "   <package>             Publish a package\n");
    printf("  " COLOR_GREEN "login" COLOR_RESET "        <user> <pass>        Login to registry\n");
    printf("  " COLOR_GREEN "logout" COLOR_RESET "                            Logout\n");
    printf("  " COLOR_GREEN "verify" COLOR_RESET "      <package>             Verify package integrity\n");
    printf("  " COLOR_GREEN "rollback" COLOR_RESET "    <package> <version>    Rollback to version\n");
    printf("  " COLOR_GREEN "cache clean" COLOR_RESET "                        Clean cache\n");
    printf("  " COLOR_GREEN "cache verify" COLOR_RESET "                       Verify cache integrity\n");
    printf("  " COLOR_GREEN "config set" COLOR_RESET "   <key> <value>         Set configuration\n");
    printf("  " COLOR_GREEN "config get" COLOR_RESET "   <key>                 Get configuration\n");
    printf("  " COLOR_GREEN "daemon start" COLOR_RESET " [config]               Start daemon\n");
    printf("  " COLOR_GREEN "daemon stop" COLOR_RESET "  [name]                Stop daemon\n\n");
    
    printf(COLOR_BOLD "OPTIONS:\n" COLOR_RESET);
    printf("  --registry <url>    Set registry URL\n");
    printf("  --arch <arch>       Set target architecture\n");
    printf("  --scope <scope>     Set package scope (public/private)\n");
    printf("  --force, -f         Force operation\n");
    printf("  --yes, -y           Auto-confirm\n");
    printf("  --debug, -d         Enable debug mode\n");
    printf("  --offline           Offline mode\n");
    printf("  --no-cache          Disable cache\n");
    printf("  --no-verify         Skip SSL verification\n");
    printf("  --version, -v       Show version\n");
    printf("  --help, -h          Show this help\n\n");
    
    printf(COLOR_BOLD "EXAMPLES:\n" COLOR_RESET);
    printf("  gpm install http\n");
    printf("  gpm install fs@1.2.0\n");
    printf("  gpm search deepseek\n");
    printf("  gpm build ./my-package\n");
    printf("  gpm publish ./my-package-1.0.0-r0-x86_64.tar.bool\n");
    printf("  gpm login myuser mypassword\n");
    printf("  gpm daemon start --config /etc/gpm/nginx.conf\n\n");
    
    printf(COLOR_BOLD "REGISTRY API: " COLOR_RESET "%s/%s/\n\n", GPM_INDEX_URL, GPM_API_VERSION);
}

void print_version(void) {
    printf("GPM v%s - Goscript Package Manager\n", GPM_VERSION);
    printf("Build: %s\n", GPM_BUILD_DATE);
    printf("Registry: %s\n", g_config.registry_url ? g_config.registry_url : GPM_DEFAULT_REGISTRY);
    printf("User-Agent: %s\n", GPM_USER_AGENT);
    printf("Libcurl: %s\n", curl_version());
    printf("OpenSSL: %s\n", OpenSSL_version(OPENSSL_VERSION));
    printf("Jansson: %s\n", JANSSON_VERSION);
}

/* ================================================================
 * PARSING DES ARGUMENTS - CORRIGÉ
 * ================================================================ */

int parse_command_line(int argc, char** argv) {
    if (argc < 2) {
        print_help();
        return 1;
    }
    
    char* command = argv[1];
    
    // Vérifier les commandes spéciales sans arguments
    if (strcmp(command, "--version") == 0 || strcmp(command, "-v") == 0) {
        print_version();
        return 0;
    }
    if (strcmp(command, "--help") == 0 || strcmp(command, "-h") == 0) {
        print_help();
        return 0;
    }
    
    // PARSER LES FLAGS GLOBAUX AVANT TOUT
    int arg_idx = 2;
    while (arg_idx < argc) {
        if (strcmp(argv[arg_idx], "--force") == 0 || strcmp(argv[arg_idx], "-f") == 0) {
            g_config.force = true;
            arg_idx++;
        }
        else if (strcmp(argv[arg_idx], "--yes") == 0 || strcmp(argv[arg_idx], "-y") == 0) {
            g_config.yes = true;
            arg_idx++;
        }
        else if (strcmp(argv[arg_idx], "--debug") == 0 || strcmp(argv[arg_idx], "-d") == 0) {
            g_config.debug = true;
            arg_idx++;
        }
        else if (strcmp(argv[arg_idx], "--offline") == 0) {
            g_config.offline = true;
            arg_idx++;
        }
        else if (strcmp(argv[arg_idx], "--no-cache") == 0) {
            g_config.use_cache = false;
            arg_idx++;
        }
        else if (strcmp(argv[arg_idx], "--no-verify") == 0) {
            g_config.verify_ssl = false;
            arg_idx++;
        }
        else if (strcmp(argv[arg_idx], "--registry") == 0 && arg_idx + 1 < argc) {
            free(g_config.registry_url);
            g_config.registry_url = strdup(argv[arg_idx + 1]);
            arg_idx += 2;
        }
        else if (strcmp(argv[arg_idx], "--arch") == 0 && arg_idx + 1 < argc) {
            free(g_config.default_arch);
            g_config.default_arch = strdup(argv[arg_idx + 1]);
            arg_idx += 2;
        }
        else if (strcmp(argv[arg_idx], "--scope") == 0 && arg_idx + 1 < argc) {
            free(g_config.default_scope);
            g_config.default_scope = strdup(argv[arg_idx + 1]);
            arg_idx += 2;
        }
        else if (strcmp(argv[arg_idx], "--timeout") == 0 && arg_idx + 1 < argc) {
            g_config.timeout = atoi(argv[arg_idx + 1]);
            arg_idx += 2;
        }
        else {
            // Ce n'est pas un flag connu, c'est un argument de commande
            break;
        }
    }
    
    // Maintenant arg_idx pointe sur le premier argument de commande
    
    // === INSTALL ===
    if (strcmp(command, "install") == 0 || strcmp(command, "i") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Package name required");
            return 1;
        }
        char* package = argv[arg_idx];
        char* version = NULL;
        // Vérifier si l'argument suivant n'est pas un flag
        if (arg_idx + 1 < argc && argv[arg_idx + 1][0] != '-') {
            version = argv[arg_idx + 1];
        }
        return gpm_install(package, version);
    }
    
    // === UNINSTALL ===
    else if (strcmp(command, "uninstall") == 0 || strcmp(command, "rm") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Package name required");
            return 1;
        }
        return gpm_uninstall(argv[arg_idx]);
    }
    
    // === UPDATE ===
    else if (strcmp(command, "update") == 0 || strcmp(command, "up") == 0) {
        char* package = (arg_idx < argc && argv[arg_idx][0] != '-') ? argv[arg_idx] : NULL;
        return gpm_update(package);
    }
    
    // === SEARCH ===
    else if (strcmp(command, "search") == 0 || strcmp(command, "s") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Search query required");
            return 1;
        }
        return gpm_search(argv[arg_idx]);
    }
    
    // === LIST ===
    else if (strcmp(command, "list") == 0 || strcmp(command, "ls") == 0) {
        char* filter = (arg_idx < argc && argv[arg_idx][0] != '-') ? argv[arg_idx] : NULL;
        return gpm_list(filter);
    }
    
    // === INFO ===
    else if (strcmp(command, "info") == 0 || strcmp(command, "show") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Package name required");
            return 1;
        }
        return gpm_info(argv[arg_idx]);
    }
    
    // === BUILD ===
    else if (strcmp(command, "build") == 0 || strcmp(command, "b") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Source directory required");
            return 1;
        }
        char* source = argv[arg_idx];
        char* output = (arg_idx + 1 < argc && argv[arg_idx + 1][0] != '-') ? argv[arg_idx + 1] : NULL;
        return gpm_build(source, output);
    }
    
    // === PUBLISH ===
    else if (strcmp(command, "publish") == 0 || strcmp(command, "p") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Package path required");
            return 1;
        }
        return gpm_publish(argv[arg_idx]);
    }
    
    // === LOGIN ===
    else if (strcmp(command, "login") == 0) {
        if (arg_idx + 1 >= argc) {
            LOG_ERROR("Username and password required");
            return 1;
        }
        return gpm_login(argv[arg_idx], argv[arg_idx + 1]);
    }
    
    // === LOGOUT ===
    else if (strcmp(command, "logout") == 0) {
        return gpm_logout();
    }
    
    // === VERIFY ===
    else if (strcmp(command, "verify") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Package path required");
            return 1;
        }
        return gpm_verify(argv[arg_idx]);
    }
    
    // === ROLLBACK ===
    else if (strcmp(command, "rollback") == 0) {
        if (arg_idx + 1 >= argc) {
            LOG_ERROR("Package and version required");
            return 1;
        }
        return gpm_rollback(argv[arg_idx], argv[arg_idx + 1]);
    }
    
    // === CACHE ===
    else if (strcmp(command, "cache") == 0) {
        if (arg_idx >= argc) {
            return gpm_cache_verify();
        }
        if (strcmp(argv[arg_idx], "clean") == 0) {
            return gpm_cache_clean();
        } else if (strcmp(argv[arg_idx], "verify") == 0) {
            return gpm_cache_verify();
        }
        LOG_ERROR("Unknown cache subcommand: %s", argv[arg_idx]);
        return 1;
    }
    
    // === CONFIG ===
    else if (strcmp(command, "config") == 0) {
        if (arg_idx + 1 >= argc) {
            LOG_ERROR("Subcommand required (set/get)");
            return 1;
        }
        if (strcmp(argv[arg_idx], "set") == 0 && arg_idx + 2 < argc) {
            return gpm_config_set(argv[arg_idx + 1], argv[arg_idx + 2]);
        } else if (strcmp(argv[arg_idx], "get") == 0 && arg_idx + 1 < argc) {
            return gpm_config_get(argv[arg_idx + 1]);
        }
        LOG_ERROR("Unknown config subcommand");
        return 1;
    }
    
    // === DAEMON ===
    else if (strcmp(command, "daemon") == 0) {
        if (arg_idx >= argc) {
            LOG_ERROR("Subcommand required (start/stop)");
            return 1;
        }
        if (strcmp(argv[arg_idx], "start") == 0) {
            char* config = (arg_idx + 1 < argc && argv[arg_idx + 1][0] != '-') ? argv[arg_idx + 1] : NULL;
            return gpm_daemon_start(config);
        } else if (strcmp(argv[arg_idx], "stop") == 0) {
            char* name = (arg_idx + 1 < argc && argv[arg_idx + 1][0] != '-') ? argv[arg_idx + 1] : NULL;
            return gpm_daemon_stop(name);
        }
        LOG_ERROR("Unknown daemon subcommand: %s", argv[arg_idx]);
        return 1;
    }
    
    // === COMMANDE INCONNUE ===
    else {
        LOG_ERROR("Unknown command: %s", command);
        print_help();
        return 1;
    }
    
    return 0;
}

/* ================================================================
 * MAIN
 * ================================================================ */

int main(int argc, char** argv) {
    // Initialisation
    init_config();
    load_config();
    
    // Créer les dossiers nécessaires
    dir_create(GPM_CACHE_DIR);
    dir_create(GPM_LIB_DIR);
    dir_create(GPM_CONFIG_DIR);
    
    // Initialisation réseau
    if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
        LOG_ERROR("Failed to initialize libcurl");
        return 1;
    }
    
    // Traitement
    int result = parse_command_line(argc, argv);
    
    // Nettoyage
    curl_global_cleanup();
    
    return result;
}
