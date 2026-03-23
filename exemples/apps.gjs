fn main() {
    lt name = "Goscript"
    lt version = "2.0"
    lt year = 2026
    
    if year >= 2026 {
        println("Welcome to " + name + " " + version)
    }
    
    for i in [1, 2, 3, 4, 5] {
        println("Count: " + i)
    }
      
    ret 0
}
println("After increment: " + counter)

counter = counter * 2
println("After multiply: " + counter)

muts message: string = "Hello"
println("Message: " + message)

message = message + " World!"
println("After concat: " + message)

println("")

// ============================================
// TEST 2: Pattern Matching (match)
// ============================================
println("=== TEST 2: Pattern Matching ===")

fn test_match(value) {
    match value {
        1 => println("Value is ONE")
        2 => println("Value is TWO")
        3 => println("Value is THREE")
        5 => println("Value is FIVE")
        10 => println("Value is TEN")
        _ => println("Value is " + value + " (default case)")
    }
}

test_match(1)
test_match(2)
test_match(3)
test_match(5)
test_match(10)
test_match(42)

println("")

// Test match avec strings
fn test_match_string(s) {
    match s {
        "hello" => println("Greeting!")
        "goodbye" => println("Farewell!")
        "yes" => println("Affirmative!")
        "no" => println("Negative!")
        _ => println("Unknown: " + s)
    }
}

test_match_string("hello")
test_match_string("goodbye")
test_match_string("yes")
test_match_string("no")
test_match_string("maybe")

println("")

// ============================================
// TEST 3: Unsafe Blocks
// ============================================
println("=== TEST 3: Unsafe Blocks ===")

unsafe {
    println("Inside unsafe block - can do low-level operations")
    muts raw_ptr = 0x1000
    println("Raw pointer value: " + raw_ptr)
}

println("Outside unsafe block - normal execution")

unsafe {
    println("Another unsafe block")
    muts x = 100
    muts y = 200
    println("x + y = " + (x + y))
}

println("")

// ============================================
// TEST 4: Combinaison de fonctionnalités
// ============================================
println("=== TEST 4: Combined Features ===")

fn factorial(n) {
    muts result = 1
    muts i = 1
    
    while i <= n {
        result = result * i
        i = i + 1
    }
    
    ret result
}

println("Factorial of 5: " + factorial(5))
println("Factorial of 7: " + factorial(7))

// Match dans une boucle
println("\nFizzBuzz with match:")
muts i = 1
while i <= 15 {
    match (i % 15) {
        0 => println("FizzBuzz")
        3 => println("Fizz")
        5 => println("Buzz")
        6 => println("Fizz")
        9 => println("Fizz")
        10 => println("Buzz")
        12 => println("Fizz")
        _ => println(i)
    }
    i = i + 1
}

println("")

// ============================================
// TEST 5: Match avec return
// ============================================
println("=== TEST 5: Match with Return ===")

fn get_day_name(day) {
    match day {
        1 => ret "Monday"
        2 => ret "Tuesday"
        3 => ret "Wednesday"
        4 => ret "Thursday"
        5 => ret "Friday"
        6 => ret "Saturday"
        7 => ret "Sunday"
        _ => ret "Invalid"
    }
}

println("Day 1: " + get_day_name(1))
println("Day 3: " + get_day_name(3))
println("Day 5: " + get_day_name(5))
println("Day 7: " + get_day_name(7))
println("Day 9: " + get_day_name(9))

println("")

// ============================================
// TEST 6: Unsafe avec match
// ============================================
println("=== TEST 6: Unsafe + Match ===")

unsafe {
    println("Calculating in unsafe context...")
    
    muts values = [10, 20, 30, 40, 50]
    muts sum = 0
    muts index = 0
    
    while index < 5 {
        match values[index] {
            10 => println("Found 10")
            20 => println("Found 20")
            30 => println("Found 30")
            40 => println("Found 40")
            50 => println("Found 50")
            _ => println("Unknown")
        }
        sum = sum + values[index]
        index = index + 1
    }
    
println("Sum of values: " + sum)
}

println("")

// ============================================
// TEST 7: Complex mutable state
// ============================================
println("=== TEST 7: Complex Mutable State ===")

fn counter_demo() {
    muts count = 0
    
    fn increment() {
        count = count + 1
        ret count
    }
    
    fn decrement() {
        count = count - 1
        ret count
    }
    
    fn get_count() {
        ret count
    }
    
    println("Initial: " + get_count())
    println("Increment: " + increment())
    println("Increment: " + increment())
    println("Increment: " + increment())
    println("Decrement: " + decrement())
    println("Final: " + get_count())
}

counter_demo()

println("")

// ============================================
// TEST 8: Edge cases
// ============================================
println("=== TEST 8: Edge Cases ===")

// Match avec wildcard uniquement
println("Match with only wildcard:")
match 999 {
    _ => println("Catch all")
}

// Match avec une seule branche
println("\nMatch with single branch:")
match "test" {
    "test" => println("Matched exactly")
}

// Variables mutables dans différents scopes
println("\nNested mutable variables:")
muts outer = 10
println("Outer before: " + outer)

if true {
    muts inner = 20
    println("Inner: " + inner)
    outer = outer + inner
    println("Outer after add: " + outer)
}

println("Outer final: " + outer)

// Unsafe avec opérations
unsafe {
    println("\nUnsafe arithmetic:")
    muts a = 100
    muts b = 50
    println("a + b = " + (a + b))
    println("a - b = " + (a - b))
    println("a * b = " + (a * b))
    println("a / b = " + (a / b))
}

println("")

// ============================================
// TEST 9: Performance test (loop with mutable)
// ============================================
println("=== TEST 9: Loop Performance ===")

muts total = 0
muts j = 1

while j <= 100 {
    total = total + j
    j = j + 1
}

println("Sum of 1 to 100: " + total)

// Test with match in loop
muts k = 1
muts even_sum = 0
muts odd_sum = 0

while k <= 20 {
    match (k % 2) {
        0 => even_sum = even_sum + k
        1 => odd_sum = odd_sum + k
        _ => println("Should not happen")
    }
    k = k + 1
}

println("Sum of evens (1-20): " + even_sum)
println("Sum of odds (1-20): " + odd_sum)

println("")
println("=== ALL TESTS COMPLETED SUCCESSFULLY! ===")

ret 0

