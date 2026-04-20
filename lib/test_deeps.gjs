import deepseek

fn main() {
    println("=== TEST DEEPSEEK API ===\n")
    
    // Remplace par ta vraie clé API
    lt api_key = "sk-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
    
    // Test avec ask (simple)
    println("--- Test ask ---")
    lt reponse1 = deepseek::ask(api_key, "Bonjour, qui es-tu?")
    println(reponse1)
    println("")
    
    // Test avec chat (configuration complète)
    println("--- Test chat ---")
    lt cfg = deepseek::new_config(api_key)
    cfg = deepseek::set_temperature(cfg, 0.8)
    cfg = deepseek::set_max_tokens(cfg, 500)
    
    lt resp = deepseek::chat(cfg, "Explique ce qu'est Goscript en une phrase.")
    
    if resp.success {
        println("Reponse: " + resp.content)
        println("Tokens: " + resp.usage_tokens)
    } else {
        println("Erreur: " + resp.error)
    }
    
    ret 0
}
