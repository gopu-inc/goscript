import http from "./lib/http"

fn main() {
    lt url = "https://httpbin.org/get"
    println(f"Testing GET {url}...")
    lt response = http::Get(url)
    println(f"Response: {response}")
}
