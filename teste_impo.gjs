import sw from switch

fn main() {
    println("=== SWITCH MODULE ADVANCED TEST ===\n")
    
    // Test 1: Switch sur entiers
    println("1. Switch sur entiers:")
    lt day = 3
    lt result = sw::match_value(day, [
        [1, "Lundi"],
        [2, "Mardi"],
        [3, "Mercredi"],
        [4, "Jeudi"],
        [5, "Vendredi"],
        [6, "Samedi"],
        [7, "Dimanche"]
    ], "Jour invalide")
    println("   Jour " + day + " = " + result)
    println("")
    
    // Test 2: Switch sur chaînes
    println("2. Switch sur chaînes:")
    lt color = "red"
    lt hex = sw::match_value(color, [
        ["red", "#FF0000"],
        ["green", "#00FF00"],
        ["blue", "#0000FF"],
        ["yellow", "#FFFF00"]
    ], "Couleur inconnue")
    println("   " + color + " = " + hex)
    println("")
    
    // Test 3: Switch avec valeur par défaut
    println("3. Switch avec valeur par défaut:")
    lt http_code = 404
    lt message = sw::match_value(http_code, [
        [200, "OK"],
        [404, "Not Found"],
        [500, "Internal Server Error"]
    ], "Unknown Status")
    println("   HTTP " + http_code + " = " + message)
    println("")
    
    // Test 4: Switch sur booléens
    println("4. Switch sur booléens:")
    lt flag = true
    lt result_flag = sw::match_value(flag, [
        [true, "Activé"],
        [false, "Désactivé"]
    ], "État inconnu")
    println("   Flag = " + result_flag)
    println("")
    
    // Test 5: Switch avec l'objet Switch
    println("5. Switch avec l'objet Switch (fluent API):")
    lt grade = 85
    lt letter = sw::Switch::new(grade)
        .case(90, "A")
        .case(80, "B")
        .case(70, "C")
        .case(60, "D")
        .default("F")
        .exec()
    println("   Note " + grade + " = " + letter)
    println("")
    
    // Test 6: Switch avec différents types
    println("6. Switch avec différents types:")
    lt values = [10, "hello", 3.14, true]
    
    for i = 0; i < len(values); i = i + 1 {
        lt val = values[i]
        lt type_name = sw::match_value(val, [
            [10, "Entier 10"],
            ["hello", "Chaîne 'hello'"],
            [3.14, "Flottant 3.14"],
            [true, "Booléen true"]
        ], "Type inconnu")
        println("   " + val + " => " + type_name)
    }
    println("")
    
    // Test 7: Utilisation de l'énumération
    println("7. Utilisation de l'énumération SwitchResult:")
    lt test_value = 999
    lt enum_result = sw::match_value(test_value, [
        [200, sw::SwitchResult::Match],
        [404, sw::SwitchResult::Default],
        [500, sw::SwitchResult::Error]
    ], sw::SwitchResult::Error)
    
    if enum_result == sw::SwitchResult::Match {
        println("   Résultat: Match trouvé!")
    } else if enum_result == sw::SwitchResult::Default {
        println("   Résultat: Valeur par défaut")
    } else if enum_result == sw::SwitchResult::Error {
        println("   Résultat: Erreur - aucun cas correspondant")
    }
    println("")
    
    println("=== TEST TERMINÉ AVEC SUCCÈS ===")
    ret 0
}

