golem post
pub fn Post(url: string, data: string): string { ret gs_http_post(url, data) }
pub fn PostJSON(url: string, json_data: string): string { ret gs_http_post(url, json_data) }
pub fn PostForm(url: string, form_data: string): string { ret gs_http_post(url, form_data) }
pub fn PostFile(url: string, file_path: string): string { ret gs_http_post(url, file_path) }
pub fn PostAuth(url: string, data: string, username: string, password: string): string {
    ret gs_http_post(url, data)
}
