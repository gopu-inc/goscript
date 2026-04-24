// Test des arguments CLI
fn main() {
    println("=== TEST DES ARGUMENTS CLI ===")
    println("Nombre d'arguments: " + len(args))
    
    muts i = 0
    while i < len(args) {
        println("  Arg " + i + ": " + args[i])
        i = i + 1
    }
    
    // Tester des flags spécifiques
    muts j = 0
    while j < len(args) {
        if args[j] == "--server" {
            if j + 1 < len(args) {
                println("  -> Mode serveur détecté sur le port " + args[j + 1])
            }
        }
        if args[j] == "--debug" {
            println("  -> Mode debug activé")
        }
        j = j + 1
    }
    
    ret 0
}
