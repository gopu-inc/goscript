// src/semver.c
#include "gpm.h"
#include <ctype.h>

/* ================================================================
 * PARSER UNE VERSION SÉMANTIQUE
 * Format: major.minor.patch-prerelease+build
 * Exemples: 1.2.3, 2.0.0-beta.1, 1.0.0-alpha+001
 * ================================================================ */

SemVer gpm_semver_parse(const char* version) {
    SemVer ver = {0, 0, 0, "", ""};
    
    if (!version || !*version) return ver;
    
    // Ignorer 'v' ou 'V' préfixe
    if (*version == 'v' || *version == 'V') version++;
    
    // Parser major.minor.patch
    char* ptr = (char*)version;
    
    // Major
    ver.major = (int)strtol(ptr, &ptr, 10);
    if (*ptr != '.') return ver;
    ptr++;
    
    // Minor
    ver.minor = (int)strtol(ptr, &ptr, 10);
    if (*ptr != '.') return ver;
    ptr++;
    
    // Patch
    ver.patch = (int)strtol(ptr, &ptr, 10);
    
    // Prerelease (optionnel)
    if (*ptr == '-') {
        ptr++;
        int i = 0;
        while (*ptr && *ptr != '+' && i < 31) {
            ver.prerelease[i++] = *ptr++;
        }
        ver.prerelease[i] = '\0';
    }
    
    // Build metadata (optionnel)
    if (*ptr == '+') {
        ptr++;
        int i = 0;
        while (*ptr && i < 31) {
            ver.build[i++] = *ptr++;
        }
        ver.build[i] = '\0';
    }
    
    LOG_DEBUG("Parsed version: %d.%d.%d%s%s%s",
              ver.major, ver.minor, ver.patch,
              ver.prerelease[0] ? "-" : "",
              ver.prerelease,
              ver.build[0] ? "+" : "",
              ver.build);
    
    return ver;
}

/* ================================================================
 * COMPARER DEUX VERSIONS
 * Retourne: -1 si a < b, 0 si a == b, 1 si a > b
 * ================================================================ */

int gpm_semver_compare(SemVer a, SemVer b) {
    // Comparer major
    if (a.major != b.major) return (a.major > b.major) ? 1 : -1;
    
    // Comparer minor
    if (a.minor != b.minor) return (a.minor > b.minor) ? 1 : -1;
    
    // Comparer patch
    if (a.patch != b.patch) return (a.patch > b.patch) ? 1 : -1;
    
    // Comparer prerelease
    bool a_has_pre = strlen(a.prerelease) > 0;
    bool b_has_pre = strlen(b.prerelease) > 0;
    
    if (!a_has_pre && !b_has_pre) return 0;  // Identiques
    if (!a_has_pre && b_has_pre) return 1;   // a > b (release > prerelease)
    if (a_has_pre && !b_has_pre) return -1;  // a < b
    
    // Comparer les prereleases lexicographiquement
    return strcmp(a.prerelease, b.prerelease);
}

/* ================================================================
 * VÉRIFIER SI UNE VERSION SATISFAIT UNE CONTRAINTE
 * ================================================================ */

bool gpm_semver_satisfies(SemVer version, Dependency dep) {
    switch (dep.type) {
        case VER_ANY:
        case VER_LATEST:
            return true;
            
        case VER_EXACT:
            return gpm_semver_compare(version, dep.version) == 0;
            
        case VER_GTE:
            return gpm_semver_compare(version, dep.version) >= 0;
            
        case VER_LTE:
            return gpm_semver_compare(version, dep.version) <= 0;
            
        case VER_GT:
            return gpm_semver_compare(version, dep.version) > 0;
            
        case VER_LT:
            return gpm_semver_compare(version, dep.version) < 0;
            
        case VER_CARET: {
            // ^1.2.3 => >=1.2.3 <2.0.0
            // ^0.2.3 => >=0.2.3 <0.3.0
            // ^0.0.3 => >=0.0.3 <0.0.4
            SemVer min = dep.version;
            SemVer max = dep.version;
            
            if (min.major > 0 || min.minor > 0 || min.patch > 0) {
                if (min.major > 0 || min.minor > 0) {
                    if (min.major > 0) {
                        max.major++;
                        max.minor = 0;
                        max.patch = 0;
                    } else {
                        max.minor++;
                        max.patch = 0;
                    }
                } else {
                    max.patch++;
                }
            }
            
            // Nettoyer prerelease pour max
            max.prerelease[0] = '\0';
            max.build[0] = '\0';
            
            return gpm_semver_compare(version, min) >= 0 && 
                   gpm_semver_compare(version, max) < 0;
        }
        
        case VER_TILDE: {
            // ~1.2.3 => >=1.2.3 <1.3.0
            SemVer min = dep.version;
            SemVer max = {min.major, min.minor + 1, 0, "", ""};
            
            return gpm_semver_compare(version, min) >= 0 && 
                   gpm_semver_compare(version, max) < 0;
        }
        
        case VER_RANGE: {
            return gpm_semver_compare(version, dep.version) >= 0 && 
                   gpm_semver_compare(version, dep.version_max) <= 0;
        }
    }
    
    return false;
}

/* ================================================================
 * CONVERTIR UNE VERSION EN CHAÎNE
 * ================================================================ */

char* gpm_semver_to_string(SemVer ver) {
    static char buffer[128];
    
    snprintf(buffer, sizeof(buffer), "%d.%d.%d%s%s%s%s",
             ver.major, ver.minor, ver.patch,
             ver.prerelease[0] ? "-" : "",
             ver.prerelease,
             ver.build[0] ? "+" : "",
             ver.build);
    
    return buffer;
}

/* ================================================================
 * PARSER UNE CONTRAINTE DE VERSION
 * Exemples: "1.2.3", ">=1.2.3", "^1.0.0", "~2.1", "*", "latest"
 * ================================================================ */

Dependency gpm_dependency_parse(const char* name, const char* constraint) {
    Dependency dep = {0};
    strncpy(dep.name, name, sizeof(dep.name) - 1);
    
    if (!constraint || !*constraint || strcmp(constraint, "*") == 0) {
        dep.type = VER_ANY;
        return dep;
    }
    
    if (strcmp(constraint, "latest") == 0) {
        dep.type = VER_LATEST;
        return dep;
    }
    
    const char* ver_str = constraint;
    
    // Détecter le type de contrainte
    if (strncmp(constraint, ">=", 2) == 0) {
        dep.type = VER_GTE;
        ver_str = constraint + 2;
    } else if (strncmp(constraint, "<=", 2) == 0) {
        dep.type = VER_LTE;
        ver_str = constraint + 2;
    } else if (strncmp(constraint, ">", 1) == 0) {
        dep.type = VER_GT;
        ver_str = constraint + 1;
    } else if (strncmp(constraint, "<", 1) == 0) {
        dep.type = VER_LT;
        ver_str = constraint + 1;
    } else if (constraint[0] == '^') {
        dep.type = VER_CARET;
        ver_str = constraint + 1;
    } else if (constraint[0] == '~') {
        dep.type = VER_TILDE;
        ver_str = constraint + 1;
    } else if (constraint[0] == '=') {
        dep.type = VER_EXACT;
        ver_str = constraint + 1;
    } else if (strchr(constraint, '-')) {
        // Range: "1.0.0 - 2.0.0"
        dep.type = VER_RANGE;
        char* dash = strstr(constraint, " - ");
        if (dash) {
            *dash = '\0';
            dep.version = gpm_semver_parse(constraint);
            dep.version_max = gpm_semver_parse(dash + 3);
            *dash = '-';
            return dep;
        }
    }
    
    // Parser la version
    while (*ver_str == ' ') ver_str++;
    dep.version = gpm_semver_parse(ver_str);
    
    if (dep.type == 0) {
        // Si pas de préfixe, c'est exact ou caret implicite
        if (ver_str[0] == '0') {
            dep.type = VER_EXACT;
        } else {
            dep.type = VER_CARET;  // npm-style: "1.2.3" => "^1.2.3"
        }
    }
    
    return dep;
}
