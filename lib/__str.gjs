// Module __str - Version ultra-minimaliste
// Seulement les fonctions qui ne causent pas de segfault

pub fn len(s: string): int {
    if s == nil { ret 0 }
    ret strlen_c(s)
}

pub fn contains(s: string, sub: string): bool {
    if s == nil || sub == nil { ret false }
    ret strstr_c(s, sub) != nil
}

pub fn to_int(s: string): int {
    if s == nil { ret 0 }
    ret atoi_c(s)
}

pub fn to_float(s: string): float {
    if s == nil { ret 0.0 }
    ret atof_c(s)
}

// Pas de to_upper, to_lower, trim, substring pour l'instant
