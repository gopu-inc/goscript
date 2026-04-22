import time

use time::now
use time::timestamp

fn main() {
    println("=== TEST 4: USE ===\n")
    
    println("Date: " + now())
    println("Timestamp: " + timestamp())
    
    println("\n=== OK ===")
    ret 0
}
