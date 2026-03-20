fn main() {
    println("=== LOOP WITH BREAK ===")
    
    lt i = 0
    loop {
        println("Iteration: " + i)
        i = i + 1
        if i >= 5 {
            println("Breaking the loop!")
            break
        }
    }
    
    ret 0
}
