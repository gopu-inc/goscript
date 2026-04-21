// ============================================
// MODULE UI - Interface Utilisateur pour Goscript
// ============================================
// Fournit une couche d'abstraction unifiée pour:
// - Boîtes de dialogue (info, erreur, input, fichier)
// - Notifications système
// - Presse-papiers
// - Terminal UI amélioré
// ============================================

module ui

// ============================================
// CONSTANTES D'ICÔNES
// ============================================
pub cn ICON_INFO = "info"
pub cn ICON_WARNING = "warning"
pub cn ICON_ERROR = "error"
pub cn ICON_QUESTION = "question"
pub cn ICON_PASSWORD = "password"

// ============================================
// DÉTECTION DU BACKEND GRAPHIQUE DISPONIBLE
// ============================================

pub fn available(): bool {
    // Vérifier si on est dans un environnement graphique
    if sh("test -n \"$DISPLAY\"") == 0 || 
       sh("test -n \"$WAYLAND_DISPLAY\"") == 0 {
        ret true
    }
    
    // macOS
    if sh("uname -s | grep -q Darwin") == 0 {
        ret true
    }
    
    // Windows (WSL ou natif)
    if sh("uname -r | grep -qi microsoft") == 0 {
        ret true
    }
    
    ret false
}

// Détecte quel outil est disponible
fn detect_backend(): string {
    // Linux: Zenity (GTK)
    if sh("which zenity > /dev/null 2>&1") == 0 {
        ret "zenity"
    }
    
    // Linux: KDialog (KDE)
    if sh("which kdialog > /dev/null 2>&1") == 0 {
        ret "kdialog"
    }
    
    // Linux: Yad (fork amélioré de Zenity)
    if sh("which yad > /dev/null 2>&1") == 0 {
        ret "yad"
    }
    
    // macOS: osascript (AppleScript)
    if sh("uname -s | grep -q Darwin") == 0 {
        if sh("which osascript > /dev/null 2>&1") == 0 {
            ret "osascript"
        }
    }
    
    // Windows via WSL: powershell.exe
    if sh("which powershell.exe > /dev/null 2>&1") == 0 {
        ret "powershell"
    }
    
    // Fallback: terminal (pas d'UI graphique)
    ret "terminal"
}

// ============================================
// BOÎTES DE DIALOGUE
// ============================================

// Affiche un message d'information
pub fn info(message: string, title: string) {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            sh("zenity --info --text='" + escape(message) + "' --title='" + escape(title) + "'")
        }
        "kdialog" => {
            sh("kdialog --msgbox '" + escape(message) + "' --title '" + escape(title) + "'")
        }
        "yad" => {
            sh("yad --info --text='" + escape(message) + "' --title='" + escape(title) + "'")
        }
        "osascript" => {
            lt script = "display dialog \"" + escape(message) + "\" with title \"" + escape(title) + "\" buttons {\"OK\"} default button \"OK\" with icon note"
            sh("osascript -e '" + script + "'")
        }
        "powershell" => {
            lt ps_cmd = "[System.Windows.Forms.MessageBox]::Show('" + escape(message) + "','" + escape(title) + "')"
            sh("powershell.exe -Command \"Add-Type -AssemblyName System.Windows.Forms; " + ps_cmd + "\"")
        }
        _ => {
            // Fallback terminal
            println("[" + title + "] " + message)
        }
    }
}

// Affiche un message d'avertissement
pub fn warning(message: string, title: string) {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            sh("zenity --warning --text='" + escape(message) + "' --title='" + escape(title) + "'")
        }
        "kdialog" => {
            sh("kdialog --sorry '" + escape(message) + "' --title '" + escape(title) + "'")
        }
        "yad" => {
            sh("yad --warning --text='" + escape(message) + "' --title='" + escape(title) + "'")
        }
        "osascript" => {
            lt script = "display dialog \"" + escape(message) + "\" with title \"" + escape(title) + "\" buttons {\"OK\"} default button \"OK\" with icon caution"
            sh("osascript -e '" + script + "'")
        }
        _ => {
            println("⚠️ [" + title + "] " + message)
        }
    }
}

// Affiche un message d'erreur
pub fn error(message: string, title: string) {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            sh("zenity --error --text='" + escape(message) + "' --title='" + escape(title) + "'")
        }
        "kdialog" => {
            sh("kdialog --error '" + escape(message) + "' --title '" + escape(title) + "'")
        }
        "yad" => {
            sh("yad --error --text='" + escape(message) + "' --title='" + escape(title) + "'")
        }
        "osascript" => {
            lt script = "display dialog \"" + escape(message) + "\" with title \"" + escape(title) + "\" buttons {\"OK\"} default button \"OK\" with icon stop"
            sh("osascript -e '" + script + "'")
        }
        _ => {
            println("❌ [" + title + "] " + message)
        }
    }
}

// Demande une confirmation (Oui/Non)
pub fn confirm(message: string, title: string): bool {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            lt code = sh("zenity --question --text='" + escape(message) + "' --title='" + escape(title) + "'")
            ret code == 0
        }
        "kdialog" => {
            lt code = sh("kdialog --yesno '" + escape(message) + "' --title '" + escape(title) + "'")
            ret code == 0
        }
        "yad" => {
            lt code = sh("yad --question --text='" + escape(message) + "' --title='" + escape(title) + "'")
            ret code == 0
        }
        "osascript" => {
            lt script = "display dialog \"" + escape(message) + "\" with title \"" + escape(title) + "\" buttons {\"Non\", \"Oui\"} default button \"Oui\""
            lt result = sysf("osascript -e '" + script + "'")
            ret contains(result, "Oui")
        }
        _ => {
            print(message + " (o/N): ")
            lt response = input()
            ret response == "o" || response == "O" || response == "oui" || response == "Oui" || response == "yes" || response == "Yes"
        }
    }
}

// Demande une saisie de texte
pub fn input(prompt: string, title: string, default: string): string {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            lt cmd = "zenity --entry --text='" + escape(prompt) + "' --title='" + escape(title) + "'"
            if default != "" {
                cmd = cmd + " --entry-text='" + escape(default) + "'"
            }
            ret trim(sysf(cmd))
        }
        "kdialog" => {
            lt cmd = "kdialog --inputbox '" + escape(prompt) + "' '" + escape(default) + "' --title '" + escape(title) + "'"
            ret trim(sysf(cmd))
        }
        "yad" => {
            lt cmd = "yad --entry --text='" + escape(prompt) + "' --title='" + escape(title) + "'"
            if default != "" {
                cmd = cmd + " --entry-text='" + escape(default) + "'"
            }
            ret trim(sysf(cmd))
        }
        "osascript" => {
            lt script = "display dialog \"" + escape(prompt) + "\" with title \"" + escape(title) + "\" default answer \"" + escape(default) + "\""
            lt result = sysf("osascript -e '" + script + "'")
            // Extraire le texte retourné
            if contains(result, "text returned:") {
                lt parts = split(result, "text returned:")
                ret trim(parts[1])
            }
            ret default
        }
        _ => {
            print(prompt)
            if default != "" {
                print(" [" + default + "]")
            }
            print(": ")
            lt response = inputln()
            if response == "" && default != "" {
                ret default
            }
            ret response
        }
    }
}

// Demande un mot de passe (masqué)
pub fn password(prompt: string, title: string): string {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            ret trim(sysf("zenity --password --text='" + escape(prompt) + "' --title='" + escape(title) + "'"))
        }
        "kdialog" => {
            ret trim(sysf("kdialog --password '" + escape(prompt) + "' --title '" + escape(title) + "'"))
        }
        "yad" => {
            ret trim(sysf("yad --password --text='" + escape(prompt) + "' --title='" + escape(title) + "'"))
        }
        "osascript" => {
            lt script = "display dialog \"" + escape(prompt) + "\" with title \"" + escape(title) + "\" default answer \"\" with hidden answer"
            lt result = sysf("osascript -e '" + script + "'")
            if contains(result, "text returned:") {
                lt parts = split(result, "text returned:")
                ret trim(parts[1])
            }
            ret ""
        }
        _ => {
            // Utiliser stty pour masquer la saisie
            sh("stty -echo")
            print(prompt + ": ")
            lt pass = inputln()
            sh("stty echo")
            println("")
            ret pass
        }
    }
}

// Sélection de fichier (ouverture)
pub fn open_file(title: string, filter: string): string {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            lt cmd = "zenity --file-selection --title='" + escape(title) + "'"
            if filter != "" {
                cmd = cmd + " --file-filter='" + escape(filter) + "'"
            }
            ret trim(sysf(cmd))
        }
        "kdialog" => {
            lt cmd = "kdialog --getopenfilename . '" + escape(filter) + "' --title '" + escape(title) + "'"
            ret trim(sysf(cmd))
        }
        "yad" => {
            lt cmd = "yad --file --title='" + escape(title) + "'"
            ret trim(sysf(cmd))
        }
        "osascript" => {
            lt script = "choose file with prompt \"" + escape(title) + "\""
            lt result = sysf("osascript -e 'POSIX path of (" + script + ")'")
            ret trim(result)
        }
        _ => {
            print("Chemin du fichier: ")
            ret inputln()
        }
    }
}

// Sélection de fichier (sauvegarde)
pub fn save_file(title: string, default_name: string): string {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            lt cmd = "zenity --file-selection --save --title='" + escape(title) + "'"
            if default_name != "" {
                cmd = cmd + " --filename='" + escape(default_name) + "'"
            }
            ret trim(sysf(cmd))
        }
        "kdialog" => {
            lt cmd = "kdialog --getsavefilename '" + escape(default_name) + "' --title '" + escape(title) + "'"
            ret trim(sysf(cmd))
        }
        "yad" => {
            lt cmd = "yad --file --save --title='" + escape(title) + "'"
            if default_name != "" {
                cmd = cmd + " --filename='" + escape(default_name) + "'"
            }
            ret trim(sysf(cmd))
        }
        "osascript" => {
            lt script = "choose file name with prompt \"" + escape(title) + "\" default name \"" + escape(default_name) + "\""
            lt result = sysf("osascript -e 'POSIX path of (" + script + ")'")
            ret trim(result)
        }
        _ => {
            print("Sauvegarder sous [" + default_name + "]: ")
            lt response = inputln()
            if response == "" {
                ret default_name
            }
            ret response
        }
    }
}

// Sélection de dossier
pub fn select_folder(title: string): string {
    lt backend = detect_backend()
    
    match backend {
        "zenity" => {
            ret trim(sysf("zenity --file-selection --directory --title='" + escape(title) + "'"))
        }
        "kdialog" => {
            ret trim(sysf("kdialog --getexistingdirectory . --title '" + escape(title) + "'"))
        }
        "yad" => {
            ret trim(sysf("yad --file --directory --title='" + escape(title) + "'"))
        }
        "osascript" => {
            lt script = "choose folder with prompt \"" + escape(title) + "\""
            lt result = sysf("osascript -e 'POSIX path of (" + script + ")'")
            ret trim(result)
        }
        _ => {
            print("Chemin du dossier: ")
            ret inputln()
        }
    }
}

// Liste de choix (dropdown)
pub fn choose(options: []string, prompt: string, title: string): string {
    lt backend = detect_backend()
    
    // Créer une chaîne avec les options séparées par des newlines
    muts options_str = ""
    muts i = 0
    while i < len(options) {
        options_str = options_str + options[i] + "\n"
        i = i + 1
    }
    
    match backend {
        "zenity" => {
            lt cmd = "echo '" + options_str + "' | zenity --list --column='Options' --text='" + escape(prompt) + "' --title='" + escape(title) + "'"
            ret trim(sysf(cmd))
        }
        "kdialog" => {
            // KDialog utilise un format différent
            muts kdialog_opts = ""
            muts j = 0
            while j < len(options) {
                kdialog_opts = kdialog_opts + " '" + options[j] + "' '" + options[j] + "'"
                j = j + 1
            }
            ret trim(sysf("kdialog --menu '" + escape(prompt) + "'" + kdialog_opts + " --title '" + escape(title) + "'"))
        }
        "yad" => {
            lt cmd = "echo '" + options_str + "' | yad --list --column='Options' --text='" + escape(prompt) + "' --title='" + escape(title) + "'"
            ret trim(sysf(cmd))
        }
        "osascript" => {
            muts apple_opts = "{"
            muts k = 0
            while k < len(options) {
                if k > 0 {
                    apple_opts = apple_opts + ", "
                }
                apple_opts = apple_opts + "\"" + options[k] + "\""
                k = k + 1
            }
            apple_opts = apple_opts + "}"
            
            lt script = "choose from list " + apple_opts + " with prompt \"" + escape(prompt) + "\" with title \"" + escape(title) + "\""
            ret trim(sysf("osascript -e '" + script + "'"))
        }
        _ => {
            println(prompt)
            muts idx = 0
            while idx < len(options) {
                println("  " + (idx + 1) + ". " + options[idx])
                idx = idx + 1
            }
            print("Choix (1-" + len(options) + "): ")
            lt choice = to_int(inputln())
            if choice >= 1 && choice <= len(options) {
                ret options[choice - 1]
            }
            ret ""
        }
    }
}

// Barre de progression
pub fn progress(current: int, total: int, message: string) {
    lt backend = detect_backend()
    lt percent = (current * 100) / total
    
    match backend {
        "zenity" => {
            // Utiliser un fichier temporaire pour communiquer avec zenity --progress
            if current == 0 {
                lt cmd = "zenity --progress --text='" + escape(message) + "' --percentage=0 --auto-close &"
                sh(cmd)
            }
            // Pour simplifier, on affiche juste en console
            print("\r[" + message + "] " + percent + "%")
        }
        _ => {
            // Affichage console avec barre de progression
            muts bar = "["
            muts i = 0
            while i < 50 {
                if i < percent / 2 {
                    bar = bar + "="
                } else if i == percent / 2 {
                    bar = bar + ">"
                } else {
                    bar = bar + " "
                }
                i = i + 1
            }
            bar = bar + "] " + percent + "%"
            print("\r" + bar)
        }
    }
    
    if current == total {
        println("")
    }
}

// ============================================
// FONCTIONS UTILITAIRES
// ============================================

// Échappe les caractères spéciaux pour le shell
fn escape(s: string): string {
    if s == nil {
        ret ""
    }
    
    muts result = ""
    muts i = 0
    while i < strlen_c(s) {
        lt c = s[i]
        if c == "'" {
            result = result + "'\\''"
        } else if c == "\"" {
            result = result + "\\\""
        } else if c == "\\" {
            result = result + "\\\\"
        } else if c == "$" {
            result = result + "\\$"
        } else if c == "`" {
            result = result + "\\`"
        } else {
            result = result + c
        }
        i = i + 1
    }
    ret result
}

// Vérifie si une chaîne contient une sous-chaîne
fn contains(s: string, sub: string): bool {
    if s == nil || sub == nil {
        ret false
    }
    ret strstr_c(s, sub) != nil
}

// Supprime les espaces en début et fin
fn trim(s: string): string {
    if s == nil {
        ret ""
    }
    
    muts start = 0
    muts end = strlen_c(s) - 1
    
    while start <= end {
        lt c = s[start]
        if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
            start = start + 1
        } else {
            break
        }
    }
    
    while end >= start {
        lt c = s[end]
        if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
            end = end - 1
        } else {
            break
        }
    }
    
    if start > end {
        ret ""
    }
    
    muts result = ""
    muts i = start
    while i <= end {
        result = result + s[i]
        i = i + 1
    }
    ret result
}

// Convertit une chaîne en entier
fn to_int(s: string): int {
    if s == nil || s == "" {
        ret 0
    }
    ret atoi_c(s)
}

// Longueur d'une chaîne
fn len(arr: []string): int {
    muts count = 0
    muts i = 0
    loop {
        if i >= 100 { break }
        // Note: c'est une approximation, à améliorer
        count = count + 1
        i = i + 1
    }
    ret count
}

// Lit une ligne depuis stdin
fn inputln(): string {
    // Utiliser read pour lire depuis stdin
    muts buffer = ""
    muts c = ""
    loop {
        lt char = sysf("dd bs=1 count=1 2>/dev/null")
        if char == "\n" || char == "" {
            break
        }
        buffer = buffer + char
    }
    ret buffer
}

fn input(): string {
    ret inputln()
}

fn split(s: string, delim: string): []string {
    // Simplifié - retourne un tableau de strings
    muts result = []
    muts current = ""
    muts i = 0
    
    while i < strlen_c(s) {
        muts found = false
        if s[i] == delim[0] {
            muts j = 0
            muts match = true
            while j < strlen_c(delim) {
                if s[i + j] != delim[j] {
                    match = false
                    break
                }
                j = j + 1
            }
            if match {
                result = push_str(result, current)
                current = ""
                i = i + strlen_c(delim)
                found = true
            }
        }
        if !found {
            current = current + s[i]
            i = i + 1
        }
    }
    result = push_str(result, current)
    ret result
}

fn push_str(arr: []string, val: string): []string {
    // Simplifié
    ret arr
}
