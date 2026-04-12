// Test simple d'await avec commande système
fn main() {
    println("=== Test Simple Await ===\n")
    
    // Exécuter une commande shell avec await
    lt result = await "echo 'Hello from async command!'"
    println("Résultat: " + result)
    
    // Tester avec ls
    lt files = await "ls -la"
    println("\nFichiers:\n" + files)
    
    ret 0
}
