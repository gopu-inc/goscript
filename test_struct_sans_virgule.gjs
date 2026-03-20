struct Person {
    name: string
    age: int
    active: bool
}

fn main() {
    println("=== STRUCT TEST ===\n")
    
    // Utilisation de 'new' pour créer une structure
    lt person = new Person{
        name: "Alice",
        age: 30,
        active: true
    }
    
    println("   Nom: " + person.name)
    println("   Âge: " + person.age)
    println("   Actif: " + person.active)
    
    // Conditions sans parenthèses
    lt a = 10
    lt b = 20
    
    if a < b {
        println("   a est plus petit que b")
    } else {
        println("   a est plus grand que b")
    }
    
    println("\n=== TEST RÉUSSI ===")
    ret 0
}
