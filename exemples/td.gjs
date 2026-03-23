fn main() {
    // Test des constantes du nouveau builtin
    println(COLOR_CYAN + "=== GOSCRIPT V" + VERSION + " ===" + COLOR_RESET)
    
    // Test des fonctions mathématiques
    lt a = -42
    println("Abs de " + a + " = " + abs(a))
    
    // Test du temps système via FFI
    println("Timestamp actuel: " + time())
    
    ret 0
}

