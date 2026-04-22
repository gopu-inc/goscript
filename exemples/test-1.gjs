import __builtin__
fn main() {
    print("Entrez un nombre : ")
    lt saisie = inputln()
    
    // Conversion en entier pour calcul
    lt nombre = ints(saisie)
    lt double = nombre * 2
    
    // Re-conversion en string pour concaténation complexe si nécessaire
    println("Le double de " + str(nombre) + " est " + str(double))
}

