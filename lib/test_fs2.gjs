// test_fs.gjs - Test ultra simple
import fs

println("=== TEST FS SIMPLE ===\n")

lt test_dir = "/tmp/fs_test_simple"

// Test mkdir
println("Création dossier: " + test_dir)
lt r1 = fs::mkdir(test_dir)
println("  mkdir: " + r1)

// Test exists
lt r2 = fs::exists(test_dir)
println("  exists: " + r2)

// Test is_dir
lt r3 = fs::is_dir(test_dir)
println("  is_dir: " + r3)

// Test write
lt test_file = test_dir + "/test.txt"
println("\nÉcriture fichier: " + test_file)
lt r4 = fs::write(test_file, "Hello")
println("  write: " + r4)

// Test is_file
lt r5 = fs::is_file(test_file)
println("  is_file: " + r5)

// Test read
lt content = fs::read(test_file)
println("  read: " + content)

// Test ls
println("\nListe fichiers:")
lt files = fs::ls(test_dir)
println(files)

// Test rm
println("Nettoyage...")
lt r6 = fs::rm(test_dir)
println("  rm: " + r6)

println("\n=== TEST TERMINÉ ===")
