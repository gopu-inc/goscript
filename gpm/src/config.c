
#include "gpm.h"

GPMConfig gpm_config = {0};

/* ================================================================
 * TROUVER LE CHEMIN DE CONFIGURATION
 * ================================================================ */

static void get_config_path(char* buffer, size_t size) {
    const char* home = getenv("HOME");
    if (!home) {
        struct passwd* pw = getpwuid(getuid());
        home = pw ? pw->pw_dir : "/root";
    }
    snprintf(buffer, size, "%s/%s", home, GPM_CONFIG_FILE);
}

/* ================================================================
 * INITIALISER LA CONFIGURATION AVEC VALEURS PAR DÉFAUT
 * ================================================================ */

int gpm_config_init(void) {
    memset(&gpm_config, 0, sizeof(GPMConfig));
    
    // Comportement
    gpm_config.debug = false;
    gpm_config.force = false;
    gpm_config.global = false;
    gpm_config.production = false;
    gpm_config.save_dev = false;
    gpm_config.offline = false;
    gpm_config.verify_ssl = true;
    gpm_config.authenticated = false;
    
    // Registry
    strcpy(gpm_config.registry_url, GPM_REGISTRY_URL);
    strcpy(gpm_config.scope, GPM_DEFAULT_SCOPE);
    strcpy(gpm_config.arch, "x86_64");
    
    // Auth
    gpm_config.token[0] = '\0';
    gpm_config.username[0] = '\0';
    
    // Cache
    gpm_config.cache_ttl = GPM_CACHE_TTL;
    gpm_config.max_parallel = GPM_MAX_PARALLEL;
    gpm_config.timeout = GPM_TIMEOUT;
    
    // Chemins
    const char* home = getenv("HOME");
    if (!home) {
        struct passwd* pw = getpwuid(getuid());
        home = pw ? pw->pw_dir : "/root";
    }
    
    snprintf(gpm_config.home_dir, sizeof(gpm_config.home_dir), 
             "%s/%s", home, GPM_HOME);
    snprintf(gpm_config.cache_dir, sizeof(gpm_config.cache_dir), 
             "%s/cache", gpm_config.home_dir);
    snprintf(gpm_config.global_dir, sizeof(gpm_config.global_dir), 
             "%s/global", gpm_config.home_dir);
    
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

/* ================================================================
 * CHARGER LA CONFIGURATION DEPUIS ~/.gpmrc
 * ================================================================ */

int gpm_config_load(void) {
    char config_path[512];
    get_config_path(config_path, sizeof(config_path));
    
    LOG_DEBUG("Chargement de la configuration depuis %s", config_path);
    
    if (!gpm_file_exists(config_path)) {
        LOG_DEBUG("Aucun fichier de configuration trouvé, utilisation des valeurs par défaut");
        return 0;
    }
    
    FILE* f = fopen(config_path, "r");
    if (!f) {
        LOG_DEBUG("Impossible d'ouvrir %s", config_path);
        return -1;
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        // Ignorer commentaires et lignes vides
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;
        
        // Trouver le '='
        char* eq = strchr(line, '=');
        if (!eq) continue;
        
        *eq = '\0';
        char* key = line;
        char* value = eq + 1;
        
        // Trim de la clé
        while (*key == ' ' || *key == '\t') key++;
        char* kend = key + strlen(key) - 1;
        while (kend > key && (*kend == ' ' || *kend == '\t' || *kend == '\n' || *kend == '\r')) {
            *kend-- = '\0';
        }
        
        // Trim de la valeur
        while (*value == ' ' || *value == '\t') value++;
        if (*value == '"' || *value == '\'') {
            char quote = *value;
            value++;
            char* vend = strrchr(value, quote);
            if (vend) *vend = '\0';
        }
        char* vend = value + strlen(value) - 1;
        while (vend > value && (*vend == ' ' || *vend == '\t' || *vend == '\n' || *vend == '\r')) {
            *vend-- = '\0';
        }
        
        LOG_DEBUG("  Config: %s = %s", key, value);
        
        // Appliquer la configuration
        if (strcmp(key, "registry") == 0) {
            strncpy(gpm_config.registry_url, value, sizeof(gpm_config.registry_url) - 1);
        } else if (strcmp(key, "token") == 0) {
            strncpy(gpm_config.token, value, sizeof(gpm_config.token) - 1);
            if (strlen(value) > 0) gpm_config.authenticated = true;
        } else if (strcmp(key, "username") == 0) {
            strncpy(gpm_config.username, value, sizeof(gpm_config.username) - 1);
        } else if (strcmp(key, "scope") == 0) {
            strncpy(gpm_config.scope, value, sizeof(gpm_config.scope) - 1);
        } else if (strcmp(key, "arch") == 0) {
            strncpy(gpm_config.arch, value, sizeof(gpm_config.arch) - 1);
        } else if (strcmp(key, "verify_ssl") == 0) {
            gpm_config.verify_ssl = (strcmp(value, "true") == 0);
        } else if (strcmp(key, "cache_ttl") == 0) {
            gpm_config.cache_ttl = atoi(value);
        } else if (strcmp(key, "timeout") == 0) {
            gpm_config.timeout = atoi(value);
        }
    }
    
    fclose(f);
    
    LOG_DEBUG("Configuration chargée avec succès");
    if (gpm_config.authenticated) {
        LOG_DEBUG("  Utilisateur: %s", gpm_config.username);
        LOG_DEBUG("  Token: %.20s...", gpm_config.token);
    }
    
    return 0;
}

/* ================================================================
 * SAUVEGARDER LA CONFIGURATION DANS ~/.gpmrc
 * ================================================================ */

int gpm_config_save(void) {
    char config_path[512];
    get_config_path(config_path, sizeof(config_path));
    
    LOG_DEBUG("Sauvegarde de la configuration dans %s", config_path);
    
    FILE* f = fopen(config_path, "w");
    if (!f) {
        LOG_ERROR("Impossible d'écrire dans %s", config_path);
        return -1;
    }
    
    time_t now = time(NULL);
    
    fprintf(f, "# GPM Configuration\n");
    fprintf(f, "# Sauvegardé le %s", ctime(&now));
    fprintf(f, "registry = \"%s\"\n", gpm_config.registry_url);
    fprintf(f, "scope = \"%s\"\n", gpm_config.scope);
    fprintf(f, "arch = \"%s\"\n", gpm_config.arch);
    
    if (gpm_config.token[0]) {
        fprintf(f, "token = \"%s\"\n", gpm_config.token);
    }
    if (gpm_config.username[0]) {
        fprintf(f, "username = \"%s\"\n", gpm_config.username);
    }
    
    fprintf(f, "verify_ssl = %s\n", gpm_config.verify_ssl ? "true" : "false");
    fprintf(f, "cache_ttl = %d\n", gpm_config.cache_ttl);
    fprintf(f, "timeout = %d\n", gpm_config.timeout);
    
    fclose(f);
    
    // Vérifier que le fichier a bien été créé
    if (gpm_file_exists(config_path)) {
        LOG_DEBUG("Configuration sauvegardée: %s", config_path);
        return 0;
    }
    
    LOG_ERROR("Échec de la sauvegarde");
    return -1;
}

/* ================================================================
 * MODIFIER UNE VALEUR DE CONFIGURATION
 * ================================================================ */

int gpm_config_set(const char* key, const char* value) {
    if (strcmp(key, "registry") == 0) {
        strncpy(gpm_config.registry_url, value, sizeof(gpm_config.registry_url) - 1);
    } else if (strcmp(key, "token") == 0) {
        strncpy(gpm_config.token, value, sizeof(gpm_config.token) - 1);
    } else if (strcmp(key, "username") == 0) {
        strncpy(gpm_config.username, value, sizeof(gpm_config.username) - 1);
    } else if (strcmp(key, "scope") == 0) {
        strncpy(gpm_config.scope, value, sizeof(gpm_config.scope) - 1);
    } else if (strcmp(key, "arch") == 0) {
        strncpy(gpm_config.arch, value, sizeof(gpm_config.arch) - 1);
    } else if (strcmp(key, "verify_ssl") == 0) {
        gpm_config.verify_ssl = (strcmp(value, "true") == 0 || strcmp(value, "1") == 0);
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

/* ================================================================
 * LIRE UNE VALEUR DE CONFIGURATION
 * ================================================================ */

char* gpm_config_get(const char* key) {
    if (strcmp(key, "registry") == 0) return gpm_config.registry_url;
    if (strcmp(key, "token") == 0) return gpm_config.token;
    if (strcmp(key, "username") == 0) return gpm_config.username;
    if (strcmp(key, "scope") == 0) return gpm_config.scope;
    if (strcmp(key, "arch") == 0) return gpm_config.arch;
    if (strcmp(key, "home_dir") == 0) return gpm_config.home_dir;
    if (strcmp(key, "cache_dir") == 0) return gpm_config.cache_dir;
    if (strcmp(key, "global_dir") == 0) return gpm_config.global_dir;
    return NULL;
}
