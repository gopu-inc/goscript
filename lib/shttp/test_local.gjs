import http from "./http"

fn main() {
    println("=== TEST LOCAL ===\n")
    
    // Utiliser httpbin.org qui accepte tout
    lt resp = http::post("https://httpbin.org/post", "hello=world")
    println(resp)
}
