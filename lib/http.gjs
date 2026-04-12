module http

pub fn Get(url: string) {
    lt cmd = f"curl -s '{url}'"
    lt result = await cmd
    ret result
}

pub fn Post(url: string, data: string) {
    lt cmd = f"curl -s -X POST -d '{data}' '{url}'"
    lt result = await cmd
    ret result
}

pub fn GetWithTimeout(url: string, sec: int) {
    lt cmd = f"curl -s --max-time {sec} '{url}'"
    lt result = await cmd
    ret result
}
