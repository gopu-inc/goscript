golem router

import strean.response

muts routes = {}
muts route_formats = {}

pub fn add(method: string, path: string, handler, format: string) {
    lt key = method + " " + path
    routes[key] = handler
    route_formats[key] = format
}

pub fn get(path: string, handler) { add("GET", path, handler, "text") }
pub fn post(path: string, handler) { add("POST", path, handler, "text") }
pub fn put(path: string, handler) { add("PUT", path, handler, "text") }
pub fn patch(path: string, handler) { add("PATCH", path, handler, "text") }
pub fn delete(path: string, handler) { add("DELETE", path, handler, "text") }
pub fn options(path: string, handler) { add("OPTIONS", path, handler, "text") }
pub fn post_as(path: string, handler, format: string) { add("POST", path, handler, format) }
pub fn get_as(path: string, handler, format: string) { add("GET", path, handler, format) }
pub fn put_as(path: string, handler, format: string) { add("PUT", path, handler, format) }
pub fn patch_as(path: string, handler, format: string) { add("PATCH", path, handler, format) }
pub fn delete_as(path: string, handler, format: string) { add("DELETE", path, handler, format) }

fn path_match(pattern: string, path: string): bool {
    lt expected = pattern.split("/")
    lt actual = path.split("/")
    muts index = 0
    if expected.len() != actual.len() {
        ret false
    }
    for segment in expected {
        lt value = actual[index]
        if segment[0] == ":" {
            index = index + 1
            continue
        } else if segment != value {
            ret false
        }
        index = index + 1
    }
    ret true
}

pub fn dispatch(request: any): any {
    lt method = request["method"]
    lt path = request["path"]
    muts path_exists = false

    for key in routes {
        lt route_parts = key.split(" ")
        lt matched = path_match(route_parts[1], path)
        if matched == true {
            if route_parts[0] == method {
                request["params"] = {}
                lt handler = routes[key]
                lt format = route_formats[key]
                if type_of(handler) == "string" {
                    if format == "json" { ret response::json(handler) }
                    if format == "stream" { ret response::stream(handler) }
                    if format == "text" { ret response::text(handler) }
                    ret response::html(handler)
                }
                lt result = handler(request)
                if result["__strean_response"] == true {
                    ret result
                }
                if format == "html" { ret response::html(result) }
                if format == "json" { ret response::json(result) }
                if format == "stream" { ret response::stream(result) }
                ret response::text(result)
            }
            path_exists = true
        }
    }

    if path_exists {
        ret response::method_not_allowed(method, path)
    }
    ret response::not_found(path)
}
