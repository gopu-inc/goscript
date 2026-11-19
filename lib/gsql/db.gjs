golem db

import sqlite

pub fn execute(db_path: string, sql: string): bool {
    ret sqlite::execute(db_path, sql)
}

pub fn query(db_path: string, sql: string): string {
    ret sqlite::query(db_path, sql)
}

pub fn sqlite_version(): string {
    ret sqlite::version()
}
