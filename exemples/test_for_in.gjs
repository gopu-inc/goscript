fn main() {
    // Boucle for-in sur un tableau
    lt numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    println("Nombres pairs:")
    for x in numbers {
        if x % 2 != 0 {
            continue  // Skip odd numbers
        }
        println(x)
    }
    
    // Boucle for-in sur une chaîne (convertissez d'abord en tableau)
    lt chars = ["a", "b", "c", "d", "e"]
    
    println("\nLettres:")
    for c in chars {
        println(c)
    }
    
    ret 0
}
