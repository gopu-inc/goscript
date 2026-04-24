import sqlite.db
import json

fn main() {
    println("--- Testing SQLite Module ---")
    lt db = "users.db"

    // 1. Create a table
    println("Creating table...")
    sqlite::db::execute(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, role TEXT)")

    // 2. Insert some data
    println("Inserting data...")
    sqlite::db::execute(db, "INSERT INTO users (name, role) VALUES ('Mauricio', 'Admin')")
    sqlite::db::execute(db, "INSERT INTO users (name, role) VALUES ('Gemini', 'AI Assistant')")

    // 3. Query data
    println("Fetching users:")
    lt result = sqlite::db::query(db, "SELECT * FROM users")
    
    // On utilise notre module JSON pour un affichage pro
    println(json::format_json(result))

    ret 0
}

