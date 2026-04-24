// lib/urllib/request.gjs
module request

// Perform an HTTP GET request with a default timeout and User-Agent
pub fn get(url: string): string {
    // On définit un User-Agent "GoScript/0.2.0" pour paraître plus pro auprès des serveurs
    lt py_code = "import urllib.request; " +
                 "req = urllib.request.Request('" + url + "', headers={'User-Agent': 'GoScript/0.2.0 (alpine linux 2.0 / strct)'}); " +
                 "print(urllib.request.urlopen(req, timeout=10).read().decode())"
                 
    ret sysf("python3 -c \"" + py_code + "\"")
}

// Perform an HTTP POST request with JSON data
pub fn post(url: string, json_data: string): string {
    lt py_code = "import urllib.request; " +
                 "req = urllib.request.Request('" + url + "', " +
                 "data='" + json_data + "'.encode(), " +
                 "headers={'Content-Type': 'application/json', 'User-Agent': 'GoScript/0.2.0 (alpine linux 2.0 / strt)'}); " +
                 "print(urllib.request.urlopen(req, timeout=10).read().decode())"
                 
    ret sysf("python3 -c \"" + py_code + "\"")
}

