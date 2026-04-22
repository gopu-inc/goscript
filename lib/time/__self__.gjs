// lib/time/__self__.gjs
// Module time - Point d'entrée principal

// Fonction publique accessible via time::now()
pub fn now(): string {
    ret sysf("date '+%Y-%m-%d %H:%M:%S'")
}

// Fonction publique accessible via time::timestamp()
pub fn timestamp(): int {
    lt ts = sysf("date +%s")
    // Utiliser atoi_c directement
    ret atoi_c(ts)
}
