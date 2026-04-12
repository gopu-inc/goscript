module router

pub fn create(): string {
    ret "{}"
}

pub fn add_route(routes: string, method: string, path: string, handler: string): string {
    lt cmd = "echo Route added: " + method + " " + path
    lt result = await cmd
    ret routes
}

pub fn get(routes: string, path: string): string {
    ret add_route(routes, "GET", path, "")
}

pub fn post(routes: string, path: string): string {
    ret add_route(routes, "POST", path, "")
}
