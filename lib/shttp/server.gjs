module server

pub fn simple(port: string): string {
    lt cmd = "sh -c \"while true; do echo -e 'HTTP/1.1 200 OK\\r\\n\\r\\nHello' | nc -l -p " + port + " -q 1; done\""
    lt result = await cmd
    ret result
}

pub fn static(port: string, dir: string): string {
    lt cmd = "sh -c \"cd " + dir + " && python3 -m http.server " + port + "\""
    lt result = await cmd
    ret result
}

pub fn php(port: string, dir: string): string {
    lt cmd = f"cd {dir} php -S 0.0.0.0:  {port}"
    lt result = sysf(cmd)
    ret result
}

pub fn busybox(port: string, dir: string): string {
    lt cmd = "sh -c \"busybox httpd -f -p " + port + " -h " + dir + "\""
    lt result = await cmd
    ret "ok"
}
