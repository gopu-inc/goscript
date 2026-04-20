// ============================================
// MODULE: deepseek.gjs
// API DeepSeek pour Goscript
// ============================================

module deepseek

cn API_URL = "https://api.deepseek.com/v1/chat/completions"

struct DeepSeekConfig {
    api_key: string,
    model: string,
    max_tokens: int,
    temperature: float
}

struct DeepSeekResponse {
    success: bool,
    content: string,
    error: string,
    usage_tokens: int
}

// ============================================
// FONCTIONS PRIVÉES
// ============================================

// Utilise strlen_c de la libc - PAS de boucle infinie !
fn len(s: string): int {
    if s == nil {
        ret 0
    }
    ret strlen_c(s)
}

fn contains(s: string, sub: string): bool {
    if s == nil || sub == nil {
        ret false
    }
    lt found = strstr_c(s, sub)
    if found == nil {
        ret false
    }
    ret true
}

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
        } else {
            if c == '\\' {
                result = result + "\\\\"
            } else {
                if c == 10 {
                    result = result + "\\n"
                } else {
                    if c == 13 {
                        result = result + "\\r"
                    } else {
                        if c == 9 {
                            result = result + "\\t"
                        } else {
                            result = result + s[i]
                        }
                    }
                }
            }
        }
        i = i + 1
    }
    ret result
}

fn extract_content(json_str: string): string {
    if json_str == nil || json_str == "" {
        ret ""
    }
    
    lt pattern = "\"content\":\""
    muts start = -1
    muts i = 0
    
    while i < len(json_str) - 9 {
        muts found = true
        muts j = 0
        while j < 10 {
            if json_str[i + j] != pattern[j] {
                found = false
                break
            }
            j = j + 1
        }
        if found {
            start = i + 10
            break
        }
        i = i + 1
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
    i = start
    while i < end {
        content = content + json_str[i]
        i = i + 1
    }
    
    ret content
}

// ============================================
// FONCTIONS PUBLIQUES
// ============================================

pub fn new_config(api_key: string): DeepSeekConfig {
    ret new DeepSeekConfig{
        api_key: api_key,
        model: "deepseek-chat",
        max_tokens: 2048,
        temperature: 0.7
    }
}

pub fn chat(cfg: DeepSeekConfig, prompt: string): DeepSeekResponse {
    lt escaped_prompt = escape_json(prompt)
    
    lt json_body = "{\"model\":\"" + cfg.model + "\",\"messages\":[{\"role\":\"user\",\"content\":\"" + escaped_prompt + "\"}],\"max_tokens\":" + cfg.max_tokens + ",\"temperature\":" + cfg.temperature + "}"
    
    lt cmd = "curl -s -X POST '" + API_URL + "' -H 'Content-Type: application/json' -H 'Authorization: Bearer " + cfg.api_key + "' -d '" + json_body + "'"
    
    lt response = sysf(cmd)
    
    if response == nil || response == "" {
        ret new DeepSeekResponse{
            success: false,
            content: "",
            error: "Pas de reponse",
            usage_tokens: 0
        }
    }
    
    if contains(response, "\"error\"") {
        ret new DeepSeekResponse{
            success: false,
            content: "",
            error: "Erreur API: " + response,
            usage_tokens: 0
        }
    }
    
    lt content = extract_content(response)
    
    ret new DeepSeekResponse{
        success: true,
        content: content,
        error: "",
        usage_tokens: 0
    }
}

pub fn ask(api_key: string, prompt: string): string {
    lt cfg = new_config(api_key)
    lt resp = chat(cfg, prompt)
    if resp.success {
        ret resp.content
    }
    ret "Erreur: " + resp.error
}