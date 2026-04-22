// test.gjs
println("=== Test de sysf et sh ===")

// sysf capture la sortie
lt files = sysf "ls -la"
println("Fichiers:\n" + files)

// sh retourne le code de sortie
lt code = sh "mkdir -p /tmp/goscript_test"
if code == 0 {
    println("Dossier créé avec succès!")
}

println("=== Test terminé ===")
