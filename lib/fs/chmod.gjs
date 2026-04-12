module_name chmod

pub fn set(path: string, mode: string): string {
    lt cmd = f"chmod {mode} '{path}'"
    lt result = await cmd
    ret "ok"
}

pub fn executable(path: string): string {
    lt cmd = f"chmod +x '{path}'"
    lt result = await cmd
    ret "ok"
}

pub fn readonly(path: string): string {
    lt cmd = f"chmod 444 '{path}'"
    lt result = await cmd
    ret "ok"
}

pub fn writable(path: string): string {
    lt cmd = f"chmod 644 '{path}'"
    lt result = await cmd
    ret "ok"
}
