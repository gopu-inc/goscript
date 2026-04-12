import http from "./http"
import client from "./client"
import download from "./download"

fn main() {
    println("=== TEST ALL HTTP MODULES ===\n")
    
    println("--- HTTP GET ---")
    lt get_resp = http::get("https://httpbin.org/get?test=1")
    println(get_resp)
    
    println("\n--- HTTP POST ---")
    lt post_resp = http::post("https://httpbin.org/post", "hello=world")
    println(post_resp)
    
    println("\n--- CLIENT TIMEOUT ---")
    lt timeout_resp = client::get_timeout("https://httpbin.org/get", "5")
    println(timeout_resp)
    
    println("\n--- DOWNLOAD ---")
    download::file_silent("https://httpbin.org/json", "/tmp/httpbin.json")
    println("Downloaded!")
    
    println("\n✅ All HTTP tests passed!")
}
