import search from "./search"

fn main() {
    println("=== TEST FS ===\n")
    
    lt files = search::search_path("/tmp/test.txt")
    println(files)
    
    lt current = search::current_dir()
    println(f"Current: {current}")
}
