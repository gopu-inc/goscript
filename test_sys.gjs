// === Test des appels système ===

println("--- 1. Test de 'sh' ---")
// sh exécute la commande et retourne un int (le code de sortie)
lt status = sh("echo 'Ceci est affiché directement par sh !'")
println("Code de retour de sh (devrait être 0) :")
println(status)

println("\n--- 2. Test de 'sysf' ---")
// sysf exécute la commande et capture la sortie dans une string
lt output = sysf("echo 'Ceci a été capturé par sysf !'")
println("Sortie capturée :")
println(output)

println("\n--- 3. Test d'erreur avec 'sh' ---")
// On teste une commande qui n'existe pas pour vérifier le code de retour
lt error_status = sh("commande_imaginaire_qui_plante 2>/dev/null")
println("Code d'erreur de sh (devrait être différent de 0) :")
println(error_status)

