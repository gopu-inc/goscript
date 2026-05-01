// lib/net.gjs
module net

// Simple HTTP GET using wget (BusyBox friendly)
pub fn get(url: string): string {
    // -q: quiet, -O -: output to stdout
    ret sysf("wget -qO- '" + url + "'")
}

// Check if a host is alive
pub fn ping(host: string): string {
    // -c 1: one packet, -W 1: 1 second timeout
    ret sysf("ping -c 1 -W 1 " + host + " > /dev/null && echo 'Online' || echo 'Offline'")
}

// Get local IP address
pub fn local_ip(): string {
    ret sysf("hostname -i | awk '{print $1}'")
}

