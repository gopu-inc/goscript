module which

pub fn find(cmd: string): string {
    lt full_cmd = "sh -c \"which " + cmd + "\""
    lt result = sysf(full_cmd)
    ret result
}

pub fn exists(cmd: string): string {
    lt full_cmd = "sh -c \"which " + cmd + " > /dev/null 2>&1 && echo true || echo false\""
    lt result = sysf(full_cmd)
    ret result
}
