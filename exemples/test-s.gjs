// Test simple de Goscript

fn main() {
    lt name = "Goscript"
    lt version = 1.0
    lt debug = true
    
    println("=== GOSCRIPT TEST ===")
    println("Name: " + name)
    println("Version: " + version)
    
    lt a = 10
    lt b = 5
    lt sum = a + b
    lt diff = a - b
    lt prod = a * b
    lt quot = a / b
    
    println("10 + 5 = " + sum)
    println("10 - 5 = " + diff)
    println("10 * 5 = " + prod)
    println("10 / 5 = " + quot)
    
    if sum > 10 {
        println("Sum is greater than 10")
    } else {
        println("Sum is less or equal to 10")
    }
    
    lt i = 0
    while i < 3 {
        println("While loop: " + i)
        i = i + 1
    }
    
    for i = 0; i < 3; i = i + 1 {
        println("For loop: " + i)
    }
    
    lt result = addNumbers(15, 25)
    println("15 + 25 = " + result)
    
    ret 0
}

fn addNumbers(x, y) {
    ret x + y
}
