fn main() {
    println("--- Test manuel ---")
    lt a = -42
    
    // Test si l'opérateur unaire fonctionne seul
    lt b = 0 - a 
    println("0 - (-42) = " + b)
    
    // Test sans le ":" dans la signature (si ton parser préfère -> ou rien)
    ret 0
}

