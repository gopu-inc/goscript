// std/error.gjs - Module de gestion des erreurs
module error
// Définition de la structure
struct Error {
    message: string
    code: int
}

// Fonction pour créer une erreur (Public pour l'export)
pub fn new_error(msg: string, code: int) -> Error {
    // Note l'utilisation de 'new' ici, exigée par ton parser.y
    ret new Error { 
        message: msg, 
        code: code 
    }
}

pub fn info(msg: string) {
    println("[INFO] " + msg)
}

pub fn warn(msg: string) {
    println("[WARN] " + msg)
}
