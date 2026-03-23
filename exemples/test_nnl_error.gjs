fn divide(a: int, b: int): int {
    if b == 0 {
        jmp divide_error
    }
    ret a / b
}

fn main() {
    println("=== GESTION D'ERREUR ===\n")
    
    nnl divide_error {
        muts result = divide(10, 2)
        println("10 / 2 = " + result)
        
        result = divide(10, 0)
        println("10 / 0 = " + result)
        println("This won't print")
    }
    
    println("After error")
    
    ret 0
}
