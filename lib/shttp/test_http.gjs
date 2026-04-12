import http from "./http"

fn main() {
    println("=== TEST HTTP ===\n")
    
    println("GET:")
    lt get_resp = http::get("https://httpbin.org/get")
    println(get_resp)
    
    println("\nPOST:")
    lt post_resp = http::post("https://httpbin.org/post", "name=test")
    println(post_resp)
}
