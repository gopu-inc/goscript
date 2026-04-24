import math

fn main() {
    println("--- Testing Native Math (Bash/Awk) ---")

    // 1. Racine carrée de 144
    lt s = math::sqrt(144)
    println("Square root of 144: " + s)

    // 2. Puissance (2^10)
    lt p = math::pow(2, 10)
    println("2 power 10: " + p)

    // 3. Arrondi
    lt r = math::round(15.7)
    println("Round 15.7: " + r)

    // 4. Random (0-100)
    lt rd = math::random(100)
    println("Random number: " + rd)

    ret 0
}

math::divide(a, b))
    println("square(" + a + ") = " + math::square(a))
    
    println("\n=== TEST RÉUSSI ===")
    ret 0
}
