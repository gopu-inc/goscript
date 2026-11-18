golem request

fn parse_pairs(source: string): any {
    muts result = {}
    if source == "" {
        ret result
    }

    lt pairs = source.split("&")
    for pair in pairs {
        lt fields = pair.split_once("=")
        result[fields[0]] = fields[1]
    }
    ret result
}

// Parse a single HTTP/1.x request into method, path, query, headers, and body.
// Percent decoding is not yet provided; query and form values are raw.
pub fn parse(raw: string): any {
    lt sections = raw.split_once("\r\n\r\n")
    lt header_lines = sections[0].split("\n")
    lt request_line = header_lines[0].trim()
    lt request_fields = request_line.split(" ")
    lt target = request_fields[1]
    lt target_fields = target.split_once("?")

    lt query_values = {}
    if target_fields[1] != "" {
        query_values = parse_pairs(target_fields[1])
    }

    lt headers = {}
    muts first_line = true
    for line in header_lines {
        if first_line {
            first_line = false
            continue
        }
        lt trimmed = line.trim()
        if trimmed != "" {
            lt header_fields = trimmed.split_once(":")
            headers[header_fields[0].trim().lower()] = header_fields[1].trim()
        }
    }

    ret {
        "method" => request_fields[0],
        "path" => target_fields[0],
        "query" => query_values,
        "headers" => headers,
        "body" => sections[1],
        "params" => {},
        "raw" => raw
    }
}

pub fn method(request: any): string {
    ret request["method"]
}

pub fn path(request: any): string {
    ret request["path"]
}

pub fn query(request: any, name: string): string {
    ret request["query"][name]
}

pub fn header(request: any, name: string): string {
    ret request["headers"][name.lower()]
}

pub fn body(request: any): string {
    ret request["body"]
}

pub fn form(request: any): any {
    ret parse_pairs(request["body"])
}

// Return the body unchanged for JSON decoding by an application library.
pub fn json(request: any): string {
    ret request["body"]
}

pub fn cookie(request: any, name: string): string {
    lt cookie_header = request["headers"]["cookie"]
    lt cookies = cookie_header.split(";")
    for item in cookies {
        lt pair = item.trim().split_once("=")
        if pair[0] == name {
            ret pair[1]
        }
    }
    ret ""
}

pub fn param(request: any, name: string): string {
    ret request["params"][name]
}
