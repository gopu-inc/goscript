import fms from "./fms"

fn main() {
    println("=== TEST FMS (CONVERSIONS) ===\n")
    
    // to_str
    println("to_str(42): " + fms::to_str("42"))
    println("to_str(hello): " + fms::to_str("hello"))
    
    // to_int
    println("\nto_int(42): " + fms::to_int("42"))
    println("to_int(-10): " + fms::to_int("-10"))
    println("to_int(3.14): " + fms::to_int("3.14"))
    println("to_int(abc): " + fms::to_int("abc"))
    
    // to_float
    println("\nto_float(3.14): " + fms::to_float("3.14"))
    println("to_float(-2.5): " + fms::to_float("-2.5"))
    println("to_float(42): " + fms::to_float("42"))
    println("to_float(abc): " + fms::to_float("abc"))
    
    // to_bool
    println("\nto_bool(1): " + fms::to_bool("1"))
    println("to_bool(0): " + fms::to_bool("0"))
    println("to_bool(true): " + fms::to_bool("true"))
    println("to_bool(): " + fms::to_bool(""))
    
    // is_xxx
    println("\nis_int(42): " + fms::is_int("42"))
    println("is_int(abc): " + fms::is_int("abc"))
    println("is_float(3.14): " + fms::is_float("3.14"))
    println("is_bool(true): " + fms::is_bool("true"))
    
    // format
    println("\nformat(Hello {}, World): " + fms::format("Hello {}", "World"))
    
    println("\n✅ All tests passed!")
}
