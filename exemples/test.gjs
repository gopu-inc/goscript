// Ce qui marchera enfin :
lt text = "Hello"
println(text::len()) // Affiche 5

t corrigé
// ============================================

// 1. Variables et types de base
lt x = 42
lt y = 3.14
lt name = "Goscript"
lt flag = true

println("=== Test 1: Variables ===")
println(x)
println(y)
println(name)
println(flag)

// 2. Opérations mathématiques
lt a = 10
lt b = 3

println("")
println("=== Test 2: Opérations ===")
println(a + b)
println(a - b)
println(a * b)
println(a / b)

// 3. Conditions
lt score = 85

println("")
println("=== Test 3: Conditions ===")

if score >= 90 {
    println("Excellent!")
} else {
    if score >= 60 {
        println("Pass")
    } else {
        println("Fail")
    }
}

// 4. Boucle while
println("")
println("=== Test 4: Boucle while ===")
lt i = 0
while i < 5 {
    println(i)
    i = i + 1
}

// 5. Boucle loop avec break
println("")
println("=== Test 5: Boucle loop ===")
lt count = 0
loop {
    println(count)
    count = count + 1
    if count >= 3 {
        break
    }
}

// 6. Tableaux
println("")
println("=== Test 6: Tableaux ===")
lt arr = [1, 2, 3, 4, 5]
println(arr)

lt fruits = ["pomme", "banane", "orange"]
println(fruits)

// 7. Fonctions
println("")
println("=== Test 7: Fonctions ===")

fn add(a: int, b: int): int {
    ret a + b
}

fn factorial(n: int): int {
    if n <= 1 {
        ret 1
    }
    ret n * factorial(n - 1)
}

println(add(5, 3))
println(factorial(5))

// 8. Structures
println("")
println("=== Test 8: Structures ===")

struct Person {
    name: string,
    age: int
}

impl Person {
    fn greet(self): void {
        println("Bonjour, je suis " + self.name)
    }
    
    fn birthday(self): void {
        self.age = self.age + 1
        println(self.name + " a maintenant " + self.age + " ans")
    }
}

lt alice = new Person { name: "Alice", age: 25 }
alice.greet()
alice.birthday()

// 9. F-strings (simplifié)
println("")
println("=== Test 9: F-strings ===")

lt prenom = "Charlie"
lt age2 = 28
println(f"Bonjour {prenom}, tu as {age2} ans")

// 10. Pattern matching
println("")
println("=== Test 10: Pattern matching ===")

fn describe(n: int): string {
    match n {
        0 => ret "zero"
        1 => ret "un"
        2 => ret "deux"
        _ => ret "beaucoup"
    }
}

println(describe(0))
println(describe(1))
println(describe(5))

// 11. Lambda
println("")
println("=== Test 11: Lambda ===")

lt double = lambda (x) { ret x * 2 }
lt triple = lambda (x) { ret x * 3 }

println(double(5))
println(triple(5))

// 12. For-in
println("")
println("=== Test 12: For-in ===")

lt numbers = [10, 20, 30, 40]
for n in numbers {
    println("Nombre: " + n)
}

// 13. Mutable variables
println("")
println("=== Test 13: Mutable ===")

muts counter = 0
counter = counter + 1
counter = counter + 2
println(counter)

// 14. Constantes
println("")
println("=== Test 14: Constantes ===")

cn PI = 3.14159
cn MAX_SIZE = 100
println(PI)
println(MAX_SIZE)

// 15. Opérateurs logiques
println("")
println("=== Test 15: Opérateurs logiques ===")

println(true && true)
println(true || false)
println(!false)

// 16. Comparaisons
println("")
println("=== Test 16: Comparaisons ===")

println(5 > 3)
println(5 < 3)
println(5 == 5)
println(5 != 3)

// 17. Assignations composées
println("")
println("=== Test 17: Assignations composées ===")

muts val = 10
val += 5
println(val)
val -= 3
println(val)
val *= 2
println(val)

// 18. Chaînes de caractères
println("")
println("=== Test 18: Chaînes ===")

lt s1 = "Hello"
lt s2 = "World"
println(s1 + " " + s2)

// 19. NNL et JMP
println("")
println("=== Test 19: NNL/JMP ===")

nnl my_label {
    println("Avant le saut")
    jmp my_label 42
    println("Ceci ne sera pas affiché")
}

// 20. Try/Catch/Throw
println("")
println("=== Test 20: Try/Catch ===")

try {
    println("Dans le bloc try")
    throw "Une erreur!"
} catch (e) {
    println("Erreur attrapee: " + e)
} finally {
    println("Finally execute")
}

// 21. Unsafe block
println("")
println("=== Test 21: Unsafe ===")

unsafe {
    println("Code unsafe execute")
}

// 22. Fonctions publiques
println("")
println("=== Test 22: Fonctions publiques ===")

pub fn public_test(): string {
    ret "Fonction publique"
}

println(public_test())

// 23. Struct avec extends
println("")
println("=== Test 23: Struct extends ===")

struct Animal {
    name: string
}

struct Dog extends Animal {
    breed: string
}

lt rex = new Dog { name: "Rex", breed: "Berger" }
println(rex.name)
println(rex.breed)

// 24. Test final
println("")
println("=== Tous les tests sont termines! ===")
println("Goscript fonctionne correctement!")	
