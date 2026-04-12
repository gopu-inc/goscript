module flout

pub fn create_app(): string {
    ret "Flout App"
}

pub fn route(app: string, path: string, handler: string): string {
    lt cmd = "echo Route " + path + " registered"
    lt result = await cmd
    ret result
}

pub fn run(app: string, port: string): string {
    lt cmd = "sh -c \"echo Flout server starting on port " + port + "...\""
    lt result = await cmd
    ret result
}
