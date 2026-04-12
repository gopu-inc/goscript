import download from "./download"

fn main() {
    println("=== TEST DOWNLOAD ===\n")
    download::file_silent("https://httpbin.org/get", "/tmp/test.json")
    println("Downloaded to /tmp/test.json")
}
