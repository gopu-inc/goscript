import ft from "../time/ft"

module websocket

// ============================================
// Serveur WebSocket avec websocketd
// ============================================

pub fn serve(port: string, command: string): string {
    lt cmd = f"websocketd --port={port} {command}"
    lt result = sysf(cmd)
    ret result
}
serve_static(port: string, message: string): string {
    lt cmd = "sh -c \"websocketd --port=" + port + " sh -c 'while true; do echo '" + message + "'; sleep 1; done'\""
    lt result = await cmd
    ret result
}

pub fn serve_echo(port: string): string {
    lt cmd = "sh -c \"websocketd --port=" + port + " cat\""
    lt result = await cmd
    ret result
}

pub fn serve_command(port: string): string {
    lt cmd = "sh -c \"websocketd --port=" + port + " sh -c 'while read line; do eval \\$line; done'\""
    lt result = await cmd
    ret result
}

// ============================================
// Client WebSocket (via wget/wscat)
// ============================================

pub fn connect_wscat(url: string): string {
    lt cmd = "sh -c \"wscat -c " + url + "\""
    lt result = await cmd
    ret result
}

pub fn test_connect(host: string, port: string): string {
    lt cmd = "sh -c \"echo 'test' | nc " + host + " " + port + "\""
    lt result = await cmd
    ret result
}

// ============================================
// Simple TCP Socket
// ============================================

pub fn tcp_listen(port: string): string {
    lt cmd = "sh -c \"nc -l -p " + port + "\""
    lt result = await cmd
    ret result
}

pub fn tcp_connect(host: string, port: string, message: string): string {
    lt cmd = "sh -c \"echo '" + message + "' | nc " + host + " " + port + "\""
    lt result = await cmd
    ret result
}
