// test_sysf.gjs - Test de sysf et sh comme expressions

println("=== Test de sysf et sh ===")

// sysf capture la sortie et retourne une string
lt files = sysf("ls -la")
println("Fichiers:\n" + files)

// sh retourne le code de sortie (int)
lt code = sh("mkdir -p /tmp/goscript_test")
if code == 0 {
    println("Dossier créé avec succès!")
} else {
    println("Erreur lors de la création du dossier")
}

// sysf sans parenthèses
lt date = sysf "date '+%Y-%m-%d %H:%M:%S'"
println("Date: " + date)

// Vérifier si un fichier existe avec sh
if sh("test -f /etc/passwd") == 0 {
    println("/etc/passwd existe!")
}

// Compter les fichiers
lt count = sysf("ls -1 | wc -l")
println("Nombre de fichiers: " + count)

// Récupérer le hostname
lt hostname = sysf("hostname")
println("Hostname: " + hostname)

// Utiliser dans une condition directement
if sh("which git > /dev/null 2>&1") == 0 {
    lt git_version = sysf("git --version")
    println("Git installé: " + git_version)
} else {
    println("Git n'est pas installé")
}

// Concaténer des commandes
lt user = sysf("whoami")
lt pwd = sysf("pwd")
println("Utilisateur: " + user + " dans " + pwd)

println("=== Test terminé ===")
