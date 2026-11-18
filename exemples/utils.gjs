golem utils

pub const VERSION = "1.0"

pub fn to_upper(s: string): string {
    extern fn toupper(c: int): int
    lt result = ""
    lt i = 0
    while i < len(s) {
        lt c = s[i]
        if c >= 'a' && c <= 'z' {
            c = c - 32
        }
        result = result + string(c)
        i = i + 1
    }
    ret result
}

pub fn to_lower(s: string): string {
    lt result = ""
    lt i = 0
    while i < len(s) {
        lt c = s[i]
        if c >= 'A' && c <= 'Z' {
            c = c + 32
        }
        result = result + string(c)
        i = i + 1
    }
    ret result
}

pub fn reverse(s: string): string {
    lt result = ""
    lt i = len(s) - 1
    while i >= 0 {
        result = result + string(s[i])
        i = i - 1
    }
    ret result
}
