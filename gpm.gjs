import gpm
import fs
import ui

module gpm

// Configuration du Zarch Hub
cn API_BASE = "https://gsql-badge.onrender.com"
cn MOD_DIR = "modules"

// Initialisation de l'environnement
pub fn init_env() {
    if fs::exists(MOD_DIR) == "False" {
        sysf("mkdir -p " + MOD_DIR)
    }
}

// Fonction pour tenter une installation sur une architecture précise
fn try_arch(name, version, release, arch) {
    lt url = API_BASE + "/package/download/public/" + name + "/" + version + "/" + release + "/" + arch
    print("  🔍 Essai " + arch + "... ")

    // On utilise curl -f pour détecter l'erreur HTTP via le code de sortie
    lt target = name + ".tar.bool"
    lt cmd = "curl -sL -f " + url + " -o " + target
    lt res = sysf(cmd)

    // Si le fichier existe et n'est pas vide (on vérifie via le shell)
    if fs::exists(target) == "True" {
        println(ui::green("✅ Trouvé !"))
        
        println("  ➜ Extraction...")
        // Extraction propre dans le dossier modules/
        sysf("mkdir -p " + MOD_DIR + "/" + name)
        sysf("tar -xf " + target + " -C " + MOD_DIR + "/" + name)
        
        // Nettoyage
        sysf("rm " + target)
        ret true
    }

    println(ui::red("❌"))
    ret false
}

// Fonction principale d'installation
pub fn install(name, version) {
    if version == "" {
        version = "1.1.0"
    }
    
    ui::banner("GPM GOSCRIPT: " + name)
    println("Installation de la version " + version + "...")

    init_env()

    // On teste les architectures dans l'ordre de probabilité sur ton serveur
    if try_arch(name, version, "r0", "x86_64") == true {
        println(ui::green("🚀 Déployé avec succès dans " + MOD_DIR + "/" + name))
        ret true
    }

    if try_arch(name, version, "r0", "i686") == true {
        println(ui::green("🚀 Déployé avec succès (i686)"))
        ret true
    }

    if try_arch(name, version, "r0", "aarch64") == true {
        println(ui::green("🚀 Déployé avec succès (aarch64)"))
        ret true
    }

    println(ui::red("❌ Erreur: Impossible de trouver un binaire pour " + name))
    ret false
}

// Point d'entrée CLI
fn main() {
    if len(ARGV) < 1 {
        println("Usage: ./gd gpm.gjs install <nom> [version]")
        ret 0
    }

    lt cmd = ARGV[0]
    if cmd == "install" {
        if len(ARGV) < 2 {
            println(ui::red("Erreur: Nom du paquet requis."))
            ret 1
        }
        
        lt pkg = ARGV[1]
        lt ver = ""
        if len(ARGV) > 2 {
            ver = ARGV[2]
        }
        
        install(pkg, ver)
    }
}

