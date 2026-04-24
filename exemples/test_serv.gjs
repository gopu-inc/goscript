import http

fn main() {
    println("--- GoScript HTTP Server ---")
    println("Press Ctrl+C to shutdown the server")
    
    // Starting the server on port 8080
    http::serve(8080)
    
    ret 0
}

