module gcsv

import fs

// On utilise []string pour typer le tableau proprement
struct Row {
    data: []string, 
    raw: string
}

struct CSVParser {
    separator: string,
    file: string,
    header: string
}

pub fn new_parser(file: string, sep: string): CSVParser {
    lt content = sysf("head -n 1 " + file)
    ret new CSVParser {
        separator: sep,
        file: file,
        header: content
    }
}

pub fn get_field(line: string, index: int, sep: string): string {
    lt cmd = "echo '" + line + "' | awk -F'" + sep + "' '{print $" + (index + 1) + "}'"
    ret sysf(cmd)
}

pub fn count(p: CSVParser): int {
    lt c = sysf("wc -l < " + p.file)
    ret atoi_c(c) - 1
}

pub fn read_line(p: CSVParser, line_num: int): Row {
    lt target = line_num + 1
    lt line_content = sysf("sed -n '" + target + "p' " + p.file)
    
    ret new Row {
        data: [], // Création d'un tableau vide en Goscript
        raw: line_content
    }
}

