module user

pub fn current(): string {
    lt cmd = "sh -c \"whoami\""
    lt result = await cmd
    ret result
}

pub fn id(): string {
    lt cmd = "sh -c \"id\""
    lt result = await cmd
    ret result
}

pub fn groups(): string {
    lt cmd = "sh -c \"groups\""
    lt result = await cmd
    ret result
}

pub fn users_list(): string {
    lt cmd = "sh -c \"cat /etc/passwd | cut -d: -f1\""
    lt result = await cmd
    ret result
}

pub fn is_root(): string {
    lt cmd = "sh -c \"test $(id -u) -eq 0 && echo true || echo false\""
    lt result = await cmd
    ret result
}
