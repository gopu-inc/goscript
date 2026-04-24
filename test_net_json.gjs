import net
import json

fn main() {
    println("--- Testing Native Network (BusyBox) ---")

    // 1. Test Ping
    println("Checking Google Connectivity...")
    lt status = net::ping("8.8.8.8")
    println("Status: " + status)

    // 2. HTTP GET (JSON API)
    println("\nFetching IP Info...")
    lt response = net::get("http://ip-api.com/json")
    
    // On utilise notre nouveau module JSON pour extraire le pays
    lt country = json::get(response, "country")
    println("Server Location: " + country)
    println("Full JSON: " + response)

    ret 0
}

