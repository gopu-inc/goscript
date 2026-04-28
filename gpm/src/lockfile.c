// src/lockfile.c
#include "gpm.h"

/* ================================================================
 * LECTURE DU GPM.LOCK
 * ================================================================ */

int gpm_lockfile_read(Lockfile* lock) {
    if (!lock) return -1;
    memset(lock, 0, sizeof(Lockfile));
    
    if (!gpm_file_exists(GPM_LOCK_FILE)) {
        return -1;
    }
    
    FILE* f = fopen(GPM_LOCK_FILE, "r");
    if (!f) return -1;
    
    char line[1024];
    char section[64] = "";
    LockEntry current_entry = {0};
    bool in_entry = false;
    
    strcpy(lock->version, "1.0");
    
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        
        if (line[0] == '#' || line[0] == '\0') continue;
        
        // Section header
        if (line[0] == '[') {
            if (in_entry) {
                // Sauvegarder l'entrée précédente
                lock->entries = realloc(lock->entries, 
                    (lock->entry_count + 1) * sizeof(LockEntry));
                lock->entries[lock->entry_count++] = current_entry;
                memset(&current_entry, 0, sizeof(LockEntry));
            }
            
            char* end = strchr(line, ']');
            if (end) {
                *end = '\0';
                strncpy(section, line + 1, sizeof(section) - 1);
                in_entry = (strcmp(section, "package") == 0);
            }
            continue;
        }
        
        // Parser clé=valeur
        char* eq = strchr(line, '=');
        if (!eq) continue;
        
        *eq = '\0';
        char* key = line;
        char* value = eq + 1;
        
        while (*key == ' ') key++;
        char* kend = key + strlen(key) - 1;
        while (*kend == ' ') *kend-- = '\0';
        
        while (*value == ' ' || *value == '"') value++;
        char* vend = value + strlen(value) - 1;
        while (*vend == ' ' || *vend == '"') *vend-- = '\0';
        
        if (in_entry) {
            if (strcmp(key, "name") == 0) {
                strncpy(current_entry.name, value, sizeof(current_entry.name) - 1);
            } else if (strcmp(key, "version") == 0) {
                strncpy(current_entry.version, value, sizeof(current_entry.version) - 1);
            } else if (strcmp(key, "resolved") == 0) {
                strncpy(current_entry.url, value, sizeof(current_entry.url) - 1);
            } else if (strcmp(key, "integrity") == 0) {
                strncpy(current_entry.integrity, value, sizeof(current_entry.integrity) - 1);
            } else if (strcmp(key, "dev") == 0) {
                current_entry.is_dev = (strcmp(value, "true") == 0);
            }
        } else if (strcmp(section, "metadata") == 0) {
            if (strcmp(key, "lockfile_version") == 0) {
                strncpy(lock->version, value, sizeof(lock->version) - 1);
            }
        }
    }
    
    // Sauvegarder la dernière entrée
    if (in_entry) {
        lock->entries = realloc(lock->entries,
            (lock->entry_count + 1) * sizeof(LockEntry));
        lock->entries[lock->entry_count++] = current_entry;
    }
    
    fclose(f);
    LOG_DEBUG("Lockfile chargé: %d entrées", lock->entry_count);
    return 0;
}

/* ================================================================
 * ÉCRITURE DU GPM.LOCK
 * ================================================================ */

int gpm_lockfile_write(Lockfile* lock) {
    FILE* f = fopen(GPM_LOCK_FILE, "w");
    if (!f) return -1;
    
    fprintf(f, "# GPM Lockfile v2\n");
    fprintf(f, "# Généré par GPM v%s\n", GPM_VERSION);
    fprintf(f, "# NE PAS ÉDITER MANUELLEMENT\n\n");
    
    fprintf(f, "[metadata]\n");
    fprintf(f, "lockfile_version = \"%s\"\n", lock->version);
    fprintf(f, "\n");
    
    for (int i = 0; i < lock->entry_count; i++) {
        LockEntry* entry = &lock->entries[i];
        
        fprintf(f, "[[package]]\n");
        fprintf(f, "name = \"%s\"\n", entry->name);
        fprintf(f, "version = \"%s\"\n", entry->version);
        fprintf(f, "resolved = \"%s\"\n", entry->url);
        fprintf(f, "integrity = \"%s\"\n", entry->integrity);
        fprintf(f, "dev = %s\n", entry->is_dev ? "true" : "false");
        fprintf(f, "\n");
    }
    
    fclose(f);
    LOG_SUCCESS("Lockfile généré: %s (%d packages)", GPM_LOCK_FILE, lock->entry_count);
    return 0;
}

/* ================================================================
 * GÉNÉRER LE LOCKFILE DEPUIS L'ARBRE
 * ================================================================ */

int gpm_lockfile_generate(DepNode* tree) {
    Lockfile lock = {0};
    strcpy(lock.version, "2.0");
    
    // Aplatir l'arbre
    DepNode** flat = NULL;
    int flat_count = 0;
    gpm_flatten_tree_to_list(tree, &flat, &flat_count);
    
    for (int i = 0; i < flat_count; i++) {
        DepNode* node = flat[i];
        if (node->depth == 0) continue;  // Skip root
        
        lock.entries = realloc(lock.entries,
            (lock.entry_count + 1) * sizeof(LockEntry));
        
        LockEntry* entry = &lock.entries[lock.entry_count++];
        memset(entry, 0, sizeof(LockEntry));
        
        strncpy(entry->name, node->name, sizeof(entry->name) - 1);
        strncpy(entry->version, node->version, sizeof(entry->version) - 1);
        entry->is_dev = node->is_dev;
        entry->depth = node->depth;
        
        // Calculer l'intégrité
        gpm_compute_integrity(node->name, node->version, entry->integrity);
    }
    
    free(flat);
    
    return gpm_lockfile_write(&lock);
}

/* ================================================================
 * CALCULER L'INTÉGRITÉ SHA512 D'UN PACKAGE
 * ================================================================ */

int gpm_compute_integrity(const char* name, const char* version, char* output) {
    // Chercher le package installé
    char pkg_path[PATH_MAX];
    
    // D'abord dans gpm_modules local
    snprintf(pkg_path, sizeof(pkg_path), "gpm_modules/%s/%s",
             name, GPM_MANIFEST_FILE);
    
    if (gpm_file_exists(pkg_path)) {
        // Lire le SHA256 du manifest
        Manifest manifest;
        char saved_dir[PATH_MAX];
        getcwd(saved_dir, sizeof(saved_dir));
        
        char manifest_dir[PATH_MAX];
        snprintf(manifest_dir, sizeof(manifest_dir), "gpm_modules/%s", name);
        chdir(manifest_dir);
        
        if (gpm_manifest_read(&manifest) == 0 && manifest.sha256[0]) {
            // Convertir SHA256 en format integrity
            snprintf(output, 128, "sha256-%s", manifest.sha256);
            chdir(saved_dir);
            return 0;
        }
        
        chdir(saved_dir);
    }
    
    // Fallback
    snprintf(output, 128, "sha256-%s-%s", name, version);
    return 0;
}
