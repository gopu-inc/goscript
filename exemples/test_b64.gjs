import b64

fn main() {
    println("--- Testing Native Base64 (Bash) ---")

    lt original = "Mauricio-Pro 2026"
    
    // 1. Encoding
    lt encoded = b64::encode(original)
    println("Original: " + original)
    println("Encoded : " + encoded)

    // 2. Decoding
    lt decoded = b64::decode(encoded)
    println("Decoded : " + decoded)

    if (original == decoded) {
        println("✅ Verification: Success!")
    } else {
        println("❌ Verification: Failed!")
    }

    ret 0
}

