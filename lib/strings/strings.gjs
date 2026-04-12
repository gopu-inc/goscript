module strings

// ============================================
// FONCTIONS DE BASE (via commandes shell)
// ============================================

pub fn len(s: string): int {
    lt cmd = "echo -n '" + s + "' | wc -c"
    lt result = await cmd
    ret to_int(trim(result))
}

pub fn to_upper(s: string): string {
    lt cmd = "echo -n '" + s + "' | tr '[:lower:]' '[:upper:]'"
    lt result = await cmd
    ret result
}

pub fn to_lower(s: string): string {
    lt cmd = "echo -n '" + s + "' | tr '[:upper:]' '[:lower:]'"
    lt result = await cmd
    ret result
}

pub fn contains(s: string, substr: string): bool {
    lt cmd = "echo -n '" + s + "' | grep -q '" + substr + "' && echo -n true || echo -n false"
    lt result = await cmd
    ret result == "true"
}

pub fn trim(s: string): string {
    lt cmd = "echo -n '" + s + "' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//'"
    lt result = await cmd
    ret result
}

pub fn slice(s: string, start: int, end: int): string {
    lt length = end - start
    if length <= 0 {
        ret ""
    }
    // cut utilise des index 1-based
    lt start1 = start + 1
    lt cmd = "echo -n '" + s + "' | cut -c" + start1 + "-" + end
    lt result = await cmd
    ret result
}

pub fn char_at(s: string, index: int): string {
    ret slice(s, index, index + 1)
}

pub fn starts_with(s: string, prefix: string): bool {
    lt prefix_len = len(prefix)
    if prefix_len > len(s) {
        ret false
    }
    ret slice(s, 0, prefix_len) == prefix
}

pub fn ends_with(s: string, suffix: string): bool {
    lt suffix_len = len(suffix)
    lt s_len = len(s)
    if suffix_len > s_len {
        ret false
    }
    ret slice(s, s_len - suffix_len, s_len) == suffix
}

pub fn is_empty(s: string): bool {
    ret len(s) == 0
}

pub fn replace_all(s: string, old: string, new_str: string): string {
    lt cmd = "echo -n '" + s + "' | sed 's/" + old + "/" + new_str + "/g'"
    lt result = await cmd
    ret result
}

pub fn replace_first(s: string, old: string, new_str: string): string {
    lt cmd = "echo -n '" + s + "' | sed 's/" + old + "/" + new_str + "/'"
    lt result = await cmd
    ret result
}

pub fn repeat(s: string, count: int): string {
    lt result = ""
    lt i = 0
    while i < count {
        result = result + s
        i = i + 1
    }
    ret result
}

pub fn reverse(s: string): string {
    lt cmd = "echo -n '" + s + "' | rev"
    lt result = await cmd
    ret result
}

pub fn to_int(s: string): int {
    // Enlever les caractères non-numériques
    lt cmd = "echo -n '" + s + "' | tr -cd '0-9'"
    lt result = await cmd
    if result == "" {
        ret 0
    }
    // Conversion manuelle
    ret parse_int(result)
}

// Helper: conversion string -> int
fn parse_int(s: string): int {
    lt result = 0
    lt i = 0
    lt len_s = 0
    // Calculer la longueur avec wc
    lt cmd = "echo -n '" + s + "' | wc -c"
    lt len_str = await cmd
    len_s = to_int(trim(len_str))
    
    while i < len_s {
        lt c = slice(s, i, i + 1)
        if c >= "0" && c <= "9" {
            result = result * 10 + (char_to_int(c))
        }
        i = i + 1
    }
    ret result
}

fn char_to_int(c: string): int {
    if c == "0" { ret 0 }
    if c == "1" { ret 1 }
    if c == "2" { ret 2 }
    if c == "3" { ret 3 }
    if c == "4" { ret 4 }
    if c == "5" { ret 5 }
    if c == "6" { ret 6 }
    if c == "7" { ret 7 }
    if c == "8" { ret 8 }
    if c == "9" { ret 9 }
    ret 0
}
