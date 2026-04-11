// Test basique d'await avec curl
async fn fetch_data() {
    println("Début du téléchargement...")
    
    // Télécharger une page web
    let result = await curl("https://httpbin.org/get")
    println("Résultat reçu!")
    println("Longueur: " + strlen(result))
    
    return result
}

fn main() {
    println("=== TEST AWAIT ===\n")
    
    let data = fetch_data()
    println("Données reçues: " + data)
    
    return 0
}
