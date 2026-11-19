import http
golem flout
pub fn create_app(): string { ret "Flout App" }
pub fn route(app: string, path: string, handler: string): string { ret app }
pub fn run(app: string, port: string): int { ret http::server(atoi_c(port)) }
