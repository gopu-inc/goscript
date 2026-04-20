// ============================================
// groq.gjs - Version ultra simple
// ============================================

module groq

struct Config {
    api_key: string
}

pub fn new_config(api_key: string): Config {
    ret new Config{
        api_key: api_key
    }
}

pub fn ask(api_key: string, question: string): string {
    lt cmd = "curl -s -X POST 'https://api.groq.com/openai/v1/chat/completions' -H 'Content-Type: application/json' -H 'Authorization: Bearer " + api_key + "' -d '{\"model\":\"llama3-8b-8192\",\"messages\":[{\"role\":\"user\",\"content\":\"" + question + "\"}]}'"
    
    lt result = sysf(cmd)
    ret result
}
