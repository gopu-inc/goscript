// lib/shttp/__self__.gjs
// Module HTTP pour GoScript

pub cn VERSION = "1.0.0"

// Exporter les composants publics
pub struct Server
pub struct Router
pub struct Request
pub struct Response
pub struct Context

// Fonctions principales
pub fn create_server(port: int): Server
pub fn create_router(): Router
pub fn get(url: string): Response
pub fn post(url: string, body: string): Response
pub fn put(url: string, body: string): Response
pub fn delete(url: string): Response

// Middleware
pub fn logger(): Middleware
pub fn cors(): Middleware
pub fn static_files(path: string): Middleware
pub fn auth(token: string): Middleware

// Types HTTP
type Method = "GET" | "POST" | "PUT" | "DELETE" | "PATCH" | "OPTIONS" | "HEAD"
type StatusCode = int
type Headers = dict<string, string>
type Middleware = fn(ctx: Context): void

// Constantes HTTP
pub cn STATUS_OK = 200
pub cn STATUS_CREATED = 201
pub cn STATUS_NO_CONTENT = 204
pub cn STATUS_BAD_REQUEST = 400
pub cn STATUS_UNAUTHORIZED = 401
pub cn STATUS_FORBIDDEN = 403
pub cn STATUS_NOT_FOUND = 404
pub cn STATUS_METHOD_NOT_ALLOWED = 405
pub cn STATUS_INTERNAL_ERROR = 500
pub cn STATUS_SERVICE_UNAVAILABLE = 503

// Implémentations
impl Server {
    pub fn new(port: int): Server
    pub fn use(middleware: Middleware): void
    pub fn route(method: Method, path: string, handler: fn(ctx: Context): void): void
    pub fn get(path: string, handler: fn(ctx: Context): void): void
    pub fn post(path: string, handler: fn(ctx: Context): void): void
    pub fn put(path: string, handler: fn(ctx: Context): void): void
    pub fn delete(path: string, handler: fn(ctx: Context): void): void
    pub fn static(path: string, dir: string): void
    pub fn start(): void
    pub fn stop(): void
}

impl Router {
    pub fn new(): Router
    pub fn use(middleware: Middleware): void
    pub fn mount(path: string, router: Router): void
    pub fn route(method: Method, path: string, handler: fn(ctx: Context): void): void
}

impl Request {
    pub fn method(): Method
    pub fn path(): string
    pub fn query(): dict<string, string>
    pub fn headers(): Headers
    pub fn body(): string
    pub fn json(): dict
    pub fn form(): dict<string, string>
    pub fn param(name: string): string
    pub fn cookie(name: string): string
    pub fn ip(): string
}

impl Response {
    pub fn status(code: StatusCode): Response
    pub fn header(key: string, value: string): Response
    pub fn send(data: string): void
    pub fn json(data: dict): void
    pub fn html(data: string): void
    pub fn file(path: string): void
    pub fn cookie(name: string, value: string, options: dict): void
    pub fn redirect(url: string, code: StatusCode): void
}
