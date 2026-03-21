// Test des fonctions C via FFI

fn main() {
    println("=== FFI TEST ===\n")
    
    // Test printf
    printf("Hello from C printf!\n")
    
    // Test strlen
    lt len = strlen("Goscript")
    println("Length of 'Goscript': " + len)
    
    // Test atoi
    lt num = atoi("12345")
    println("String to int: " + num)
    
    // Test system
    system("echo 'System command executed!'")
    
    // Test malloc et free
    lt ptr = malloc(100)
    if ptr != nil {
        println("Memory allocated successfully")
        free(ptr)
        println("Memory freed")
    }
    
    println("\n=== TEST RÉUSSI ===")
    ret 0
}
