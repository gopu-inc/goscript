// lib/io.gjs
module io

// Lire le contenu complet d'un fichier
pub fn read_file(path: string): string {
    lt py_code = "print(open('" + path + "', 'r', encoding='utf-8').read(), end='')"
    ret sysf("python3 -c \"" + py_code + "\"")
}

// Écrire du contenu (écrase le fichier existant)
pub fn write_file(path: string, content: string) {
    // On utilise les triples apostrophes (''') pour englober la variable content
    // Cela permet à Python de gérer les sauts de ligne nativement sans crasher
    lt py_code = "open('" + path + "', 'w', encoding='utf-8').write('''" + content + "''')"
    sysf("python3 -c \"" + py_code + "\"")
}

// Ajouter du contenu (à la fin du fichier)
pub fn append_file(path: string, content: string) {
    lt py_code = "open('" + path + "', 'a', encoding='utf-8').write('''" + content + "''')"
    sysf("python3 -c \"" + py_code + "\"")
}

