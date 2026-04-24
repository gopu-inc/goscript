// lib/fs.gjs
module fs

// Équivalent de fopen/fwrite (Écrase le fichier)
pub fn write(path: string, content: string) {
    sysf("echo '" + content + "' > " + path)
}

// Équivalent de fopen/fwrite (Ajoute à la fin)
pub fn append(path: string, content: string) {
    sysf("echo '" + content + "' >> " + path)
}

// Équivalent de fread (Lit tout le contenu)
pub fn read(path: string): string {
    ret sysf("cat " + path)
}

// Récupérer la taille du fichier (en octets)
pub fn size(path: string): string {
    ret sysf("stat -c %s " + path)
}

// Vérifier si un fichier existe
pub fn exists(path: string): string {
    ret sysf("[ -f " + path + " ] && echo 'True' || echo 'False'")
}

// Supprimer un fichier (unlink)
pub fn remove(path: string) {
    sysf("rm -rf " + path)
}

