/* lib/db.gjs
*/
module db

// Ajouter ou mettre à jour une entrée (Format KEY:VALUE)
pub fn set(file: string, key: string, value: string) {
    // On supprime l'ancienne clé si elle existe, puis on ajoute la nouvelle
    // C'est l'équivalent d'un "UPSERT"
    lt cmd = "touch " + file + "; sed -i '/^" + key + ":/d' " + file + "; echo '" + key + ":" + value + "' >> " + file
    sysf(cmd)
}

// Récupérer une valeur par sa clé
pub fn get(file: string, key: string): string {
    // On cherche la ligne commençant par key:, puis on coupe après le premier ':'
    lt cmd = "grep '^" + key + ":' " + file + " | cut -d':' -f2-"
    ret sysf(cmd)
}

// Vérifier si une clé existe
pub fn exists(file: string, key: string): string {
    ret sysf("grep -q '^" + key + ":' " + file + " && echo 'True' || echo 'False'")
}

// Supprimer une clé
pub fn delete(file: string, key: string) {
    sysf("sed -i '/^" + key + ":/d' " + file)
}

// Compter le nombre d'entrées
pub fn count(file: string): string {
    ret sysf("wc -l < " + file)
}

// Chercher toutes les lignes contenant un motif (pattern)
pub fn search(file: string, pattern: string): string {
    // -i pour ignorer la casse, tr pour mettre sur une seule ligne avec des virgules
    ret sysf("grep -i '" + pattern + "' " + file + " | tr '\\n' ',' | sed 's/,$//'")
}

