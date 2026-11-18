// lib/urllib/server.gjs
golem urllib

// Start a simple HTTP server
pub fn start(port: int) {
    println("🚀 GoScript Server running on port " + port)
    // Simple command, no complex python script needed
    sysf("python3 -m http.server " + port)
}

