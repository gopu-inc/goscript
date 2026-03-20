fn main() {
    lt i = 0
    while i < 5 {
        println("Count: " + i)
        lt i = i + 1
    }
    ret 0
}
umération
enm Color {
    Red,
    Green,
    Blue,
}

// Structure
struct Person {
    name: string,
    age: int,
}

// Fonction principale
fn @main() {
    lt name = "Goscript"
    lt version = APP_VERSION
    
    println("Bienvenue dans ${name} ${version}")
    
    // Boucle for
    for i in 0..10 {
        println("Compteur: ${i}")
    }
    
    // Boucle while
    lt count = 0
    while count < 5 {
        println("While: ${count}")
        count = count + 1
    }
    
    // Condition
    lt value = 42
    if value > 50 {
        println("Grand")
    } else if value > 20 {
        println("Moyen")
    } else {
        println("Petit")
    }
    
    // Match
    lt color = Color::Blue
    match color {
        Color::Red => println("Rouge"),
        Color::Green => println("Vert"),
        Color::Blue => println("Bleu"),
    }
    
    // Struct
    lt person = Person{name: "Alice", age: 30}
    println("${person.name} a ${person.age} ans")
    
    // Fonction
    lt result = add(10, 20)
    println("Résultat: ${result}")
}

fn add(a: int, b: int) int {
    ret a + b
}
