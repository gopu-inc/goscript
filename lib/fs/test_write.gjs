import write from "./write"
import read from "./read"

fn main() {
    println("=== TEST WRITE ===\n")
    
    write::file("/tmp/test.txt", "Hello World")
    lt content = read::file("/tmp/test.txt")
    println("Content: " + content)
}
