import __builtin__
fn main() {
    print("Entrez un nombre : ")
    
    // Utilisation du namespace du module
    lt saisie = __builtin__::inputln()
    
    lt nombre = __builtin__::ints(saisie)
    lt double = nombre * 2
    
    println("Le double de " + __builtin__::str(nombre) + " est " + __builtin__::str(double))
}

