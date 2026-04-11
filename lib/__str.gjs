// ============================================
// Module __str - Manipulation de chaînes 100% Goscript
// Pas de FFI, pas de libc, tout est natif
// ============================================

pub cn VERSION = "1.0.0"

// Longueur d'une chaîne (implémentation maison)
pub fn len(s: string): int {
    if s == nil {
        ret 0
    }
    muts count = 0
    muts i = 0
    loop {
        if s[i] == 0 {
            break
        }
        count = count + 1
        i = i + 1
    }
    ret count
}

// Convertir en majuscules
pub fn to_upper(s: string): string {
    if s == nil {
        ret ""
    }
    muts result = ""
    muts i = 0
    while i < len(s) {
        muts c = s[i]
        if c >= 'a' && c <= 'z' {
            c = c - 32
        }
        result = result + string(c)
        i = i + 1
    }
    ret result
}

// Convertir en minuscules
pub fn to_lower(s: string): string {
    if s == nil {
        ret ""
    }
    muts result = ""
    muts i = 0
    while i < len(s) {
        muts c = s[i]
        if c >= 'A' && c <= 'Z' {
            c = c + 32
        }
        result = result + string(c)
        i = i + 1
    }
    ret result
}

// Vérifier si une chaîne contient une sous-chaîne
pub fn contains(s: string, substr: string): bool {
    if s == nil || substr == nil {
        ret false
    }
    muts s_len = len(s)
    muts sub_len = len(substr)
    
    if sub_len == 0 {
        ret true
    }
    if sub_len > s_len {
        ret false
    }
    
    muts i = 0
    while i <= s_len - sub_len {
        muts j = 0
        muts match = true
        while j < sub_len {
            if s[i + j] != substr[j] {
                match = false
                break
            }
            j = j + 1
        }
        if match {
            ret true
        }
        i = i + 1
    }
    ret false
}

// Extraire une sous-chaîne
pub fn substring(s: string, start: int, end: int): string {
    if s == nil {
        ret ""
    }
    muts s_len = len(s)
    if start < 0 { start = 0 }
    if end > s_len { end = s_len }
    if start >= end {
        ret ""
    }
    
    muts result = ""
    muts i = start
    while i < end {
        result = result + string(s[i])
        i = i + 1
    }
    ret result
}

// Index de la première occurrence
pub fn index_of(s: string, substr: string): int {
    if s == nil || substr == nil {
        ret -1
    }
    muts s_len = len(s)
    muts sub_len = len(substr)
    
    if sub_len == 0 {
        ret 0
    }
    if sub_len > s_len {
        ret -1
    }
    
    muts i = 0
    while i <= s_len - sub_len {
        muts j = 0
        muts match = true
        while j < sub_len {
            if s[i + j] != substr[j] {
                match = false
                break
            }
            j = j + 1
        }
        if match {
            ret i
        }
        i = i + 1
    }
    ret -1
}

// Remplacer toutes les occurrences
pub fn replace(s: string, old: string, new: string): string {
    if s == nil || old == nil {
        ret s
    }
    muts result = ""
    muts i = 0
    muts s_len = len(s)
    muts old_len = len(old)
    
    while i < s_len {
        muts found = true
        muts j = 0
        while j < old_len && i + j < s_len {
            if s[i + j] != old[j] {
                found = false
                break
            }
            j = j + 1
        }
        
        if found && old_len > 0 {
            result = result + new
            i = i + old_len
        } else {
            result = result + string(s[i])
            i = i + 1
        }
    }
    ret result
}

// Supprimer les espaces au début et à la fin
pub fn trim(s: string): string {
    if s == nil {
        ret ""
    }
    muts s_len = len(s)
    muts start = 0
    muts end = s_len - 1
    
    while start < s_len && (s[start] == ' ' || s[start] == '\t' || s[start] == '\n') {
        start = start + 1
    }
    while end >= 0 && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n') {
        end = end - 1
    }
    
    if start > end {
        ret ""
    }
    ret substring(s, start, end + 1)
}

// Diviser une chaîne en tableau
pub fn split(s: string, sep: string): []string {
    muts result = []
    if s == nil {
        ret result
    }
    if sep == nil || len(sep) == 0 {
        ret [s]
    }
    
    muts start = 0
    muts pos = index_of(s, sep)
    
    while pos != -1 {
        result = push(result, substring(s, start, pos))
        start = pos + len(sep)
        pos = index_of(substring(s, start, len(s)), sep)
        if pos != -1 {
            pos = pos + start
        }
    }
    
    result = push(result, substring(s, start, len(s)))
    ret result
}

// Joindre un tableau de chaînes
pub fn join(arr: []string, sep: string): string {
    if arr == nil {
        ret ""
    }
    muts result = ""
    muts arr_len = len(arr)
    
    muts i = 0
    while i < arr_len {
        if i > 0 {
            result = result + sep
        }
        result = result + arr[i]
        i = i + 1
    }
    ret result
}

// Vérifier si la chaîne commence par un préfixe
pub fn starts_with(s: string, prefix: string): bool {
    if s == nil || prefix == nil {
        ret false
    }
    ret substring(s, 0, len(prefix)) == prefix
}

// Vérifier si la chaîne termine par un suffixe
pub fn ends_with(s: string, suffix: string): bool {
    if s == nil || suffix == nil {
        ret false
    }
    muts s_len = len(s)
    muts suf_len = len(suffix)
    if suf_len > s_len {
        ret false
    }
    ret substring(s, s_len - suf_len, s_len) == suffix
}

// Convertir en entier
pub fn to_int(s: string): int {
    if s == nil {
        ret 0
    }
    muts result = 0
    muts i = 0
    muts sign = 1
    muts s_len = len(s)
    
    if s_len > 0 && s[0] == '-' {
        sign = -1
        i = 1
    }
    
    while i < s_len {
        muts c = s[i]
        if c >= '0' && c <= '9' {
            result = result * 10 + (c - '0')
        } else {
            break
        }
        i = i + 1
    }
    ret result * sign
}

// Convertir en flottant
pub fn to_float(s: string): float {
    if s == nil {
        ret 0.0
    }
    muts result = 0.0
    muts i = 0
    muts sign = 1.0
    muts s_len = len(s)
    
    if s_len > 0 && s[0] == '-' {
        sign = -1.0
        i = 1
    }
    
    while i < s_len && s[i] >= '0' && s[i] <= '9' {
        result = result * 10.0 + (s[i] - '0')
        i = i + 1
    }
    
    if i < s_len && s[i] == '.' {
        i = i + 1
        muts divisor = 10.0
        while i < s_len && s[i] >= '0' && s[i] <= '9' {
            result = result + (s[i] - '0') / divisor
            divisor = divisor * 10.0
            i = i + 1
        }
    }
    
    ret result * sign
}

// Fonctions helper
fn push(arr: []string, val: string): []string {
    ret arr + [val]
}

fn len(arr: []string): int {
    if arr == nil {
        ret 0
    }
    muts count = 0
    loop {
        if arr[count] == nil {
            break
        }
        count = count + 1
        if count > 1000 { break } // sécurité
    }
    ret count
}
