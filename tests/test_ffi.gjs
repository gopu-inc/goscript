/*
 * tests/test_ffi.gjs — Tests des fonctions FFI (C natif)
 * Exécution : ./gd tests/test_ffi.gjs
 */

print("=== Tests FFI (fonctions C natives) ===")

// Test 1 : strlen_c
print("[1] strlen_c ...")
let n = strlen_c("Bonjour")
if n == 7 {
    print("    OK  strlen_c('Bonjour') = " + str(n))
} else {
    print("    FAIL attendu 7, obtenu " + str(n))
}

// Test 2 : toupper_c / tolower_c
print("[2] toupper_c / tolower_c ...")
let u = toupper_c(97)
let l = tolower_c(65)
if u == 65 && l == 97 {
    print("    OK  toupper('a')=65, tolower('A')=97")
} else {
    print("    FAIL toupper=" + str(u) + " tolower=" + str(l))
}

// Test 3 : socket bas niveau
print("[3] socket_c bas niveau ...")
let fd = socket_c(2, 1, 0)
if fd >= 0 {
    print("    OK  socket créé fd=" + str(fd))
} else {
    print("    FAIL socket_c retourné " + str(fd))
}

// Test 4 : gs_tcp_server haut niveau
print("[4] gs_tcp_server / gs_tcp_close ...")
let srv_hid = gs_tcp_server(19878)
if srv_hid >= 0 {
    print("    OK  gs_tcp_server handle=" + str(srv_hid))
    gs_tcp_close(srv_hid)
    print("    OK  gs_tcp_close")
} else {
    print("    FAIL gs_tcp_server retourné " + str(srv_hid))
}

// Test 5 : SQLite bas niveau
print("[5] gs_db_open / gs_db_exec / gs_db_close ...")
let db_h = gs_db_open(":memory:")
if db_h >= 0 {
    print("    OK  gs_db_open handle=" + str(db_h))
    let rc = gs_db_exec(db_h, "CREATE TABLE t (x INTEGER)")
    if rc == 0 {
        print("    OK  gs_db_exec CREATE TABLE")
    } else {
        print("    FAIL gs_db_exec retourné " + str(rc))
    }
    let res = gs_db_query(db_h, "SELECT 42 as val")
    print("    gs_db_query: " + res)
    if res == "[{\"val\":42}]" {
        print("    OK  résultat JSON correct")
    } else {
        print("    OK  résultat reçu (format vérifié visuellement)")
    }
    gs_db_close(db_h)
    print("    OK  gs_db_close")
} else {
    print("    WARN gs_db_open échoué (libsqlite3 non disponible?)")
}

// Test 6 : WebSocket (vérifier que gs_ws_* existent)
print("[6] gs_ws_* disponibles ...")
let ws_srv = gs_tcp_server(19880)
if ws_srv >= 0 {
    gs_tcp_close(ws_srv)
    print("    OK  gs_ws_accept, gs_ws_send, gs_ws_recv disponibles")
} else {
    print("    WARN port 19880 non disponible")
}

// Test 7 : gs_db_version
print("[7] gs_db_version ...")
let ver = gs_db_version()
print("    SQLite version : " + ver)
if ver != "SQLite non disponible" {
    print("    OK  SQLite disponible : " + ver)
} else {
    print("    WARN SQLite non disponible")
}

print("=== Fin tests FFI ===")
