import error

fn main() {
    println("=== TEST MODULE ET STRUCT ===")
    
    // Appel d'une fonction simple du module
    error::info("Chargement du module réussi")
    
    // Test de la structure via le module
    lt mon_err = error::new_error("Fichier non trouvé", 404)
    
    // Affichage des champs (si ton interpréteur gère NODE_MEMBER_ACCESS)
    println("Message d'erreur: " + mon_err.message)
    println("Code d'erreur: " + mon_err.code)
    
    ret 0
}

