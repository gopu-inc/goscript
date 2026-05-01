module env

pub fn user(): string {
    lt cmd = "sh -c \"echo $USER\""
    lt result = await cmd
    ret result
}

pub fn home(): string {
    lt cmd = "sh -c \"echo $HOME\""
    lt result = await cmd
    ret result
}

pub fn shell(): string {
    lt cmd = "sh -c \"echo $SHELL\""
    lt result = await cmd
    ret result
}

pub fn pwd(): string {
    lt cmd = "sh -c \"pwd\""
    lt result = await cmd
    ret result
}

pub fn path(): string {
    lt cmd = "sh -c \"echo $PATH\""
    lt result = await cmd
    ret result
}
pub fn getenv(w: string): string {
    lt GET = "echo $" + w + ""
    lt EXEC = sysf(GET)
    ret EXEC
}
   
