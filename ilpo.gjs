import c__builtin__

fn main() {
    println("=== TEST BUILTIN MODULE ===\n")
    
    // Test des constantes
    println("Version: " + builtin::VERSION)
    println("Author: " + builtin::AUTHOR)
    println("PI: " + builtin::PI)
    println("E: " + builtin::E)
    println("")
    
    // Test des assertions
    builtin::assert(1 + 1 == 2, "Math works!")
    builtin::assert_eq(10, 10, "Numbers equal")
    builtin::assert_eq("hello", "hello", "Strings equal")
    println("")
    
    // Test des logs
    builtin::info("Information message")
    builtin::warn("Warning message")
    builtin::error("Error message")
    println("")
    
    // Test des maths
    println("abs(-5): " + builtin::abs(-5))
    println("max(10, 20): " + builtin::max(10, 20))
    println("min(10, 20): " + builtin::min(10, 20))
    println("clamp(15, 10, 20): " + builtin::clamp(15, 10, 20))
    println("clamp(5, 10, 20): " + builtin::clamp(5, 10, 20))
    println("clamp(25, 10, 20): " + builtin::clamp(25, 10, 20))
    println("")
    
    // Test des strings
    println('is_empty(""): ' + builtin::is_empty(""))
    println('is_empty("hello"): ' + builtin::is_empty("hello"))
    println('not_empty(""): ' + builtin::not_empty(""))
    println('not_empty("hello"): ' + builtin::not_empty("hello"))
    println('contains("hello world", "world"): ' + builtin::contains("hello world", "world"))
    println('contains("hello world", "xyz"): ' + builtin::contains("hello world", "xyz"))
    
    ret 0
}
