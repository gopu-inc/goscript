module config

struct Parser {
    Info: string,
    parse: string,
    ligne: int,
    returne: string
}

fn parser_conf(file: string, search: string): Parser {
    // Vérification des arguments (utilisation de || pour le OR logique)
    if file == "" || search == "" {
        ret new Parser {
            Info: "error",
            parse: "0",
            ligne: 0,
            returne: "Error: Missing file or search term"
        }
    }

    // Exécution de la recherche dynamique
    lt cmd = "grep '" + search + "' " + file + " | cut -d'=' -f2"
    lt result = sysf(cmd)
    
    // On récupère toujours le nombre total de lignes pour la structure
    lt nb_lignes = atoi_c(sysf("wc -l < " + file))
    
    ret new Parser {
        Info: "Config: " + file,
        parse: result,
        ligne: nb_lignes,
        returne: "Success"
    }
}

