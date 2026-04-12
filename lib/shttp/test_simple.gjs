import http from "./http"

fn main() {
    println("=== TEST SIMPLE ===\n")
    
    lt get_resp = http::get("https://httpbin.org/get")
    println(get_resp)
}
