import deepseek

fn main() {
    println("=== TEST DEEPSEEK ===\n")
    
    lt key = "sk-c21ef26edc184fcfa5124a171fbd6f49"
    lt response = deepseek::ask(key, "Bonjour")
    
    println("Réponse: " + response)
    
    ret 0
}
