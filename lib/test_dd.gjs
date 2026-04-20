import deepseek

fn main() {
    println("=== TEST DEEPSEEK API ===\n")
    
   // cette api et juste pour usage de teste pas pour production par c'est pas d'abonnement
    lt api_key = "sk-c21ef26edc184fcfa5124a171fbd6f49"
    println("--- Test ask ---")
    lt reponse = deepseek::ask(api_key, "Bonjour, qui es-tu?")
    println("Réponse: " + reponse)
    println("")
    
    println("--- Test chat avec config ---")
    lt cfg = deepseek::new_config(api_key)
    cfg = deepseek::set_temperature(cfg, 0.8)
    cfg = deepseek::set_max_tokens(cfg, 100)
    
    lt resp = deepseek::chat(cfg, "Explique ce qu'est Goscript en une phrase.")
    
    if resp.success {
        println("Succès: " + resp.content)
    } else {
        println("Erreur: " + resp.error)
    }
    
    ret 0
}