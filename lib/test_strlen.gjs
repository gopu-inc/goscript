fn main() {
    println("=== TEST STRLEN ===\n")
    
    lt s = "hello"
    println("String: " + s)
    
    lt l = strlen_c(s)
    println("Longueur: " + l)
    
    ret 0
}
