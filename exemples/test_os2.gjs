import os

fn main() {
    println("--- Testing Native OS (Bash) ---")

    // 1. Infos de base
    println("Working Dir: " + os::getcwd())
    println("User: " + os::getenv("USER"))

    // 2. Gestion de dossiers
    lt tmp_dir = "goscript_tmp"
    println("Creating: " + tmp_dir)
    os::mkdir(tmp_dir)

    // 3. Vérification
    if (os::exists(tmp_dir) == "True") {
        println("✅ Folder exists.")
        println("Listing current directory:")
        println(os::list_dir("."))
        
        println("Deleting: " + tmp_dir)
        os::remove(tmp_dir)
        println("✅ Folder deleted.")
    } else {
        println("❌ Failed to create folder.")
    }

    ret 0
}

