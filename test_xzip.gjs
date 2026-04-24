import xzip

fn main() {
    println("=== TEST MODULE XZIP (GZIP + B64) ===")

    lt text = "Goscript est une technologie de 2026. " + 
              "La compression permet de réduire la taille des échanges réseau."
    
    println("Texte original (taille: " + text::len() + " octets)")

    // 1. Compression
    lt compressed = xzip::compress(text)
    println("Compresse (B64) : " + compressed)
    println("Nouvelle taille : " + compressed::len() + " octets")

    // 2. Décompression
    lt decompressed = xzip::decompress(compressed)
    println("\nRésultat décompressé :")
    println(decompressed)

    if (text == decompressed) {
        println("\nStatut : SUCCÈS ✅")
    } else {
        println("\nStatut : ÉREUR ❌")
    }

    ret 0
}

