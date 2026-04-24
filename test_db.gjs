import db
import ui

fn main() {
    lt database = "users.db"
    ui::banner(ui::bold(ui::blue("NATIVE DATABASE TEST")))

    // 1. Stockage de données
    println("Saving user data...")
    db::set(database, "user_1", "Mauricio")
    db::set(database, "user_2", "Gemini")
    db::set(database, "version", "0.2.6")

    // 2. Récupération
    lt name = db::get(database, "user_1")
    println("User 1: " + ui::green(name))

    // 3. Mise à jour (On change la version)
    db::set(database, "version", "0.3.0")
    lt ver = db::get(database, "version")
    println("Updated Version: " + ui::yellow(ver))

    // 4. Statistiques
    lt total = db::count(database)
    println("Total records: " + total)

    // 5. Recherche d'une clé inexistante
    if (db::exists(database, "admin") == "False") {
        println(ui::red("Admin not found!"))
    }
        // 6. Test Recherche
    println("\nSearching for 'user':")
    lt results = db::search(database, "user")
    println("Found: " + results)

    ret 0
}

