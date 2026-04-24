// lib/time.gjs
module time

// Temps actuel formaté (Ex: 2026-04-24 10:45:30)
pub fn now(): string {
    ret sysf("date '+%Y-%m-%d %H:%M:%S'")
}

// Timestamp Unix (Secondes depuis 1970)
pub fn timestamp(): string {
    ret sysf("date +%s")
}

// Obtenir uniquement l'année ou le jour (utile pour les backups)
pub fn format(fmt: string): string {
    // fmt peut être "%d-%m-%Y" par exemple
    ret sysf("date '+" + fmt + "'")
}

// Pause de l'exécution
pub fn sleep(seconds: int) {
    // On utilise la commande système sleep
    sysf("sleep " + seconds)
}

