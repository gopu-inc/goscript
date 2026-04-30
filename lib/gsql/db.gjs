// Définition de la structure pour la connexion
struct Database {
    path: string,
    is_open: bool,
    timeout: int
}

// Fonction pour "ouvrir" une connexion
fn open(path: string, timeout: int) {
    lt db = new Database {
        path: path,
        is_open: true,
        timeout: timeout
    }
    ret db
}

// Fonction pour exécuter une requête SQL via l'appel système sysf
fn query(db: Database, sql: string) {
    if db.is_open == false {
        ret "Error: Database is closed"
    }

    // On utilise sysf pour appeler un moteur SQL externe (ex: sqlite3)
    [span_2](start_span)[span_3](start_span)// conformément à l'usage de ton langage[span_2](end_span)[span_3](end_span)
    lt command = "sqlite3 " + db.path + " \"" + sql + "\""
    lt result = sysf(command)
    
    ret result
}

// Fonction pour fermer la connexion
fn close(db: Database) {
    db.is_open = false
    ret true
}

