// test_deepseek.gjs - Test simple de l'API DeepSeek
import deepseek

fn main() {
    println("=== TEST DEEPSEEK API ===\n")
    
    // Remplace par ta vraie clé API DeepSeek
    lt api_key = "sk-c21ef26edc184fcfa5124a171fbd6f49"
    
    // Test simple avec ask
    println("--- Test ask ---")
    lt reponse = deepseek::ask(api_key, "Bonjour, qui es-tu?")
    println("Réponse: " + reponse)
    
    ret 0
}
