import upload from "./upload"

fn main() {
    println("=== TEST UPLOAD ===\n")
    // Créer un fichier test
    lt cmd = "echo 'test content' > /tmp/upload.txt"
    lt r = await cmd
    
    lt result = upload::file("https://httpbin.org/post", "/tmp/upload.txt")
    println(result)
}
