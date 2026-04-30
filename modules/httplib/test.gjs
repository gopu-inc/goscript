import get from "./src/get"

fn main() {
    println("=== Test GET Module ===")
    lt response = get::Get("https://httpbin.org/get")
    println(response)
}
