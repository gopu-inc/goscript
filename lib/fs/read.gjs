module read

pub fn file_r(path: string): string {
    lt cmd = "sh -c \"cat " + path + "\""
    lt result = await cmd
    ret result
}

pub fn lines(path: string): string {
    lt cmd = "sh -c \"cat " + path + " | wc -l\""
    lt result = await cmd
    ret result
}
