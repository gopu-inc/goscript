#include "../gpm.h"

// ============================================================================
// RÉCUPÉRATION COMPLÈTE DES INFORMATIONS SYSTÈME
// ============================================================================
SystemInfo* get_system_info(void) {
    SystemInfo* info = calloc(1, sizeof(SystemInfo));
    if (!info) return NULL;
    
    struct utsname uts;
    if (uname(&uts) == 0) {
        strncpy(info->system, uts.sysname, sizeof(info->system) - 1);
        strncpy(info->release, uts.release, sizeof(info->release) - 1);
        strncpy(info->machine, uts.machine, sizeof(info->machine) - 1);
        strncpy(info->version, uts.version, sizeof(info->version) - 1);
        strncpy(info->kernel, uts.release, sizeof(info->kernel) - 1);
    }
    
    // Hostname
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        strncpy(info->hostname, hostname, sizeof(info->hostname) - 1);
    }
    
    // Processeur
    char* cpu_info = sh_cat("/proc/cpuinfo");
    if (cpu_info) {
        char* model = strstr(cpu_info, "model name");
        if (model) {
            model = strchr(model, ':');
            if (model) {
                model++;
                while (*model == ' ' || *model == '\t') model++;
                char* nl = strchr(model, '\n');
                if (nl) *nl = '\0';
                strncpy(info->model, str_trim(model), sizeof(info->model) - 1);
            }
        }
        
        // CPU cores
        char* cores = strstr(cpu_info, "cpu cores");
        if (cores) {
            sscanf(cores, "cpu cores : %d", &info->cpu_cores);
        }
        
        // CPU flags
        char* flags = strstr(cpu_info, "flags");
        if (flags) {
            flags = strchr(flags, ':');
            if (flags) {
                flags++;
                while (*flags == ' ' || *flags == '\t') flags++;
                char* nl = strchr(flags, '\n');
                if (nl) *nl = '\0';
                strncpy(info->cpu_flags, str_trim(flags), sizeof(info->cpu_flags) - 1);
            }
        }
        
        free(cpu_info);
    }
    
    // Mémoire RAM
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        info->total_ram = si.totalram * si.mem_unit;
        info->free_ram = si.freeram * si.mem_unit;
    }
    
    // LibC version
    char* libc = sh_exec_capture("ldd --version 2>/dev/null | head -1");
    if (libc) {
        char* nl = strchr(libc, '\n');
        if (nl) *nl = '\0';
        strncpy(info->libc_version, str_trim(libc), sizeof(info->libc_version) - 1);
        free(libc);
    }
    
    // GCC version
    char* gcc = sh_exec_capture("gcc --version 2>/dev/null | head -1");
    if (gcc) {
        char* nl = strchr(gcc, '\n');
        if (nl) *nl = '\0';
        strncpy(info->gcc_version, str_trim(gcc), sizeof(info->gcc_version) - 1);
        free(gcc);
    }
    
    // Goscript version
    char* gs = sh_exec_capture("gd --version 2>/dev/null");
    if (gs) {
        char* nl = strchr(gs, '\n');
        if (nl) *nl = '\0';
        strncpy(info->goscript_version, str_trim(gs), sizeof(info->goscript_version) - 1);
        free(gs);
    }
    
    // User info
    struct passwd* pw = getpwuid(getuid());
    if (pw) {
        strncpy(info->user, pw->pw_name, sizeof(info->user) - 1);
        strncpy(info->home, pw->pw_dir, sizeof(info->home) - 1);
        strncpy(info->shell, pw->pw_shell, sizeof(info->shell) - 1);
    }
    
    // Lang & Timezone
    char* lang = getenv("LANG");
    if (lang) strncpy(info->lang, lang, sizeof(info->lang) - 1);
    
    char* tz = getenv("TZ");
    if (!tz) {
        char* tz_link = sh_exec_capture("readlink /etc/localtime 2>/dev/null | sed 's|.*/zoneinfo/||'");
        if (tz_link) {
            char* nl = strchr(tz_link, '\n');
            if (nl) *nl = '\0';
            strncpy(info->timezone, str_trim(tz_link), sizeof(info->timezone) - 1);
            free(tz_link);
        }
    } else {
        strncpy(info->timezone, tz, sizeof(info->timezone) - 1);
    }
    
    // Docker detection
    info->is_docker = (file_exists("/.dockerenv") || 
                       (sh_exec_capture("grep -q docker /proc/1/cgroup 2>/dev/null") != NULL));
    
    // WSL detection
    info->is_wsl = (sh_exec_capture("grep -qi microsoft /proc/version 2>/dev/null") != NULL);
    
    // VM detection
    info->is_vm = (sh_exec_capture("systemd-detect-virt --vm 2>/dev/null | grep -qv none") != NULL);
    
    // IP address
    char* ip = sh_exec_capture("hostname -I 2>/dev/null | awk '{print $1}'");
    if (ip) {
        char* nl = strchr(ip, '\n');
        if (nl) *nl = '\0';
        strncpy(info->ip_address, str_trim(ip), sizeof(info->ip_address) - 1);
        free(ip);
    }
    
    // MAC address
    char* mac = sh_exec_capture("cat /sys/class/net/$(ip route show default | awk '/default/ {print $5}')/address 2>/dev/null");
    if (mac) {
        char* nl = strchr(mac, '\n');
        if (nl) *nl = '\0';
        strncpy(info->mac_address, str_trim(mac), sizeof(info->mac_address) - 1);
        free(mac);
    }
    
    // Board info
    char* board = sh_cat("/sys/devices/virtual/dmi/id/board_name");
    if (board) {
        char* nl = strchr(board, '\n');
        if (nl) *nl = '\0';
        strncpy(info->board, str_trim(board), sizeof(info->board) - 1);
        free(board);
    }
    
    return info;
}

// ============================================================================
// GÉNÉRATION D'UN USER-AGENT ULTRA COMPLET
// ============================================================================
char* generate_user_agent(void) {
    SystemInfo* info = get_system_info();
    if (!info) return str_dup(GPM_USER_AGENT_BASE);
    
    // Buffer large pour contenir toutes les métadonnées
    char* ua = calloc(4096, 1);
    if (!ua) {
        free_system_info(info);
        return str_dup(GPM_USER_AGENT_BASE);
    }
    
    // Format: GPM/version (Goscript/version; OS/arch; Kernel/release; CPU; LibC; GCC; Docker; WSL; VM)
    snprintf(ua, 4096,
        "GPM-Goscript/%s ("
        "Goscript/%s; "
        "%s %s; "
        "Kernel %s; "
        "CPU %s (%d cores); "
        "RAM %ldMB/%ldMB; "
        "LibC %s; "
        "GCC %s; "
        "Shell %s; "
        "User %s; "
        "Lang %s; "
        "TZ %s; "
        "%s%s%s"
        ")",
        GPM_VERSION,
        info->goscript_version[0] ? info->goscript_version : "unknown",
        info->system, info->machine,
        info->kernel,
        info->model[0] ? info->model : info->machine,
        info->cpu_cores,
        info->total_ram / (1024 * 1024),
        info->free_ram / (1024 * 1024),
        info->libc_version[0] ? info->libc_version : "unknown",
        info->gcc_version[0] ? info->gcc_version : "unknown",
        info->shell[0] ? info->shell : "unknown",
        info->user[0] ? info->user : "unknown",
        info->lang[0] ? info->lang : "unknown",
        info->timezone[0] ? info->timezone : "unknown",
        info->is_docker ? "Docker " : "",
        info->is_wsl ? "WSL " : "",
        info->is_vm ? "VM " : ""
    );
    
    free_system_info(info);
    return ua;
}

// ============================================================================
// GÉNÉRATION DES HEADERS DE REQUÊTE COMPLETS
// ============================================================================
char* generate_request_headers(AuthCredentials* auth) {
    char* ua = generate_user_agent();
    char* headers = calloc(MAX_HEADERS, 1);
    
    if (!headers) {
        free(ua);
        return NULL;
    }
    
    SystemInfo* info = get_system_info();
    
    snprintf(headers, MAX_HEADERS,
        "User-Agent: %s\r\n"
        "X-GPM-Version: %s\r\n"
        "X-GPM-API-Version: %s\r\n"
        "X-System-Arch: %s\r\n"
        "X-System-Name: %s\r\n"
        "X-Kernel-Version: %s\r\n"
        "X-Hostname: %s\r\n"
        "X-CPU-Model: %s\r\n"
        "X-CPU-Cores: %d\r\n"
        "X-Total-RAM: %ld\r\n"
        "X-LibC: %s\r\n"
        "X-Is-Docker: %d\r\n"
        "X-Is-WSL: %d\r\n"
        "X-Is-VM: %d\r\n"
        "X-Timestamp: %ld\r\n"
        "Content-Type: application/json\r\n"
        "Accept: application/json\r\n"
        "Connection: keep-alive\r\n",
        ua,
        GPM_VERSION,
        GPM_API_VERSION,
        info ? info->machine : "unknown",
        info ? info->system : "unknown",
        info ? info->kernel : "unknown",
        info ? info->hostname : "unknown",
        info ? info->model : "unknown",
        info ? info->cpu_cores : 0,
        info ? info->total_ram : 0,
        info ? info->libc_version : "unknown",
        info ? info->is_docker : 0,
        info ? info->is_wsl : 0,
        info ? info->is_vm : 0,
        (long)time(NULL)
    );
    
    if (auth && auth->token[0]) {
        char auth_header[2048];
        snprintf(auth_header, sizeof(auth_header),
            "Authorization: Bearer %s\r\n"
            "X-Username: %s\r\n"
            "X-Role: %s\r\n",
            auth->token,
            auth->username,
            auth->role
        );
        strncat(headers, auth_header, MAX_HEADERS - strlen(headers) - 1);
    }
    
    free(ua);
    if (info) free_system_info(info);
    
    return headers;
}

// ============================================================================
// NETTOYAGE
// ============================================================================
void free_system_info(SystemInfo* info) {
    if (info) free(info);
}

// ============================================================================
// AFFICHAGE DES INFORMATIONS SYSTÈME
// ============================================================================
void print_system_info(SystemInfo* info) {
    if (!info) {
        printf(COLOR_RED "Failed to get system info" COLOR_RESET "\n");
        return;
    }
    
    printf(COLOR_BOLD COLOR_CYAN "\n📊 SYSTEM INFORMATION" COLOR_RESET "\n");
    printf("══════════════════════════════════════\n");
    printf("OS:           %s %s (%s)\n", info->system, info->release, info->machine);
    printf("Kernel:       %s\n", info->kernel);
    printf("Hostname:     %s\n", info->hostname);
    printf("CPU:          %s (%d cores)\n", info->model, info->cpu_cores);
    if (info->cpu_flags[0]) printf("CPU Flags:    %s\n", info->cpu_flags);
    printf("RAM:          %ld MB total / %ld MB free\n", 
           info->total_ram / (1024*1024), info->free_ram / (1024*1024));
    printf("LibC:         %s\n", info->libc_version[0] ? info->libc_version : "unknown");
    printf("GCC:          %s\n", info->gcc_version[0] ? info->gcc_version : "unknown");
    printf("Goscript:     %s\n", info->goscript_version[0] ? info->goscript_version : "unknown");
    printf("User:         %s\n", info->user);
    printf("Shell:        %s\n", info->shell);
    printf("Home:         %s\n", info->home);
    printf("Lang:         %s\n", info->lang[0] ? info->lang : "not set");
    printf("Timezone:     %s\n", info->timezone[0] ? info->timezone : "unknown");
    printf("IP:           %s\n", info->ip_address[0] ? info->ip_address : "unknown");
    if (info->is_docker) printf(COLOR_YELLOW "🐳 Running in Docker\n" COLOR_RESET);
    if (info->is_wsl) printf(COLOR_YELLOW "🪟 Running in WSL\n" COLOR_RESET);
    if (info->is_vm) printf(COLOR_YELLOW "💻 Running in VM\n" COLOR_RESET);
    printf("══════════════════════════════════════\n\n");
}
