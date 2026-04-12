// test_debug2.gjs
fn main() {
    println("=== DEBUG 2 ===\n")
    
    lt url = "https://httpbin.org/get?id=440"
    println("URL: " + url)
    
    lt cmd = "curl -s " + url
    println("Cmd: " + cmd)
    
    lt response = await cmd
    println("Response type: " + typeof(response))
    println("Response: [" + response + "]")
}
