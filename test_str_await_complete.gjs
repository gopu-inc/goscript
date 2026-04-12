import __str

fn main() {
    println("=== __str + AWAIT ===\n")
    
    // Récupérer des données JSON
    lt data = await "curl -s https://httpbin.org/get"
    
    println("Longueur: " + __str::len(data))
    println("En majuscules (début): " + __str::substring(__str::to_upper(data), 0, 50))
    println("Contient 'origin': " + __str::contains(data, "origin"))
    
    // Extraire une partie
    lt start = __str::index_of(data, "origin")
    if start != -1 {
        lt snippet = __str::substring(data, start, start + 30)
        println("Extrait: " + snippet)
    }
    
    // Nettoyer
    lt cleaned = __str::trim(data)
    println("Trimmed length: " + __str::len(cleaned))
    
    ret 0
}
