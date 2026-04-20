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
