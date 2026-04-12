module write

pub fn file_w(path: string, content: string): string {
    lt cmd = "sh -c \"echo " + content + " > " + path + "\""
    lt result = await cmd
    ret "ok"
}

pub fn files(path: string, content: string): string {
    lt cmd = "sh -c \"echo " + content + " > " + path + "\""
    lt result = await cmd
    ret "ok"
}
