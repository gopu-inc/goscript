// test_deepseek.gjs
import deepseek

fn main() {
    println("=== TEST DEEPSEEK API ===\n")
    
    // Votre clé API
    lt api_key = "votre-cle-api-ici"
    
    // Configuration
    lt cfg = deepseek::new_config(api_key)
    cfg = deepseek::set_temperature(cfg, 0.8)
    
    // Requête simple
    lt response = deepseek::chat(cfg, "Qu'est-ce que le langage Goscript?")
    
    if response.success {
        println("Réponse: " + response.content)
        println("Tokens utilisés: " + response.usage_tokens)
    } else {
        println("Erreur: " + response.error)
    }
    
    // Version simplifiée
    lt answer = deepseek::ask(api_key, "Bonjour, qui es-tu?")
    println(answer)
    
    ret 0
}
