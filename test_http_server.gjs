// Run with ./gd test_http_server.gjs, then request it with:
// curl -i http://127.0.0.1:8080/
import http

fn hello(request: string): string {
    ret "Hello from Goscript HTTP!\n"
}

fn main() {
    http::serve_once(8080, hello)
}
