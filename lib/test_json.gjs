import json

fn main() {
    println("=== TEST JSON MODULE ===\n")
    
    // Exemple de réponse API
    lt response = "{\"id\":\"chatcmpl-123\",\"model\":\"llama3\",\"choices\":[{\"message\":{\"role\":\"assistant\",\"content\":\"Bonjour! Je suis une IA.\"}}],\"usage\":{\"total_tokens\":42}}"
    
    println("1. Parser une réponse complète:")
    lt content = json::parse_response(response)
    println("   Content: " + content)
    println("")
    
    println("2. Extraire des valeurs spécifiques:")
    lt model = json::get(response, "model")
    lt tokens = json::get(response, "total_tokens")
    println("   Model: " + model)
    println("   Tokens: " + tokens)
    println("")
    
    println("3. Vérifier les types:")
    match json::type_of(response, "choices") {
        "array" => println("   choices est un array")
        "object" => println("   choices est un object")
        "string" => println("   choices est un string")
        _ => println("   type inconnu")
    }
    println("")
    
    println("4. Vérifier si une clé existe:")
    if json::has_key(response, "model") {
        println("   'model' existe")
    }
    if !json::has_key(response, "nonexistent") {
        println("   'nonexistent' n'existe pas")
    }
    println("")
    
    println("5. Toutes les clés:")
    lt keys = json::keys(response)
    println("   " + keys)
    
    ret 0
}
