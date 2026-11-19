golem response

fn make(status: int, content_type: string, body: string): any {
    ret {
        "__strean_response" => true,
        "status" => status,
        "content_type" => content_type,
        "body" => body,
        "headers" => {}
    }
}

pub fn text(body: string): any {
    ret make(200, "text/plain; charset=utf-8", body)
}

pub fn html(body: string): any {
    ret make(200, "text/html; charset=utf-8", body)
}

// Pass a JSON document as a string. The framework keeps it unchanged.
pub fn json(body: string): any {
    ret make(200, "application/json; charset=utf-8", body)
}

pub fn stream(body: string): any {
    ret make(200, "text/event-stream; charset=utf-8", body)
}

pub fn status(status_code: int, body: string): any {
    ret make(status_code, "text/plain; charset=utf-8", body)
}

pub fn redirect(location: string): any {
    lt result = make(302, "text/plain; charset=utf-8", "Redirecting to " + location)
    lt headers = result["headers"]
    headers["Location"] = location
    result["headers"] = headers
    ret result
}

pub fn cookie(result: any, name: string, value: string): any {
    lt headers = result["headers"]
    headers["Set-Cookie"] = name + "=" + value + "; Path=/; HttpOnly; SameSite=Lax"
    result["headers"] = headers
    ret result
}

pub fn set_header(result: any, name: string, value: string): any {
    lt headers = result["headers"]
    headers[name] = value
    result["headers"] = headers
    ret result
}

pub fn not_found(path: string): any {
    ret make(404, "text/plain; charset=utf-8", "Not Found: " + path)
}

pub fn method_not_allowed(method: string, path: string): any {
    ret make(405, "text/plain; charset=utf-8", "Method Not Allowed: " + method + " " + path)
}

fn reason(status_code: int): string {
    if status_code == 200 { ret "OK" }
    if status_code == 201 { ret "Created" }
    if status_code == 204 { ret "No Content" }
    if status_code == 301 { ret "Moved Permanently" }
    if status_code == 302 { ret "Found" }
    if status_code == 400 { ret "Bad Request" }
    if status_code == 401 { ret "Unauthorized" }
    if status_code == 403 { ret "Forbidden" }
    if status_code == 404 { ret "Not Found" }
    if status_code == 405 { ret "Method Not Allowed" }
    if status_code == 500 { ret "Internal Server Error" }
    if status_code == 503 { ret "Service Unavailable" }
    ret "Response"
}

pub fn to_http(result: any): string {
    lt code = result["status"]
    lt body = result["body"]
    lt headers = result["headers"]
    muts wire = "HTTP/1.1 " + code + " " + reason(code) + "\r\n"
    wire = wire + "Content-Type: " + result["content_type"] + "\r\n"
    wire = wire + "Content-Length: " + body.len() + "\r\n"
    wire = wire + "Connection: close\r\n"
    for name in headers {
        wire = wire + name + ": " + headers[name] + "\r\n"
    }
    ret wire + "\r\n" + body
}
