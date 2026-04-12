import http

fn main() {
    println("Testing HTTP module...")
    lt response = http::Get("https://httpbin.org/get")
    println("Response: " + response)
}
