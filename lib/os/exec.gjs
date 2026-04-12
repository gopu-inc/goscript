module exec

pub fn command(cmd: string): string {
    lt full_cmd = "sh -c \"" + cmd + "\""
    lt result = await full_cmd
    ret result
}

pub fn shell(cmd: string): string {
    lt result = await cmd
    ret result
}

pub fn background(cmd: string): string {
    lt full_cmd = "sh -c \"" + cmd + " &\""
    lt result = await full_cmd
    ret "ok"
}
