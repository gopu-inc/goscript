// test_fs.gjs - Test du module fs avec f-strings
import fs

println(f"=== TEST FS AVEC F-STRINGS ===\n")

lt test_dir = "/tmp/fs_test"
lt test_file = f"{test_dir}/test.txt"

// mkdir
println(f"Création: {test_dir}")
fs::mkdir(test_dir)

// write
lt content = "Hello from Goscript!"
println(f"Écriture: {test_file}")
fs::write(test_file, content)

// exists
println(f"Exists dir: {fs::is_dir(test_dir)}")
println(f"Exists file: {fs::is_file(test_file)}")

// read
lt read_content = fs::read(test_file)
println(f"Contenu: {read_content}")

// size
lt sz = fs::size(test_file)
println(f"Taille: {sz} octets")

// ls
println(f"\nContenu du dossier:")
println(fs::ls(test_dir))

// head/tail
fs::write_lines(test_file, ["ligne1", "ligne2", "ligne3", "ligne4", "ligne5"])
println(f"\nHead 3: {fs::head(test_file, 3)}")
println(f"Lines: {fs::count_lines(test_file)}")

// file info
println(f"\nType: {fs::file_type(test_file)}")
println(f"Owner: {fs::owner(test_file)}")
println(f"Perms: {fs::perms(test_file)}")

// pwd
lt current = fs::pwd()
println(f"\nPWD: {current}")

// temp file
lt tmp = fs::mktemp("gs")
println(f"Temp file: {tmp}")
fs::write(tmp, "temp content")
fs::rm(tmp)

// nettoyage
println(f"\nNettoyage...")
fs::rm(test_dir)
println(f"Supprimé: {!fs::exists(test_dir)}")

println(f"\n=== TEST OK ===")
