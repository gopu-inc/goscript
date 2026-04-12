module client

// ============================================
// Client avec timeout
// ============================================

pub fn get_timeout(url: string, timeout_sec: string): string {
    lt cmd = "sh -c \"curl -s --max-time " + timeout_sec + " " + url + "\""
    lt result = await cmd
    ret result
}

// ============================================
// Client avec authentification
// ============================================

pub fn get_with_auth(url: string, user: string, pass: string): string {
    lt cmd = "sh -c \"curl -s -u " + user + ":" + pass + " " + url + "\""
    lt result = await cmd
    ret result
}

pub fn get_with_bearer(url: string, token: string): string {
    lt cmd = "sh -c \"curl -s -H 'Authorization: Bearer " + token + "' " + url + "\""
    lt result = await cmd
    ret result
}

// ============================================
// Client avec cookies
// ============================================

pub fn get_with_cookie(url: string, cookie: string): string {
    lt cmd = "sh -c \"curl -s -H 'Cookie: " + cookie + "' " + url + "\""
    lt result = await cmd
    ret result
}

pub fn save_cookies(url: string, cookie_file: string): string {
    lt cmd = "sh -c \"curl -s -c " + cookie_file + " " + url + "\""
    lt result = await cmd
    ret "ok"
}

pub fn load_cookies(url: string, cookie_file: string): string {
    lt cmd = "sh -c \"curl -s -b " + cookie_file + " " + url + "\""
    lt result = await cmd
    ret result
}

// ============================================
// Client avec proxy
// ============================================

pub fn get_with_proxy(url: string, proxy: string): string {
    lt cmd = "sh -c \"curl -s -x " + proxy + " " + url + "\""
    lt result = await cmd
    ret result
}

// ============================================
// Client avec redirection
// ============================================

pub fn get_follow(url: string): string {
    lt cmd = "sh -c \"curl -s -L " + url + "\""
    lt result = await cmd
    ret result
}

pub fn get_no_follow(url: string): string {
    lt cmd = "sh -c \"curl -s " + url + "\""
    lt result = await cmd
    ret result
}

// ============================================
// Client verbose (debug)
// ============================================

pub fn get_verbose(url: string): string {
    lt cmd = "sh -c \"curl -v " + url + " 2>&1\""
    lt result = await cmd
    ret result
}

// ============================================
// Session (cookies automatiques)
// ============================================

pub fn session_get(session_file: string, url: string): string {
    lt cmd = "sh -c \"curl -s -b " + session_file + " -c " + session_file + " " + url + "\""
    lt result = await cmd
    ret result
}

pub fn session_post(session_file: string, url: string, data: string): string {
    lt cmd = "sh -c \"curl -s -b " + session_file + " -c " + session_file + " -X POST -d '" + data + "' " + url + "\""
    lt result = await cmd
    ret result
}
