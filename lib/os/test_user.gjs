import user from "./user"

fn main() {
    println("=== TEST USER ===\n")
    println("Current: " + user::current())
    println("Is root: " + user::is_root())
}
