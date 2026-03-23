// Built-in minimal

pub cn VERSION = "0.3.0"
pub cn PI = 3.14159

// Time
pub fn time(): int {
    ret time_c(0)
}

pub fn clock(): int {
    ret clock_c()
}

// System
pub fn system(cmd: string): int {
    ret system_c(cmd)
}

pub fn getpid(): int {
    ret getpid_c()
}

// String
pub fn strlen(s: string): int {
    ret strlen_c(s)
}

// Math
pub fn abs(x: int): int {
    if x < 0 { ret -x }
    ret x
}

pub fn max(a, b) {
    if a > b { ret a }
    ret b
}

pub fn min(a, b) {
    if a < b { ret a }
    ret b
}

// Colors
pub cn COLOR_RESET = "033[0m"
pub cn COLOR_RED = "033[31m"
pub cn COLOR_GREEN = "033[32m"
pub cn COLOR_YELLOW = "033[33m"
pub cn COLOR_CYAN = "033[36m"

pub fn colorize(text: string, color: string): string {
    ret color + text + COLOR_RESET
}

// Info
pub fn info(msg: string) {
    println("[INFO] " + msg)
}

// Type of (temporaire)
pub fn type_of(obj) {
    ret "unknown"
}

