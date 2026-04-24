import json

fn main() {
    println("=== TEST JSON PARSER VIA PYTHON ===")

    // Données JSON brutes
    lt raw_json = '{"name": "Goscript", "version": 2.0, "status": "active"}'

    // 1. Extraire des données
    println("Extraction des données :")
    lt name = json::get_value(raw_json, "name")
    lt version = json::get_value(raw_json, "version")
    
    println("Nom : " + name)
    println("Version : " + version)

    // 2. Formater le JSON
    println("\nJSON Formaté :")
    lt pretty = json::format_json(raw_json)
    println(pretty)

    ret 0
}

