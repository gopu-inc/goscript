import crypto

fn main() {
    println("--- Testing Native Crypto (Bash) ---")

    lt secret = "mauricio_pro_2026"
    
    // Test SHA256
    lt h256 = crypto::sha256(secret)
    println("SHA256: " + h256)

    // Test MD5
    lt hmd5 = crypto::md5(secret)
    println("MD5   : " + hmd5)

    ret 0
}

