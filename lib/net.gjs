golem net
pub fn get(url: string): string { ret gs_http_get(url) }
pub fn ping(host: string): string {
    lt socket = gs_tcp_connect(host, "80")
    if socket < 0 { ret "Offline" }
    gs_tcp_close(socket)
    ret "Online"
}
pub fn local_ip(): string { ret gs_hostname() }
