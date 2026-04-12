module_name mkdir

pub fn dir(path: string): string {
    lt cmd = f"mkdir -p '{path}'"
    lt result = await cmd
    ret "ok"
}

pub fn dirs(path: string): string {
    lt cmd = f"mkdir -p '{path}'"
    lt result = await cmd
    ret "ok"
}

pub fn temp(): string {
    lt cmd = "mktemp -d"
    lt result = await cmd
    ret result
}

pub fn with_parents(path: string): string {
    lt cmd = f"mkdir -p '{path}'"
    lt result = await cmd
    ret "ok"
}
