import fs
import ui
import system

module gpm

lt API_BASE = "https://gsql-badge.onrender.com"
lt MOD_DIR = "modules"

pub fn init_env() {
    if (fs::exists(MOD_DIR) == "False") {
        sysf("mkdir -p " + MOD_DIR)
    }
}

fn download_and_extract(url, name) {
    lt target = name + ".tar.bool"
    
    // On télécharge
    sysf("curl -sL " + url + " -o " + target)
    
    // On vérifie l'existence via fs au lieu de sysf stat pour éviter les "0" à l'écran
    if (fs::exists(target) == "True") {
        println(ui::cyan("➜ Archive reçue. Installation..."))
        
        // Extraction directe dans MOD_DIR (car l'archive contient déjà le dossier 'httplib')
        sysf("tar -xf " + target + " -C " + MOD_DIR)
        
        sysf("rm " + target)
        ret true
    }
    ret false
}

pub fn install(name, version, release, is_public) {
    ui::banner("GPM DEPLOY: " + name)
    
    lt mode = "private"
    if (is_public == true) { mode = "public" }
    
    lt v = version
    if (v == "") { v = "1.1.0" }
    lt r = release
    if (r == "") { r = "r0" }

    // On commence par x86_64 qui est le binaire valide sur ton serveur
    lt arch = "x86_64"
    lt url = API_BASE + "/package/download/" + mode + "/" + name + "/" + v + "/" + r + "/" + arch
    
    println(ui::yellow("🔍 Connexion au dépôt Zarch Hub..."))
    
    // On tente l'installation sans trop de vérifications sysf pour éviter les messages parasites
    if (download_and_extract(url, name) == true) {
        println(ui::green("✅ " + name + " installé avec succès !"))
        ret true
    }

    println(ui::red("❌ Erreur : Impossible de récupérer " + name))
    ret false
}

