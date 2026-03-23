fn main() {
    println("=== TEST TABLEAUX ===\n")
    
    // Créer un tableau
    lt a = [10, 20, 30, 40, 50]
    
    println("Tableau complet: " + a)
    println("Premier élément: " + a[0])
    println("Deuxième élément: " + a[1])
    println("Dernier élément: " + a[4])
    
    // Modifier un élément
    a[2] = 99
    println("Après modification: " + a)
    
    ret 0
}
