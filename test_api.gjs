fn main() {
    println("=== APPEL API ASYNCHRONE ===\n")
    
    // Appel API météo
    lt weather = await "curl -s 'https://api.open-meteo.com/v1/forecast?latitude=48.8566&longitude=2.3522&current_weather=true'"
    println("Météo Paris:\n" + weather)
    
    // Appel API GitHub
    lt repo = await "curl -s https://api.github.com/repos/gopu-inc/goscript"
    println("\nInfos repo:\n" + repo)
    
    ret 0
}
