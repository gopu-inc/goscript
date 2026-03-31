/* 
 * Goscript Standard Built-in Module
 * Ce module est chargé automatiquement au démarrage.
 */

// =========================================================
// 1. GESTION DES CHAÎNES (STRING)
// =========================================================

module __builtin__

pub fn len(s) {
    // Utilise la fonction native strlen via FFI
    return strlen_c(s);
}

pub fn str_compare(s1, s2) {
    return strcmp_c(s1, s2) == 0;
}

pub fn str_contains(haystack, needle) {
    let res = strstr_c(haystack, needle);
    return res != nil;
}

// =========================================================
// 2. MATHÉMATIQUES
// =========================================================

pub const PI = 3.14159265359;
pub const E  = 2.71828182846;

pub fn abs(n) {
    if n < 0 { return -n; }
    return n;
}

pub fn max(a, b) {
    if a > b { return a; }
    return b;
}

pub fn min(a, b) {
    if a < b { return a; }
    return b;
}

// =========================================================
// 3. UTILITAIRES DE COLLECTIONS (FONCTIONNEL)
// =========================================================

// Ex: [1, 2, 3] |> each(fn(x) { println(x); });
pub fn each(collection, callback) {
    for item in collection {
        callback(item);
    }
}

// Ex: let doubled = [1, 2, 3] |> map(fn(x) { x * 2; });
pub fn map(collection, callback) {
    muts res = [];
    for item in collection {
        res = res + [callback(item)]; // Simulé car push() n'est pas encore en C
    }
    return res;
}

pub fn filter(collection, test) {
    muts res = [];
    for item in collection {
        if test(item) {
            res = res + [item];
        }
    }
    return res;
}

// =========================================================
// 4. SYSTÈME DE FICHIERS (ORIENTATION OBJET)
// =========================================================

pub struct File {
    path: string,
    handle: int,
    is_open: bool
}

impl File {
    pub fn open(path, mode) {
        let fd = fopen_c(path, mode);
        return new File {
            path: path,
            handle: fd,
            is_open: fd != 0
        };
    }

    pub fn write(self, content) {
        if self.is_open {
            return fputs_c(content, self.handle);
        }
        return -1;
    }

    pub fn close(self) {
        if self.is_open {
            fclose_c(self.handle);
            self.is_open = false;
        }
    }
}

// =========================================================
// 5. RÉSEAU (BASIC TCP)
// =========================================================

pub struct TcpClient {
    fd: int,
    host: string,
    port: int
}

impl TcpClient {
    pub fn connect(host, port) {
        // AF_INET = 2, SOCK_STREAM = 1
        let socket_fd = socket_c(2, 1, 0);
        // Ici, on pourrait ajouter la logique de bind/connect via FFI
        return new TcpClient {
            fd: socket_fd,
            host: host,
            port: port
        };
    }

    pub fn send(self, data) {
        return send_c(self.fd, data, len(data), 0);
    }
}

// =========================================================
// 6. SYSTÈME ET DÉBOGAGE
// =========================================================

pub fn assert(condition, message) {
    if !condition {
        print("Assertion failed: ");
        println(message);
        exit_c(1);
    }
}

pub fn sleep(seconds) {
    sleep_c(seconds);
}

pub fn get_env(name) {
    return getenv_c(name);
}

// Petit sucre syntaxique pour le temps
pub fn now() {
    return time_c(0);
}

// Fin du module builtin
