module_name cd

pub fn to(path: string): string {
    lt cmd = f"cd '{path}' && pwd"
    lt result = await cmd
    ret result
}

pub fn home(): string {
    lt cmd = "cd ~ && pwd"
    lt result = await cmd
    ret result
}

pub fn up(): string {
    lt cmd = "cd .. && pwd"
    lt result = await cmd
    ret result
}

pub fn root(): string {
    lt cmd = "cd / && pwd"
    lt result = await cmd
    ret result
}

pub fn previous(): string {
    lt cmd = "cd - && pwd"
    lt result = await cmd
    ret result
}
