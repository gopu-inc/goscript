// Import des sous-modules (le parseur lira "http.client" et chargera "lib/http/client.gjs")
import http
import http.client
import http.transport

fn main() {
    println("=== TEST DU PACKAGE HTTP ===")
    
    // Accès au module racine (via __self__.gjs)
    println("Version HTTP : " + http::VERSION)
    
    // Accès aux sous-modules avec ::
    lt config = transport::new_config(60)
    println("Timeout configuré : " + config.timeout)
    
    println("\nExécution d'une requête GET...")
    lt response = client::get("https://httpbin.org/get")
    
    // Affichage natif
    println(response)
    
    ret 0
}

