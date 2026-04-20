// ============================================
// MODULE: json.gjs
// Parser JSON
// ============================================

module json

// ============================================
// FONCTIONS DE BASE
// ============================================

// Extraire une valeur par sa clé
pub fn get(json_str: string, key: string): string {
    if json_str == nil || key == nil {
        ret ""
    }
    
    lt pattern = "\"" + key + "\":"
    muts start = -1
    
    // Chercher la clé
    lt found = strstr_c(json_str, pattern)
    if found == nil {
        ret ""
    }
    
    // Position après la clé
    start = found - json_str + strlen_c(pattern)
    
    // Sauter les espaces
    while start < strlen_c(json_str) {
        lt c = json_str[start]
        if c != ' ' && c != 10 && c != 13 && c != 9 {
            break
        }
        start = start + 1
    }
    
    // Déterminer le type de valeur
    lt c = json_str[start]
    
    // Valeur string: "..."
    if c == '"' {
        start = start + 1
        muts end = start
        while end < strlen_c(json_str) {
            if json_str[end] == '"' {
                if json_str[end - 1] != '\\' {
                    break
                }
            }
            end = end + 1
        }
        
        muts result = ""
        muts i = start
        while i < end {
            result = result + json_str[i]
            i = i + 1
        }
        ret result
    }
    
    // Valeur numérique ou booléenne
    if c == '-' || (c >= '0' && c <= '9') || c == 't' || c == 'f' || c == 'n' {
        muts end = start
        while end < strlen_c(json_str) {
            lt ch = json_str[end]
            if ch == ',' || ch == '}' || ch == ']' || ch == 10 || ch == 13 {
                break
            }
            end = end + 1
        }
        
        muts result = ""
        muts i = start
        while i < end {
            result = result + json_str[i]
            i = i + 1
        }
        ret result
    }
    
    // Objet ou tableau - retourner la sous-chaîne
    if c == '{' || c == '[' {
        muts depth = 1
        muts end = start + 1
        while end < strlen_c(json_str) {
            if depth <= 0 {
                break
            }
            lt ch = json_str[end]
            if ch == '{' || ch == '[' {
                depth = depth + 1
            } else {
                if ch == '}' || ch == ']' {
                    depth = depth - 1
                }
            }
            end = end + 1
        }
        
        muts result = ""
        muts i = start
        while i < end {
            result = result + json_str[i]
            i = i + 1
        }
        ret result
    }
    
    ret ""
}

// Vérifier le type d'une valeur JSON
pub fn type_of(json_str: string, key: string): string {
    lt val = get(json_str, key)
    if val == "" {
        ret "null"
    }
    
    lt c = val[0]
    
    if c == '"' {
        ret "string"
    }
    if c == '{' {
        ret "object"
    }
    if c == '[' {
        ret "array"
    }
    if c == 't' || c == 'f' {
        ret "boolean"
    }
    if c == 'n' {
        ret "null"
    }
    ret "number"
}

// ============================================
// FONCTIONS AVEC MATCH (version if/else)
// ============================================

// Extraire et convertir selon le type
pub fn value(json_str: string, key: string): string {
    lt val = get(json_str, key)
    ret val
}

// Parser une réponse API complète
pub fn parse_response(response: string): string {
    // Vérifier si c'est une erreur
    if strstr_c(response, "\"error\"") != nil {
        lt error_msg = get(response, "message")
        if error_msg != "" {
            ret "ERROR: " + error_msg
        }
        ret "ERROR: Unknown error"
    }
    
    // Extraire le contenu selon le format
    lt choices_type = type_of(response, "choices")
    
    if choices_type == "array" {
        // Format OpenAI/DeepSeek/Groq
        lt choices = get(response, "choices")
        if choices != "" {
            lt message = get(choices, "message")
            if message != "" {
                lt content = get(message, "content")
                ret content
            }
        }
        ret ""
    }
    
    if choices_type == "object" {
        // Format direct
        lt content = get(response, "content")
        if content != "" {
            ret content
        }
        ret ""
    }
    
    ret ""
}

// ============================================
// CONVERSIONS
// ============================================

// Convertir en entier
pub fn to_int(json_str: string, key: string): int {
    lt val = get(json_str, key)
    if val == "" {
        ret 0
    }
    ret atoi_c(val)
}

// Convertir en flottant
pub fn to_float(json_str: string, key: string): float {
    lt val = get(json_str, key)
    if val == "" {
        ret 0.0
    }
    ret atof_c(val)
}

// Convertir en booléen
pub fn to_bool(json_str: string, key: string): bool {
    lt val = get(json_str, key)
    if val == "true" {
        ret true
    }
    ret false
}

// ============================================
// UTILITAIRES
// ============================================

// Vérifier si une clé existe
pub fn has_key(json_str: string, key: string): bool {
    lt pattern = "\"" + key + "\":"
    lt found = strstr_c(json_str, pattern)
    ret found != nil
}

// Obtenir toutes les clés d'un objet (simple)
pub fn keys(json_str: string): string {
    muts result = "["
    muts i = 0
    muts first = true
    
    while i < strlen_c(json_str) {
        if json_str[i] == '"' {
            muts start = i + 1
            muts end = start
            while end < strlen_c(json_str) && json_str[end] != '"' {
                end = end + 1
            }
            
            // Vérifier si c'est une clé (suivi de :)
            muts j = end + 1
            while j < strlen_c(json_str) && (json_str[j] == ' ' || json_str[j] == 10 || json_str[j] == 13) {
                j = j + 1
            }
            
            if j < strlen_c(json_str) && json_str[j] == ':' {
                if !first {
                    result = result + ","
                }
                first = false
                
                muts k = start
                while k < end {
                    result = result + json_str[k]
                    k = k + 1
                }
            }
            
            i = end
        }
        i = i + 1
    }
    
    result = result + "]"
    ret result
}
