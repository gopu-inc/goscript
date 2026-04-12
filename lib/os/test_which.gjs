import which from "./which"

fn main() {
    println("=== TEST WHICH ===\n")
    println("ls path: " + which::find("ls"))
    println("python3 exists: " + which::exists("python3"))
    println("nonexistent exists: " + which::exists("nonexistent"))
}
