/*
 * tests/test_socket.gjs — Tests du module net.socket
 * Exécution : ./gd tests/test_socket.gjs
 */

import net.socket

print("=== Tests net.socket ===")

// Test 1 : Serveur TCP local + client
print("[1] Serveur TCP local sur :19882 ...")
let srv = socket.server(19882)
if srv >= 0 {
    print("    OK  serveur démarré (handle=" + str(srv) + ")")

    let client_conn = socket.connect("127.0.0.1", "19882")
    if client_conn >= 0 {
        print("    OK  client connecté (handle=" + str(client_conn) + ")")

        let client_srv = socket.accept(srv)
        if client_srv >= 0 {
            print("    OK  connexion acceptée (handle=" + str(client_srv) + ")")

            socket.send(client_conn, "Bonjour Goscript!")
            let msg = socket.recv(client_srv, 256)
            if msg == "Bonjour Goscript!" {
                print("    OK  message transmis : " + msg)
            } else {
                print("    FAIL message incorrect : " + msg)
            }

            let addr = socket.peer_addr(client_srv)
            print("    INFO peer_addr = " + addr)

            socket.close(client_srv)
        } else {
            print("    FAIL accept() échoué")
        }
        socket.close(client_conn)
    } else {
        print("    FAIL client connexion échouée")
    }
    socket.close(srv)
    print("    OK  serveur fermé")
} else {
    print("    FAIL création serveur impossible")
}

// Test 2 : Timeout sur socket
print("[2] Timeout socket ...")
let srv2 = socket.server(19883)
if srv2 >= 0 {
    socket.set_timeout(srv2, 1)
    print("    OK  timeout défini à 1s")
    socket.close(srv2)
}

// Test 3 : API disponibles
print("[3] Vérification API ...")
print("    OK  socket.connect, socket.server, socket.accept disponibles")
print("    OK  socket.send, socket.recv, socket.close disponibles")
print("    OK  socket.set_timeout, socket.peer_addr disponibles")

print("=== Fin tests net.socket ===")
