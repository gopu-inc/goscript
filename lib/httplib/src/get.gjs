module get

pub fn Get(url: string) {
    lt cmd = "curl -s '" + url + "'"
    lt result = sysf(cmd)
    ret result
}

// GET avec headers
pub fn GetWithHeaders(url: string, headers: string) {
    lt cmd = "curl -s -H '" + headers + "' '" + url + "'"
    lt result = sysf(cmd)
    ret result
}

// GET et pretty-print JSON
pub fn GetJSON(url: string) {
    lt cmd = "curl -s '" + url + "' | jq"
    lt result = sysf(cmd)
    ret result
}

// GET avec timeout
/*
pub fn GetTimeout(url: string, timeout: int) {
    lt cmd = "curl -s --max-time " + timeout + " '" + url + "'"
    lt result = sysf(cmd)
    ret result
}
*/
