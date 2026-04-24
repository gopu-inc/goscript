import system
import ui
import os

fn main() {
    // 1. Initialisation complète via notre nouveau module
    system::init("MAURICIO OS")

    // 2. Récupération d'infos
    lt user = os::getenv("USER")
    lt boots = system::get_param("boot_count")

    system::log("INFO", "Current User: " + user)
    system::log("INFO", "System has booted " + boots + " times.")

    // 3. Simulation d'une erreur
    if (user == "root") {
        system::log("WARN", "Running as root is dangerous!")
    } else {
        system::log("ERROR", "Access denied for user: " + user)
    }

    println("\n" + ui::bold("--- Activity Log (Last 3 lines) ---"))
    sysf("tail -n 3 activity.log")

    ret 0
}

