import gcsv
import ui

fn main() {
    println(ui::green("--- GCSV Framework Test ---"))

    // 1. Initialisation du parser sur un fichier existant
    lt parser = gcsv::new_parser("/var/lib/gsql/master_users.gdb", ",")
    
    // 2. Affichage des infos
    println("Fichier: " + parser.file)
    println("Colonnes detectées: " + parser.header)
    
    // 3. Extraction de données
    lt nb = gcsv::count(parser)
    println("Nombre d'entrées: " + nb)

    // 4. Lecture de la première ligne de données (index 2 dans le fichier)
    lt row1 = gcsv::read_line(parser, 2)
    
    // On extrait le nom (colonne index 1)
    lt nom = gcsv::get_field(row1.raw, 1, ",")
    println("Nom extrait de la ligne 2: " + nom)
}

