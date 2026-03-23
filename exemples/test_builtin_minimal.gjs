fn main() {
    println("=== TEST BUILTIN ===\n")
    
    println("VERSION: " + VERSION)
    println("PI: " + PI)
    println("")
    
    println("abs(-10) = " + abs(-10))
    println("max(5,10) = " + max(5,10))
    println("min(5,10) = " + min(5,10))
    println("")
    
    println("sqrt(16) = " + sqrt(16))
    println("")
    
    println("getpid() = " + getpid())
    println("")
    
    println(colorize("SUCCESS!", COLOR_GREEN))
    
    ret 0
}
