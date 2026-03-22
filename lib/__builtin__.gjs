// ============================================
// Built-in Module for Gopu.inc
// Chargé automatiquement au démarrage
// ============================================

pub cn VERSION = "0.2.0"
pub cn AUTHOR = "Gopu.inc Team"
pub cn PI = 3.141592653589793
pub cn E = 2.718281828459045

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

pub fn contains(s: string, substr: string): bool {
    // Implementation simple - à améliorer avec FFI
    muts i = 0
    muts j = 0
    
    while i < len(s) {
        if s[i] == substr[0] {
            j = 0
            while j < len(substr) && i + j < len(s) && s[i + j] == substr[j] {
                j = j + 1
            }
            if j == len(substr) {
                ret true
            }
        }
        i = i + 1
    }
    ret false
}

// ============================================
// Type utilities
// ============================================
pub fn type_of(value) {
    // À implémenter avec FFI
    ret "unknown"
}

// ============================================
// Timing utilities
// ============================================
pub fn now(): int {
    ret system("date +%s")
}

// ============================================
// Debug flag
// ============================================
pub cn DEBUG = false
