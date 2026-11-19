/*
 * lib/net/websocket.gjs — Support WebSocket RFC 6455 pour Goscript
 * Usage : import net.websocket
 */

pub fn accept(handle_client) {
    ret gs_ws_accept(handle_client)
}

pub fn send(handle, message) {
    ret gs_ws_send(handle, message)
}

pub fn recv(handle) {
    ret gs_ws_recv(handle)
}

pub fn serve(port, callback) {
    lt srv = gs_tcp_server(port)
    if srv < 0 {
        print("[websocket] Erreur: impossible d'écouter sur le port " + str(port))
        ret nil
    }
    print("[websocket] Serveur démarré sur :" + str(port))
    loop {
        lt client = gs_tcp_accept(srv)
        if client >= 0 {
            lt ok = gs_ws_accept(client)
            if ok == 1 {
                callback(client)
            }
            gs_tcp_close(client)
        }
    }
}
