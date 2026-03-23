import switch from switch

fn main() {
    println("=== Switch Module Test ===\n")
    
    // Test 1: Switch simple sur entier
    println("1. Switch sur entier:")
    lt day = 3
    lt day_name = switch::switch_int(day, [
        switch::case(1, "Lundi"),
        switch::case(2, "Mardi"),
        switch::case(3, "Mercredi"),
        switch::case(4, "Jeudi"),
        switch::case(5, "Vendredi"),
        switch::case(6, "Samedi"),
        switch::case(7, "Dimanche")
    ])
    println("   Jour " + day + " = " + day_name)
    println("")
    
    // Test 2: Switch avec valeur par défaut
    println("2. Switch avec défaut:")
    lt http_code = 404
    lt message = switch::switch_default(http_code, [
        switch::case(200, "OK"),
        switch::case(404, "Non trouvé"),
        switch::case(500, "Erreur serveur")
    ], "Code inconnu")
    println("   HTTP " + http_code + " = " + message)
    println("")
    
    // Test 3: Switch sur chaînes
    println("3. Switch sur chaînes:")
    lt color = "red"
    lt hex = switch::switch_string(color, [
        switch::case("red", "#FF0000"),
        switch::case("green", "#00FF00"),
        switch::case("blue", "#0000FF"),
        switch::case("yellow", "#FFFF00")
    ])
    println("   " + color + " = " + hex)
    println("")
    
    // Test 4: Switch avec conditions
    println("4. Switch avec conditions (notes):")
    lt score = 85
    lt grade = switch::switch_cond(score, [
        fn(x) { ret x >= 90 },
        fn(x) { ret x >= 80 },
        fn(x) { ret x >= 70 },
        fn(x) { ret x >= 60 }
    ], [
        "A",
        "B",
        "C",
        "D"
    ])
    
    if grade == nil {
        grade = "F"
    }
    println("   Note " + score + " = " + grade)
    println("")
    
    // Test 5: Switch avec différents types
    println("5. Switch avec différents types:")
    lt test_values = [10, "hello", 3.14, true]
    
    for i = 0; i < len(test_values); i = i + 1 {
        lt val = test_values[i]
        lt type_name = switch::switch_cond(val, [
            fn(x) { ret x == 10 },
            fn(x) { ret x == "hello" },
            fn(x) { ret x == 3.14 },
            fn(x) { ret x == true }
        ], [
            "C'est un entier 10",
            "C'est une chaîne 'hello'",
            "C'est un flottant 3.14",
            "C'est un booléen true"
        ])
        
        if type_name == nil {
            type_name = "Type inconnu"
        }
        println("   " + val + " => " + type_name)
    }
    
    println("\n=== Test terminé ===")
    ret 0
}
