import groq

fn main() {
    println("=== TEST GROQ ===\n")
    
    // Remplace par ta clé API Groq
    lt key = "VOTRE_CLE_API_GROQ"
    lt response = groq::ask(key, "Bonjour")
    
    println("Réponse: " + response)
    
    ret 0
}
