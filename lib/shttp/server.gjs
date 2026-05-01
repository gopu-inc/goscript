module server

pub fn simple(port: string): string {
    lt cmd = "sh -c \"while true; do echo -e 'HTTP/1.1 200 OK\\r\\n\\r\\nHello' | nc -l -p " + port + " -q 1; done\""
    lt result = await cmd
    ret result
}

pub fn static(port: string, dir: string): string {
    lt cmd = "sh -c \"cd " + dir + " && python3 -m http.server " + port + "\""
    lt result = await cmd
    ret result
}

pub fn php(port: string, dir: string): string {
    lt cmd = f"cd {dir} php -S 0.0.0.0:  {port}"
    lt result = sysf(cmd)
    ret result
}

pub fn busybox(port: string, dir: string): string {
    lt cmd = "sh -c \"busybox httpd -f -p " + port + " -h " + dir + "\""
    lt result = await cmd
    ret "ok"
}
it cmd
    ret "ok"
}
eware)
    }
    
    pub fn get(path: string, handler: fn(ctx: Context): void): void {
        self.route("GET", path, handler)
    }
    
    pub fn post(path: string, handler: fn(ctx: Context): void): void {
        self.route("POST", path, handler)
    }
    
    pub fn put(path: string, handler: fn(ctx: Context): void): void {
        self.route("PUT", path, handler)
    }
    
    pub fn delete(path: string, handler: fn(ctx: Context): void): void {
        self.route("DELETE", path, handler)
    }
    
    pub fn route(method: Method, path: string, handler: fn(ctx: Context): void): void {
        if !self.routes[path] {
            self.routes[path] = {}
        }
        self.routes[path][method] = handler
    }
    
    pub fn static(path: string, dir: string): void {
        self.static_routes[path] = dir
    }
    
    pub fn start(): void {
        // Créer le socket avec netcat/nc
        self.socket = socket_c(AF_INET, SOCK_STREAM, 0)
        
        if self.socket < 0 {
            println "Failed to create socket"
            ret
        }
        
        // Configurer le socket pour réutilisation
        lt opt = 1
        setsockopt_c(self.socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))
        
        // Binder le socket
        lt addr = create_sockaddr_in(self.port)
        if bind_c(self.socket, &addr, sizeof(addr)) < 0 {
            println "Failed to bind to port " + self.port
            ret
        }
        
        // Écouter les connexions
        listen_c(self.socket, 10)
        self.running = true
        
        println "[[POGS]] Server started on http://localhost:" + self.port
        
        // Boucle principale
        while self.running {
            lt client = accept_c(self.socket, null, null)
            
            if client >= 0 {
                // Gérer la connexion dans un processus séparé
                spawn self.handle_connection(client)
            }
        }
    }
    
    fn handle_connection(client: int): void {
        // Lire la requête
        lt buffer = malloc_c(4096)
        lt bytes = recv_c(client, buffer, 4095, 0)
        
        if bytes > 0 {
            buffer[bytes] = 0
            lt request_str = string(buffer)
            
            // Parser la requête HTTP
            lt request = parse_http_request(request_str)
            
            // Créer le contexte
            lt ctx = Context{
                request: request,
                response: Response{
                    status: 200,
                    headers: {},
                    client_fd: client
                },
                params: {},
                query: parse_query_string(request.path)
            }
            
            // Exécuter les middlewares
            for middleware in self.middlewares {
                middleware(ctx)
                if ctx.response.sent { break }
            }
            
            // Router la requête
            if !ctx.response.sent {
                self.handle_route(ctx)
            }
        }
        
        close_c(client)
        free_c(buffer)
    }
    
    fn handle_route(ctx: Context): void {
        lt path = ctx.request.path
        lt method = ctx.request.method
        
        // Vérifier les routes statiques
        for static_path, static_dir in self.static_routes {
            if path.starts_with(static_path) {
                lt file_path = static_dir + path.substring(static_path.length)
                ctx.response.file(file_path)
                ret
            }
        }
        
        // Chercher la route exacte
        if self.routes[path] && self.routes[path][method] {
            self.routes[path][method](ctx)
            ret
        }
        
        // Chercher les routes avec paramètres (:id)
        for route_path, handlers in self.routes {
            if route_path.contains(":") {
                lt match = match_route_params(route_path, path)
                if match.found && handlers[method] {
                    ctx.params = match.params
                    handlers[method](ctx)
                    ret
                }
            }
        }
        
        // Route non trouvée
        ctx.response.status(404).json({
            "error": "Not Found",
            "path": path,
            "method": method
        })
    }
    
    pub fn stop(): void {
        self.running = false
        if self.socket >= 0 {
            close_c(self.socket)
        }
    }
}
