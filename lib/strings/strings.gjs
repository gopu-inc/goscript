module strings

// ============================================
// FONCTIONS DE BASE
// ============================================

// Longueur d'une chaîne
pub fn len(s: string): int {
    ret strlen_c(s)
}

// Comparer deux chaînes
pub fn compare(a: string, b: string): int {
    ret strcmp_c(a, b)
}

// Comparer n caractères
pub fn compare_n(a: string, b: string, n: int): int {
    ret strncmp_c(a, b, n)
}

// ============================================
// RECHERCHE
// ============================================

// Trouver un caractère dans une chaîne
pub fn contains_char(s: string, c: string): bool {
    lt result = strchr_c(s, c)
    ret result != ""
}

// Trouver une sous-chaîne
pub fn contains(s: string, substr: string): bool {
    lt result = strstr_c(s, substr)
    ret result != ""
}

// Trouver la première occurrence d'un caractère
pub fn index_of_char(s: string, c: string): int {
    lt ptr = strchr_c(s, c)
    if ptr == "" {
        ret -1
    }
    ret len(s) - len(ptr)
}

// Trouver la dernière occurrence d'un caractère
pub fn last_index_of_char(s: string, c: string): int {
    lt ptr = strrchr_c(s, c)
    if ptr == "" {
        ret -1
    }
    ret len(s) - len(ptr)
}

// Trouver une sous-chaîne
pub fn index_of(s: string, substr: string): int {
    lt ptr = strstr_c(s, substr)
    if ptr == "" {
        ret -1
    }
    ret len(s) - len(ptr)
}

// ============================================
// MODIFICATION
// ============================================

// Mettre en majuscules (via commande tr)
pub fn to_upper(s: string): string {
    lt cmd = f"echo '{s}' | tr '[:lower:]' '[:upper:]'"
    lt result = await cmd
    // Enlever le newline final
    ret trim_right(result, "\n")
}

// Mettre en minuscules
pub fn to_lower(s: string): string {
    lt cmd = f"echo '{s}' | tr '[:upper:]' '[:lower:]'"
    lt result = await cmd
    ret trim_right(result, "\n")
}

// Capitaliser première lettre
pub fn capitalize(s: string): string {
    if len(s) == 0 {
        ret ""
    }
    lt first = slice(s, 0, 1)
    lt rest = slice(s, 1, len(s))
    ret to_upper(first) + to_lower(rest)
}

// ============================================
// DÉCOUPAGE ET EXTRACTION
// ============================================

// Sous-chaîne (début, fin)
pub fn slice(s: string, start: int, end: int): string {
    if start < 0 { start = 0 }
    if end > len(s) { end = len(s) }
    if start >= end { ret "" }
    
    lt result = ""
    lt i = start
    while i < end {
        result = result + char_at(s, i)
        i = i + 1
    }
    ret result
}

// Caractère à une position
pub fn char_at(s: string, index: int): string {
    if index < 0 || index >= len(s) {
        ret ""
    }
    // Utiliser cut pour extraire un caractère
    lt cmd = f"echo '{s}' | cut -c {index + 1}"
    lt result = await cmd
    ret trim(result)
}

// ============================================
// NETTOYAGE
// ============================================

// Enlever les espaces au début et à la fin
pub fn trim(s: string): string {
    lt cmd = f"echo '{s}' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//'"
    lt result = await cmd
    ret trim_right(result, "\n")
}

// Enlever les espaces à gauche
pub fn trim_left(s: string): string {
    lt cmd = f"echo '{s}' | sed 's/^[[:space:]]*//'"
    lt result = await cmd
    ret trim_right(result, "\n")
}

// Enlever les espaces à droite
pub fn trim_right(s: string, chars: string): string {
    if chars == "" {
        chars = " \t\n\r"
    }
    lt i = len(s) - 1
    while i >= 0 && contains_char(chars, char_at(s, i)) {
        i = i - 1
    }
    ret slice(s, 0, i + 1)
}

// Enlever un préfixe
pub fn trim_prefix(s: string, prefix: string): string {
    if starts_with(s, prefix) {
        ret slice(s, len(prefix), len(s))
    }
    ret s
}

// Enlever un suffixe
pub fn trim_suffix(s: string, suffix: string): string {
    if ends_with(s, suffix) {
        ret slice(s, 0, len(s) - len(suffix))
    }
    ret s
}

// ============================================
// PRÉDICATS
// ============================================

// Commence par
pub fn starts_with(s: string, prefix: string): bool {
    if len(prefix) > len(s) {
        ret false
    }
    ret slice(s, 0, len(prefix)) == prefix
}

// Termine par
pub fn ends_with(s: string, suffix: string): bool {
    if len(suffix) > len(s) {
        ret false
    }
    ret slice(s, len(s) - len(suffix), len(s)) == suffix
}

// Est vide
pub fn is_empty(s: string): bool {
    ret len(s) == 0
}

// Est un nombre
pub fn is_number(s: string): bool {
    if is_empty(s) { ret false }
    lt i = 0
    if char_at(s, 0) == "-" { i = 1 }
    while i < len(s) {
        lt c = char_at(s, i)
        if c < "0" || c > "9" {
            ret false
        }
        i = i + 1
    }
    ret len(s) > 0
}

// Est alphabétique
pub fn is_alpha(s: string): bool {
    if is_empty(s) { ret false }
    lt i = 0
    while i < len(s) {
        lt c = char_at(s, i)
        if !((c >= "a" && c <= "z") || (c >= "A" && c <= "Z")) {
            ret false
        }
        i = i + 1
    }
    ret true
}

// Est alphanumérique
pub fn is_alnum(s: string): bool {
    if is_empty(s) { ret false }
    lt i = 0
    while i < len(s) {
        lt c = char_at(s, i)
        if !((c >= "a" && c <= "z") || 
             (c >= "A" && c <= "Z") || 
             (c >= "0" && c <= "9")) {
            ret false
        }
        i = i + 1
    }
    ret true
}

// ============================================
// REMPLACEMENT
// ============================================

// Remplacer toutes les occurrences
pub fn replace_all(s: string, old: string, new: string): string {
    lt cmd = f"echo '{s}' | sed 's/{old}/{new}/g'"
    lt result = await cmd
    ret trim_right(result, "\n")
}

// Remplacer la première occurrence
pub fn replace_first(s: string, old: string, new: string): string {
    lt cmd = f"echo '{s}' | sed 's/{old}/{new}/'"
    lt result = await cmd
    ret trim_right(result, "\n")
}

// ============================================
// SPLIT ET JOIN
// ============================================

// Diviser une chaîne (via awk)
pub fn split(s: string, delimiter: string): string {
    // Retourne les éléments séparés par des newlines
    lt cmd = f"echo '{s}' | awk -F'{delimiter}' '{{for(i=1;i<=NF;i++) print $i}}'"
    lt result = await cmd
    ret result
}

// Joindre des chaînes (simplifié)
pub fn join(parts: string, separator: string): string {
    // Pour l'instant, version simple
    ret replace_all(parts, "\n", separator)
}

// ============================================
// CONVERSION
// ============================================

// Convertir en nombre
pub fn to_int(s: string): int {
    ret atoi_c(s)
}

// Convertir en float
pub fn to_float(s: string): float {
    ret atof_c(s)
}

// Répéter une chaîne
pub fn repeat(s: string, count: int): string {
    lt result = ""
    lt i = 0
    while i < count {
        result = result + s
        i = i + 1
    }
    ret result
}

// Inverser une chaîne
pub fn reverse(s: string): string {
    lt cmd = f"echo '{s}' | rev"
    lt result = await cmd
    ret trim_right(result, "\n")
}

// ============================================
// HASHAGE SIMPLE
// ============================================

// Hash MD5
pub fn md5(s: string): string {
    lt cmd = f"echo -n '{s}' | md5sum | cut -d' ' -f1"
    lt result = await cmd
    ret trim(result)
}

// Hash SHA256
pub fn sha256(s: string): string {
    lt cmd = f"echo -n '{s}' | sha256sum | cut -d' ' -f1"
    lt result = await cmd
    ret trim(result)
}

// ============================================
// ENCODAGE
// ============================================

// Base64 encode
pub fn base64_encode(s: string): string {
    lt cmd = f"echo -n '{s}' | base64"
    lt result = await cmd
    ret trim(result)
}

// Base64 decode
pub fn base64_decode(s: string): string {
    lt cmd = f"echo -n '{s}' | base64 -d"
    lt result = await cmd
    ret result
}
