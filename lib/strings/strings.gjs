module strings

// ============================================
// HELPER: Échapper les guillemets doubles
// ============================================

fn escape(s: string): string {
    lt cmd = "echo -n \"" + s + "\" | sed 's/\"/\\\\\"/g'"
    lt result = await cmd
    ret result
}

// ============================================
// FONCTIONS DE BASE
// ============================================

pub fn len(s: string): string {
    lt escaped = escape(s)
    lt cmd = "echo -n \"" + escaped + "\" | wc -c | tr -d ' \n\t'"
    lt result = await cmd
    ret result
}

pub fn to_upper(s: string): string {
    lt escaped = escape(s)
    lt cmd = "echo -n \"" + escaped + "\" | tr '[:lower:]' '[:upper:]'"
    lt result = await cmd
    ret result
}

pub fn to_lower(s: string): string {
    lt escaped = escape(s)
    lt cmd = "echo -n \"" + escaped + "\" | tr '[:upper:]' '[:lower:]'"
    lt result = await cmd
    ret result
}

pub fn contains(s: string, substr: string): string {
    lt escaped_s = escape(s)
    lt escaped_sub = escape(substr)
    lt cmd = "echo -n \"" + escaped_s + "\" | grep -q \"" + escaped_sub + "\" && echo -n true || echo -n false"
    lt result = await cmd
    ret result
}

pub fn trim(s: string): string {
    lt escaped = escape(s)
    lt cmd = "echo -n \"" + escaped + "\" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//'"
    lt result = await cmd
    ret result
}

pub fn starts_with(s: string, prefix: string): string {
    lt escaped_s = escape(s)
    lt escaped_pref = escape(prefix)
    lt cmd = "echo -n \"" + escaped_s + "\" | grep -q \"^" + escaped_pref + "\" && echo -n true || echo -n false"
    lt result = await cmd
    ret result
}

pub fn ends_with(s: string, suffix: string): string {
    lt escaped_s = escape(s)
    lt escaped_suff = escape(suffix)
    lt cmd = "echo -n \"" + escaped_s + "\" | grep -q \"" + escaped_suff + "$\" && echo -n true || echo -n false"
    lt result = await cmd
    ret result
}

pub fn replace_first(s: string, old: string, new_str: string): string {
    lt escaped_s = escape(s)
    lt escaped_old = escape(old)
    lt escaped_new = escape(new_str)
    lt cmd = "echo -n \"" + escaped_s + "\" | sed 's/" + escaped_old + "/" + escaped_new + "/'"
    lt result = await cmd
    ret result
}

pub fn reverse(s: string): string {
    lt escaped = escape(s)
    lt cmd = "echo -n \"" + escaped + "\" | rev"
    lt result = await cmd
    ret result
}