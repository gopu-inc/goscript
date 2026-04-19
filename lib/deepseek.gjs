// ============================================
// MODULE: deepseek.gjs
// API DeepSeek pour Goscript
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
    error: string,
    usage_tokens: int
}

// ============================================
// FONCTIONS PRIVÉES
// ============================================

// Échapper les guillemets pour JSON
fn escape_json(s: string): string {
    if s == nil {
        ret ""
    }
    muts result = ""
    muts i = 0
    while i < len(s) {
        lt c = s[i]
        if c == '"' {
            result = result + "\\\""
        } else if c == '\\' {
            result = result + "\\\\"
        } else if c == 10 {  // \n
            result = result + "\\n"
        } else if c == 13 {  // \r
            result = result + "\\r"
        } else if c == 9 {   // \t
            result = result + "\\t"
        } else {
            result = result + s[i]
        }
        i = i + 1
    }
    ret result
}

// Extraire le contenu de la réponse JSON
fn extract_content(json_str: string): string {
    if json_str == nil || json_str == "" {
        ret ""
    }
    
    // Chercher "content":" ou "content": "
    lt pattern = "\"content\":\""
    muts start = -1
    muts i = 0
    
    while i < len(json_str) - 9 {
        muts match = true
        muts j = 0
        while j < 10 {
            if json_str[i + j] != pattern[j] {
                match = false
                break
            }
            j = j + 1
        }
        if match {
            start = i + 10
            break
        }
        i = i + 1
    }
    
    if start == -1 {
        ret ""
    }
    
    // Trouver la fin du contenu
    muts end = start
    while end < len(json_str) {
        if json_str[end] == '"' && (end == 0 || json_str[end - 1] != '\\') {
            break
        }
        end = end + 1
    }
    
    // Extraire
    muts content = ""
    i = start
    while i < end {
        content = content + json_str[i]
        i = i + 1
    }
    
    ret content
}

// Extraire les tokens utilisés
fn extract_tokens(json_str: string): int {
    if json_str == nil || json_str == "" {
        ret 0
    }
    
    lt pattern = "\"total_tokens\":"
    muts start = -1
    muts i = 0
    
    while i < len(json_str) - 14 {
        muts match = true
        muts j = 0
        while j < 14 {
            if json_str[i + j] != pattern[j] {
                match = false
                break
            }
            j = j + 1
        }
        if match {
            start = i + 14
            break
        }
        i = i + 1
    }
    
    if start == -1 {
        ret 0
    }
    
    // Lire le nombre
    muts num_str = ""
    i = start
    while i < len(json_str) {
        lt c = json_str[i]
        if c >= '0' && c <= '9' {
            num_str = num_str + c
        } else {
            break
        }
        i = i + 1
    }
    
    // Convertir en int
    muts result = 0
    i = 0
    while i < len(num_str) {
        result = result * 10 + (num_str[i] - '0')
        i = i + 1
    }
    
    ret result
}

// ============================================
// FONCTIONS PUBLIQUES
// ============================================

// Créer une configuration
pub fn new_config(api_key: string): DeepSeekConfig {
    ret DeepSeekConfig{
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
    // Échapper le prompt
    lt escaped_prompt = escape_json(prompt)
    
    // Construire le JSON
    lt json_body = "{\"model\":\"" + cfg.model + "\",\"messages\":[{\"role\":\"user\",\"content\":\"" + escaped_prompt + "\"}],\"max_tokens\":" + cfg.max_tokens + ",\"temperature\":" + cfg.temperature + "}"
    
    // Construire la commande curl
    lt cmd = "curl -s -X POST '" + API_URL + "' -H 'Content-Type: application/json' -H 'Authorization: Bearer " + cfg.api_key + "' -d '" + json_body + "'"
    
    // Exécuter avec sysf (capture la sortie)
    lt response = sysf(cmd)
    
    // Vérifier si erreur
    if response == nil || response == "" {
        ret DeepSeekResponse{
            success: false,
            content: "",
            error: "Pas de réponse de l'API",
            usage_tokens: 0
        }
    }
    
    // Vérifier si c'est une erreur API
    if contains(response, "\"error\"") {
        ret DeepSeekResponse{
            success: false,
            content: "",
            error: "Erreur API: " + response,
            usage_tokens: 0
        }
    }
    
    // Extraire le contenu et les tokens
    lt content = extract_content(response)
    lt tokens = extract_tokens(response)
    
    ret DeepSeekResponse{
        success: true,
        content: content,
        error: "",
        usage_tokens: tokens
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
    // Construire le tableau de messages JSON
    muts json_messages = "["
    muts i = 0
    while i < len(messages) {
        lt msg = messages[i]
        if i > 0 {
            json_messages = json_messages + ","
        }
        json_messages = json_messages + "{\"role\":\"" + msg.role + "\",\"content\":\"" + escape_json(msg.content) + "\"}"
        i = i + 1
    }
    json_messages = json_messages + "]"
    
    // Construire le JSON complet
    lt json_body = "{\"model\":\"" + cfg.model + "\",\"messages\":" + json_messages + ",\"max_tokens\":" + cfg.max_tokens + ",\"temperature\":" + cfg.temperature + "}"
    
    // Commande curl
    lt cmd = "curl -s -X POST '" + API_URL + "' -H 'Content-Type: application/json' -H 'Authorization: Bearer " + cfg.api_key + "' -d '" + json_body + "'"
    
    lt response = sysf(cmd)
    
    if response == nil || response == "" {
        ret DeepSeekResponse{
            success: false,
            content: "",
            error: "Pas de réponse de l'API",
            usage_tokens: 0
        }
    }
    
    lt content = extract_content(response)
    lt tokens = extract_tokens(response)
    
    ret DeepSeekResponse{
        success: true,
        content: content,
        error: "",
        usage_tokens: tokens
    }
}

// Fonction helper pour contains
fn contains(s: string, sub: string): bool {
    if s == nil || sub == nil {
        ret false
    }
    muts i = 0
    while i <= len(s) - len(sub) {
        muts j = 0
        muts match = true
        while j < len(sub) {
            if s[i + j] != sub[j] {
                match = false
                break
            }
            j = j + 1
        }
        if match {
            ret true
        }
        i = i + 1
    }
    ret false
}

// Fonction len
fn len(s: string): int {
    if s == nil {
        ret 0
    }
    muts count = 0
    muts i = 0
    loop {
        if s[i] == nil {
            break
        }
        count = count + 1
        i = i + 1
    }
    ret count
}