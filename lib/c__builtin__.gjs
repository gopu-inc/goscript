// ============================================
// Built-in Module for Gopu.inc
// Chargé automatiquement au démarrage
// ============================================

pub const VERSION = "0.2.0"
pub const AUTHOR = "Gopu.inc Team"
pub const PI = 3.141592653589793
pub const E = 2.718281828459045
pub const DEBUG = false

// ============================================
// Assertions
// ============================================
pub fn assert(condition: bool, message: string): bool {
    if !condition {
        println("[ASSERT FAILED] " + message)
        ret false
    }
    ret true
}

pub fn assert_eq(a, b, message: string): bool {
    if a != b {
        println("[ASSERT FAILED] " + message + " (" + a + " != " + b + ")")
        ret false
    }
    ret true
}

// ============================================
// Logging utilities
// ============================================
pub fn log(level: string, msg: string) {
    println("[" + level + "] " + msg)
}

pub fn info(msg: string) {
    log("INFO", msg)
}

pub fn warn(msg: string) {
    log("WARN", msg)
}

pub fn error(msg: string) {
    log("ERROR", msg)
}

pub fn debug(msg: string) {
    if DEBUG {
        log("DEBUG", msg)
    }
}

// ============================================
// Math utilities
// ============================================
pub fn abs(x: int): int {
    if x < 0 {
        ret -x
    }
    ret x
}

pub fn max(a, b) {
    if a > b {
        ret a
    }
    ret b
}

pub fn min(a, b) {
    if a < b {
        ret a
    }
    ret b
}

pub fn clamp(x, low, high) {
    if x < low {
        ret low
    }
    if x > high {
        ret high
    }
    ret x
}

// ============================================
// String utilities
// ============================================
pub fn is_empty(s: string): bool {
    ret s == ""
}

pub fn not_empty(s: string): bool {
    ret s != ""
}

pub fn len(s: string): int {
    muts count = 0
    for _ in s {
        count = count + 1
    }
    ret count
}

pub fn contains(s: string, substr: string): bool {
    muts i = 0
    muts s_len = len(s)
    muts sub_len = len(substr)
    
    while i <= s_len - sub_len {
        muts j = 0
        muts match = true
        while j < sub_len {
            if s[i + j] != substr[j] {
                match = false
                break
            }
            j = j + 1
        }
        if match {
            ret true
        }
        i = i + 1
    }
    ret false
}

// ============================================
// Type utilities
// ============================================
pub fn type_of(value) {
    ret "unknown"
}

// ============================================
// Timing utilities
// ============================================
pub fn now(): int {
    ret system("date +%s")
}
