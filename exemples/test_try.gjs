// test_try_basic.gjs - Test simple de try/catch

fn divide(a: int, b: int): int {
    if b == 0 {
        throw "Division by zero!"
    }
    ret a / b
}

fn main() {
    println("=== TEST TRY/CATCH BASIC ===\n")
    
    try {
        lt result = divide(10, 2)
        println("10 / 2 = " + result)
    } catch (e) {
        println("ERROR: " + e)
    }
    
    try {
        lt result = divide(10, 0)
        println("This won't print")
    } catch (e) {
        println("Caught: " + e)
    }
    
    println("\nProgram continues after try/catch!")
}
