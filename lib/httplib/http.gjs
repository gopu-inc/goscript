module http

// Importer les sous-modules
import get from "src"
import post from "src"


// Ré-exporter les fonctions GET
pub fn Get(url: string) {
    ret get::Get(url)
}

pub fn GetWithHeaders(url: string, headers: string) {
    ret get::GetWithHeaders(url, headers)
}

pub fn GetJSON(url: string) {
    ret get::GetJSON(url)
}

pub fn GetTimeout(url: string, timeout: int) {
    ret get::GetTimeout(url, timeout)
}

// Ré-exporter les fonctions POST
pub fn Post(url: string, data: string) {
    ret post::Post(url, data)
}

pub fn PostJSON(url: string, json_data: string) {
    ret post::PostJSON(url, json_data)
}

pub fn PostForm(url: string, form_data: string) {
    ret post::PostForm(url, form_data)
}

pub fn PostFile(url: string, file_path: string) {
    ret post::PostFile(url, file_path)
}

pub fn PostAuth(url: string, data: string, username: string, password: string) {
    ret post::PostAuth(url, data, username, password)
}
