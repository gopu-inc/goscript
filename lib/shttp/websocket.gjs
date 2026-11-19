golem websocket
pub fn serve(port: int): int { ret gs_tcp_server(port) }
pub fn serve_echo(port: int): int { ret gs_tcp_server(port) }
pub fn tcp_connect(host: string, port: string, message: string): string {
    lt socket = gs_tcp_connect(host, port)
    if socket < 0 { ret "" }
    gs_tcp_send(socket, message)
    lt result = gs_tcp_recv(socket, 4096)
    gs_tcp_close(socket)
    ret result
}
