golem sqlite

pub fn execute(db_path: string, sql: string): bool {
    lt database = gs_db_open(db_path)
    if database < 0 { ret false }
    lt status = gs_db_exec(database, sql)
    gs_db_close(database)
    ret status == 0
}

pub fn query(db_path: string, sql: string): string {
    lt database = gs_db_open(db_path)
    if database < 0 { ret "" }
    lt rows = gs_db_query(database, sql)
    gs_db_close(database)
    ret rows
}

pub fn version(): string { ret gs_db_version() }
