import urllib.request
import json

fn main() {
    println("--- Testing HTTP POST ---")
    lt my_data = "{\"name\": \"Mauricio\", \"project\": \"GoScript\"}"
    
    lt response = urllib::request::post("https://httpbin.org/post", my_data)
    println("Server Response: " + json::format_json(response))
    
    ret 0
}

