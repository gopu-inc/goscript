golem groq
struct Config { api_key: string }
pub fn new_config(api_key: string): Config { ret new Config { api_key: api_key } }
pub fn ask(api_key: string, question: string): string {
    lt body = "{\"model\":\"llama3-8b-8192\",\"messages\":[{\"role\":\"user\",\"content\":" + gpm_json_quote(question) + "}]}"
    ret gpm_http_post_json("https://api.groq.com/openai/v1/chat/completions", body, api_key)
}
