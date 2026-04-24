// lib/crypto.gjs
module crypto

// Hash using sha256sum
pub fn sha256(data: string): string {
    // On utilise printf pour envoyer la string sans \n, puis sha256sum
    lt cmd = "printf '" + data + "' | sha256sum | awk '{print $1}'"
    ret sysf(cmd)
}

// Hash using md5sum
pub fn md5(data: string): string {
    lt cmd = "printf '" + data + "' | md5sum | awk '{print $1}'"
    ret sysf(cmd)
}

