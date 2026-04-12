module_name search

// ============================================
// RECHERCHE DE FICHIERS
// ============================================

pub fn search_path(path: string): string {
    lt research = f"ls {path}"
    lt result = await research
    ret result
}

pub fn search_info(path: string): string {
    lt ser = f"ls -la {path}"
    lt result = await ser
    ret result
}

pub fn search_all(path: string): string {
    lt ser = f"ls -a {path}"
    lt result = await ser
    ret result
}

// ============================================
// RECHERCHE AVEC PATTERN
// ============================================

pub fn search_pattern(path: string, pattern: string): string {
    lt cmd = f"ls {path} | grep '{pattern}'"
    lt result = await cmd
    ret result
}

pub fn find_files(path: string, name: string): string {
    lt cmd = f"find {path} -name '{name}' -file_type_str f"
    lt result = await cmd
    ret result
}

pub fn find_dirs(path: string, name: string): string {
    lt cmd = f"find {path} -name '{name}' -file_type_str d"
    lt result = await cmd
    ret result
}

// ============================================
// INFORMATIONS
// ============================================

pub fn file_exists(path: string): string {
    lt cmd = f"test -f '{path}' && echo -n true || echo -n false"
    lt result = await cmd
    ret result
}

pub fn dir_exists(path: string): string {
    lt cmd = f"test -d '{path}' && echo -n true || echo -n false"
    lt result = await cmd
    ret result
}

pub fn file_size(path: string): string {
    lt cmd = f"stat -c %s '{path}' 2>/dev/null || echo -n 0"
    lt result = await cmd
    ret result
}

pub fn file_type(path: string): string {
    lt cmd = f"file -b '{path}'"
    lt result = await cmd
    ret result
}

// ============================================
// NAVIGATION
// ============================================

pub fn current_dir(): string {
    lt cmd = "pwd"
    lt result = await cmd
    ret result
}

pub fn list_dirs(path: string): string {
    lt cmd = f"ls -d {path}/*/ 2>/dev/null | xargs -n1 basename"
    lt result = await cmd
    ret result
}

pub fn list_files(path: string): string {
    lt cmd = f"find {path} -maxdepth 1 -file_type_str f | xargs -n1 basename"
    lt result = await cmd
    ret result
}
