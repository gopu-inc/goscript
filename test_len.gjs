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

// Exemple d'utilisation
fn main() {
    lt ma_chaine = "Goscript"
    lt mon_tableau = [10, 20, 30, 40]
    lt mon_dict = "pourquoi ça ?"
    println("Taille chaîne : " + len(ma_chaine))   // Affiche 8
    println("Taille tableau : " + len(mon_tableau)) // Affiche 4
    println("Taille dictionnaire : " + len(mon_dict)) // Affiche 2
}

