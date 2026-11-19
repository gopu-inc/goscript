golem builbase

pub cn VERSION = "0.1.1"

pub fn version(): string {
    ret VERSION
}

pub fn banner(title: string) {
    println("== " + title + " ==")
}

pub fn step(message: string) {
    println("[build] " + message)
}

pub fn success(message: string) {
    println("[build] OK: " + message)
}

pub fn error(message: string) {
    println("[build] ERROR: " + message)
}

pub fn require(condition: bool, message: string): bool {
    if (condition == false) {
        error(message)
        ret false
    }
    ret true
}
