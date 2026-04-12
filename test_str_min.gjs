import __str

fn main() {
    println("=== TEST __str ===\n")
    
    lt s = "Hello Goscript"
    
    println("len: " + __str::len(s))
    println("contains Goscript: " + __str::contains(s, "Goscript"))
    println("to_int 123: " + __str::to_int("123"))
    
    ret 0
}
