import write from "./write"
import read from "./read"

fn main() {
    println("=== TEST ===\n")
    
    write::file_w("/tmp/test.txt", "Hello")
    println("Written")
    
    lt content = read::file_r("/tmp/test.txt")
    println("Content: " + content)
}
