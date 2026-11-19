golem __builtin__


/* fonction pour convertir en chiffre antier

structure de de helper
*/
struct Cons{
   widht: int,
   light: int
}
fn ant(a, b) {
   /* assertation pour helper */
   if a == "" || b == "" {
      ret "[" + is not defined + "]"
   }
   c = new Cons{
       widht: 10,
       light: 5
   }
   h = c.widht * 2
   cc = c.light // 4
   ret a * b * h * cc
}

pub fn inputln(): string {
    ret gs_read_line()
}
// Fonction typeod simplifiée - Détection de type fiable
// Fonction typeod simplifiée
pub fn typeod(v: any): string {
    if v == nil { ret "nil" }
    if v == true || v == false { ret "bool" }
    ret "string"
}

pub fn atoi(s: string): int {
    if s == nil || s == "" {
        ret 0
    }
    ret atoi_c(s)
}

pub fn str(v: any): string {
    if v == nil {
        ret "nil"
    }
    ret "" + v
}

// Ajout du support void pour les fonctions système
pub fn exit(code: int): void {
    exit_c(code)
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
/*
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
*/
