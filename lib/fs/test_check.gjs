import search from "./search"

fn main() {
    println("=== CHECK FILE ===\n")
    
    lt exists = search::file_exists("/tmp/test.txt")
    println("File exists: " + exists)
    
    if exists == "true" {
        lt cmd = "sh -c \"cat '/tmp/test.txt'\""
        lt content = await cmd
        println("Content: " + content)
    }
}
