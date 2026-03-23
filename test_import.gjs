// test_import.gjs - Test de la bibliothèque standard
import error
import helper

fn main() {
    println("=== TEST BIBLIOTHÈQUE STANDARD ===\n")
    
    // Test des fonctions d'erreur
    error::info("Ceci est un message d'information")
    error::warn("Ceci est un avertissement")
    error::error("Ceci est une erreur")
    
    // Test d'assertion
    error::assert(1 + 1 == 2, "Les maths fonctionnent !")
    println("Assertion passée")
    
    // Test de type
    lt num = 42
    lt text = "Hello"
    lt flag = true
    lt arr = [1, 2, 3]
    lt dicts = dict {
        "a" => 1,
        "b" => 2
    }
    
    println("\n=== TESTS DE TYPE ===")
    println("type_of(42): " + error::type_of(num))
    println("type_of('Hello'): " + error::type_of(text))
    println("type_of(true): " + error::type_of(flag))
    println("type_of([1,2,3]): " + error::type_of(arr))
    println("type_of(dict): " + error::type_of(dicts))
    
    // Test de conversion en string
    println("\n=== TESTS DE CONVERSION ===")
    println("to_string(42): " + error::to_string(42))
    println("to_string(3.14): " + error::to_string(3.14))
    println("to_string(true): " + error::to_string(true))
    
    // Test helper
    println("\n=== TESTS HELPERS ===")
    println("repeat_str('*', 10): " + helper::repeat_str("*", 10))
    println("join(['a','b','c'], '-'): " + helper::join(["a", "b", "c"], "-"))
    
    ret 0
}
