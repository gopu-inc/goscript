fn main() {
    println("=== ADVANCED OPERATORS TEST ===")
    
    // Comparison operators
    lt a = 10
    lt b = 20
    
    println("a >= b: " + (a >= b))
    println("a <= b: " + (a <= b))
    println("")
    
    // Assignment operators
    lt x = 5
    println("x = " + x)
    
    x += 3
    println("x += 3 => " + x)
    
    x -= 2
    println("x -= 2 => " + x)
    
    x *= 4
    println("x *= 4 => " + x)
    
    x /= 2
    println("x /= 2 => " + x)
    
    x %= 3
    println("x %= 3 => " + x)
    
    // While with >=
    println("")
    println("=== COUNTDOWN WITH >= ===")
    lt i = 5
    while i >= 1 {
        println("Count: " + i)
        i -= 1
    }
    
    ret 0
}
