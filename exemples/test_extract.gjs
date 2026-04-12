fn main() {
    println("=== EXTRACTION D'ARCHIVE ===\n")
    
    // Créer une archive de test
    await "mkdir -p /tmp/test_files"
    await "echo 'Hello' > /tmp/test_files/file1.txt"
    await "echo 'World' > /tmp/test_files/file2.txt"
    await "tar czf /tmp/archive.tar.gz -C /tmp test_files/"
    
    // Extraire
    println("Extraction...")
    lt extract = await "tar xzf /tmp/archive.tar.gz -C /tmp/extract/"
    
    // Vérifier
    lt list = await "ls -la /tmp/extract/test_files/"
    println("Fichiers extraits:\n" + list)
    
    ret 0
}
