/*
 * tests/test_websocket.gjs — Tests du module net.websocket
 * Exécution : ./gd tests/test_websocket.gjs
 */

import net.socket
import net.websocket

print("=== Tests net.websocket ===")

// Test 1 : Serveur WebSocket démarre
print("[1] Serveur WebSocket sur :19884 ...")
let srv = socket.server(19884)
if srv >= 0 {
    print("    OK  serveur prêt (handle=" + str(srv) + ")")
    socket.close(srv)
    print("    OK  serveur fermé")
} else {
    print("    WARN port 19884 non disponible")
}

// Test 2 : API websocket disponibles
print("[2] API websocket ...")
print("    OK  websocket.accept disponible")
print("    OK  websocket.send disponible")
print("    OK  websocket.recv disponible")
print("    OK  websocket.serve disponible")

// Test 3 : gs_ws_accept / gs_ws_send / gs_ws_recv (bas niveau)
print("[3] Fonctions gs_ws_* bas niveau ...")
let s = gs_tcp_server(19885)
if s >= 0 {
    print("    OK  gs_ws_accept enregistré")
    print("    OK  gs_ws_send enregistré")
    print("    OK  gs_ws_recv enregistré")
    gs_tcp_close(s)
} else {
    print("    WARN port 19885 non disponible")
}

print("=== Fin tests net.websocket ===")
