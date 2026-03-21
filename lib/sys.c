// lib/sys.c - Bibliothèque système pour Goscript
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>

// Structure pour les informations système
typedef struct {
    char version[64];
    char os[32];
    char arch[32];
} SysInfo;

// Récupérer les informations système
SysInfo* sys_get_info() {
    SysInfo* info = malloc(sizeof(SysInfo));
    struct utsname uname_data;
    
    if (uname(&uname_data) == 0) {
        strcpy(info->os, uname_data.sysname);
        strcpy(info->arch, uname_data.machine);
        snprintf(info->version, sizeof(info->version), "%s %s", 
                 uname_data.release, uname_data.version);
    } else {
        strcpy(info->os, "unknown");
        strcpy(info->arch, "unknown");
        strcpy(info->version, "unknown");
    }
    
    return info;
}

// Récupérer le PID
int sys_getpid() {
    return getpid();
}

// Lire une variable d'environnement
char* sys_getenv(const char* name) {
    return getenv(name);
}

// Écrire dans un fichier
int sys_write_file(const char* path, const char* content) {
    FILE* f = fopen(path, "w");
    if (!f) return -1;
    int len = fprintf(f, "%s", content);
    fclose(f);
    return len;
}

// Lire un fichier
char* sys_read_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) return NULL;
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* content = malloc(size + 1);
    fread(content, 1, size, f);
    content[size] = '\0';
    fclose(f);
    
    return content;
}

// Supprimer un fichier
int sys_remove_file(const char* path) {
    return remove(path);
}

// Exécuter une commande système
int sys_system(const char* cmd) {
    return system(cmd);
}

// Obtenir le timestamp
long sys_timestamp() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

// Lire l'entrée standard
char* sys_input() {
    char* line = NULL;
    size_t len = 0;
    getline(&line, &len, stdin);
    if (line && line[strlen(line)-1] == '\n') {
        line[strlen(line)-1] = '\0';
    }
    return line;
}

// Afficher du texte
void sys_print(const char* text) {
    printf("%s", text);
    fflush(stdout);
}

void sys_println(const char* text) {
    printf("%s\n", text);
    fflush(stdout);
}
