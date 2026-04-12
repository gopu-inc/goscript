module strings

// ============================================
// CONVERSION STRING -> INT (fait maison)
// ============================================

fn str_to_int(s: string): int {
    if s == "" {
        ret 0
    }
    lt result = 0
    lt i = 0
    while i < 20 {
        lt c = char_at(s, i)
        if c == "" {
            break
        }
        if c == "0" { result = result * 10 + 0 }
        if c == "1" { result = result * 10 + 1 }
        if c == "2" { result = result * 10 + 2 }
        if c == "3" { result = result * 10 + 3 }
        if c == "4" { result = result * 10 + 4 }
        if c == "5" { result = result * 10 + 5 }
        if c == "6" { result = result * 10 + 6 }
        if c == "7" { result = result * 10 + 7 }
        if c == "8" { result = result * 10 + 8 }
        if c == "9" { result = result * 10 + 9 }
        i = i + 1
    }
    ret result
}

// ============================================
// EXTRACTION DE CARACTÈRE (via cut)
// ============================================

fn char_at(s: string, index: int): string {
    lt pos = index + 1
    lt cmd = "echo -n '" + s + "' | cut -c " + pos
    lt result = await cmd
    ret result
}

// ============================================
// FONCTIONS PUBLIQUES
// ============================================

pub fn len(s: string): int {
    lt cmd = "echo -n '" + s + "' | wc -c"
    lt result = await cmd
    // Nettoyer les espaces
    lt cleaned = ""
    lt i = 0
    while i < 10 {
        lt c = char_at(result, i)
        if c == "" { break }
        if c != " " && c != "\n" && c != "\t" {
            cleaned = cleaned + c
        }
        i = i + 1
    }
    ret str_to_int(cleaned)
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
    lt start1 = start + 1
    lt cmd = "echo -n '" + s + "' | cut -c " + start1 + "-" + end
    lt result = await cmd
    ret result
}

pub fn starts_with(s: string, prefix: string): bool {
    lt prefix_len = len(prefix)
    lt s_len = len(s)
    if prefix_len > s_len {
        ret false
    }
    lt extracted = slice(s, 0, prefix_len)
    ret extracted == prefix
}

pub fn ends_with(s: string, suffix: string): bool {
    lt suffix_len = len(suffix)
    lt s_len = len(s)
    if suffix_len > s_len {
        ret false
    }
    lt extracted = slice(s, s_len - suffix_len, s_len)
    ret extracted == suffix
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

pub fn capitalize(s: string): string {
    if is_empty(s) {
        ret ""
    }
    lt first = slice(s, 0, 1)
    lt rest = slice(s, 1, len(s))
    ret to_upper(first) + to_lower(rest)
}

pub fn count(s: string, substr: string): int {
    lt cmd = "echo -n '" + s + "' | grep -o '" + substr + "' | wc -l"
    lt result = await cmd
    lt cleaned = ""
    lt i = 0
    while i < 10 {
        lt c = char_at(result, i)
        if c == "" { break }
        if c != " " && c != "\n" && c != "\t" {
            cleaned = cleaned + c
        }
        i = i + 1
    }
    ret str_to_int(cleaned)
}
