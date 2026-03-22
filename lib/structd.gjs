
// ============================================
// STRUCTD - Module avancé pour structures
// Serialization, Cloning, Comparison, etc.
// ============================================

// ========== UTILITAIRES DE STRUCTURE ==========

// Convertir une structure en JSON
pub fn to_json(obj) {
    match type_of(obj) {
        "struct" => {
            muts result = "{"
            muts fields = struct_fields(obj)
            muts i = 0
            while i < len(fields) {
                result = result + "\"" + fields[i] + "\": " + to_json(struct_get(obj, fields[i]))
                if i < len(fields) - 1 {
                    result = result + ", "
                }
                i = i + 1
            }
            ret result + "}"
        }
        "int" => ret obj
        "string" => ret "\"" + obj + "\""
        "bool" => ret obj ? "true" : "false"
        "array" => {
            muts result = "["
            muts i = 0
            while i < len(obj) {
                result = result + to_json(obj[i])
                if i < len(obj) - 1 {
                    result = result + ", "
                }
                i = i + 1
            }
            ret result + "]"
        }
        _ => ret "null"
    }
}

// Cloner une structure (copie profonde)
pub fn clone(obj) {
    match type_of(obj) {
        "struct" => {
            muts result = struct_new(obj)
            muts fields = struct_fields(obj)
            muts i = 0
            while i < len(fields) {
                struct_set(result, fields[i], clone(struct_get(obj, fields[i])))
                i = i + 1
            }
            ret result
        }
        "array" => {
            muts result = []
            muts i = 0
            while i < len(obj) {
                result = push(result, clone(obj[i]))
                i = i + 1
            }
            ret result
        }
        _ => ret obj
    }
}

// Comparer deux structures
pub fn equals(a, b): bool {
    if type_of(a) != type_of(b) {
        ret false
    }
    
    match type_of(a) {
        "struct" => {
            muts fields_a = struct_fields(a)
            muts fields_b = struct_fields(b)
            
            if len(fields_a) != len(fields_b) {
                ret false
            }
            
            muts i = 0
            while i < len(fields_a) {
                if fields_a[i] != fields_b[i] {
                    ret false
                }
                if !equals(struct_get(a, fields_a[i]), struct_get(b, fields_b[i])) {
                    ret false
                }
                i = i + 1
            }
            ret true
        }
        "array" => {
            if len(a) != len(b) {
                ret false
            }
            muts i = 0
            while i < len(a) {
                if !equals(a[i], b[i]) {
                    ret false
                }
                i = i + 1
            }
            ret true
        }
        _ => ret a == b
    }
}

// Obtenir les noms des champs d'une structure
pub fn fields(obj): []string {
    ret struct_fields(obj)
}

// Obtenir la valeur d'un champ
pub fn get(obj, field) {
    ret struct_get(obj, field)
}

// Définir la valeur d'un champ
pub fn set(obj, field, value) {
    struct_set(obj, field, value)
}

// Vérifier si une structure a un champ
pub fn has_field(obj, field): bool {
    ret struct_has_field(obj, field)
}

// Créer une structure vide du même type
pub fn new(obj) {
    ret struct_new(obj)
}

// ========== STRUCTURE UTILITIES ==========

// Convertir structure en map
pub fn to_map(obj) {
    muts result = map_new()
    muts fields_list = fields(obj)
    muts i = 0
    while i < len(fields_list) {
        map_set(result, fields_list[i], get(obj, fields_list[i]))
        i = i + 1
    }
    ret result
}

// Créer structure depuis map
pub fn from_map(obj, map) {
    muts fields_list = fields(obj)
    muts i = 0
    while i < len(fields_list) {
        if map_has(map, fields_list[i]) {
            set(obj, fields_list[i], map_get(map, fields_list[i]))
        }
        i = i + 1
    }
    ret obj
}

// ========== SERIALIZATION ==========

// Sérialiser en format binaire (simplifié)
pub fn serialize(obj): string {
    match type_of(obj) {
        "struct" => {
            muts result = "S{"
            muts fields_list = fields(obj)
            muts i = 0
            while i < len(fields_list) {
                result = result + fields_list[i] + ":" + serialize(get(obj, fields_list[i]))
                if i < len(fields_list) - 1 {
                    result = result + ","
                }
                i = i + 1
            }
            ret result + "}"
        }
        "int" => ret "I" + obj
        "string" => ret "S\"" + obj + "\""
        "bool" => ret "B" + (obj ? "true" : "false")
        "array" => {
            muts result = "A["
            muts i = 0
            while i < len(obj) {
                result = result + serialize(obj[i])
                if i < len(obj) - 1 {
                    result = result + ","
                }
                i = i + 1
            }
            ret result + "]"
        }
        _ => ret "N"
    }
}

// Désérialiser (version simplifiée)
pub fn deserialize(data: string) {
    // À implémenter
    ret null
}

// ========== DEBUG ==========

// Afficher une structure de façon lisible
pub fn dump(obj) {
    println("=== STRUCTURE DUMP ===")
    println("Type: " + type_of(obj))
    println("Fields: " + fields(obj))
    println("JSON: " + to_json(obj))
    println("===================")
}

// ========== INIT ==========
info("structd module loaded - Advanced structure utilities")
