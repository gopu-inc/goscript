golem strean

import http
import strean.request as reqmod
import strean.response
import strean.router
import strean.middleware
import strean.static as staticmod
import strean.template as templatemod
import strean.config as configmod
import strean.json as jsonmod

pub cn VERSION = "0.1.0"

pub fn route(method: string, path: string, handler) {
    router::add(method, path, handler)
}

pub fn get(path: string, handler) { router::get(path, handler) }
pub fn post(path: string, handler) { router::post(path, handler) }
pub fn put(path: string, handler) { router::put(path, handler) }
pub fn patch(path: string, handler) { router::patch(path, handler) }
pub fn delete(path: string, handler) { router::delete(path, handler) }
pub fn options(path: string, handler) { router::options(path, handler) }

pub fn before_request(handler) { middleware::before_request(handler) }
pub fn enable_cors() { middleware::enable_cors() }
pub fn logger(request: any) { middleware::logger(request) }

pub fn text(body: string): any { ret response::text(body) }
pub fn html(body: string): any { ret response::html(body) }
pub fn json(body: string): any { ret response::json(body) }
pub fn status(code: int, body: string): any { ret response::status(code, body) }
pub fn redirect(location: string): any { ret response::redirect(location) }
pub fn header(result: any, name: string, value: string): any {
    ret response::set_header(result, name, value)
}
pub fn cookie(result: any, name: string, value: string): any {
    ret response::cookie(result, name, value)
}

pub fn param(request: any, name: string): string { ret reqmod::param(request, name) }
pub fn query(request: any, name: string): string { ret reqmod::query(request, name) }
pub fn body(request: any): string { ret reqmod::body(request) }
pub fn form(request: any): any { ret reqmod::form(request) }
pub fn json_body(request: any): string { ret reqmod::json(request) }
pub fn cookie(request: any, name: string): string { ret reqmod::cookie(request, name) }
pub fn request_header(request: any, name: string): string {
    ret reqmod::header(request, name)
}
pub fn static_file(path: string): any { ret staticmod::file(path) }
pub fn render(source: string, values: any): string { ret templatemod::render(source, values) }
pub fn config_set(name: string, value: any) { configmod::set(name, value) }
pub fn config_get(name: string): any { ret configmod::get(name) }
pub fn json_quote(value: string): string { ret jsonmod::quote(value) }
pub fn json_string_field(name: string, value: string): string {
    ret jsonmod::string_field(name, value)
}

fn dispatch(raw_request: string): string {
    lt request = reqmod::parse(raw_request)
    middleware::before(request)
    lt result = router::dispatch(request)
    result = middleware::apply(result)
    ret response::to_http(result)
}

pub fn run(port: int): int {
    ret http::serve_raw(port, dispatch)
}

pub fn run_on(host: string, port: int): int {
    ret http::serve_raw_on(host, port, dispatch)
}
