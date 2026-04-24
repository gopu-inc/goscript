fn test_cli(args) {
    match args {
        ["server", "start", lt port] => {
            println("Action: Démarrage du serveur")
            println("Port détecté: " + port)
        }
        ["server", "stop"] => {
            println("Action: Arrêt du serveur")
        }
        ["help"] => {
            println("Usage: server [start|stop] [port]")
        }
        _ => {
            println("Commande inconnue")
        }
    }
}

fn main() {
    // Test 1: Capture de variable
    println("--- Test 1 ---")
    test_cli(["server", "start", "8080"])

    // Test 2: Match exact
    println("\n--- Test 2 ---")
    test_cli(["server", "stop"])

    // Test 3: Défaut
    println("\n--- Test 3 ---")
    test_cli(["random", "cmd"])
}

