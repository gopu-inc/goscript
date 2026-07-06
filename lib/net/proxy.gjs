/*
 * lib/net/proxy.gjs — Proxy TCP/HTTP transparent pour Goscript
 * Usage : import net.proxy
 */

pub fn start(port_local, hote_cible, port_cible) {
    lt h = gs_proxy_start(port_local, hote_cible, port_cible)
    if h < 0 {
        print("[proxy] Erreur: impossible de démarrer sur :" + str(port_local))
        ret -1
    }
    ret h
}

pub fn run(port_local, hote_cible, port_cible) {
    lt srv = start(port_local, hote_cible, port_cible)
    if srv < 0 { ret nil }
    print("[proxy] En écoute :" + str(port_local) + " -> " + hote_cible + ":" + str(port_cible))
    loop {
        gs_proxy_accept_and_relay(srv, hote_cible, port_cible)
    }
}

pub fn accept_once(handle_serveur, hote_cible, port_cible) {
    ret gs_proxy_accept_and_relay(handle_serveur, hote_cible, port_cible)
}
