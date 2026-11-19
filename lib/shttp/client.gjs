golem client

pub fn get_timeout(url: string, timeout_seconds: string): string {
    ret gs_http_get_timeout(url, atoi_c(timeout_seconds))
}
pub fn get_with_auth(url: string, user: string, password: string): string {
    ret gs_http_get_auth(url, user, password)
}
pub fn get_with_bearer(url: string, token: string): string {
    ret gs_http_get_headers(url, "Authorization: Bearer " + token)
}
pub fn get_with_cookie(url: string, cookie: string): string {
    ret gs_http_get_headers(url, "Cookie: " + cookie)
}
pub fn save_cookies(url: string, cookie_file: string): string {
    ret gs_http_cookie_request(url, cookie_file, 1)
}
pub fn load_cookies(url: string, cookie_file: string): string {
    ret gs_http_cookie_request(url, cookie_file, 0)
}
pub fn get_with_proxy(url: string, proxy: string): string { ret gs_http_get_proxy(url, proxy) }
pub fn get_follow(url: string): string { ret gs_http_get(url) }
pub fn get_no_follow(url: string): string { ret gs_http_get_no_follow(url) }
pub fn get_verbose(url: string): string { ret gs_http_get(url) }
pub fn session_get(session_file: string, url: string): string {
    ret gs_http_cookie_request(url, session_file, 0)
}
pub fn session_post(session_file: string, url: string, data: string): string {
    ret gs_http_request("POST", url, data)
}
