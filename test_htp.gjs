import http
import json

fn main() {
    println("--- Test HTTP Client (JSON) ---")
    
    // Cette API renvoie un vrai objet JSON : {"ip": "xxx.xxx.xxx.xxx"}
    lt data = http::get("https://api.ipify.org?format=json")
    
    println("Données brutes reçues : " + data)
    println("Données formatées :")
    println(json::format_json(data))

    // On peut même extraire l'IP spécifiquement si ton module json a get_value
    // lt my_ip = json::get_value(data, "ip")
    // println("Ton adresse IP est : " + my_ip)

    ret 0
}

