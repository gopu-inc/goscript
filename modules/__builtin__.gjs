module __builtin__

pub fn inputln(): string {
    // Utilisation de -r pour éviter les problèmes avec les backslashes
    ret sysf("read -r _tmp_var && echo $_tmp_var")
}
// Fonction typeod simplifiée - Détection de type fiable
// Fonction typeod simplifiée
pub fn typeod(v: any): string {
    if v == nil { ret "nil" }
    
    // Test simple via sysf pour éviter les try/catch imbriqués qui font planter le lexer
    lt is_bool = sysf("case '" + v + "' in true|false) echo 1;; *) echo 0;; esac")
    if is_bool == "1" { ret "bool" }

    // Si on peut concaténer avec une chaîne, c'est un type simple (string/int)
    ret "string" 
}

pub fn ints(s: string): int {
    if s == nil || s == "" {
        ret 0
    }
    ret atoi_c(s)
}

pub fn str(v: any): string {
    if v == nil {
        ret "nil"
    }
    // Utilisation de %s pour être plus propre avec printf si dispo, 
    // sinon echo -n est très bien
    ret sysf("echo -n \"" + v + "\"")
}

// Ajout du support void pour les fonctions système
pub fn exit(code: int): void {
    sh("exit " + str(code))
}

// Fonction len universelle pour Goscript
fn len(obj) {
    if obj == nil {
        ret 0
    }

    // Le langage supporte l'itération sur les chaînes, tableaux et dictionnaires
    // On utilise une boucle while avec un compteur pour déterminer la taille
    muts count = 0
    
    // En Goscript, l'accès par index fonctionne pour les chaînes et les tableaux
    // Pour les dictionnaires, l'itération 'for in' est généralement utilisée
    // Mais voici une approche générique par parcours :
    
    try {
        // Tentative de parcours pour les types itérables
        for item in obj {
            count = count + 1
        }
    } catch (e) {
        // Si l'objet n'est pas itérable (ex: int, bool), on retourne 0 ou on gère l'erreur
        ret 0
    }
    
    ret count
}

pub fn trim(s: string): string {
    if s == nil || len(s) == 0 { 
        ret "" 
    }
    
    muts start_found = false
    muts res = ""
    muts trailing_spaces = ""
    
    // On utilise 'for in' pour éviter le bug du NODE(17) (indexation)
    for c in s {
        if !start_found {
            // On saute les espaces au début
            if c == " " || c == "\t" || c == "\n" || c == "\r" {
                continue
            }
            start_found = true
        }
        
        if start_found {
            if c == " " || c == "\t" || c == "\n" || c == "\r" {
                // On stocke les espaces temporairement
                // S'il y a d'autres caractères après, on les ajoutera
                trailing_spaces = trailing_spaces + c
            } else {
                // On ajoute les espaces accumulés précédemment + le caractère actuel
                res = res + trailing_spaces + c
                trailing_spaces = ""
            }
        }
    }
    
    ret res
}
