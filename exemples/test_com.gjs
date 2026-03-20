// ============================================
// TEST COMPLET DU LANGAGE GOSCRIPT
// ============================================

// 1. IMPORTS
import std
import math
import .gui
import packet net/http
import crypto from security

// 2. CONSTANTES
cn APP_NAME = "Goscript"
cn VERSION = "1.0.0"
cn MAX_SIZE = 1024
cn DEBUG_MODE = true

// 3. ÉNUMÉRATIONS
enm Color {
    Red,
    Green,
    Blue,
    Yellow
}

enm Status {
    Active,
    Inactive,
    Pending,
    Error
}

enm HttpMethod {
    GET,
    POST,
    PUT,
    DELETE
}

// 4. STRUCTURES
struct Person {
    name: string,
    age: int,
    email: string,
    active: bool
}

struct Point {
    x: int,
    y: int
}

struct Rectangle {
    width: int,
    height: int,
    color: Color
}

// 5. FONCTIONS SIMPLES
fn add(a: int, b: int) int {
    ret a + b
}

fn subtract(a: int, b: int) int {
    ret a - b
}

fn multiply(a: int, b: int) int {
    ret a * b
}

fn divide(a: int, b: int) int {
    if b == 0 {
        ret 0
    }
    ret a / b
}

fn greet(name: string) {
    println("Hello, " + name + "!")
}

// 6. FONCTION PRINCIPALE
fn @main() {
    println("=== GOSCRIPT TEST SUITE ===")
    println("Version: " + VERSION)
    println("")
    
    // 7. VARIABLES
    lt name = "Goscript User"
    lt age = 25
    lt pi = 3.14159
    lt isActive = true
    lt empty = nil
    
    println("=== VARIABLES ===")
    println("Name: " + name)
    println("Age: " + age)
    println("Pi: " + pi)
    println("Active: " + isActive)
    println("")
    
    // 8. OPÉRATIONS ARITHMÉTIQUES
    println("=== ARITHMETIC OPERATIONS ===")
    lt a = 10
    lt b = 5
    
    lt sum = a + b
    lt diff = a - b
    lt prod = a * b
    lt quot = a / b
    
    println(a + " + " + b + " = " + sum)
    println(a + " - " + b + " = " + diff)
    println(a + " * " + b + " = " + prod)
    println(a + " / " + b + " = " + quot)
    println("")
    
    // 9. FONCTIONS
    println("=== FUNCTIONS ===")
    lt result1 = add(15, 25)
    lt result2 = multiply(8, 7)
    
    println("add(15, 25) = " + result1)
    println("multiply(8, 7) = " + result2)
    greet("Alice")
    println("")
    
    // 10. CONDITIONS IF/ELSE
    println("=== CONDITIONALS ===")
    lt score = 85
    
    if score >= 90 {
        println("Grade: A")
    } else if score >= 80 {
        println("Grade: B")
    } else if score >= 70 {
        println("Grade: C")
    } else if score >= 60 {
        println("Grade: D")
    } else {
        println("Grade: F")
    }
    
    lt temperature = 25
    if temperature > 30 {
        println("It's hot!")
    } else if temperature > 20 {
        println("It's warm")
    } else if temperature > 10 {
        println("It's cool")
    } else {
        println("It's cold!")
    }
    println("")
    
    // 11. BOUCLE FOR (style classique)
    println("=== FOR LOOP (classic) ===")
    for i = 0; i < 5; i = i + 1 {
        println("Iteration: " + i)
    }
    println("")
    
    // 12. BOUCLE WHILE
    println("=== WHILE LOOP ===")
    lt counter = 0
    while counter < 3 {
        println("While count: " + counter)
        counter = counter + 1
    }
    println("")
    
    // 13. BOUCLE INFINIE AVEC BREAK
    println("=== LOOP WITH BREAK ===")
    lt count = 0
    loop {
        println("Loop iteration: " + count)
        count = count + 1
        if count >= 3 {
            break
        }
    }
    println("")
    
    // 14. ÉNUMÉRATIONS
    println("=== ENUMS ===")
    lt color = Color::Blue
    lt status = Status::Active
    
    if color == Color::Blue {
        println("Color is Blue")
    }
    
    if status == Status::Active {
        println("Status is Active")
    }
    println("")
    
    // 15. STRUCTURES
    println("=== STRUCTURES ===")
    lt person = Person{name: "John Doe", age: 30, email: "john@example.com", active: true}
    lt point = Point{x: 10, y: 20}
    lt rect = Rectangle{width: 100, height: 50, color: Color::Red}
    
    println("Person: " + person.name + ", " + person.age + " years old")
    println("Point: (" + point.x + ", " + point.y + ")")
    println("R")

