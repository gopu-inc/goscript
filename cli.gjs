import gpm
import ui

fn main() {
    // Initialisation de l'environnement (création de /modules, etc.)
    gpm::init_env()

    // Vérification des arguments
    if (len(ARGV) == 0) {
        ui::banner("GOSCRIPT PACKAGE MANAGER v5.2")
        println(ui::bold("Système détecté : ") + gpm::get_os_type() + " (" + gpm::get_arch() + ")")
        println("")
        println(ui::bold("Usage :"))
        println("  ./gd cli.gjs login <user> <pass>   " + ui::yellow("- Connexion au Zarch Hub"))
        println("  ./gd cli.gjs list                  " + ui::yellow("- Lister les paquets disponibles"))
        println("  ./gd cli.gjs install <nom> [ver]   " + ui::yellow("- Installer un paquet public"))
        println("  ./gd cli.gjs get-private <nom>     " + ui::yellow("- Installer un paquet privé (Token requis)"))
        println("")
        ret 0
    }

    lt cmd = ARGV[0]

    // --- COMMANDE : LOGIN ---
    if (cmd == "login") {
        if (len(ARGV) < 3) {
            println(ui::red("Erreur : Utilisation -> gpm login <utilisateur> <mot_de_passe>"))
            ret 1
        }
        gpm::login(ARGV[1], ARGV[2])
        ret 0
    }

    // --- COMMANDE : LIST ---
    if (cmd == "list") {
        gpm::list_packages()
        ret 0
    }

    // --- COMMANDE : INSTALL (PUBLIC) ---
    if (cmd == "install") {
        if (len(ARGV) < 2) {
            println(ui::red("Erreur : Précise au moins le nom du paquet."))
            ret 1
        }

        lt pkg_name = ARGV[1]
        lt pkg_ver = "1.1.0" // Version par défaut
        
        if (len(ARGV) >= 3) {
            pkg_ver = ARGV[2]
        }

        // Appel de la fonction install(nom, version, release, is_public)
        gpm::install(pkg_name, pkg_ver, "r0", true)
        ret 0
    }

    // --- COMMANDE : GET-PRIVATE ---
    if (cmd == "get-private") {
        if (len(ARGV) < 2) {
            println(ui::red("Erreur : Nom du paquet privé requis."))
            ret 1
        }

        lt pkg_name = ARGV[1]
        // On force is_public à false
        gpm::install(pkg_name, "1.0.0", "r0", false)
        ret 0
    }

    // --- COMMANDE INCONNUE ---
    println(ui::red("Commande '" + cmd + "' inconnue."))
    println("Utilise ./gd cli.gjs sans argument pour voir l'aide.")
}

