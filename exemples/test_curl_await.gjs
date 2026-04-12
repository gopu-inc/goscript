fn main() {
    println("=== TEST CURL WITH AWAIT ===\n")
    
    // Télécharger une page simple
    lt response = await "curl -s https://httpbin.org/ip"
    println("IP: " + response)
    
    // Tester avec JSON
    lt json = await "curl -s https://httpbin.org/get?test=1"
    println("\nJSON reçu:\n" + json)
    
    ret 0
}
