import websocket from "./websocket"

fn main() {
    println("=== TEST WEBSOCKET ===\n")
    println("Starting echo server on port 8080...")
    println("Connect with: websocat ws://localhost:8080")
    println("Or test with: echo 'hello' | nc localhost 8080")
    
    // Démarre un serveur echo (bloquant)
    websocket::serve_echo("8080")
}
