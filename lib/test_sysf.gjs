import ft from "time/ft"

fn main() {
    println("=== TEST SYSF ===\n")
    
    lt result = sysf("echo 'hello world'")
    ft::sleep(5)
    println("Resultat: " + result)
    
    ret 0
}
