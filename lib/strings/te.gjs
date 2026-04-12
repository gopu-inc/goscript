fn main() {
    println("=== TEST MINIMAL ===\n")
    
    lt s = "Hello"
    println("String: " + s)
    
    lt cmd = "echo -n '" + s + "' | tr '[:lower:]' '[:upper:]'"
    lt upper = await cmd
    println("Upper: " + upper)
    
    lt cmd2 = "echo -n '" + s + "' | wc -c | tr -d ' \n\t'"
    lt len = await cmd2
    println("Length: " + len)
}
