/*
 * lib/net/__self__.gjs — Package net (point d'entrée)
 *
 * import "net"           → charge tous les sous-modules
 * import "net/socket"    → TCP client/serveur
 * import "net/websocket" → WebSocket RFC 6455
 * import "net/proxy"     → Proxy TCP transparent
 */

import "net/socket"
import "net/websocket"
import "net/proxy"
