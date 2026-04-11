// ============================================
// Module __str - Manipulation de chaînes
// Usage: import __str
//        __str::len("hello")
// ============================================

pub cn VERSION = "1.0.0"

// Longueur d'une chaîne
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
        if c >= 97 && c <= 122 {  // 'a' to 'z'
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
        if c >= 65 && c <= 90 {  // 'A' to 'Z'
            c = c + 32
        }
        result = result + string(c)
        i = i + 1
    }
    ret result
}

// Vérifier si contient
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

// Extraire sous-chaîne
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

// Remplacer
pub fn replace(s: string, old: string, new: string): string {
    if s == nil || old == nil {
        ret s
    }
    if len(old) == 0 {
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
        
        if found {
            result = result + new
            i = i + old_len
        } else {
            result = result + string(s[i])
            i = i + 1
        }
    }
    ret result
}

// Supprimer espaces
pub fn trim(s: string): string {
    if s == nil {
        ret ""
    }
    muts s_len = len(s)
    muts start = 0
    muts end = s_len - 1
    
    while start < s_len && (s[start] == 32 || s[start] == 9 || s[start] == 10) {
        start = start + 1
    }
    while end >= 0 && (s[end] == 32 || s[end] == 9 || s[end] == 10) {
        end = end - 1
    }
    
    if start > end {
        ret ""
    }
    ret substring(s, start, end + 1)
}

// Diviser
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
        pos = index_of(s, sep)
        if pos != -1 && pos < start {
            pos = -1
        }
    }
    
    result = push(result, substring(s, start, len(s)))
    ret result
}

// Joindre
pub fn join(arr: []string, sep: string): string {
    if arr == nil {
        ret ""
    }
    muts result = ""
    muts arr_len = array_len(arr)
    
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

// Début par
pub fn starts_with(s: string, prefix: string): bool {
    if s == nil || prefix == nil {
        ret false
    }
    ret substring(s, 0, len(prefix)) == prefix
}

// Fin par
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
    
    if s_len > 0 && s[0] == 45 {  // '-'
        sign = -1
        i = 1
    }
    
    while i < s_len {
        muts c = s[i]
        if c >= 48 && c <= 57 {  // '0' to '9'
            result = result * 10 + (c - 48)
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
    
    if s_len > 0 && s[0] == 45 {  // '-'
        sign = -1.0
        i = 1
    }
    
    while i < s_len && s[i] >= 48 && s[i] <= 57 {
        result = result * 10.0 + (s[i] - 48)
        i = i + 1
    }
    
    if i < s_len && s[i] == 46 {  // '.'
        i = i + 1
        muts divisor = 10.0
        while i < s_len && s[i] >= 48 && s[i] <= 57 {
            result = result + (s[i] - 48) / divisor
            divisor = divisor * 10.0
            i = i + 1
        }
    }
    
    ret result * sign
}

// Fonctions helper internes
fn push(arr: []string, val: string): []string {
    ret arr + [val]
}

fn array_len(arr: []string): int {
    if arr == nil {
        ret 0
    }
    muts count = 0
    loop {
        if arr[count] == nil {
            break
        }
        count = count + 1
    }
    ret count
}
