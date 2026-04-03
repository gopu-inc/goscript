struct Point {
    x: int,
    y: int,
    label: string
}

fn main() {
    // Test de l'initialisation avec virgules
    lt p = new Point {
        x: 10,
        y: 20,
        label: "Origine"
    }
    
    print("Point label : ")
    println(p.label)
    print("Coordonnees : ")
    print(p.x)
    print(",")
    println(p.y)
    
    ret 0
}
