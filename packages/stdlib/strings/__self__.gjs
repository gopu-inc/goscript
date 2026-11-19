golem strings

pub fn len(value: string): int { ret strlen_c(value) }
pub fn to_upper(value: string): string { ret gs_string_upper(value, 1) }
pub fn to_lower(value: string): string { ret gs_string_lower(value, 0) }
pub fn contains(value: string, part: string): bool { ret gs_string_contains(value, part) == 1 }
pub fn trim(value: string): string { ret gs_string_trim(value) }
pub fn slice(value: string, start: string, end: string): string {
    ret gs_string_slice(value, start, end)
}
pub fn starts_with(value: string, prefix: string): bool { ret gs_string_starts(value, prefix) == 1 }
pub fn ends_with(value: string, suffix: string): bool { ret gs_string_ends(value, suffix) == 1 }
pub fn replace_first(value: string, old: string, replacement: string): string {
    ret gs_string_replace_first(value, old, replacement, 0)
}
pub fn replace_all(value: string, old: string, replacement: string): string {
    ret gs_string_replace_all(value, old, replacement, 1)
}
pub fn reverse(value: string): string { ret gs_string_reverse(value) }
pub fn capitalize(value: string): string {
    if value == "" { ret "" }
    lt first = gs_string_slice(value, "1", "1")
    lt rest = gs_string_slice(value, "2", str(strlen_c(value)))
    ret gs_string_upper(first, 1) + gs_string_lower(rest, 0)
}
pub fn count(value: string, part: string): int { ret gs_string_count(value, part) }
