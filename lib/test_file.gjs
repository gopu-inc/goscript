// test_gg.gjs - Test du module fs sans f-strings
import fs

println("=== TEST FS SIMPLE ===\n")

lt test_dir = "/tmp/fs_test"
lt test_file = test_dir + "/test.txt"

// mkdir
println("Création: " + test_dir)
fs::mkdir(test_dir)

// write
lt content = "Hello from Goscript!"
println("Écriture: " + test_file)
fs::write(test_file, content)

// exists
println("Exists dir: " + fs::is_dir(test_dir))
println("Exists file: " + fs::is_file(test_file))

// read
lt read_content = fs::read(test_file)
println("Contenu: " + read_content)

// size
lt sz = fs::size(test_file)
println("Taille: " + sz + " octets")

// ls
println("\nContenu du dossier:")
println(fs::ls(test_dir))

// pwd
lt current = fs::pwd()
println("\nPWD: " + current)

// basename/dirname
println("Basename: " + fs::basename(test_file))
println("Dirname: " + fs::dirname(test_file))

// realpath
println("Realpath: " + fs::realpath(test_file))

// touch
fs::touch(test_dir + "/touched.txt")
println("Touché: " + fs::exists(test_dir + "/touched.txt"))

// cp
fs::cp(test_file, test_dir + "/copy.txt")
println("Copié: " + fs::exists(test_dir + "/copy.txt"))

// mv
fs::mv(test_dir + "/copy.txt", test_dir + "/renamed.txt")
println("Renommé: " + fs::exists(test_dir + "/renamed.txt"))

// nettoyage
println("\nNettoyage...")
fs::rm(test_dir)
println("Supprimé: " + (!fs::exists(test_dir)))

println("\n=== TEST OK ===")
