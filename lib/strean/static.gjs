golem static

import io
import strean.response

pub fn mime_type(path: string): string {
    lt pieces = path.split(".")
    lt extension = pieces[pieces.len() - 1].lower()
    if extension == "html" || extension == "htm" { ret "text/html; charset=utf-8" }
    if extension == "css" { ret "text/css; charset=utf-8" }
    if extension == "js" { ret "text/javascript; charset=utf-8" }
    if extension == "json" { ret "application/json; charset=utf-8" }
    if extension == "svg" { ret "image/svg+xml" }
    if extension == "txt" { ret "text/plain; charset=utf-8" }
    if extension == "png" { ret "image/png" }
    if extension == "jpg" || extension == "jpeg" { ret "image/jpeg" }
    if extension == "gif" { ret "image/gif" }
    ret "application/octet-stream"
}

pub fn file(path: string): any {
    ret response::set_header(
        response::status(200, io::read_file(path)),
        "Content-Type",
        mime_type(path)
    )
}
