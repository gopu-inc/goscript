ýodule post

pub fn Post(url: string, data: string) {
    lt cmd = "curl -s -X POST -d '" + data + "' '" + url + "'"
    lt result = sysf(cmd)
    ret result
}

// POST JSON
pub fn PostJSON(url: string, json_data: string) {
    lt cmd = "curl -s -X POST -H 'Content-Type: application/json' -d '" + json_data + "' '" + url + "'"
    lt result = sysf(cmd)
    ret result
}

// POST form data
pub fn PostForm(url: string, form_data: string) {
    lt cmd = "curl -s -X POST -F '" + form_data + "' '" + url + "'"
    lt result = sysf(cmd)
    ret result
}

// POST avec fichier
pub fn PostFile(url: string, file_path: string) {
    lt cmd = "curl -s -X POST -F 'file=@" + file_path + "' '" + url + "'"
    lt result = sysf(cmd)
    ret result
}

// POST avec authentification
pub fn PostAuth(url: string, data: string, username: string, password: string) {
    lt cmd = "curl -s -X POST -u '" + username + ":" + password + "' -d '" + data + "' '" + url + "'"
    lt result = sysf(cmd)
    ret result
}
