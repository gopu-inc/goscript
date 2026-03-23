// std/helper.gjs - Fonctions utilitaires générales
module helper
import error
// Répéter une chaîne
pub fn repeat_str(s: string, n: int) -> string {
    muts result = ""
    muts i = 0
    while i < n {
        result = result + s
        i = i + 1
    }
    ret result
}

// Joindre un tableau de chaînes
pub fn join(arr: array, sep: string) -> string {
    muts result = ""
    muts i = 0
    for item in arr {
        if i > 0 {
            result = result + sep
        }
        result = result + to_string(item)
        i = i + 1
    }
    ret result
}

// Fonction map sur tableau
pub fn map(arr: array, fn_to_apply: lambda) -> array {
    muts result = []
    for item in arr {
        muts new_item = fn_to_apply(item)
        result = result + [new_item]
    }
    ret result
}

// Fonction filter sur tableau
pub fn filter(arr: array, predicate: lambda) -> array {
    muts result = []
    for item in arr {
        if predicate(item) {
            result = result + [item]
        }
    }
    ret result
}

// Fonction reduce sur tableau
pub fn reduce(arr: array, initial: any, reducer: lambda) -> any {
    muts accumulator = initial
    for item in arr {
        accumulator = reducer(accumulator, item)
    }
    ret accumulator
}

// Fonction pour obtenir la longueur d'un tableau ou d'une chaîne
pub fn len(val: any) -> int {
    if is_array(val) {
        muts count = 0
        for _ in val {
            count = count + 1
        }
        ret count
    }
    if is_string(val) {
        muts count = 0
        for _ in val {
            count = count + 1
        }
        ret count
    }
    ret 0
}

// Fonction pour inverser un tableau
pub fn reverse(arr: array) -> array {
    muts result = []
    muts i = len(arr) - 1
    while i >= 0 {
        result = result + [arr[i]]
        i = i - 1
    }
    ret result
}

// Fonction pour obtenir les clés d'un dictionnaire
pub fn keys(dict_val: dict) -> array {
    muts result = []
    for key in dict_val {
        result = result + [key]
    }
    ret result
}

// Fonction pour obtenir les valeurs d'un dictionnaire
pub fn values(dict_val: dict) -> array {
    muts result = []
    for key in dict_val {
        result = result + [dict_val[key]]
    }
    ret result
}

// Fonction pour vérifier si une clé existe dans un dictionnaire
pub fn has_key(dict_val: dict, key: any) -> bool {
    for k in dict_val {
        if k == key {
            ret true
        }
    }
    ret false
}

// Fonction pour obtenir la valeur par défaut
pub fn get_or(dict_val: dict, key: any, default: any) -> any {
    if has_key(dict_val, key) {
        ret dict_val[key]
    }
    ret default
}
