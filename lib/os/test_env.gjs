import env from "./env"

fn main() {
    println("=== TEST ENV ===\n")
    println("USER: " + env::user())
    println("HOME: " + env::home())
    println("SHELL: " + env::shell())
    println("PWD: " + env::pwd())
}
