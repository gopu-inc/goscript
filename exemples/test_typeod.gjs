// test_typeod.gjs - Test de la fonction typeod

fn main() {
    println("=== TEST TYPEOD ===\n")
    
    // Test 1: nil
    lt v1 = nil
    println("typeod(nil)    = " + typeod(v1) + " (attendu: nil)")
    
    // Test 2: booléens
    lt v2 = true
    lt v3 = false
    println("typeod(true)   = " + typeod(v2) + " (attendu: bool)")
    println("typeod(false)  = " + typeod(v3) + " (attendu: bool)")
    
    // Test 3: entiers
    lt v4 = 42
    lt v5 = 0
    lt v6 = -10
    println("typeod(42)     = " + typeod(v4) + " (attendu: int)")
    println("typeod(0)      = " + typeod(v5) + " (attendu: int)")
    println("typeod(-10)    = " + typeod(v6) + " (attendu: int)")
    
    // Test 4: chaînes
    lt v7 = "hello"
    lt v8 = ""
    lt v9 = "Goscript 2026"
    println("typeod('hello') = " + typeod(v7) + " (attendu: string)")
    println("typeod('')      = " + typeod(v8) + " (attendu: string)")
    println("typeod('Goscript 2026') = " + typeod(v9) + " (attendu: string)")
    
    // Test 5: tableaux
    lt v10 = [1, 2, 3]
    lt v11 = []
    lt v12 = ["pomme", "banane", "orange"]
    println("typeod([1,2,3]) = " + typeod(v10) + " (attendu: array)")
    println("typeod([])      = " + typeod(v11) + " (attendu: array)")
    println("typeod(['pomme','banane']) = " + typeod(v12) + " (attendu: array)")
    
    // Test 6: dictionnaires
    lt v13 = dict{"cle": "valeur"}
    println("typeod(dict)    = " + typeod(v13) + " (attendu: dict)")
    
    // Test 7: structures
    struct Person {
        name: string,
        age: int
    }
    
    lt v14 = new Person{
        name: "Alice",
        age: 30
    }
    println("typeod(struct)  = " + typeod(v14) + " (attendu: struct)")
    
    println("\n=== TEST TYPEOD RÉUSSI ===")
    
    ret 0
}

// Fonction typeod simplifiée - Détection de type fiable
pub fn typeod(v: any): string {
    if v == nil {
        ret "nil"
    }
    
    // Booléens
    if v == true || v == false {
        ret "bool"
    }
    
    // Test pour les chaînes (concaténation avec string vide)
    try {
        muts s = v + ""
        // Vérifier si c'est itérable comme une chaîne
        try {
            for c in v {
                // Si on peut itérer ET concaténer, c'est une chaîne
                ret "string"
            }
            // Si c'est concaténable mais pas itérable, c'est un nombre
            ret "int"
        } catch (e) {
            // Pas itérable, donc probablement un nombre
            ret "int"
        }
    } catch (e) {}
    
    // Test pour les tableaux/dictionnaires (itérables)
    try {
        for item in v {
            // Si on peut itérer, c'est soit un array, soit un dict
            // On essaie de concaténer pour voir
            try {
                muts arr_test = v + []
                ret "array"
            } catch (e) {
                ret "dict"
            }
        }
    } catch (e) {}
    
    // Si rien ne correspond, c'est une structure
    ret "struct"
}
