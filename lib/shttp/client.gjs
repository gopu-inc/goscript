// lib/shttp/client.gjs

struct Client {
    base_url: string,
    headers: Headers,
    timeout: int
}

impl Client {
    pub fn new(base_url: string): Client {
        ret new Client{
            base_url: base_url,
            headers: {
                "User-Agent": "GoScript-HTTP/1.0",
                "Accept": "*/*"
            },
            timeout: 30000
        }
    }
    
    pub fn set_header(key: string, value: string): void {
        self.headers[key] = value
    }
    
    pub fn set_timeout(ms: int): void {
        self.timeout = ms
    }
    
    pub fn get(path: string): Response {
        ret self.request("GET", path, "")
    }
    
    pub fn post(path: string, body: string): Response {
        ret self.request("POST", path, body)
    }
    
    pub fn put(path: string, body: string): Response {
        ret self.request("PUT", path, body)
    }
    
    pub fn delete(path: string): Response {
        ret self.request("DELETE", path, "")
    }
    
    pub fn patch(path: string, body: string): Response {
        ret self.request("PATCH", path, body)
    }
    
    fn request(method: Method, path: string, body: string): Response {
        lt url = self.base_url + path
        
        // Construire la commande curl
        lt curl_cmd = "curl -s -i -X " + method
        
        // Ajouter les headers
        for key, value in self.headers {
            curl_cmd = curl_cmd + " -H '" + key + ": " + value + "'"
        }
        
        // Ajouter le timeout
        curl_cmd = curl_cmd + " --max-time " + (self.timeout / 1000)
        
        // Ajouter le body si présent
        if body != "" {
            curl_cmd = curl_cmd + " -d '" + body.replace("'", "'\\''") + "'"
        }
        
        // Ajouter l'URL
        curl_cmd = curl_cmd + " '" + url + "'"
        
        // Exécuter la requête
        lt result = await async_curl_wrapper(curl_cmd)
        
        // Parser la réponse HTTP
        ret parse_http_response(result)
    }
}

// Fonctions de convenance
pub fn get(url: string): Response {
    lt client = Client.new("")
    ret client.request("GET", url, "")
}

pub fn post(url: string, body: string): Response {
    lt client = Client.new("")
    ret client.request("POST", url, body)
}

pub fn put(url: string, body: string): Response {
    lt client = Client.new("")
    ret client.request("PUT", url, body)
}

pub fn delete(url: string): Response {
    lt client = Client.new("")
    ret client.request("DELETE", url, "")
}

// Fonction async pour curl
async fn async_curl_wrapper(cmd: string): string {
    lt promise = run_async_command(cmd)
    lt result = await promise
    ret result.string_val
}
