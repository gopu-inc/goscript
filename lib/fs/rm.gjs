module_name rm

pub fn file(path: string): string {
    lt cmd = f"rm -f '{path}'"
    lt result = await cmd
    ret "ok"
}

pub fn dir(path: string): string {
    lt cmd = f"rm -rf '{path}'"
    lt result = await cmd
    ret "ok"
}

pub fn empty_dir(path: string): string {
    lt cmd = f"rmdir '{path}' 2>/dev/null"
    lt result = await cmd
    ret "ok"
}

pub fn pattern(path: string, pattern: string): string {
    lt cmd = f"find '{path}' -name '{pattern}' -delete"
    lt result = await cmd
    ret "ok"
}
