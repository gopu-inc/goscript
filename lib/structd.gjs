// ============================================
// STRUCTD - Module pour structures
// Version stable sans erreurs de syntaxe
// ============================================

// Convertir une structure en JSON
pub fn to_json(obj) {
    if type_of(obj) == "struct" {
        muts result = "{"
        muts fields_list = fields(obj)
        muts i = 0
        while i < len(fields_list) {
            result = result + "\"" + fields_list[i] + "\":" + to_json(get(obj, fields_list[i]))
            if i < len(fields_list) - 1 {
                result = result + ","
            }
            i = i + 1
        }
        ret result + "}"
    } else if type_of(obj) == "int" {
        ret obj
    } else if type_of(obj) == "string" {
        ret "\"" + obj + "\""
    } else if type_of(obj) == "bool" {
        if obj {
            ret "true"
        } else {
            ret "false"
        }
    } else if type_of(obj) == "array" {
        muts result = "["
        muts i = 0
        while i < len(obj) {
            result = result + to_json(obj[i])
            if i < len(obj) - 1 {
                result = result + ","
            }
            i = i + 1
        }
        ret result + "]"
    } else {
        ret "null"
    }
}

// Cloner une structure
pub fn clone(obj) {
    if type_of(obj) == "struct" {
        ret obj
    } else if type_of(obj) == "array" {
        muts result = []
        muts i = 0
        while i < len(obj) {
            result = push(result, clone(obj[i]))
            i = i + 1
        }
        ret result
    } else {
        ret obj
    }
}

// Comparer deux objets
pub fn equals(a, b): bool {
    if type_of(a) != type_of(b) {
        ret false
    }
    ret a == b
}

// Obtenir les champs d'une structure
pub fn fields(obj) {
    ret []
}

// Obtenir un champ
pub fn get(obj, field) {
    ret obj[field]
}

// Définir un champ
pub fn set(obj, field, value) {
    obj[field] = value
    ret obj
}

// Afficher une structure
pub fn dump(obj) {
    println("=== STRUCTURE DUMP ===")
    println("Type: " + type_of(obj))
    println("JSON: " + to_json(obj))
    println("===================")
}

info("structd module loaded")
