import sys

println("Hostname: " + sys::hostname())
println("PWD: " + sys::pwd())

if sys::exists("/etc/passwd") == true {
    lt content = sys::cat("/etc/passwd")
    println("Fichier trouvé, taille: " + strlen_c(content))
}

sys::mkdir("/tmp/test_goscript")
sys::write("/tmp/test_goscript/test.txt", "Hello from Goscript!")
lt files = sys::ls("/tmp/test_goscript")
println("Fichiers créés:\n" + files)
