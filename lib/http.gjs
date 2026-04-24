// lib/http.gjs
module http

// Perform a simple HTTP GET request
pub fn get(url: string): string {
    lt cmd = "python3 -c \"import urllib.request; print(urllib.request.urlopen('" + url + "').read().decode())\""
    ret sysf(cmd)
}

// Start a local HTTP server (Simple version)
pub fn serve(port: int) {
    println("🚀 GoScript Server running on port " + port)
    
    // On utilise directement le module http.server de python
    // C'est la méthode la plus fiable en une ligne
    lt cmd = "python3 -m http.server " + port
    
    sysf(cmd)
}

