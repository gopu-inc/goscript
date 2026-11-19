golem httplib

import httplib.src.get as getmod
import httplib.src.post as postmod


// Ré-exporter les fonctions GET
pub fn Get(url: string) {
    ret getmod::Get(url)
}

pub fn GetWithHeaders(url: string, headers: string) {
    ret getmod::GetWithHeaders(url, headers)
}

pub fn GetJSON(url: string) {
    ret getmod::GetJSON(url)
}

pub fn GetTimeout(url: string, timeout_seconds: int) {
    ret getmod::GetTimeout(url, timeout_seconds)
}

// Ré-exporter les fonctions POST
pub fn Post(url: string, data: string) {
    ret postmod::Post(url, data)
}

pub fn PostJSON(url: string, json_data: string) {
    ret postmod::PostJSON(url, json_data)
}

pub fn PostForm(url: string, form_data: string) {
    ret postmod::PostForm(url, form_data)
}

pub fn PostFile(url: string, file_path: string) {
    ret postmod::PostFile(url, file_path)
}

pub fn PostAuth(url: string, data: string, username: string, password: string) {
    ret postmod::PostAuth(url, data, username, password)
}
