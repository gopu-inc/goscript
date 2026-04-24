import b64

fn main() {
    println("=== TEST MODULE BASE64 ===")

    lt original = "Goscript est super puissant !"
    
    // 1. Encodage
    lt encoded = b64::encode(original)
    println("Texte original : " + original)
    println("En Base64      : " + encoded)

    // 2. Décodage
    lt decoded = b64::decode(encoded)
    println("Décodé         : " + decoded)

    // Petit test de vérification
    if (original == decoded) {
        println("\nRésultat : SUCCÈS ✅")
    } else {
        println("\nRésultat : ÉCHEC ❌")
    }

    ret 0
}

