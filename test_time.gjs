import time

fn main() {
    println("--- Testing Native Time (Bash) ---")

    // 1. Test de l'heure
    lt heure = time::now()
    println("Il est actuellement : " + heure)

    // 2. Test du Timestamp
    lt ts = time::timestamp()
    println("Timestamp Unix : " + ts)

    // 3. Test du formateur personnalisé (pour tes backups)
    lt jour = time::format("%A %d %B")
    println("Aujourd'hui : " + jour)

    // 4. Test du sleep
    println("Dodo pour 1 seconde...")
    time::sleep(1)
    println("Réveil !")

    ret 0
}

