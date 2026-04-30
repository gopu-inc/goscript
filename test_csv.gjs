import gcsv

fn main() {
    println("--- GCSV Framework Test ---")

    // On initialise sur ton fichier master_users
    lt parser = gcsv::new_parser("/var/lib/gsql/master_users.gdb", ",")
    
    println("Fichier: " + parser.file)
    println("Header: " + parser.header)
    
    lt total = gcsv::count(parser)
    println("Total lignes: " + total)

    // On lit la ligne 2 du fichier (première donnée après header)
    lt row = gcsv::read_line(parser, 2)
    
    // On récupère le champ "nom" (colonne 2, donc index 1)
    lt nom = gcsv::get_field(row.raw, 1, ",")
    println("Nom extrait: " + nom)
}

