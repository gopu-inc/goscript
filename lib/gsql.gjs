module gsql

import fs
import json
import crypto // Optionnel pour le chiffrement
import ui


// Représente une table dans la base de données
struct Table {
    name: string,
    path: string,
    lines: int
}

fn Ginit() {
    println(ui::green("--- [GSQL]: ok susseful ok ---"))
    ret sysf("mkdir /var/lib/gsql/ 2&>/dev/null") 
}
    
// Crée une nouvelle table (un fichier .gdb)
fn create_table(db_name: string, table_name: string): Table {
    lt filepath = "/var/lib/gsql/" + db_name + "_" + table_name + ".gdb"
    
    // On initialise le fichier vide (ex: un tableau JSON vide "[]" ou juste un header)
    fs::write(filepath, "") 
    
    ret new Table {
        name: table_name,
        path: filepath,
        lines: 0
    }
}

// Insère des données dans la table
fn insert(tb: Table, data: string): string {
    // Dans une version avancée, on utiliserait structd ou json
    // Ici on ajoute simplement une nouvelle ligne au fichier
    sysf("echo '" + data + "' >> " + tb.path)
    
    ret "Success: 1 row inserted"
}

// Fait une recherche simple (comme un SELECT * WHERE)
fn select_where(tb: Table, search: string): string {
    // On réutilise la logique de ton parser !
    lt result = sysf("grep '" + search + "' " + tb.path)
    ret result
}

