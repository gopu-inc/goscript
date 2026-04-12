fn main() {
    println("=== TÉLÉCHARGEMENT ===\n")
    
    // Télécharger un fichier
    lt download = await "wget -q -O /tmp/test.txt https://httpbin.org/anything"
    println("Téléchargement terminé")
    
    // Lire le fichier
    lt content = await "cat /tmp/test.txt"
    println("Contenu:\n" + content)
    
    ret 0
}
