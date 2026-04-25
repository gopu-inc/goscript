import system
import ui
import fs
import time
import db

fn main() {
    // 1. Initialisation du framework
    // Cela va effacer l'écran, afficher la bannière et incrémenter le boot_count
    system::init("MAURICIO-OS V1")

    // 2. Test du système de Logging
    println("\n" + ui::bold("--- Test des Logs ---"))
    system::log("INFO", "Démarrage des tests unitaires...")
    system::log("WARN", "Ceci est un avertissement de test.")
    
    // 3. Test de la persistance (Database + Config)
    println("\n" + ui::bold("--- Test de Configuration ---"))
    
    // On enregistre une info personnalisée
    system::log("INFO", "Sauvegarde du profil utilisateur...")
    sysf("touch system.conf") // Sécurité pour s'assurer que le fichier existe
    
    lt current_boots = system::get_param("boot_count")
    println("Nombre de démarrages enregistrés : " + ui::green(current_boots))

    // 4. Test du File System (via les logs)
    println("\n" + ui::bold("--- Vérification du fichier Log ---"))
    if (fs::exists("activity.log") == "True") {
        lt log_size = fs::size("activity.log")
        println("Fichier activity.log détecté (" + log_size + " octets)")
    } else {
        system::log("ERROR", "Échec critique : activity.log introuvable !")
    }

    // 5. Affichage final des dernières activités
    println("\n" + ui::blue("Dernières entrées du journal :"))
    println("----------------------------------------")
    sysf("tail -n 5 activity.log")
    println("----------------------------------------")

    println("\n" + ui::green("✅ Test terminé avec succès !"))
    
    ret 0
}

