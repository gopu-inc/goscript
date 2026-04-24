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

ntln("2. Fonctions importées via use:")
    println("   now(): " + now())
    println("   timestamp(): " + timestamp())
    println("")
    
    // Test 3: Sous-module ft
    println("3. Test du sous-module ft:")
    println("   sleep_ms(500) - attendez 0.5s...")
    sleep_ms(500)
    println("   Fait!")
    println("")
    
    println("4. Test avec namespace complet:")
    println("   time::ft::sleep(1) - attendez 1s...")
    time::ft::sleep(1)
    println("   Fait!")
    println("")
    
    println("=== TEST TERMINÉ ===")
    
    ret 0
}
