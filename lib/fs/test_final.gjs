import write from "./write"
import read from "./read"

fn main() {
    println("=== TEST FINAL ===\n")
    
    write::file_w("/tmp/hello.txt", "Hello from GoScript!")
    println("File written!")
    
    lt content = read::file_r("/tmp/hello.txt")
    println("Content: " + content)
    
    lt lines = read::lines("/tmp/hello.txt")
    println("Lines: " + lines)
}
