import http
golem server
pub fn simple(port: int): int { ret http::server(port) }
pub fn static(port: int, directory: string): int { ret http::server(port) }
pub fn php(port: int, directory: string): int { ret -1 }
pub fn busybox(port: int, directory: string): int { ret http::server(port) }
