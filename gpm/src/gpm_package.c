// src/utils.c
#include "gpm.h"

/* ================================================================
 * STRDUP SÉCURISÉ
 * ================================================================ */

char* gpm_strdup(const char* src) {
    if (!src) return NULL;
    size_t len = strlen(src) + 1;
    char* dst = malloc(len);
    if (dst) memcpy(dst, src, len);
    return dst;
}

/* ================================================================
 * CONCATÉNER DEUX CHEMINS
 * ================================================================ */

char* gpm_path_join(const char* p1, const char* p2) {
    size_t len1 = strlen(p1);
    size_t len2 = strlen(p2);
    bool need_slash = (p1[len1 - 1] != '/' && p2[0] != '/');
    
    char* result = malloc(len1 + len2 + 2);
    strcpy(result, p1);
    if (need_slash) strcat(result, "/");
    strcat(result, p2);
    return result;
}

/* ================================================================
 * VÉRIFIER SI UN FICHIER EXISTE
 * ================================================================ */

bool gpm_file_exists(const char* path) {
    return access(path, F_OK) == 0;
}

/* ================================================================
 * CRÉER UN RÉPERTOIRE RÉCURSIVEMENT (mkdir -p)
 * ================================================================ */

int gpm_mkdir_p(const char* path) {
    char cmd[PATH_MAX + 256];
    snprintf(cmd, sizeof(cmd), "mkdir -p '%s'", path);
    return system(cmd);
}

/* ================================================================
 * CALCULER SHA256 D'UN FICHIER
 * ================================================================ */

char* gpm_sha256_file(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    
    unsigned char buffer[8192];
    size_t bytes;
    
    while ((bytes = fread(buffer, 1, sizeof(buffer), f)) > 0) {
        SHA256_Update(&ctx, buffer, bytes);
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &ctx);
    
    static char output[65];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
    
    fclose(f);
    return output;
}
