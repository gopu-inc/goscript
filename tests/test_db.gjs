/*
 * tests/test_db.gjs — Tests du module db.sqlite
 * Mots-clés : lt (var), ret (return), lambda (anonyme)
 */

import db.sqlite

print("=== Tests db.sqlite ===")

// Test 1 : Version SQLite
print("[1] Version SQLite ...")
lt ver = sqlite.version()
print("    Version : " + ver)
if ver != "SQLite non disponible" {
    print("    OK  SQLite disponible : " + ver)
} else {
    print("    WARN SQLite non disponible")
}

// Test 2 : Ouverture base mémoire
print("[2] Ouverture base mémoire ...")
lt db = sqlite.open(":memory:")
if db >= 0 {
    print("    OK  base ouverte (handle=" + str(db) + ")")
} else {
    print("    FAIL ouverture base impossible")
}

// Test 3 : Création de table
print("[3] Création de table ...")
lt rc1 = sqlite.exec(db, "CREATE TABLE IF NOT EXISTS utilisateurs (id INTEGER PRIMARY KEY AUTOINCREMENT, nom TEXT NOT NULL, age INTEGER)")
if rc1 == 0 {
    print("    OK  table créée")
} else {
    print("    FAIL rc=" + str(rc1))
}

// Test 4 : Insertions
print("[4] Insertions ...")
sqlite.exec(db, "INSERT INTO utilisateurs (nom, age) VALUES ('Alice', 30)")
sqlite.exec(db, "INSERT INTO utilisateurs (nom, age) VALUES ('Bob', 25)")
sqlite.exec(db, "INSERT INTO utilisateurs (nom, age) VALUES ('Charlie', 35)")
print("    OK  3 lignes insérées")

// Test 5 : SELECT *
print("[5] SELECT * ...")
lt rows = sqlite.query(db, "SELECT * FROM utilisateurs")
print("    JSON : " + rows)
if rows != "[]" {
    print("    OK  résultats non vides")
} else {
    print("    FAIL résultats vides")
}

// Test 6 : SELECT filtré
print("[6] SELECT WHERE ...")
lt row = sqlite.query(db, "SELECT nom, age FROM utilisateurs WHERE nom = 'Alice'")
print("    Alice : " + row)
if row != "[]" {
    print("    OK  Alice trouvée")
} else {
    print("    FAIL Alice non trouvée")
}

// Test 7 : UPDATE
print("[7] UPDATE ...")
sqlite.exec(db, "UPDATE utilisateurs SET age = 31 WHERE nom = 'Alice'")
lt after = sqlite.query(db, "SELECT age FROM utilisateurs WHERE nom = 'Alice'")
print("    Après UPDATE : " + after)
print("    OK  UPDATE réussi")

// Test 8 : DELETE
print("[8] DELETE ...")
sqlite.exec(db, "DELETE FROM utilisateurs WHERE nom = 'Bob'")
lt count = sqlite.query(db, "SELECT COUNT(*) as total FROM utilisateurs")
print("    Nb restant : " + count)
print("    OK  DELETE réussi")

// Test 9 : with_db helper (lambda comme callback)
print("[9] with_db helper ...")
sqlite.with_db(":memory:", lambda(db2) {
    sqlite.exec(db2, "CREATE TABLE t (v TEXT)")
    sqlite.exec(db2, "INSERT INTO t VALUES ('hello')")
    lt r = sqlite.query(db2, "SELECT * FROM t")
    if r != "[]" {
        print("    OK  with_db fonctionne : " + r)
    } else {
        print("    FAIL with_db vide")
    }
})

// Test 10 : Fermeture
print("[10] Fermeture ...")
lt rc3 = sqlite.close(db)
if rc3 == 0 {
    print("    OK  base fermée")
} else {
    print("    FAIL rc=" + str(rc3))
}

print("=== Fin tests db.sqlite ===")
