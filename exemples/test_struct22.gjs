// Test des structures

struct Person {
    name: string
    age: int
    email: string
}

struct Point {
    x: int
    y: int
}

struct Rectangle {
    top_left: Point
    bottom_right: Point
    color: string
}

fn main() {
    println("=== TEST STRUCTURES ===\n")
    
    // TEST 1: Création simple
    println("1. Création de personne...")
    muts p = new Person{
        name: "Alice",
        age: 30,
        email: "alice@example.com"
    }
    println("   Nom: " + p.name)
    println("   Age: " + p.age)
    println("   Email: " + p.email)
    println("")
    
    // TEST 2: Modification des champs
    println("2. Modification des champs...")
    p.age = 31
    p.email = "alice.new@example.com"
    println("   Nouvel age: " + p.age)
    println("   Nouvel email: " + p.email)
    println("")
    
    // TEST 3: Structure imbriquée
    println("3. Structure imbriquée...")
    muts rect = new Rectangle{
        top_left: new Point{x: 0, y: 10},
        bottom_right: new Point{x: 100, y: 0},
        color: "blue"
    }
    println("   Rectangle " + rect.color)
    println("   Top-left: (" + rect.top_left.x + ", " + rect.top_left.y + ")")
    println("   Bottom-right: (" + rect.bottom_right.x + ", " + rect.bottom_right.y + ")")
    println("")
    
    // TEST 4: Fonction qui retourne une structure
    println("4. Fonction retournant une structure...")
    
    fn create_point(x: int, y: int): Point {
        ret new Point{x: x, y: y}
    }
    
    muts pt = create_point(50, 75)
    println("   Point créé: (" + pt.x + ", " + pt.y + ")")
    println("")
    
    // TEST 5: Structure comme paramètre
    println("5. Structure comme paramètre...")
    
    fn move_point(p: Point, dx: int, dy: int): Point {
        ret new Point{x: p.x + dx, y: p.y + dy}
    }
    
    muts moved = move_point(pt, 10, 20)
    println("   Original: (" + pt.x + ", " + pt.y + ")")
    println("   Après déplacement: (" + moved.x + ", " + moved.y + ")")
    println("")
    
    // TEST 6: Tableau de structures
    println("6. Tableau de structures...")
    
    muts people = [
        new Person{name: "Bob", age: 25, email: "bob@test.com"},
        new Person{name: "Charlie", age: 35, email: "charlie@test.com"},
        new Person{name: "Diana", age: 28, email: "diana@test.com"}
    ]
    
    muts i = 0
    while i < 3 {
        println("   [" + i + "] " + people[i].name + " (" + people[i].age + ")")
        i = i + 1
    }
    println("")
    
    // TEST 7: Structure avec méthode (via impl)
    println("7. Structure avec méthode...")
    
    struct Counter {
        value: int
    }
    
    impl Counter {
        fn increment(self: Counter): Counter {
            ret new Counter{value: self.value + 1}
        }
        
        fn get_value(self: Counter): int {
            ret self.value
        }
    }
    
    muts counter = new Counter{value: 0}
    println("   Initial: " + counter.get_value())
    counter = counter.increment()
    println("   Après incrément: " + counter.get_value())
    counter = counter.increment()
    println("   Après second incrément: " + counter.get_value())
    println("")
    
    // TEST 8: Comparaison de structures
    println("8. Comparaison de structures...")
    
    fn points_equal(p1: Point, p2: Point): bool {
        ret p1.x == p2.x && p1.y == p2.y
    }
    
    muts p1 = new Point{x: 10, y: 20}
    muts p2 = new Point{x: 10, y: 20}
    muts p3 = new Point{x: 30, y: 40}
    
    println("   p1 == p2: " + points_equal(p1, p2))
    println("   p1 == p3: " + points_equal(p1, p3))
    println("")
    
    // TEST 9: Structure avec chaînes
    println("9. Structure avec chaînes concaténées...")
    
    struct Message {
        from: string
        to: string
        content: string
    }
    
    fn format_message(msg: Message): string {
        ret "From: " + msg.from + "\nTo: " + msg.to + "\n" + msg.content
    }
    
    muts msg = new Message{
        from: "Alice",
        to: "Bob",
        content: "Hello, how are you?"
    }
    
    println(format_message(msg))
    println("")
    
    println("=== TEST STRUCTURES TERMINÉ ===")
    
    ret 0
}
