fn main() {
    println("=== TEST LAMBDAS ===\n")
    
    // Lambda simple
    muts add = lambda a, b {
        ret a + b
    }
    
    muts result = add(5, 3)
    println("5 + 3 = " + result)
    
    // Lambda multiplication
    muts multiply = lambda x, y {
        ret x * y
    }
    
    println("4 * 7 = " + multiply(4, 7))
    
    // Lambda avec une variable
    muts square = lambda x {
        ret x * x
    }
    
    println("square(6) = " + square(6))
    
    ret 0
}
