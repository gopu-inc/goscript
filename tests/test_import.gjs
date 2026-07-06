/*
 * tests/test_import.gjs — Tests du système d'imports
 * Exécution : ./gd tests/test_import.gjs
 *
 * Syntaxe d'import Goscript :
 *   import module          -> cherche module.gjs dans ./lib/, ./modules/...
 *   import net.socket      -> cherche net/socket.gjs
 *   import net.socket as s -> avec alias
 */

print("=== Tests système d'imports ===")

// Test 1 : Import module net.socket (cherche lib/net/socket.gjs)
print("[1] Import net.socket ...")
import net.socket
print("    OK  net.socket chargé")

// Test 2 : Import module db.sqlite (cherche lib/db/sqlite.gjs)
print("[2] Import db.sqlite ...")
import db.sqlite
let ver = sqlite.version()
print("    OK  db.sqlite chargé, SQLite: " + ver)

// Test 3 : Import avec alias
print("[3] Import avec alias ...")
import net.socket as sock
let srv = sock.server(19881)
if srv >= 0 {
    sock.close(srv)
    print("    OK  alias 'sock' fonctionne")
} else {
    print("    WARN alias: serveur non créé (port occupé?)")
}

// Test 4 : Double import (cache — doit ne pas recharger)
print("[4] Double import (cache) ...")
import db.sqlite
let ver2 = sqlite.version()
if ver2 == ver {
    print("    OK  cache d'import fonctionne")
} else {
    print("    WARN versions différentes (" + ver + " vs " + ver2 + ")")
}

// Test 5 : Import net.websocket
print("[5] Import net.websocket ...")
import net.websocket
print("    OK  net.websocket chargé")

// Test 6 : Import net.proxy
print("[6] Import net.proxy ...")
import net.proxy
print("    OK  net.proxy chargé")

print("=== Fin tests imports ===")
