module request

pub fn get_method(req: string): string {
    lt cmd = "echo \"$1\" | head -1 | cut -d\" \" -f1"
    lt result = await cmd
    ret result
}

pub fn get_path(req: string): string {
    lt cmd = "echo \"$1\" | head -1 | cut -d\" \" -f2"
    lt result = await cmd
    ret result
}
