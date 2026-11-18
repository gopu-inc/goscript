golem middleware

muts hooks = {}
muts hook_count = 0
muts cors_enabled = false

// Register a before-request function. It receives the parsed request dict.
pub fn before_request(handler) {
    hooks["hook" + hook_count] = handler
    hook_count = hook_count + 1
}

pub fn before(request: any) {
    muts index = 0
    while index < hook_count {
        lt handler = hooks["hook" + index]
        handler(request)
        index = index + 1
    }
}

pub fn logger(request: any) {
    println(request["method"] + " " + request["path"])
}

pub fn enable_cors() {
    cors_enabled = true
}

pub fn apply(result: any): any {
    if cors_enabled {
        lt headers = result["headers"]
        headers["Access-Control-Allow-Origin"] = "*"
        headers["Access-Control-Allow-Methods"] = "GET, POST, PUT, PATCH, DELETE, OPTIONS"
        headers["Access-Control-Allow-Headers"] = "Content-Type, Authorization"
        result["headers"] = headers
    }
    ret result
}
