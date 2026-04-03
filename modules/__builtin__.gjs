module __builtin__

// =========================================================
// 1. MATHÉMATIQUES
// =========================================================

pub cn PI = 3.14159265359
pub cn E  = 2.71828182846

pub fn abs(n) {
    if n < 0 { 
        ret -n 
    }
    ret n
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

pub fn clamp(val, min_val, max_val) {
    if val < min_val { ret min_val }
    if val > max_val { ret max_val }
    ret val
}

pub fn pow(base, exp) {
    lt result = 1
    lt i = 0
    while i < exp {
        result = result * base
        i = i + 1
    }
    ret result
}

// =========================================================
// 2. CHAÎNES ET LOGIQUE
// =========================================================

// L'opérateur == de Goscript compare déjà les chaînes en natif !
pub fn str_compare(s1, s2) {
    ret s1 == s2
}

// =========================================================
// 3. UTILITAIRES DE COLLECTIONS
// =========================================================

pub fn each(collection, callback) {
    for item in collection {
        callback(item)
    }
}

// =========================================================
// 4. DÉBOGAGE
// =========================================================

pub fn assert(condition, message) {
    if !condition {
        print("[ERREUR ASSERTION] ")
        println(message)
    } else {
        print("[OK] ")
        println(message)
    }
}
