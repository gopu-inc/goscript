import __str

fn main() {
    println("=== TEST __str ===\n")
    
    lt s = "Hello Goscript"
    
    println("len: " + __str::len(s))
    println("to_upper: " + __str::to_upper(s))
    println("to_lower: " + __str::to_lower(s))
    println("contains Goscript: " + __str::contains(s, "Goscript"))
    
    lt trimmed = __str::trim("  hello  ")
    println("trim: '" + trimmed + "'")
    
    lt parts = __str::split("a,b,c", ",")
    println("join: " + __str::join(parts, "-"))
    
    println("to_int 123: " + __str::to_int("123"))
    
    ret 0
}
