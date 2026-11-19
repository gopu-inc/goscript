golem http
pub fn get(url: string): string { ret gs_http_get(url) }
pub fn post(url: string, data: string): string { ret gs_http_request("POST", url, data) }
pub fn put(url: string, data: string): string { ret gs_http_request("PUT", url, data) }
pub fn delete(url: string): string { ret gs_http_request("DELETE", url, "") }
