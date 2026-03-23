fn main() {
    // Test 1: Création et affichage
    lt user = dict {
        "name" => "Alice",
        "age" => 30,
        "city" => "Paris"
    }
    
    println("=== TEST DICTIONNAIRE ===")
    println("User: " + user)
    println("")
    
    // Test 2: Accès aux éléments
    println("Name: " + user["name"])
    println("Age: " + user["age"])
    println("City: " + user["city"])
    println("")
    
    // Test 3: Modification
    user["age"] = 31
    println("Après modification age: " + user["age"])
    println("")
    
    // Test 4: Ajout d'une nouvelle clé
    user["email"] = "alice@example.com"
    println("Après ajout email: " + user)
    println("")
    
    // Test 5: Dictionnaire avec nombres comme clés
    lt scores = dict {
        1 => "Facile",
        2 => "Moyen",
        3 => "Difficile"
    }
    
    println("Scores: " + scores)
    println("Niveau 1: " + scores[1])
    println("Niveau 2: " + scores[2])
    println("Niveau 3: " + scores[3])
    println("")
    
    // Test 6: Dictionnaire vide
    lt empty = dict {}
    println("Dictionnaire vide: " + empty)
    empty["new"] = "value"
    println("Après ajout: " + empty)
    
    ret 0
}
