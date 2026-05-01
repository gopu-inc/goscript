module gcsv

import fs

// Structure pour représenter une ligne parsée
struct Row {
    data: array, // Changé de dict à array
    raw: string
}

// Le parser principal
struct CSVParser {
    separator: string,
    file: string,
    header: string
}

fn new_parser(file: string, sep: string): CSVParser {
    // On récupère la première ligne pour le header
    lt content = sysf("head -n 1 " + file)
    ret new CSVParser {
        separator: sep,
        file: file,
        header: content
    }
}

// Fonction pour récupérer une colonne spécifique
fn get_field(line: string, index: int, sep: string): string {
    lt cmd = "echo '" + line + "' | awk -F'" + sep + "' '{print $" + (index + 1) + "}'"
    ret sysf(cmd)
}

// Compte le nombre de lignes de données
fn count(p: CSVParser): int {
    lt c = sysf("wc -l < " + p.file)
    // On retire 1 pour ne pas compter le header
    ret atoi(c) - 1
}

// Lit une ligne et l'organise
fn read_line(p: CSVParser, line_num: int): Row {
    // +1 pour sauter le header (ligne 1 du fichier)
    lt target = line_num + 1
    lt line_content = sysf("sed -n '" + target + "p' " + p.file)
    
    ret new Row {
        data: new array, // Initialisé en tant que tableau
        raw: line_content
    }
}

