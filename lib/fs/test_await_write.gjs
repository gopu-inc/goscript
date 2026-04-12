fn main() {
    println("=== TEST AWAIT WRITE ===\n")
    
    lt content = "Hello World"
    lt path = "/tmp/test_await.txt"
    
    lt cmd = "echo -n '" + content + "' > '" + path + "'"
    println("Cmd: " + cmd)
    
    lt result = await cmd
    println("Result: " + result)
    
    lt cmd2 = "cat '" + path + "'"
    lt content2 = await cmd2
    println("Content: " + content2)
}
