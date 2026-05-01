// Math utilities for Goscript

// lib/math.gjs
module math

// Racine carrée
pub fn sqrt(n: float): string {
    ret sysf("awk 'BEGIN { print sqrt(" + n + ") }'")
}

// Puissance (n^p)
pub fn pow(n: float, p: float): string {
    ret sysf("awk 'BEGIN { print " + n + " ^ " + p + " }'")
}

// Arrondi (Round)
pub fn round(n: float): string {
    ret sysf("awk 'BEGIN { printf(\"%.0f\", " + n + ") }'")
}

// Valeur absolue
pub fn abs(n: float): string {
    ret sysf("awk 'BEGIN { print (" + n + " < 0) ? -" + n + " : " + n + " }'")
}

// Générer un nombre aléatoire entre 0 et max
pub fn random(max: int): string {
    // Utilise l'heure actuelle comme graine (seed) pour plus de hasard
    ret sysf("awk 'BEGIN { srand(); print int(rand() * " + max + ") }'")
}

