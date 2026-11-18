golem json

// Escape a string and quote it as a JSON string value.
pub fn quote(value: string): string {
    muts result = "\""
    for character in value {
        if character == "\"" { result = result + "\\\"" }
        else if character == "\\" { result = result + "\\\\" }
        else if character == "\n" { result = result + "\\n" }
        else if character == "\r" { result = result + "\\r" }
        else if character == "\t" { result = result + "\\t" }
        else { result = result + character }
    }
    ret result + "\""
}

pub fn string_field(name: string, value: string): string {
    ret quote(name) + ":" + quote(value)
}

pub fn string_object(name: string, value: string): string {
    ret "{" + string_field(name, value) + "}"
}
