// lib/http.gjs
golem http

// Perform a simple HTTP GET request.
pub fn get(url: string): string {
    lt cmd = "python3 -c \"import urllib.request; print(urllib.request.urlopen('" + url + "').read().decode())\""
    ret sysf(cmd)
}

// Start an HTTP/1.1 server. The handler receives the raw request and returns
// the response body. Each connection gets one request and a 200 text response.
fn serve_requests(host: string, port: int, handler, request_limit: int, raw_response: bool): int {
    lt listener = gs_tcp_server_host(host, port)
    if listener < 0 {
        println("http: could not listen on port " + port)
        ret -1
    }

    println("HTTP server listening on http://127.0.0.1:" + port)
    muts served = 0

    while request_limit == 0 || served < request_limit {
        lt client = gs_tcp_accept(listener)
        if client < 0 {
            continue
        }

        gs_tcp_set_timeout(client, 5)
        lt request = gs_tcp_recv_http(client, 65535)
        if request != "" {
            lt result = handler(request)
            lt response = result
            if !raw_response {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\nConnection: close\r\n\r\n" + result
            }
            gs_tcp_send(client, response)
            served = served + 1
        }
        gs_tcp_close(client)
    }

    gs_tcp_close(listener)
    ret served
}

// Serve requests until the process is interrupted.
pub fn server(port: int): int {
    ret serve_requests("0.0.0.0", port, default_handler, 0, false)
}

// Start a server with an application handler.
pub fn serve(port: int, handler): int {
    ret serve_requests("0.0.0.0", port, handler, 0, false)
}

// The handler returns a complete HTTP response including status and headers.
pub fn serve_raw(port: int, handler): int {
    ret serve_requests("127.0.0.1", port, handler, 0, true)
}

pub fn serve_raw_on(host: string, port: int, handler): int {
    ret serve_requests(host, port, handler, 0, true)
}

// One-request variant for small scripts and local checks.
pub fn serve_once(port: int, handler): int {
    ret serve_requests("127.0.0.1", port, handler, 1, false)
}

fn default_handler(request: string): string {
    ret "Goscript HTTP server is running.\n"
}

