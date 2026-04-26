#include "../gpm.h"

// ============================================================================
// AFFICHAGE DES MACROS DE CONFIGURATION
// ============================================================================
void macro_print_build_info(void) {
    printf(COLOR_BOLD COLOR_CYAN "GPM Build Information" COLOR_RESET "\n");
    printf("══════════════════════════════════\n");
    printf("Version:        " COLOR_GREEN "%s" COLOR_RESET "\n", GPM_VERSION);
    printf("Codename:       " COLOR_YELLOW "%s" COLOR_RESET "\n", GPM_CODENAME);
    printf("API Version:    " COLOR_BLUE "%s" COLOR_RESET "\n", GPM_API_VERSION);
    printf("Build Date:     %s\n", __DATE__);
    printf("Build Time:     %s\n", __TIME__);
    printf("Compiler:       GCC %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    
    #ifdef __x86_64__
    printf("Architecture:   x86_64\n");
    #elif __aarch64__
    printf("Architecture:   ARM64\n");
    #elif __i386__
    printf("Architecture:   i386\n");
    #endif
    
    printf("══════════════════════════════════\n\n");
}

// ============================================================================
// MAPPING DES CODES D'ERREUR
// ============================================================================
const char* macro_error_string(int code) {
    switch (code) {
        case GPM_OK:                    return "Success";
        case GPM_ERROR:                 return "Generic error";
        case GPM_ERROR_NETWORK:         return "Network error";
        case GPM_ERROR_AUTH:            return "Authentication failed";
        case GPM_ERROR_PACKAGE_NOT_FOUND: return "Package not found";
        case GPM_ERROR_VERSION_NOT_FOUND: return "Version not found";
        case GPM_ERROR_CHECKSUM:        return "Checksum verification failed";
        case GPM_ERROR_DISK_FULL:       return "Disk full";
        case GPM_ERROR_PERMISSION:      return "Permission denied";
        case GPM_ERROR_LOCK:            return "Another GPM instance is running";
        case GPM_ERROR_ALREADY_INSTALLED: return "Package already installed";
        case GPM_ERROR_DEPENDENCY:      return "Dependency resolution failed";
        case GPM_ERROR_INVALID_ARCHIVE: return "Invalid package archive";
        default:                        return "Unknown error";
    }
}
