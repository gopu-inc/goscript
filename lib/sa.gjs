import http.transport

fn main() {
    // Utilisation de la méthode associée via l'impl
    lt config = transport::TransportConfig::time(45)
    
    println("Configuration initiale :")
    println(config.max_time)
    
    // Si tu as implémenté les setters
    config.enable_ssl(false)
    
    println("SSL activé :")
    println(config.verify_ssl)
}

