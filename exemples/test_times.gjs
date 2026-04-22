import time
import time.ft

fn main() {
    println("=== TEST 3: TIME + TIME.FT ===\n")
    
    println("Date: " + time::now())
    println("Timestamp: " + time::timestamp())
    
    println("\nSleep 1 seconde...")
    ft::sleep(1)
    println("Fait!")
    
    println("\n=== OK ===")
    ret 0
}
