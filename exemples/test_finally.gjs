// test_except.gjs - Test de except/raise (syntaxe Python)

fn divide(a: int, b: int): int {
    if b == 0 {
        raise "Division by zero!"  // Syntaxe Python
    }
    ret a / b
}

fn check_value(x: int): string {
    if x < 0 {
        raise "Negative value not allowed!"
    }
    ret "OK"
}

fn main() {
    println("=== TEST EXCEPT/RAISE ===\n")
    
    // Test 1: raise avec except
    println("1. Test raise/except:")
    try {
        lt result = divide(10, 0)
        println("Result: " + result)
    } except (e) {
        println("   Except caught: " + e)
    }
    
    // Test 2: pas d'erreur
    println("\n2. Test sans erreur:")
    try {
        lt result = divide(10, 2)
        println("   10/2 = " + result)
    } except (e) {
        println("   Except: " + e)
    }
    
    // Test 3: raise avec finally
    println("\n3. Test raise/except/finally:")
    try {
        lt status = check_value(-5)
        println("   Status: " + status)
    } except (e) {
        println("   Except: " + e)
    } finally {
        println("   [FINALLY] Cleanup!")
    }
    
    // Test 4: Mix catch et except (les deux fonctionnent)
    println("\n4. Test avec catch (syntaxe JavaScript):")
    try {
        raise "Error with raise!"
    } catch (e) {
        println("   Catch caught: " + e)
    }
    
    println("\n5. Test avec except (syntaxe Python):")
    try {
        throw "Error with throw!"
    } except (e) {
        println("   Except caught: " + e)
    }
    
    println("\n✅ Except/raise works perfectly!")
}
