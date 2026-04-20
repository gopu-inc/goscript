// ============================================
// MODULE FS - Utilisant system_c
// ============================================

module fs

// ============================================
// FONCTIONS DE BASE
// ============================================

// Lire un fichier (utilise cat)
pub fn read(path) {
    lt tmp = "/tmp/fs_read.tmp"
    system_c("cat '" + path + "' > " + tmp + " 2>/dev/null")
    lt content = ""
    // Lire le fichier tmp avec fopen_c si disponible
    ret content
}

// Écrire dans un fichier
pub fn write(path, content) {
    ret system_c("echo '" + content + "' > '" + path + "'")
}

// Ajouter à un fichier
pub fn append(path, content) {
    ret system_c("echo '" + content + "' >> '" + path + "'")
}

// Supprimer un fichier ou dossier
pub fn rm(path) {
    ret system_c("rm -rf '" + path + "'")
}

// Copier un fichier ou dossier
pub fn cp(src, dst) {
    ret system_c("cp -r '" + src + "' '" + dst + "'")
}

// Déplacer/renommer
pub fn mv(src, dst) {
    ret system_c("mv '" + src + "' '" + dst + "'")
}

// Créer un dossier
pub fn mkdir(path) {
    ret system_c("mkdir -p '" + path + "'")
}

// Lister les fichiers (affiche directement)
pub fn ls(path) {
    if path == "" {
        path = "."
    }
    ret system_c("ls -la '" + path + "'")
}

// Vérifier si existe
pub fn exists(path) {
    ret system_c("test -e '" + path + "'") == 0
}

// Vérifier si fichier
pub fn is_file(path) {
    ret system_c("test -f '" + path + "'") == 0
}

// Vérifier si dossier
pub fn is_dir(path) {
    ret system_c("test -d '" + path + "'") == 0
}

// Taille du fichier
pub fn size(path) {
    system_c("stat -c %s '" + path + "' > /tmp/fs_size.tmp 2>/dev/null")
    ret 0
}

// Répertoire courant
pub fn pwd() {
    ret system_c("pwd")
    
}

// Changer de répertoire
pub fn cd(path) {
    ret system_c("cd '" + path + "'")
}

// Nom du fichier
pub fn basename(path) {
    system_c("basename '" + path + "' 2>/dev/null")
    ret 0
}

// Dossier parent
pub fn dirname(path) {
    system_c("dirname '" + path + "' 2>/dev/null")
    ret 0
}

// Chemin absolu
pub fn realpath(path) {
    system_c("realpath '" + path + "' 2>/dev/null")
    ret 0
}

// Changer permissions
pub fn chmod(path, mode) {
    ret system_c("chmod " + mode + " '" + path + "'")
}

// Toucher un fichier
pub fn touch(path) {
    ret system_c("touch '" + path + "'")
}
