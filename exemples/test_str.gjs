import __str

fn main() {
    println("=== TEST MODULE __str ===\n")
    
    // Test len
    lt s = "Hello Goscript!"
    println("len('" + s + "') = " + len(s))
    
    // Test to_upper/to_lower
    println("to_upper: " + to_upper(s))
    println("to_lower: " + to_lower(s))
    
    // Test contains
    println("contains('World'): " + contains(s, "World"))
    println("contains('Goscript'): " + contains(s, "Goscript"))
    
    // Test substring
    println("substring(0,5): " + substring(s, 0, 5))
    
    // Test index_of
    println("index_of('script'): " + index_of(s, "script"))
    
    // Test replace
    println("replace('Goscript', 'Go'): " + replace(s, "Goscript", "Go"))
    
    // Test trim
    lt spaced = "  hello  "
    println("trim('" + spaced + "') = '" + trim(spaced) + "'")
    
    // Test split/join
    lt parts = split("a,b,c", ",")
    println("split: " + join(parts, "-"))
    
    // Test starts_with/ends_with
    println("starts_with('Hello'): " + starts_with(s, "Hello"))
    println("ends_with('!'): " + ends_with(s, "!"))
    
    // Test to_int/to_float
    println("to_int('123'): " + to_int("123"))
    println("to_float('3.14'): " + to_float("3.14"))
    
    ret 0
}
