fn main() {
    println("=== Test Goscript (Syntaxe Pure) ===")

    // Pas de ; ici
    let nom = "Goscript"
    let version = 1
    
    println("Langage : " + nom)
    println("Longueur : " + len(nom))

    // Utilisation exclusive de for...in
    let nombres = [10, 20, 30]
    println("Itération sur tableau :")
    for n in nombres {
        println("Valeur : " + n)
    }

    // Utilisation d'une fonction du builtin (map)
    // Note : map utilise 'for item in collection' à l'intérieur
    let carres = map(nombres, lambda(x) { 
        return x * x 
    })
    
    println("Fin du test")
}
