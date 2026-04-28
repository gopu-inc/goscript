// src/config.c
#include "gpm.h"

GPMConfig gpm_config = {0};

static char* get_home_config_path(char* buffer, size_t size) {
    const char* home = getenv("HOME");
    if (!home) {
        struct passwd* pw = getpwuid(getuid());
        home = pw ? pw->pw_dir : "/root";
    }
    snprintf(buffer, size, "%s/%s", home, GPM_CONFIG_FILE);
    return buffer;
}

int gpm_config_init(void) {
    // Valeurs par défaut
    gpm_config.debug = false;
    gpm_config.force = false;
    gpm_config.global = false;
    gpm_config.production = false;
    gpm_config.save_dev = false;
    gpm_config.offline = false;
    gpm_config.verify_ssl = true;
    gpm_config.authenticated = false;
    
    strcpy(gpm_config.registry_url, GPM_REGISTRY_URL);
    strcpy(gpm_config.scope, GPM_DEFAULT_SCOPE);
    strcpy(gpm_config.arch, "x86_64");
    strcpy(gpm_config.token, "");
    strcpy(gpm_config.username, "");
    
    gpm_config.cache_ttl = GPM_CACHE_TTL;
    gpm_config.max_parallel = GPM_MAX_PARALLEL;
    gpm_config.timeout = GPM_TIMEOUT;
    
    // Chemins
    const char* home = getenv("HOME");
    if (!home) home = "/root";
    
    snprintf(gpm_config.home_dir, sizeof(gpm_config.home_dir), "%s/%s", home, GPM_HOME);
    snprintf(gpm_config.cache_dir, sizeof(gpm_config.cache_dir), "%s/cache", gpm_config.home_dir);
    snprintf(gpm_config.global_dir, sizeof(gpm_config.global_dir), "%s/global", gpm_config.home_dir);
    
    // Créer les répertoires
    gpm_mkdir_p(gpm_config.home_dir);
    gpm_mkdir_p(gpm_config.cache_dir);
    gpm_mkdir_p(gpm_config.global_dir);
    
    LOG_DEBUG("Configuration initialisée");
    LOG_DEBUG("  Home: %s", gpm_config.home_dir);
    LOG_DEBUG("  Cache: %s", gpm_config.cache_dir);
    LOG_DEBUG("  Registry: %s", gpm_config.registry_url);
    
    return 0;
}

int gpm_config_load(void) {
    char config_path[512];
    get_home_config_path(config_path, sizeof(config_path));
    
    if (!gpm_file_exists(config_path)) {
        // Chercher aussi dans /etc/gpm
        snprintf(config_path, sizeof(config_path), "%s/%s", GPM_CONFIG_DIR, GPM_CONFIG_FILE);
        if (!gpm_file_exists(config_path)) {
            return 0;  // Pas de config, utiliser les défauts
        }
    }
    
    FILE* f = fopen(config_path, "r");
    if (!f) return -1;
    
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        // Ignorer commentaires et lignes vides
        if (line[0] == '#' || line[0] == '\n') continue;
        
        char* eq = strchr(line, '=');
        if (!eq) continue;
        
        *eq = '\0';
        char* key = line;
        char* value = eq + 1;
        
        // Trim
        while (*key == ' ' || *key == '\t') key++;
        char* kend = key + strlen(key) - 1;
        while (*kend == ' ' || *kend == '\t' || *kend == '\n') *kend-- = '\0';
        
        while (*value == ' ' || *value == '\t') value++;
        char* vend = value + strlen(value) - 1;
        while (*vend == ' ' || *vend == '\t' || *vend == '\n') *vend-- = '\0';
        
        // Enlever les guillemets
        if (value[0] == '"' || value[0] == '\'') {
            value++;
            if (value[strlen(value)-1] == '"' || value[strlen(value)-1] == '\'') {
                value[strlen(value)-1] = '\0';
            }
        }
        
        gpm_config_set(key, value);
    }
    
    fclose(f);
    LOG_DEBUG("Configuration chargée depuis %s", config_path);
    return 0;
}

int gpm_config_save(void) {
    char config_path[512];
    get_home_config_path(config_path, sizeof(config_path));
    
    FILE* f = fopen(config_path, "w");
    if (!f) return -1;
    
    fprintf(f, "# GPM Configuration\n");
    fprintf(f, "# Generated: %s\n\n", ctime(&(time_t){time(NULL)}));
    
    fprintf(f, "registry = \"%s\"\n", gpm_config.registry_url);
    fprintf(f, "scope = \"%s\"\n", gpm_config.scope);
    fprintf(f, "arch = \"%s\"\n", gpm_config.arch);
    if (gpm_config.token[0]) {
        fprintf(f, "token = \"%s\"\n", gpm_config.token);
    }
    fprintf(f, "verify_ssl = %s\n", gpm_config.verify_ssl ? "true" : "false");
    fprintf(f, "cache_ttl = %d\n", gpm_config.cache_ttl);
    fprintf(f, "timeout = %d\n", gpm_config.timeout);
    
    fclose(f);
    LOG_DEBUG("Configuration sauvegardée dans %s", config_path);
    return 0;
}

int gpm_config_set(const char* key, const char* value) {
    if (strcmp(key, "registry") == 0) {
        strncpy(gpm_config.registry_url, value, sizeof(gpm_config.registry_url)-1);
    } else if (strcmp(key, "token") == 0) {
        strncpy(gpm_config.token, value, sizeof(gpm_config.token)-1);
    } else if (strcmp(key, "scope") == 0) {
        strncpy(gpm_config.scope, value, sizeof(gpm_config.scope)-1);
    } else if (strcmp(key, "arch") == 0) {
        strncpy(gpm_config.arch, value, sizeof(gpm_config.arch)-1);
    } else if (strcmp(key, "verify_ssl") == 0) {
        gpm_config.verify_ssl = (strcmp(value, "true") == 0);
    } else if (strcmp(key, "cache_ttl") == 0) {
        gpm_config.cache_ttl = atoi(value);
    } else if (strcmp(key, "timeout") == 0) {
        gpm_config.timeout = atoi(value);
    } else {
        LOG_WARN("Clé de configuration inconnue: %s", key);
        return -1;
    }
    return 0;
}

char* gpm_config_get(const char* key) {
    static char buffer[512];
    
    if (strcmp(key, "registry") == 0) {
        return gpm_config.registry_url;
    } else if (strcmp(key, "scope") == 0) {
        return gpm_config.scope;
    } else if (strcmp(key, "arch") == 0) {
        return gpm_config.arch;
    } else if (strcmp(key, "cache_dir") == 0) {
        return gpm_config.cache_dir;
    }
    
    return NULL;
}
