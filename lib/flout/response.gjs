module response

pub fn html(content: string): string {
    lt headers = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"
    ret headers + content
}

pub fn json(content: string): string {
    lt headers = "HTTP/1.1 200 OK\nContent-Type: application/json\n\n"
    ret headers + content
}

pub fn error(code: string, message: string): string {
    lt headers = "HTTP/1.1 " + code + " " + message + "\nContent-Type: text/html\n\n"
    lt body = "<h1>Error " + code + "</h1><p>" + message + "</p>"
    ret headers + body
}
