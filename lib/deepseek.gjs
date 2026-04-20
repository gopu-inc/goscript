// ============================================
// MODULE: deepseek.gjs
// API DeepSeek pour Goscript
// Utilise les nouvelles fonctionnalités du langage
// ============================================

module deepseek

// Constantes
cn API_URL = "https://api.deepseek.com/v1/chat/completions"

// Structure pour la configuration
struct DeepSeekConfig {
    api_key: string,
    model: string,
    max_tokens: int,
    temperature: float
}

// Structure pour un message
struct Message {
    role: string,
    content: string
}

// Structure pour la réponse
struct DeepSeekResponse {
    success: bool,
    content: string,
    error: string
}

// ============================================
// FONCTIONS UTILITAIRES (utilisent FFI)
// ============================================

// Longueur d'une chaîne - utilise strlen_c de la libc
fn len(s: string): int {
    if s == nil {
        ret 0
    }
    ret strlen_c(s)
}

// Comparer deux chaînes
fn str_eq(a: string, b: string): bool {
    if a == nil || b == nil {
        ret false
    }
    ret strcmp_c(a, b) == 0
}

// Chercher une sous-chaîne
fn str_contains(s: string, sub: string): bool {
    if s == nil || sub == nil {
        ret false
    }
    lt found = strstr_c(s, sub)
    ret found != nil
}

// Échapper les caractères spéciaux pour JSON
fn escape_json(s: string): string {
    if s == nil {
        ret ""
    }
    muts result = ""
    for i in 0..len(s)-1 {
        lt c = s[i]
        switch c {
            '"' => result = result + "\\\""
            '\\' => result = result + "\\\\"
            10 => result = result + "\\n"
            13 => result = result + "\\r"
            9 => result = result + "\\t"
            _ => result = result + s[i]
        }
    }
    ret result
}

// Extraire le contenu de la réponse JSON
fn extract_content(json_str: string): string {
    if json_str == nil || str_eq(json_str, "") {
        ret ""
    }
    
    lt pattern = "\"content\":\""
    muts start = -1
    
    for i in 0..len(json_str)-10 {
        muts found = true
        for j in 0..9 {
            if json_str[i + j] != pattern[j] {
                found = false
                break
            }
        }
        if found {
            start = i + 10
            break
        }
    }
    
    if start == -1 {
        ret ""
    }
    
    muts end = start
    while end < len(json_str) {
        if json_str[end] == '"' {
            if end == 0 {
                break
            } else {
                if json_str[end - 1] != '\\' {
                    break
                }
            }
        }
        end = end + 1
    }
    
    muts content = ""
    for i in start..end-1 {
        content = content + json_str[i]
    }
    
    ret content
}

// ============================================
// FONCTIONS PUBLIQUES
// ============================================

// Créer une configuration
pub fn new_config(api_key: string): DeepSeekConfig {
    ret new DeepSeekConfig{
        api_key: api_key,
        model: "deepseek-chat",
        max_tokens: 2048,
        temperature: 0.7
    }
}

// Définir le modèle
pub fn set_model(cfg: DeepSeekConfig, model: string): DeepSeekConfig {
    cfg.model = model
    ret cfg
}

// Définir max_tokens
pub fn set_max_tokens(cfg: DeepSeekConfig, tokens: int): DeepSeekConfig {
    cfg.max_tokens = tokens
    ret cfg
}

// Définir temperature
pub fn set_temperature(cfg: DeepSeekConfig, temp: float): DeepSeekConfig {
    cfg.temperature = temp
    ret cfg
}

// Envoyer une requête à DeepSeek
pub fn chat(cfg: DeepSeekConfig, prompt: string): DeepSeekResponse {
    lt escaped_prompt = escape_json(prompt)
    
    lt json_body = "{\"model\":\"" + cfg.model + "\",\"messages\":[{\"role\":\"user\",\"content\":\"" + escaped_prompt + "\"}],\"max_tokens\":" + cfg.max_tokens + ",\"temperature\":" + cfg.temperature + "}"
    
    lt cmd = "curl -s -X POST '" + API_URL + "' -H 'Content-Type: application/json' -H 'Authorization: Bearer " + cfg.api_key + "' -d '" + json_body + "'"
    
    lt response = sysf(cmd)
    
    if response == nil || str_eq(response, "") {
        ret new DeepSeekResponse{
            success: false,
            content: "",
            error: "Pas de reponse de l'API"
        }
    }
    
    if str_contains(response, "\"error\"") {
        ret new DeepSeekResponse{
            success: false,
            content: "",
            error: "Erreur API: " + response
        }
    }
    
    lt content = extract_content(response)
    
    ret new DeepSeekResponse{
        success: true,
        content: content,
        error: ""
    }
}

// Version simplifiée avec juste l'API key
pub fn ask(api_key: string, prompt: string): string {
    lt cfg = new_config(api_key)
    lt resp = chat(cfg, prompt)
    if resp.success {
        ret resp.content
    }
    ret "Erreur: " + resp.error
}

// Conversation avec historique
pub fn chat_with_history(cfg: DeepSeekConfig, messages: []Message): DeepSeekResponse {
    muts json_messages = "["
    muts first = true
    
    for i in 0..len(messages)-1 {
        lt msg = messages[i]
        if !first {
            json_messages = json_messages + ","
        }
        first = false
        json_messages = json_messages + "{\"role\":\"" + msg.role + "\",\"content\":\"" + escape_json(msg.content) + "\"}"
    }
    json_messages = json_messages + "]"
    
    lt json_body = "{\"model\":\"" + cfg.model + "\",\"messages\":" + json_messages + ",\"max_tokens\":" + cfg.max_tokens + ",\"temperature\":" + cfg.temperature + "}"
    
    lt cmd = "curl -s -X POST '" + API_URL + "' -H 'Content-Type: application/json' -H 'Authorization: Bearer " + cfg.api_key + "' -d '" + json_body + "'"
    
    lt response = sysf(cmd)
    
    if response == nil || str_eq(response, "") {
        ret new DeepSeekResponse{
            success: false,
            content: "",
            error: "Pas de reponse de l'API"
        }
    }
    
    lt content = extract_content(response)
    
    ret new DeepSeekResponse{
        success: true,
        content: content,
        error: ""
    }
}