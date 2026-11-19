golem download
pub fn file(url: string, output: string): bool { ret gs_http_download(url, output, "") == 1 }
pub fn file_silent(url: string, output: string): bool { ret gs_http_download(url, output, "") == 1 }
pub fn file_with_progress(url: string, output: string): bool { ret gs_http_download(url, output, "") == 1 }
pub fn resume(url: string, output: string): bool { ret gs_http_download(url, output, "") == 1 }
pub fn multiple(urls: string, output_dir: string): bool { ret false }
