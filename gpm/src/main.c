#include "../gpm.h"

static GPMConfig* global_config = NULL;
static volatile int running = 1;

// ============================================================================
// AIDE
// ============================================================================
static void print_help(void) {
    printf(COLOR_BOLD COLOR_CYAN "GPM - Goscript Package Manager v%s" COLOR_RESET "\n", GPM_VERSION);
    printf("Codename: " COLOR_YELLOW "%s" COLOR_RESET "\n\n", GPM_CODENAME);
    
    printf(COLOR_BOLD "USAGE:" COLOR_RESET "\n");
    printf("  gpm [global-options] <command> [command-options]\n\n");
    
    printf(COLOR_BOLD "GLOBAL OPTIONS:" COLOR_RESET "\n");
    printf("  -v, --verbose        Verbose output\n");
    printf("  -q, --quiet          Quiet mode\n");
    printf("  -f, --force          Force operation\n");
    printf("  -d, --debug          Debug mode\n");
    printf("  --dry-run            Simulate operation\n");
    printf("  --no-cache           Disable cache\n");
    printf("  --offline            Offline mode\n");
    printf("  --proxy <url>        Use proxy\n");
    printf("  --registry <url>     Custom registry URL\n");
    printf("  --arch <arch>        Override architecture\n");
    printf("  -y, --yes            Assume yes to prompts\n\n");
    
    printf(COLOR_BOLD "COMMANDS:" COLOR_RESET "\n");
    printf("  install <pkg> [ver]  Install package\n");
    printf("  uninstall <pkg>      Uninstall package\n");
    printf("  update [pkg]         Update packages\n");
    printf("  search <query>       Search packages\n");
    printf("  list                 List installed packages\n");
    printf("  info <pkg>           Show package info\n");
    printf("  login                Log in to registry\n");
    printf("  logout               Log out\n");
    printf("  publish <dir>        Publish a package\n");
    printf("  doctor               System diagnostics\n");
    printf("  cache clean          Clean package cache\n");
    printf("  version              Show version\n");
    printf("  help                 Show this help\n\n");
    
    printf(COLOR_BOLD "EXAMPLES:" COLOR_RESET "\n");
    printf("  gpm install httplib\n");
    printf("  gpm install httplib 1.2.0\n");
    printf("  gpm search json\n");
    printf("  gpm doctor\n");
    printf("  gpm publish ./my-module\n");
}

// ============================================================================
// COMMAND HANDLERS
// ============================================================================
static int cmd_doctor(void) {
    printf(COLOR_BOLD COLOR_CYAN "\n🩺 GPM SYSTEM DIAGNOSTICS" COLOR_RESET "\n");
    printf("═══════════════════════════════════════\n\n");
    
    macro_print_build_info();
    
    SystemInfo* info = get_system_info();
    if (info) {
        print_system_info(info);
        free_system_info(info);
    }
    
    // Check dependencies
    printf(COLOR_BOLD "📦 DEPENDENCIES:" COLOR_RESET "\n");
    const char* deps[] = {"curl", "openssl", "tar", "gcc", "make", "cmake", "python3", "git", NULL};
    for (int i = 0; deps[i]; i++) {
        char* path = sh_which(deps[i]);
        printf("  %-15s %s\n", deps[i], path ? COLOR_GREEN "✓ FOUND" COLOR_RESET : COLOR_RED "✗ MISSING" COLOR_RESET);
        if (path) free(path);
    }
    
    // Check directories
    printf(COLOR_BOLD "\n📁 DIRECTORIES:" COLOR_RESET "\n");
    const char* dirs[] = {GPM_ROOT, GPM_LIB_DIR, GPM_CACHE_DIR, GPM_MODULES_DIR, GPM_PACKAGES_DIR};
    for (int i = 0; dirs[i]; i++) {
        printf("  %-45s %s\n", dirs[i], 
               dir_exists(dirs[i]) ? COLOR_GREEN "✓ EXISTS" COLOR_RESET : COLOR_YELLOW "⟳ WILL BE CREATED" COLOR_RESET);
    }
    
    // Check auth
    printf(COLOR_BOLD "\n🔐 AUTHENTICATION:" COLOR_RESET "\n");
    AuthCredentials* auth = auth_load();
    if (auth && auth->token[0]) {
        printf(COLOR_GREEN "  ✓ Logged in as %s (role: %s)" COLOR_RESET "\n", auth->username, auth->role);
    } else {
        printf(COLOR_YELLOW "  ⚠ Not logged in. Run 'gpm login'" COLOR_RESET "\n");
    }
    if (auth) auth_free(auth);
    
    // Check network
    printf(COLOR_BOLD "\n🌐 NETWORK:" COLOR_RESET "\n");
    char* test = protocol_api_get("/", NULL);
    if (test) {
        printf(COLOR_GREEN "  ✓ Registry reachable" COLOR_RESET "\n");
        free(test);
    } else {
        printf(COLOR_RED "  ✗ Registry unreachable" COLOR_RESET "\n");
    }
    
    printf("\n═══════════════════════════════════════\n");
    return 0;
}

// ============================================================================
// MAIN
// ============================================================================
int main(int argc, char** argv) {
    signal(SIGINT, gpm_signal_handler);
    signal(SIGTERM, gpm_signal_handler);
    
    // Init config
    global_config = config_init_default();
    int cmd_index = config_parse_args(global_config, argc, argv);
    
    if (cmd_index >= argc) {
        print_help();
        config_free(global_config);
        return 0;
    }
    
    char* command = argv[cmd_index];
    
    // Init subsystems
    gpm_init(global_config);
    
    int result = 0;
    
    if (strcmp(command, "install") == 0 || strcmp(command, "i") == 0) {
        if (cmd_index + 1 >= argc) {
            print_error("Package name required");
            result = GPM_ERROR;
        } else {
            char* name = argv[cmd_index + 1];
            char* version = (cmd_index + 2 < argc) ? argv[cmd_index + 2] : NULL;
            AuthCredentials* auth = auth_load();
            result = install_package(name, version, auth, global_config);
            if (auth) auth_free(auth);
        }
    }
    else if (strcmp(command, "search") == 0 || strcmp(command, "s") == 0) {
        if (cmd_index + 1 >= argc) {
            print_error("Search query required");
            result = GPM_ERROR;
        } else {
            AuthCredentials* auth = auth_load();
            PackageIndex* results = NULL;
            result = protocol_search(argv[cmd_index + 1], &results, auth);
            if (result == GPM_OK && results) {
                print_success("Found %d packages:", results->count);
                for (int i = 0; i < results->count; i++) {
                    printf("  " COLOR_GREEN "%-30s" COLOR_RESET " v%-10s by %s\n",
                           results->packages[i]->name,
                           results->packages[i]->version,
                           results->packages[i]->author);
                }
            }
            if (auth) auth_free(auth);
        }
    }
    else if (strcmp(command, "login") == 0) {
        char username[MAX_USERNAME] = {0};
        char password[MAX_PASSWORD] = {0};
        
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        str_trim(username);
        
        printf("Password: ");
        sh_exec("stty -echo");
        fgets(password, sizeof(password), stdin);
        sh_exec("stty echo");
        printf("\n");
        str_trim(password);
        
        result = auth_login(username, password);
    }
    else if (strcmp(command, "logout") == 0) {
        result = auth_logout();
    }
    else if (strcmp(command, "doctor") == 0) {
        result = cmd_doctor();
    }
    else if (strcmp(command, "version") == 0 || strcmp(command, "--version") == 0 || strcmp(command, "-V") == 0) {
        macro_print_build_info();
    }
    else if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0 || strcmp(command, "-h") == 0) {
        print_help();
    }
    else if (strcmp(command, "list") == 0 || strcmp(command, "ls") == 0) {
        list_installed_packages();
    }
    else if (strcmp(command, "uninstall") == 0 || strcmp(command, "remove") == 0) {
        if (cmd_index + 1 >= argc) {
            print_error("Package name required");
            result = GPM_ERROR;
        } else {
            result = uninstall_package(argv[cmd_index + 1], global_config);
        }
    }
    else if (strcmp(command, "cache") == 0) {
        if (cmd_index + 1 < argc && strcmp(argv[cmd_index + 1], "clean") == 0) {
            cache_clean(CACHE_TTL);
            print_success("Cache cleaned");
        } else {
            print_help();
        }
    }
    else {
        print_error("Unknown command: %s", command);
        print_help();
        result = GPM_ERROR;
    }
    
    gpm_shutdown();
    config_free(global_config);
    
    return result;
}
