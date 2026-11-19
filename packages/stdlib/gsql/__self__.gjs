golem gsql

import fs

struct Table {
    name: string,
    path: string,
    lines: int
}

fn valid_name(value: string): bool {
    if value == "" { ret false }
    for character in value {
        if !((character >= "a" && character <= "z") ||
             (character >= "A" && character <= "Z") ||
             (character >= "0" && character <= "9") ||
             character == "_" || character == "-") {
            ret false
        }
    }
    ret true
}

pub fn init(): bool {
    ret gs_fs_mkdir(".gsql") == 1
}

pub fn create_table(database: string, table_name: string): Table {
    if valid_name(database) == false || valid_name(table_name) == false { ret nil }
    init()
    lt filepath = ".gsql/" + database + "_" + table_name + ".gdb"
    if fs::exists(filepath) == false { fs::write(filepath, "") }
    ret new Table { name: table_name, path: filepath, lines: 0 }
}

pub fn insert(table: Table, data: string): bool {
    if fs::append(table.path, data + "\n") == false { ret false }
    table.lines = table.lines + 1
    ret true
}

pub fn select_where(table: Table, search: string): string {
    lt rows = fs::read(table.path).split("\n")
    muts result = ""
    for row in rows {
        if row.contains(search) {
            if result != "" { result = result + "\n" }
            result = result + row
        }
    }
    ret result
}
