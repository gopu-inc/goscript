fn main() { ret 0 }
on syntaxique Goscript
// Les couleurs devraient être variées

// ============================================
// Variables et constantes
// ============================================
lt name = "John"                    // variable string
lt age = 25                         // variable int
lt height = 1.85                    // variable float
lt is_active = true                 // boolean
lt PI = 3.14159                     // constante

// Variables mutables
muts counter = 0
muts user = struct User {
    name: string,
    age: int
}

// ============================================
// Structures
// ============================================
struct Person {
    name: string,
    age: int,
    email: string?,
    scores: [int]
}

struct Employee extends Person {
    salary: float,
    position: string
}

// ============================================
// Énumérations
// ============================================
enm Status {
    Active,
    Inactive,
    Pending,
    Deleted
}

// ============================================
// Implémentations
// ============================================
impl Person {
    fn greet(self) {
        println("Hello, " + self.name)
    }
    
    fn update_age(self, new_age: int) {
        self.age = new_age
    }
}

// ============================================
// Fonctions
// ============================================
fn add(a: int, b: int) -> int {
    ret a + b
}

fn process_array(arr: [int]) {
    for value in arr {
        if value % 2 == 0 {
            println("Even: " + value)
        } else {
            println("Odd: " + value)
        }
    }
}

// ============================================
// Dictionnaires et tableaux
// ============================================
lt dict = dict {
    "name": "John",
    "age": 30,
    "active": true
}

lt array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

// Accès
lt value = dict["name"]
lt first = array[0]

// ============================================
// Opérateurs
// ============================================
lt x = 10
lt y = 20

if x < y && x > 0 {
    println("x is less than y")
}

x += 5
y -= 3

lt result = (x * y) / (x + y)

// ============================================
// Boucles
// ============================================
while counter < 10 {
    counter = counter + 1
    if counter % 2 == 0 {
        continue
    }
    println("Counter: " + counter)
}

for i in [1, 2, 3, 4, 5] {
    if i == 3 {
        break
    }
    println("i = " + i)
}

// ============================================
// Pattern matching
// ============================================
match status {
    Active => println("User is active")
    Inactive => println("User is inactive")
    _ => println("Unknown status")
}

// ============================================
// Modules et imports
// ============================================
import math from .math
import sys as system from .system { only: [println, input] }

// ============================================
// Expressions lambda
// ============================================
lt square = lambda x { ret x * x }
lt numbers = [1, 2, 3, 4, 5]
lt squares = map(numbers, square)

// ============================================
// Pipeline
// ============================================
lt processed = numbers
    |> filter( lambda x { x % 2 == 0 } )
    |> map( lambda x { x * x } )
    |> reduce( lambda acc, x { acc + x } )

// ============================================
// Sauts non-locaux
// ============================================
nnl error_handler {
    if something_bad_happens() {
        jmp error_handler "Erreur détectée"
    }
}

// ============================================
// Fonction main
// ============================================
fn main() {
    println("=== Goscript Color Demo ===")
    
    lt person = new Person {
        name: "Alice",
        age: 28,
        email: "alice@example.com"
    }
    
    person.greet()
    
    lt sum = add(10, 20)
    println("Sum: " + sum)
    
    process_array([1, 2, 3, 4, 5])
    
    ret 0
}
