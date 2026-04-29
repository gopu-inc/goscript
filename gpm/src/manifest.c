// src/manifest.c
#include "gpm.h"
#include <ctype.h>

/* ================================================================
 * LECTURE DU MANIFEST.TOML
 * ================================================================ */

int gpm_manifest_read(Manifest* manifest) {
    if (!manifest) return -1;
    memset(manifest, 0, sizeof(Manifest));
    
    // Chercher le manifest
    const char* paths[] = {
        GPM_MANIFEST_FILE,
        "Manifest.toml",
        "manifest.toml",
        NULL
    };
    
    const char* manifest_path = NULL;
    for (int i = 0; paths[i]; i++) {
        if (gpm_file_exists(paths[i])) {
            manifest_path = paths[i];
            break;
        }
    }
    
    if (!manifest_path) {
        LOG_ERROR("Aucun Manifest.toml trouvé");
        return -1;
    }
    
    LOG_DEBUG("Lecture du manifest: %s", manifest_path);
    
    FILE* f = fopen(manifest_path, "r");
    if (!f) {
        LOG_ERROR("Impossible d'ouvrir %s", manifest_path);
        return -1;
    }
    
    char line[1024];
    char section[64] = "";
    bool in_deps = false;
    bool in_dev_deps = false;
    
    // Valeurs par défaut
    strcpy(manifest->release, "r0");
    strcpy(manifest->arch, gpm_config.arch[0] ? gpm_config.arch : "x86_64");
    strcpy(manifest->license, "MIT");
    strcpy(manifest->main, "main.gjs");
    
    while (fgets(line, sizeof(line), f)) {
        // Nettoyer la ligne
        line[strcspn(line, "\n")] = '\0';
        
        // Ignorer commentaires et lignes vides
        if (line[0] == '#' || line[0] == '\0') continue;
        
        // Trim
        char* trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
        
        // Section header [section]
        if (trimmed[0] == '[') {
            char* end = strchr(trimmed, ']');
            if (end) {
                *end = '\0';
                strncpy(section, trimmed + 1, sizeof(section) - 1);
                in_deps = (strcmp(section, "dependencies") == 0);
                in_dev_deps = (strcmp(section, "dev-dependencies") == 0);
            }
            continue;
        }
       
    if (strcmp(section, "bin") == 0) {
        continue;
    }
}

if (strcmp(section, "bin") == 0) {
    char* eq = strchr(line, '=');
    if (eq && manifest->bin_count < GPM_MAX_BINS) {
        *eq = '\0';
        char* key = line; // Tu peux utiliser une fonction de trim ici
        char* val = eq + 1;
        
        // Nettoyer les espaces et guillemets (simplifié)
        while(*key == ' ' || *key == '\t') key++;
        char* end_key = key + strlen(key) - 1;
        while(end_key > key && (*end_key == ' ' || *end_key == '\t')) *end_key-- = '\0';
        
        while(*val == ' ' || *val == '\t' || *val == '"') val++;
        char* end_val = val + strlen(val) - 1;
        while(end_val > val && (*end_val == ' ' || *end_val == '\t' || *end_val == '"')) *end_val-- = '\0';

        strncpy(manifest->bins[manifest->bin_count].cmd_name, key, 63);
        strncpy(manifest->bins[manifest->bin_count].script_path, val, 255);
        manifest->bin_count++;
    }
}

        // Clé = valeur
        char* eq = strchr(line, '=');
        if (!eq) continue;
        
        *eq = '\0';
        char* key = line;
        char* value = eq + 1;
        
        // Nettoyer la clé
        while (*key == ' ' || *key == '\t') key++;
        char* kend = key + strlen(key) - 1;
        while (kend > key && (*kend == ' ' || *kend == '\t')) *kend-- = '\0';
        
        // Nettoyer la valeur
        while (*value == ' ' || *value == '\t') value++;
        if (*value == '"' || *value == '\'') {
            char quote = *value;
            value++;
            char* vend = strrchr(value, quote);
            if (vend) *vend = '\0';
        }
        char* vend = value + strlen(value) - 1;
        while (vend > value && (*vend == ' ' || *vend == '\t')) *vend-- = '\0';
        
        LOG_DEBUG("  [%s] %s = %s", section, key, value);
        
        // Traiter selon la section
        if (strcmp(section, "metadata") == 0 || section[0] == '\0') {
            if (strcmp(key, "name") == 0) {
                strncpy(manifest->name, value, sizeof(manifest->name) - 1);
            } else if (strcmp(key, "version") == 0) {
                strncpy(manifest->version, value, sizeof(manifest->version) - 1);
            } else if (strcmp(key, "release") == 0) {
                strncpy(manifest->release, value, sizeof(manifest->release) - 1);
            } else if (strcmp(key, "arch") == 0) {
                strncpy(manifest->arch, value, sizeof(manifest->arch) - 1);
            } else if (strcmp(key, "description") == 0) {
                strncpy(manifest->description, value, sizeof(manifest->description) - 1);
            } else if (strcmp(key, "author") == 0) {
                strncpy(manifest->author, value, sizeof(manifest->author) - 1);
            } else if (strcmp(key, "license") == 0) {
                strncpy(manifest->license, value, sizeof(manifest->license) - 1);
            } else if (strcmp(key, "homepage") == 0) {
                strncpy(manifest->homepage, value, sizeof(manifest->homepage) - 1);
            } else if (strcmp(key, "main") == 0) {
                strncpy(manifest->main, value, sizeof(manifest->main) - 1);
            }
        }
        else if (in_deps) {
            // Ajouter une dépendance
            if (manifest->dep_count < 256) {
                Dependency dep = gpm_dependency_parse(key, value);
                manifest->dependencies = realloc(manifest->dependencies, 
                    (manifest->dep_count + 1) * sizeof(Dependency));
                manifest->dependencies[manifest->dep_count++] = dep;
            }
        }
        else if (in_dev_deps) {
            // Ajouter une dépendance de développement
            if (manifest->dev_dep_count < 256) {
                Dependency dep = gpm_dependency_parse(key, value);
                manifest->dev_dependencies = realloc(manifest->dev_dependencies,
                    (manifest->dev_dep_count + 1) * sizeof(Dependency));
                manifest->dev_dependencies[manifest->dev_dep_count++] = dep;
            }
        }
        else if (strcmp(section, "scripts") == 0) {
            if (strcmp(key, "preinstall") == 0) {
                strncpy(manifest->scripts_preinstall, value, sizeof(manifest->scripts_preinstall) - 1);
            } else if (strcmp(key, "install") == 0) {
                strncpy(manifest->scripts_install, value, sizeof(manifest->scripts_install) - 1);
            } else if (strcmp(key, "postinstall") == 0) {
                strncpy(manifest->scripts_postinstall, value, sizeof(manifest->scripts_postinstall) - 1);
            } else if (strcmp(key, "build") == 0) {
                strncpy(manifest->scripts_build, value, sizeof(manifest->scripts_build) - 1);
            } else if (strcmp(key, "test") == 0) {
                strncpy(manifest->scripts_test, value, sizeof(manifest->scripts_test) - 1);
            }
        }
    }
    
    fclose(f);
    
    LOG_SUCCESS("Manifest chargé: %s@%s", manifest->name, manifest->version);
    LOG_DEBUG("  Dépendances: %d", manifest->dep_count);
    LOG_DEBUG("  Dev dépendances: %d", manifest->dev_dep_count);
    
    return 0;
}

/* ================================================================
 * ÉCRITURE DU MANIFEST.TOML
 * ================================================================ */

int gpm_manifest_write(Manifest* manifest) {
    FILE* f = fopen(GPM_MANIFEST_FILE, "w");
    if (!f) return -1;
    
    fprintf(f, "# Manifest.toml\n");
    fprintf(f, "# Généré par GPM v%s\n\n", GPM_VERSION);
    
    // Section metadata
    fprintf(f, "[metadata]\n");
    fprintf(f, "name = \"%s\"\n", manifest->name);
    fprintf(f, "version = \"%s\"\n", manifest->version);
    fprintf(f, "release = \"%s\"\n", manifest->release);
    fprintf(f, "arch = \"%s\"\n", manifest->arch);
    if (manifest->description[0])
        fprintf(f, "description = \"%s\"\n", manifest->description);
    if (manifest->author[0])
        fprintf(f, "author = \"%s\"\n", manifest->author);
    fprintf(f, "license = \"%s\"\n", manifest->license);
    if (manifest->homepage[0])
        fprintf(f, "homepage = \"%s\"\n", manifest->homepage);
    if (manifest->main[0])
        fprintf(f, "main = \"%s\"\n", manifest->main);
    fprintf(f, "\n");
    
    // Section dépendances
    if (manifest->dep_count > 0) {
        fprintf(f, "[dependencies]\n");
        for (int i = 0; i < manifest->dep_count; i++) {
            Dependency* dep = &manifest->dependencies[i];
            fprintf(f, "%s = \"%s\"\n", dep->name, 
                   gpm_semver_to_string(dep->version));
        }
        fprintf(f, "\n");
    }
    
    // Section scripts
    bool has_scripts = false;
    if (manifest->scripts_build[0]) has_scripts = true;
    if (manifest->scripts_test[0]) has_scripts = true;
    if (manifest->scripts_install[0]) has_scripts = true;
    
    if (has_scripts) {
        fprintf(f, "[scripts]\n");
        if (manifest->scripts_build[0])
            fprintf(f, "build = \"%s\"\n", manifest->scripts_build);
        if (manifest->scripts_test[0])
            fprintf(f, "test = \"%s\"\n", manifest->scripts_test);
        if (manifest->scripts_install[0])
            fprintf(f, "install = \"%s\"\n", manifest->scripts_install);
        fprintf(f, "\n");
    }
    
    fclose(f);
    LOG_SUCCESS("Manifest sauvegardé dans %s", GPM_MANIFEST_FILE);
    return 0;
}

/* ================================================================
 * VALIDATION DU MANIFEST
 * ================================================================ */

int gpm_manifest_validate(Manifest* manifest) {
    int errors = 0;
    
    if (!manifest->name[0]) {
        LOG_ERROR("Le champ 'name' est requis");
        errors++;
    }
    if (!manifest->version[0]) {
        LOG_ERROR("Le champ 'version' est requis");
        errors++;
    }
    if (!manifest->arch[0]) {
        strcpy(manifest->arch, "x86_64");
        LOG_WARN("Arch non spécifiée, utilisation de x86_64");
    }
    
    return errors == 0 ? 0 : -1;
}
