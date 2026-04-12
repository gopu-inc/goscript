import strings from "./strings"

fn main() {
    println("=== TEST STRINGS MODULE ===\n")
    
    lt s = "Hello World"
    println(f"String: '{s}'")
    
    lt len_result = strings::len(s)
    println(f"Length: {len_result}")
    
    lt upper_result = strings::to_upper(s)
    println(f"Upper: {upper_result}")
    
    lt lower_result = strings::to_lower(s)
    println(f"Lower: {lower_result}")
    
    println("")
    
    lt contains1 = strings::contains(s, "World")
    println(f"Contains 'World': {contains1}")
    
    lt contains2 = strings::contains(s, "xyz")
    println(f"Contains 'xyz': {contains2}")
    
    println("")
    
    lt spaced = "  Hello  "
    lt trim_result = strings::trim(spaced)
    println(f"Trim: '{trim_result}'")
    
    println("")
    
    lt starts = strings::starts_with(s, "Hello")
    println(f"Starts with 'Hello': {starts}")
    
    lt ends = strings::ends_with(s, "World")
    println(f"Ends with 'World': {ends}")
    
    println("")
    
    lt replace1 = strings::replace_first(s, "Hello", "Hi")
    println(f"Replace 'Hello' with 'Hi': {replace1}")
    
    lt replace2 = strings::replace_all("banana", "a", "o")
    println(f"Replace all 'a' with 'o' in 'banana': {replace2}")
    
    println("")
    
    lt reversed = strings::reverse("Hello")
    println(f"Reverse 'Hello': {reversed}")
    
    lt count_l = strings::count(s, "l")
    println(f"Count 'l' in '{s}': {count_l}")
    
    println("")
    println("✅ All tests completed!")
}