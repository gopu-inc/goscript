fn main() {
    println("=== Test 1: Simple break ===")
    for i in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] {
        if i > 5 {
            println("Break at: " + i)
            break
        }
        println("  i = " + i)
    }
    
    println("\n=== Test 2: Simple continue ===")
    for i in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] {
        if i % 2 == 0 {
            continue
        }
        println("  odd number: " + i)
    }
    
    println("\n=== Test 3: Break in nested loops ===")
    for i in [1, 2, 3] {
        println("Outer loop: i = " + i)
        for j in [1, 2, 3, 4, 5] {
            if j == 3 {
                println("  Break at j = " + j)
                break
            }
            println("    j = " + j)
        }
    }
    
    println("\n=== Test 4: Continue in nested loops ===")
    for i in [1, 2] {
        println("Outer loop: i = " + i)
        for j in [1, 2, 3, 4, 5] {
            if j % 2 == 0 {
                println("    Continue at even j = " + j)
                continue
            }
            println("    j = " + j)
        }
    }
    
    println("\n=== Test 5: Multiple breaks (finding prime numbers) ===")
    for n in [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] {
        lt is_prime = 1
        for d in [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14] {
            if d >= n {
                break
            }
            if n % d == 0 {
                is_prime = 0
                break
            }
        }
        if is_prime == 1 {
            println("Prime: " + n)
        }
    }
    
    println("\n=== Test 6: Stack with break/continue (using while loop) ===")
    lt counter = 0
    while counter < 10 {
        counter = counter + 1
        if counter % 2 == 0 {
            println("  Continue at " + counter)
            continue
        }
        println("  Counter: " + counter)
    }
    
    println("\n=== Test 7: Nested loops with break and continue together ===")
    for a in [1, 2, 3] {
        println("a = " + a)
        for b in [1, 2, 3] {
            if a == 2 && b == 2 {
                println("  Continue (skip) at a=2,b=2")
                continue
            }
            if a == 3 && b == 1 {
                println("  Break outer at a=3,b=1")
                break
            }
            println("    b = " + b)
        }
    }
    
    println("\n=== Test 8: Complex control flow ===")
    lt total = 0
    for x in [1, 2, 3, 4, 5] {
        if x == 2 {
            println("Skip x=2")
            continue
        }
        if x == 4 {
            println("Stop at x=4")
            break
        }
        total = total + x
        println("Added " + x + ", total = " + total)
    }
    println("Final total: " + total)
    
    println("\n=== Test 9: While with break ===")
    lt x = 0
    while x < 10 {
        x = x + 1
        if x == 5 {
            println("Breaking at x=5")
            break
        }
        println("  x = " + x)
    }
    
    println("\n=== Test 10: While with continue ===")
    lt y = 0
    while y < 10 {
        y = y + 1
        if y % 2 == 0 {
            continue
        }
        println("  odd y = " + y)
    }
    
    println("\n=== All tests completed! ===")
    ret 0
}
