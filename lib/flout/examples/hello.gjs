import flout from "../flout"
import response from "../response"

fn hello(): string {
    ret response::html("<h1>Hello from Flout!</h1>")
}

fn main() {
    println("=== FLOUT HELLO ===\n")
    println(hello())
}
