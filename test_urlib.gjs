import urllib.request
import urllib.server
import json

fn main() {
    println("--- Testing urllib structure ---")

    // 1. Test Request
    lt data = urllib::request::get("https://api.ipify.org?format=json")
    println("IP Data: " + json::format_json(data))

    // 2. Test Server (optional)
    // println("\nStarting server...")
    // urllib::server::start(8080)

    ret 0
}

