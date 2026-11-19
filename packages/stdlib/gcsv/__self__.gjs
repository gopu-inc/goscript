golem gcsv

import fs

// Structure pour représenter une ligne parsée
struct Row {
    data: array
    raw: string
}

// Le parser principal
struct CSVParser {
    separator: string
    file: string
    header: string
}

pub fn new_parser(file: string, sep: string): CSVParser {
    if sep == "" { sep = "," }
    lt content = fs::read(file)
    lt rows = content.split("\n")
    lt header = ""
    if rows.len() > 0 { header = rows[0] }
    ret new CSVParser {
        separator: sep,
        file: file,
        header: header
    }
}

// Fonction pour récupérer une colonne spécifique
pub fn get_field(line: string, index: int, sep: string): string {
    lt fields = line.split(sep)
    if index < 0 || index >= fields.len() { ret "" }
    ret fields[index]
}

// Compte le nombre de lignes de données
pub fn count(p: CSVParser): int {
    lt content = fs::read(p.file)
    if content == "" { ret 0 }
    lt rows = content.split("\n")
    muts row_count = 0
    for row in rows {
        if row != "" { row_count = row_count + 1 }
    }
    if row_count > 0 { row_count = row_count - 1 }
    ret row_count
}

// Lit une ligne et l'organise
pub fn read_line(p: CSVParser, line_num: int): Row {
    lt rows = fs::read(p.file).split("\n")
    lt target = line_num + 1
    if line_num < 0 || target >= rows.len() {
        ret new Row { data: [], raw: "" }
    }
    lt line_content = rows[target]
    ret new Row {
        data: line_content.split(p.separator),
        raw: line_content
    }
}

