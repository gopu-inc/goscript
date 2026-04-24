// lib/sqlite/db.gjs
module sqlite

// Execute non-returning queries
pub fn execute(db_path: string, sql: string) {
    // Utilisation de triples quotes Python pour le SQL
    lt py_code = "import sqlite3; c=sqlite3.connect('" + db_path + "'); c.execute('''" + sql + "'''); c.commit(); c.close()"
    sysf("python3 -c \"" + py_code + "\"")
}

// Query and return JSON
pub fn query(db_path: string, sql: string): string {
    lt py_code = "import sqlite3, json; c=sqlite3.connect('" + db_path + "'); c.row_factory=sqlite3.Row; r=[dict(x) for x in c.execute('''" + sql + "''').fetchall()]; print(json.dumps(r)); c.close()"
    ret sysf("python3 -c \"" + py_code + "\"")
}

