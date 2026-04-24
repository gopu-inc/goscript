import sys

fn main() {
    println("--- GoScript System Information ---")

    // 1. Platform Info
    lt os_name = sys::platform()
    lt py_ver = sys::version()
    println("OS Platform: " + os_name)
    println("Backend Version: " + py_ver)

    // 2. Command Line Arguments
    println("\nReading arguments...")
    lt args = sys::argv()
    println("Arguments received: " + args)

    // 3. Testing exit (optional)
    // println("Exiting now...")
    // sys::exit(0)

    ret 0
}

ln("\n--- 3. Test d'erreur avec 'sh' ---")
// On teste une commande qui n'existe pas pour vérifier le code de retour
lt error_status = sh("commande_imaginaire_qui_plante 2>/dev/null")
println("Code d'erreur de sh (devrait être différent de 0) :")
println(error_status)

