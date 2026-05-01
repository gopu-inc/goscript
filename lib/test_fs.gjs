// test_fs.gjs - Test du module fs
import fs

println("=== TEST DU MODULE FS ===\n")

// Test pwd
lt current = fs::pwd()
println("Répertoire courant: " + current)

// Test mkdir
lt test_dir = "/tmp/fs_test"
println("\nCréation du dossier: " + test_dir)
fs::mkdir(test_dir)
println("Dossier créé: " + fs::is_dir(test_dir))

// Test cd
println("Changement de répertoire vers: " + test_dir)
fs::cd(test_dir)
println("Nouveau répertoire: " + fs::pwd())

// Test write
lt test_file = "test.txt"
lt content = "Hello from Goscript!"
println("\nÉcriture du fichier: " + test_file)
fs::write(test_file, content)
println("Fichier créé: " + fs::is_file(test_file))

// Test read
lt read_content = fs::read(test_file)
println("Contenu lu: " + read_content)

// Test size
lt file_size = fs::size(test_file)
println("Taille: " + file_size + " octets")

// Test append
fs::append(test_file, "\nDeuxième ligne")
lt appended = fs::read(test_file)
println("Après append: " + appended)

// Test basename/dirname
println("\nBasename: " + fs::basename(test_file))
println("Dirname: " + fs::dirname(test_file))

// Test realpath
lt real = fs::realpath(test_file)
println("Realpath: " + real)

// Test ls
println("\nListe des fichiers:")
println(fs::ls("."))

// Test cp
fs::cp(test_file, "test_copy.txt")
println("\nCopie créée: " + fs::exists("test_copy.txt"))

// Test mv
fs::mv("test_copy.txt", "test_renamed.txt")
println("Renommé: " + fs::exists("test_renamed.txt"))

// Retour au répertoire précédent
fs::cd(current)

// Test rm (nettoyage)
println("\nNettoyage...")
fs::rm(test_dir)
println("Dossier supprimé: " + !fs::exists(test_dir))

println("\n=== TEST TERMINÉ ===")
