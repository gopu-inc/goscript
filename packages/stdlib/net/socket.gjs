/*
 * lib/net/socket.gjs — Module TCP haut niveau pour Goscript
 * Usage : import net.socket
 * Mots-clés Goscript : lt (var), ret (return), fn (fonction nommée)
 */

pub fn connect(host, port) {
    lt port_str = str(port)
    ret gs_tcp_connect(host, port_str)
}

pub fn send(handle, message) {
    ret gs_tcp_send(handle, message)
}

pub fn recv(handle, taille) {
    ret gs_tcp_recv(handle, taille)
}

pub fn close(handle) {
    ret gs_tcp_close(handle)
}

pub fn set_timeout(handle, secondes) {
    ret gs_tcp_set_timeout(handle, secondes)
}

pub fn peer_addr(handle) {
    ret gs_tcp_peer_addr(handle)
}

pub fn server(port) {
    ret gs_tcp_server(port)
}

pub fn accept(handle_serveur) {
    ret gs_tcp_accept(handle_serveur)
}

pub fn request(host, port, message) {
    lt port_str = str(port)
    lt h = gs_tcp_connect(host, port_str)
    if h < 0 {
        ret ""
    }
    gs_tcp_send(h, message)
    lt rep = gs_tcp_recv(h, 65536)
    gs_tcp_close(h)
    ret rep
}
