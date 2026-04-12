module strings

// ============================================
// FONCTIONS DE BASE (uniquement await + shell)
// ============================================

pub fn len(s: string): string {
    lt cmd = "echo -n '" + s + "' | wc -c | tr -d ' \n\t'"
    lt result = await cmd
    ret result
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

pub fn contains(s: string, substr: string): string {
    lt cmd = "echo -n '" + s + "' | grep -q '" + substr + "' && echo -n true || echo -n false"
    lt result = await cmd
    ret result
}

pub fn trim(s: string): string {
    lt cmd = "echo -n '" + s + "' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//'"
    lt result = await cmd
    ret result
}

pub fn slice(s: string, start: string, end: string): string {
    lt cmd = "echo -n '" + s + "' | cut -c " + start + "-" + end
    lt result = await cmd
    ret result
}

pub fn starts_with(s: string, prefix: string): string {
    lt cmd = "echo -n '" + s + "' | grep -q '^" + prefix + "' && echo -n true || echo -n false"
    lt result = await cmd
    ret result
}

pub fn ends_with(s: string, suffix: string): string {
    lt cmd = "echo -n '" + s + "' | grep -q '" + suffix + "$' && echo -n true || echo -n false"
    lt result = await cmd
    ret result
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

pub fn reverse(s: string): string {
    lt cmd = "echo -n '" + s + "' | rev"
    lt result = await cmd
    ret result
}

pub fn capitalize(s: string): string {
    lt cmd = "echo -n '" + s + "' | sed 's/.*/\\L&/; s/^./\\U&/'"
    lt result = await cmd
    ret result
}

pub fn count(s: string, substr: string): string {
    lt cmd = "echo -n '" + s + "' | grep -o '" + substr + "' | wc -l | tr -d ' \n\t'"
    lt result = await cmd
    ret result
}
