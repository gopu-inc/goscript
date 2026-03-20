fn main() {
    println("=== GOSCRIPT COMPLETE TEST ===")
    println("")
    
    // Variables
    lt a = 10
    lt b = 20
    lt c = 5
    
    println("1. Variables:")
    println("   a = " + a)
    println("   b = " + b)
    println("   c = " + c)
    println("")
    
    // Comparisons
    println("2. Comparisons:")
    println("   a < b: " + a < b)
    println("   a > b: " + a > b)
    println("   a <= b: " + a <= b)
    println("   a >= b: " + a >= b)
    println("   a == b: " + a == b)
    println("   a != b: " + a != b)
    println("")
    
    // Arithmetic
    println("3. Arithmetic:")
    println("   a + b = " + a + b)
    println("   a - b = " + a - b)
    println("   a * b = " + a * b)
    println("   a / b = " + a / b)
    println("   a % c = " + a % c)
    println("")
    
    // Assignment operators
    println("4. Assignment operators:")
    lt x = 10
    println("   x = " + x)
    
    x += 5
    println("   x += 5 => " + x)
    
    x -= 3
    println("   x -= 3 => " + x)
    
    x *= 2
    println("   x *= 2 => " + x)
    
    x /= 4
    println("   x /= 4 => " + x)
    
    x %= 3
    println("   x %= 3 => " + x)
    println("")
    
    // Logical operators
    println("5. Logical operators:")
    lt t = true
    lt f = false
    println("   true && true: " + t && t)
    println("   true && false: " + t && f)
    println("   true || false: " + t || f)
    println("   false || false: " + f || f)
    println("   !true: " + !t)
    println("   !false: " + !f)
    println("")
    
    // While loop
    println("6. While loop (countdown):")
    lt i = 5
    while i >= 1 {
        println("   " + i)
        i -= 1
    }
    println("")
    
    // Loop with break
    println("7. Loop with break:")
    lt j = 0
    loop {
        println("   " + j)
        j += 1
        if j >= 3 {
            println("   Breaking...")
            break
        }
    }
    println("")
    
    // Nested loops
    println("8. Multiplication table (3x3):")
    lt row = 1
    while row <= 3 {
        print("   ")
        lt col = 1
        while col <= 3 {
            print(row * col)
            print(" ")
            col += 1
        }
        println("")
        row += 1
    }
    println("")
    
    // String concatenation
    println("9. String concatenation:")
    lt name = "Goscript"
    lt version = "1.0"
    println("   Welcome to " + name + " version " + version)
    println("")
    
    // Complex expression
    println("10. Complex expression:")
    lt result = (a + b) * 2 - (c * 3) + (b / a)
    println("   (a + b) * 2 - (c * 3) + (b / a) = " + result)
    println("")
    
    println("=== ALL TESTS PASSED ===")
    ret 0
}
