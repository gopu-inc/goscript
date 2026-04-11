// lib/shttp/router.gjs

struct Router {
    routes: [Route],
    middlewares: [Middleware],
    prefix: string
}

struct Route {
    method: Method,
    path: string,
    handler: fn(ctx: Context): void,
    middlewares: [Middleware]
}

impl Router {
    pub fn new(): Router {
        ret new Router{
            routes: [],
            middlewares: [],
            prefix: ""
        }
    }
    
    pub fn use(middleware: Middleware): void {
        self.middlewares.push(middleware)
    }
    
    pub fn group(prefix: string, callback: fn(router: Router): void): void {
        lt sub_router = Router.new()
        sub_router.prefix = self.prefix + prefix
        callback(sub_router)
        
        // Fusionner les routes
        for route in sub_router.routes {
            self.routes.push(route)
        }
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
    
    pub fn patch(path: string, handler: fn(ctx: Context): void): void {
        self.route("PATCH", path, handler)
    }
    
    pub fn route(method: Method, path: string, handler: fn(ctx: Context): void): void {
        self.routes.push(new Route{
            method: method,
            path: self.prefix + path,
            handler: handler,
            middlewares: []
        })
    }
    
    pub fn mount(path: string, router: Router): void {
        for route in router.routes {
            self.routes.push(new Route{
                method: route.method,
                path: self.prefix + path + route.path,
                handler: route.handler,
                middlewares: self.middlewares + router.middlewares + route.middlewares
            })
        }
    }
}
