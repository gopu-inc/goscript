// std/error.gjs - Module de gestion des erreurs
// Exporte les fonctions utilitaires pour la gestion des erreurs

module error


// std/error.gjs - Module de gestion des erreurs

// Structure d'erreur simple
struct Error {
    message: string
    code: int
}

// Créer une nouvelle erreur
pub fn new_error(msg: string, code: int) -> Error {
    ret Error { message: msg, code: code }
}

// Afficher une erreur
pub fn print_error(err: Error) {
    println("[ERROR " + err.code + "] " + err.message)
}

// Fonction info simple
pub fn info(msg: string) {
    println("[INFO] " + msg)
}

// Fonction warn
pub fn warn(msg: string) {
    println("[WARN] " + msg)
}

// Fonction error (affiche une erreur)
pub fn error(msg: string) {
    println("[ERROR] " + msg)
}

// Fonction fatal (affiche et quitte)
pub fn fatal(msg: string) {
    println("[FATAL] " + msg)
    exit(1)
}

// Fonction assert
pub fn assert(condition: bool, msg: string) {
    if !condition {
        fatal("Assertion failed: " + msg)
    }
}

// Fonction pour convertir une valeur en string
pub fn to_string(val: any) -> string {
    if val.type == 0 { ret "" + val }
    if val.type == 1 { ret "" + val }
    if val.type == 2 { ret val }
    if val.type == 3 { 
        if val { ret "true" } 
        else { ret "false" }
    }
    ret "unknown"
}

// Fonction pour obtenir le type d'une valeur
pub fn type_of(val: any) -> string {
    if val.type == 0 { ret "number" }
    if val.type == 1 { ret "float" }
    if val.type == 2 { ret "string" }
    if val.type == 3 { ret "boolean" }
    if val.type == 8 { ret "array" }
    if val.type == 10 { ret "dict" }
    ret "unknown"
}

// Fonction pour vérifier si une valeur est nulle
pub fn is_nil(val: any) -> bool {
    ret val == nil
}

// Fonction pour vérifier si une valeur est un nombre
pub fn is_number(val: any) -> bool {
    ret val.type == 0 || val.type == 1
}

// Fonction pour vérifier si une valeur est une chaîne
pub fn is_string(val: any) -> bool {
    ret val.type == 2
}

// Fonction pour vérifier si une valeur est un booléen
pub fn is_bool(val: any) -> bool {
    ret val.type == 3
}

// Fonction pour vérifier si une valeur est un tableau
pub fn is_array(val: any) -> bool {
    ret val.type == 8
}

// Fonction pour vérifier si une valeur est un dictionnaire
pub fn is_dict(val: any) -> bool {
    ret val.type == 10
}
