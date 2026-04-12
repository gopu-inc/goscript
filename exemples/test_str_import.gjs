import __str

fn main() {
    println("=== TEST IMPORT __str ===\n")
    
    lt s = "Hello Goscript!"
    
    // Appels via __str::
    println("len: " + __str::len(s))
    println("to_upper: " + __str::to_upper(s))
    println("to_lower: " + __str::to_lower(s))
    println("contains('Goscript'): " + __str::contains(s, "Goscript"))
    println("contains('World'): " + __str::contains(s, "World"))
    println("substring(0,5): " + __str::substring(s, 0, 5))
    println("index_of('script'): " + __str::index_of(s, "script"))
    
    lt spaced = "  hello world  "
    println("trim('" + spaced + "') = '" + __str::trim(spaced) + "'")
    
    lt parts = __str::split("a,b,c", ",")
    println("split: " + __str::join(parts, "-"))
    
    println("starts_with('Hello'): " + __str::starts_with(s, "Hello"))
    println("ends_with('!'): " + __str::ends_with(s, "!"))
    
    println("to_int('123'): " + __str::to_int("123"))
    println("to_int('-456'): " + __str::to_int("-456"))
    println("to_float('3.14159'): " + __str::to_float("3.14159"))
    
    ret 0
}
