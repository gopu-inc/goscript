import client from "./client"

fn main() {
    println("=== TEST CLIENT ===\n")
    
    lt resp = client::get_timeout("https://httpbin.org/get", "5")
    println(resp)
}
