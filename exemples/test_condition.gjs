fn main() {
    println("=== WHILE LOOP TEST ===")
    
    lt i = 0
    while i < 5 {
        println("Count: " + i)
        i = i + 1
    }
    
    println("")
    println("=== COUNTDOWN ===")
    
    lt j = 5
    while j > 0 {
        println("T-minus: " + j)
        j = j - 1
    }
    
    println("Liftoff!")
    
    ret 0
}
