golem router

import strean.response

muts routes = {}

pub fn add(method: string, path: string, handler) {
    routes[method + " " + path] = handler
}

pub fn get(path: string, handler) { add("GET", path, handler) }
pub fn post(path: string, handler) { add("POST", path, handler) }
pub fn put(path: string, handler) { add("PUT", path, handler) }
pub fn patch(path: string, handler) { add("PATCH", path, handler) }
pub fn delete(path: string, handler) { add("DELETE", path, handler) }
pub fn options(path: string, handler) { add("OPTIONS", path, handler) }

fn path_match(pattern: string, path: string): any {
    lt expected = pattern.split("/")
    lt actual = path.split("/")
    if expected.len() != actual.len() {
        ret { "matched" => false, "params" => {} }
    }

    muts params = {}
    muts index = 0
    for segment in expected {
        lt value = actual[index]
        if segment[0] == ":" {
            muts name = ""
            muts char_index = 0
            for character in segment {
                if char_index > 0 { name = name + character }
                char_index = char_index + 1
            }
            params[name] = value
        } else if segment != value {
            ret { "matched" => false, "params" => {} }
        }
        index = index + 1
    }
    ret { "matched" => true, "params" => params }
}

pub fn dispatch(request: any): any {
    lt method = request["method"]
    lt path = request["path"]
    muts path_exists = false

    for key in routes {
        lt route_parts = key.split(" ")
        lt matched = path_match(route_parts[1], path)
        if matched["matched"] == true {
            if route_parts[0] == method {
                request["params"] = matched["params"]
                lt handler = routes[key]
                if type_of(handler) == "string" {
                    ret response::html(handler)
                }
                lt result = handler(request)
                if result["__strean_response"] == true {
                    ret result
                }
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
