module sys

pub fn hostname(): string {
    lt cmd = "sh -c \"hostname\""
    lt result = await cmd
    ret result
}

pub fn os_type(): string {
    lt cmd = "sh -c \"uname -s\""
    lt result = await cmd
    ret result
}

pub fn arch(): string {
    lt cmd = "sh -c \"uname -m\""
    lt result = await cmd
    ret result
}

pub fn kernel_version(): string {
    lt cmd = "sh -c \"uname -r\""
    lt result = await cmd
    ret result
}
