module http

pub fn get(url: string): string {
    lt cmd = "curl -s --get --data-urlencode \"\" \"" + url + "\""
    lt result = await cmd
    ret result
}

pub fn post(url: string, data: string): string {
    lt cmd = "curl -s -X POST -d \"" + data + "\" \"" + url + "\""
    lt result = await cmd
    ret result
}

pub fn put(url: string, data: string): string {
    lt cmd = "curl -s -X PUT -d \"" + data + "\" \"" + url + "\""
    lt result = await cmd
    ret result
}

pub fn delete(url: string): string {
    lt cmd = "curl -s -X DELETE \"" + url + "\""
    lt result = await cmd
    ret result
}
