// fms.gjs - Version corrigée SANS f-string

module fms

// ============================================
// CONVERSIONS
// ============================================

pub fn to_str(value: string): string {
    ret value
}

pub fn to_int(value: string): string {
    lt cmd = "echo '" + value + "' | grep -oE '^-?[0-9]+' | head -1"
    lt result = await cmd
    if result == "" {
        ret "0"
    }
    ret result
}

pub fn to_float(value: string): string {
    lt cmd = "echo '" + value + "' | grep -oE '^-?[0-9]+\\.[0-9]+' | head -1"
    lt result = await cmd
    if result == "" {
        ret "0.0"
    }
    ret result
}

pub fn to_bool(value: string): string {
    if value == "" || value == "0" || value == "false" || value == "nil" {
        ret "false"
    }
    ret "true"
}

pub fn is_int(value: string): string {
    lt cmd = "echo '" + value + "' | grep -qE '^-?[0-9]+$' && echo true || echo false"
    lt result = await cmd
    ret result
}

pub fn is_float(value: string): string {
    lt cmd = "echo '" + value + "' | grep -qE '^-?[0-9]+\\.[0-9]+$' && echo true || echo false"
    lt result = await cmd
    ret result
}

pub fn is_bool(value: string): string {
    if value == "true" || value == "false" {
        ret "true"
    }
    ret "false"
}
