golem get
pub fn Get(url: string): string { ret gs_http_get(url) }
pub fn GetWithHeaders(url: string, headers: string): string { ret gs_http_get(url) }
pub fn GetJSON(url: string): string { ret gs_http_get(url) }
pub fn GetTimeout(url: string, timeout_seconds: int): string { ret gs_http_get(url) }
