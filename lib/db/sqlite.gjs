/*
 * lib/db/sqlite.gjs — Interface SQLite pour Goscript
 * Usage : import db.sqlite
 *
 * Exemples :
 *   lt db = sqlite.open("app.db")
 *   sqlite.exec(db, "CREATE TABLE IF NOT EXISTS t (id INTEGER PRIMARY KEY, v TEXT)")
 *   sqlite.exec(db, "INSERT INTO t (v) VALUES ('hello')")
 *   lt rows = sqlite.query(db, "SELECT * FROM t")
 *   print(rows)
 *   sqlite.close(db)
 */

pub fn open(chemin) {
    lt h = gs_db_open(chemin)
    if h < 0 {
        print("[sqlite] Erreur: impossible d'ouvrir " + chemin)
    }
    ret h
}

pub fn close(handle_db) {
    ret gs_db_close(handle_db)
}

pub fn exec(handle_db, sql) {
    ret gs_db_exec(handle_db, sql)
}

pub fn query(handle_db, sql) {
    ret gs_db_query(handle_db, sql)
}

pub fn version() {
    ret gs_db_version()
}

pub fn with_db(chemin, callback) {
    lt db = open(chemin)
    if db < 0 { ret nil }
    callback(db)
    close(db)
}

pub fn create_table(handle_db, nom, colonnes) {
    lt sql = "CREATE TABLE IF NOT EXISTS " + nom + " (" + colonnes + ")"
    ret exec(handle_db, sql)
}
