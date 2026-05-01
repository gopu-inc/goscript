// ============================================
// deepseek.gjs - Version ultra simple
// ============================================

module deepseek

struct Config {
    api_key: string
}

pub fn new_config(api_key: string): Config {
    ret new Config{
        api_key: api_key
    }
}

pub fn ask(api_key: string, question: string): string {
    lt cmd = "curl -s -X POST 'https://api.deepseek.com/v1/chat/completions' -H 'Content-Type: application/json' -H 'Authorization: Bearer " + api_key + "' -d '{\"model\":\"deepseek-chat\",\"messages\":[{\"role\":\"user\",\"content\":\"" + question + "\"}]}'"
    
    lt result = sysf(cmd)
    ret result
}
