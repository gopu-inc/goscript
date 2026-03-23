// Test simple des structures

struct Person {
    name: string
    age: int
}

fn main() {
    println("=== TEST STRUCTURES ===\n")
    
    // Créer une personne
    muts p = new Person{
        name: "Alice",
        age: 30
    }
    
    println("Nom: " + p.name)
    println("Age: " + p.age)
    
    // Modifier
    p.age = 31
    println("Nouvel age: " + p.age)
    
    // Créer une autre
    muts p2 = new Person{
        name: "Bob",
        age: 25
    }
    
    println("Autre: " + p2.name + ", " + p2.age)
    
    println("\n=== OK ===")
    
    ret 0
}
