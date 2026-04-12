import read from "./read"

fn main() {
    println("=== TEST READ ===\n")
    lt lines = read::lines("/tmp/test.txt")
    println(f"Lines: {lines}")
}
