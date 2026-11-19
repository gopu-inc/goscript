golem request
pub fn get(url: string): string { ret gs_http_get(url) }
pub fn post(url: string, json_data: string): string { ret gs_http_post(url, json_data) }
