// Test réseau ultra simple

fn main() {
    println("=== TEST RESEAU ===")
    
    // Ping Google DNS
    println("\n[1] Ping 8.8.8.8")
    system("ping -c 1 8.8.8.8")
    
    // Ping localhost
    println("\n[2] Ping localhost")
    system("ping -c 1 127.0.0.1")
    
    // DNS lookup
    println("\n[3] DNS google.com")
    system("nslookup google.com || host google.com")
    
    // HTTP request
    println("\n[4] HTTP example.com")
    system("curl -I http://example.com 2>/dev/null | head -1 || wget -q -S --spider http://example.com 2>&1 | head -1")
    
    // Network interfaces
    println("\n[5] Interfaces")
    system("ifconfig | head -5 || ip addr | head -5")
    
    println("\n=== FIN ===")
    
    ret 0
}
