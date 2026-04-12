import strings from "./strings"

fn main() {
    println("=== TEST STRINGS MODULE (Pure Shell) ===\n")
    
    lt s = "Hello World"
    println("String: '" + s + "'")
    println("Length: " + strings::len(s))
    println("Upper: " + strings::to_upper(s))
    println("Lower: " + strings::to_lower(s))
    println("Capitalize: " + strings::capitalize("hello world"))
    println("")
    
    println("Contains 'World': " + strings::contains(s, "World"))
    println("Contains 'xyz': " + strings::contains(s, "xyz"))
    println("Count 'l': " + strings::count(s, "l"))
    println("")
    
    lt spaced = "  Hello  "
    println("Trim: '" + strings::trim(spaced) + "'")
    println("")
    
    println("Slice(0,5): '" + strings::slice(s, 0, 5) + "'")
    println("Slice(6,11): '" + strings::slice(s, 6, 11) + "'")
    println("")
    
    println("Starts with 'Hello': " + strings::starts_with(s, "Hello"))
    println("Ends with 'World': " + strings::ends_with(s, "World"))
    println("")
    
    println("Replace 'Hello' with 'Hi': " + strings::replace_first(s, "Hello", "Hi"))
    println("Replace all 'l' with 'L': " + strings::replace_all(s, "l", "L"))
    println("")
    
    println("Repeat 'Hi' 3x: " + strings::repeat("Hi", 3))
    println("Reverse 'Hello': " + strings::reverse("Hello"))
    println("")
    
    println("✅ All tests completed!")
}
