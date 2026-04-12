import strings from "./strings"

fn main() {
    println("=== TEST SIMPLE ===")
    
    lt s = "Hello World"
    println("String: " + s)
    println("Length: " + strings::len(s))
    println("Upper: " + strings::to_upper(s))
    println("Lower: " + strings::to_lower(s))
    println("Contains 'World': " + strings::contains(s, "World"))
    println("Trim: '" + strings::trim("  Hello  ") + "'")
    
    println("✅ Tests completed!")
}
