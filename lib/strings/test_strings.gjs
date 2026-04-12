import strings from "./strings"

fn main() {
    println("=== TEST STRINGS MODULE ===\n")
    
    lt s = "Hello World"
    println("String: " + s)
    
    lt len_result = strings::len(s)
    println("Length: " + len_result)
    
    lt upper_result = strings::to_upper(s)
    println("Upper: " + upper_result)
    
    lt lower_result = strings::to_lower(s)
    println("Lower: " + lower_result)
    
    println("")
    
    lt contains1 = strings::contains(s, "World")
    println("Contains 'World': " + contains1)
    
    lt contains2 = strings::contains(s, "xyz")
    println("Contains 'xyz': " + contains2)
    
    println("")
    
    lt spaced = "  Hello  "
    lt trim_result = strings::trim(spaced)
    println("Trim: '" + trim_result + "'")
    
    println("")
    
    lt starts = strings::starts_with(s, "Hello")
    println("Starts with 'Hello': " + starts)
    
    lt ends = strings::ends_with(s, "World")
    println("Ends with 'World': " + ends)
    
    println("")
    
    lt replace1 = strings::replace_first(s, "Hello", "Hi")
    println("Replace 'Hello' with 'Hi': " + replace1)
    
    println("")
    println("✅ All tests completed!")
}
