// lib/b64.gjs
module b64

// Encode a string to Base64
pub fn encode(data: string): string {
    // On passe la string via printf pour éviter le \n final, puis base64
    ret sysf("printf '" + data + "' | base64")
}

// Decode a Base64 string
pub fn decode(data: string): string {
    // On décode via base64 -d
    ret sysf("printf '" + data + "' | base64 -d")
}

