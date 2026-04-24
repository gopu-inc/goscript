import json

fn main() {
    println("--- Testing Native JSON (Bash/Sed) ---")

    lt raw_json = "{\"name\": \"Mauricio\", \"role\": \"Admin\", \"id\": 2026}"
    
    // 1. Formatage (Pretty Print)
    println("Formatted JSON:")
    println(json::format(raw_json))

    // 2. Extraction de valeurs
    lt user = json::get(raw_json, "name")
    lt year = json::get(raw_json, "id")

    println("Extracted Name : " + user)
    println("Extracted Year : " + year)

    // 3. Validation
    if (json::is_json(raw_json) == "True") {
        println("✅ Valid JSON structure.")
    }

    ret 0
}

