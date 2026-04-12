// test_type.gjs - Avec import explicite
import __builtin__ from "/usr/local/lib/goscript/modules/__builtin__"

fn main() {
    println("=== TEST TYPEOF DIRECT ===\n")
    
    println("typeof(42): " + __builtin__::typeof("42"))
    println("typeof(-10): " + __builtin__::typeof("-10"))
    println("typeof(3.14): " + __builtin__::typeof("3.14"))
    println("typeof(true): " + __builtin__::typeof("true"))
    println("typeof(false): " + __builtin__::typeof("false"))
    println("typeof(nil): " + __builtin__::typeof("nil"))
    println("typeof(hello): " + __builtin__::typeof("hello"))
    println("typeof(): " + __builtin__::typeof(""))
}
