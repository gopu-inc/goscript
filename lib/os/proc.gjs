module proc

pub fn my_pid(): string {
    lt cmd = "sh -c \"echo $$\""
    lt result = await cmd
    ret result
}

pub fn ppid(): string {
    lt cmd = "sh -c \"echo $PPID\""
    lt result = await cmd
    ret result
}

pub fn list(): string {
    lt cmd = "sh -c \"ps\""
    lt result = await cmd
    ret result
}
