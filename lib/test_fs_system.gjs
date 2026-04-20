// test_fs_system.gjs - Test du module fs avec system_c
import fs

println("=== TEST FS AVEC SYSTEM_C ===\n")

lt test_dir = "/tmp/fs_system_test"
lt test_file = test_dir + "/test.txt"

// mkdir
println("1. Création dossier: " + test_dir)
lt r1 = fs::mkdir(test_dir)
println("   mkdir retour: " + r1)

// exists
println("2. Exists dossier: " + fs::exists(test_dir))

// is_dir
println("3. Is dir: " + fs::is_dir(test_dir))

// write
println("\n4. Écriture fichier: " + test_file)
lt r2 = fs::write(test_file, "Hello from system_c")
println("   write retour: " + r2)

// is_file
println("5. Is file: " + fs::is_file(test_file))

// exists file
println("6. Exists fichier: " + fs::exists(test_file))

// ls
println("\n7. Liste du dossier:")
lt r3 = fs::ls(test_dir)
println("   ls retour: " + r3)

// pwd
println("\n8. PWD:")
lt r4 = fs::pwd()
println("   pwd retour: " + r4)

// touch
println("\n9. Touch:")
lt test_file2 = test_dir + "/touched.txt"
fs::touch(test_file2)
println("   Touched exists: " + fs::exists(test_file2))

// cp
println("\n10. Copie:")
fs::cp(test_file, test_dir + "/copy.txt")
println("    Copie exists: " + fs::exists(test_dir + "/copy.txt"))

// mv
println("\n11. Déplacement:")
fs::mv(test_dir + "/copy.txt", test_dir + "/renamed.txt")
println("    Renamed exists: " + fs::exists(test_dir + "/renamed.txt"))
println("    Copy exists: " + fs::exists(test_dir + "/copy.txt"))

// rm
println("\n12. Nettoyage:")
fs::rm(test_dir)
println("    Dossier supprimé: " + (!fs::exists(test_dir)))

println("\n=== TEST TERMINÉ ===")
