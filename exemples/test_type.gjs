// test_typeof_direct.gjs - Pas besoin d'import !

fn main() {
    println("=== TEST TYPEOF DIRECT ===\n")
    
    println("typeof(42): " + of("42"))
    println("typeof(-10): " + of("-10"))
    println("typeof(3.14): " + of("3.14"))
    println("typeof(true): " + of("true"))
    println("typeof(false): " + of("false"))
    println("typeof(nil): " + of("nil"))
    println("typeof(hello): " + of("hello"))
    println("typeof(): " + of(""))
    
    println("\n--- is_xxx functions ---")
    println("is_int(42): " + is_int("42"))
    println("is_float(3.14): " + is_float("3.14"))
    println("is_bool(true): " + is_bool("true"))
    println("is_nil(): " + is_nil(""))
    println("is_string(hello): " + is_string("hello"))
}
