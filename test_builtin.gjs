fn main() {
    println("=== TEST DU MODULE BUILTIN ===")

    // 1. Mathématiques (Constantes et fonctions)
    println("\n-- 1. Mathematiques --")
    print("PI = ")
    println(PI)
    
    lt absolu = abs(-42)
    print("abs(-42) = ")
    println(absolu)

    lt maximum = max(10, 25)
    print("max(10, 25) = ")
    println(maximum)

    // 2. Chaînes de caractères (via strlen_c et strcmp_c)
    println("\n-- 2. Chaines (Strings) --")
    lt chaine = "Goscript"
    lt longueur = len(chaine)
    print("len('Goscript') = ")
    println(longueur)

    lt cmp1 = str_compare("test", "test")
    lt cmp2 = str_compare("test", "fail")
    print("str_compare('test', 'test') = ")
    println(cmp1)
    print("str_compare('test', 'fail') = ")
    println(cmp2)

    // 3. Utilitaires (Temps)
    println("\n-- 3. Temps --")
    print("now() (timestamp Unix) = ")
    println(now())

    // 4. Fichiers (Test de la structure File et de la FFI libc)
    println("\n-- 4. Fichiers (POO + FFI) --")
    
    // On ouvre un fichier en mode écriture ("w")
    lt mon_fichier = File::open("test_output.txt", "w")
    
    if mon_fichier.is_open {
        println("Fichier 'test_output.txt' ouvert avec succes !")
        
        // Appel de la méthode d'instance avec ::
        mon_fichier::write("Bravo ! Ton langage Goscript sait ecrire dans des fichiers nativement via la libc !\n")
        
        println("Ecriture terminee. (Regarde dans ton dossier, le fichier a ete cree !)")
    } else {
        println("Echec de l'ouverture du fichier.")
    }

    println("\n=== FIN DU TEST ===")
    ret 0
}
