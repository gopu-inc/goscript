golem upload
pub fn file(url: string, file_path: string): string { ret gs_http_post_file(url, file_path) }
pub fn file_with_name(url: string, file_path: string, field_name: string): string {
    ret gs_http_post_form(url, field_name + "=@" + file_path)
}
