// ============================================
// TEST ANSI - Toutes les façons d'utiliser les couleurs
// ============================================

fn main() {
    println("\n╔══════════════════════════════════════════════════════════════╗")
    println("║                    TEST ANSI COMPLET                          ║")
    println("╚══════════════════════════════════════════════════════════════╝\n")
    
    // ============================================
    // 1. COULEURS DE TEXTE (FOREGROUND)
    // ============================================
    println("\033[1m=== 1. COULEURS DE TEXTE ===\033[0m\n")
    
    println("\033[30mNoir\033[0m")
    println("\033[31mRouge\033[0m")
    println("\033[32mVert\033[0m")
    println("\033[33mJaune\033[0m")
    println("\033[34mBleu\033[0m")
    println("\033[35mMagenta\033[0m")
    println("\033[36mCyan\033[0m")
    println("\033[37mBlanc\033[0m")
    
    // Version avec \\x1b
    println("\n\x1b[90mGris foncé\x1b[0m")
    println("\x1b[91mRouge clair\x1b[0m")
    println("\x1b[92mVert clair\x1b[0m")
    println("\x1b[93mJaune clair\x1b[0m")
    println("\x1b[94mBleu clair\x1b[0m")
    println("\x1b[95mMagenta clair\x1b[0m")
    println("\x1b[96mCyan clair\x1b[0m")
    println("\x1b[97mBlanc brillant\x1b[0m")
    
    // ============================================
    // 2. STYLES DE TEXTE
    // ============================================
    println("\n\033[1m=== 2. STYLES DE TEXTE ===\033[0m\n")
    
    println("\033[1mGras (Bold)\033[0m")
    println("\033[3mItalique\033[0m")
    println("\033[4mSouligné\033[0m")
    println("\033[5mClignotant\033[0m")
    println("\033[7mInversé\033[0m")
    println("\033[9mBarré\033[0m")
    
    // Combinaisons
    println("\n\033[1;31;4mGras + Rouge + Souligné\033[0m")
    println("\033[3;34;7mItalique + Bleu + Inversé\033[0m")
    
    // ============================================
    // 3. COULEURS DE FOND (BACKGROUND)
    // ============================================
    println("\n\033[1m=== 3. COULEURS DE FOND ===\033[0m\n")
    
    println("\033[40m Fond noir \033[0m")
    println("\033[41m Fond rouge \033[0m")
    println("\033[42m Fond vert \033[0m")
    println("\033[43m Fond jaune \033[0m")
    println("\033[44m Fond bleu \033[0m")
    println("\033[45m Fond magenta \033[0m")
    println("\033[46m Fond cyan \033[0m")
    println("\033[47m Fond blanc \033[0m")
    
    // Fonds clairs
    println("\n\033[100m Fond gris foncé \033[0m")
    println("\033[101m Fond rouge clair \033[0m")
    println("\033[102m Fond vert clair \033[0m")
    println("\033[103m Fond jaune clair \033[0m")
    println("\033[104m Fond bleu clair \033[0m")
    println("\033[105m Fond magenta clair \033[0m")
    println("\033[106m Fond cyan clair \033[0m")
    println("\033[107m Fond blanc brillant \033[0m")
    
    // ============================================
    // 4. F-STRINGS AVEC ANSI
    // ============================================
    println("\n\033[1m=== 4. F-STRINGS AVEC ANSI ===\033[0m\n")
    
    lt name = "Goscript"
    lt version = "2.0"
    lt status = "OK"
    
    // F-string avec guillemets doubles
    lt msg1 = f"\033[32m✓ {name} v{version}\033[0m"
    println(msg1)
    
    // F-string avec apostrophes
    lt msg2 = f'\033[34mℹ Statut: {status}\033[0m'
    println(msg2)
    
    // F-string avec expressions
    lt score = 95
    lt color = if score >= 90 { "\033[32m" } else { "\033[33m" }
    println(f"{color}Score: {score}/100\033[0m")
    
    // ============================================
    // 5. BARRE DE PROGRESSION STYLÉE
    // ============================================
    println("\n\033[1m=== 5. BARRE DE PROGRESSION ===\033[0m\n")
    
    muts progress = 0
    while progress <= 100 {
        lt bar_width = 50
        lt filled = progress * bar_width / 100
        lt empty = bar_width - filled
        
        // Choisir la couleur selon la progression
        lt bar_color = "\033[33m"  // Jaune par défaut
        if progress >= 80 {
            bar_color = "\033[32m"  // Vert
        } else if progress >= 50 {
            bar_color = "\033[36m"  // Cyan
        }
        
        print(f"\r{bar_color}[")
        muts i = 0
        while i < filled {
            print("=")
            i = i + 1
        }
        while i < bar_width {
            print(" ")
            i = i + 1
        }
        print(f"] {progress}%\033[0m")
        
        // Force l'affichage immédiat (simule flush)
        sysf("")
        
        progress = progress + 10
        // Pause courte
        muts wait = 0
        while wait < 5000000 {
            wait = wait + 1
        }
    }
    println("\n")
    
    // ============================================
    // 6. TABLEAU COLORÉ
    // ============================================
    println("\033[1m=== 6. TABLEAU COLORÉ ===\033[0m\n")
    
    // En-tête
    println("\033[1;44;37m ID \033[0m \033[1;44;37m Nom           \033[0m \033[1;44;37m Score \033[0m \033[1;44;37m Statut \033[0m")
    
    // Lignes de données
    lt data = [
        [1, "Alice", 95, "OK"],
        [2, "Bob",   67, "WARN"],
        [3, "Charlie", 42, "FAIL"],
        [4, "Diana", 88, "OK"]
    ]
    
    muts row = 0
    while row < 4 {
        lt id = data[row][0]
        lt name = data[row][1]
        lt score_val = data[row][2]
        lt status_val = data[row][3]
        
        // Couleur selon le score
        lt score_color = "\033[32m"
        if score_val < 50 {
            score_color = "\033[31m"
        } else if score_val < 70 {
            score_color = "\033[33m"
        }
        
        // Couleur selon le statut
        lt status_color = "\033[32m"
        if status_val == "FAIL" {
            status_color = "\033[31m"
        } else if status_val == "WARN" {
            status_color = "\033[33m"
        }
        
        println(f" \033[36m{id}\033[0m  {name}           {score_color}{score_val}\033[0m   {status_color}{status_val}\033[0m")
        row = row + 1
    }
    
    // ============================================
    // 7. SPINNER ANIMÉ
    // ============================================
    println("\n\033[1m=== 7. SPINNER ANIMÉ ===\033[0m\n")
    
    lt spinner_frames = ["⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"]
    lt colors = ["\033[31m", "\033[33m", "\033[32m", "\033[36m", "\033[34m", "\033[35m"]
    
    println("Chargement...")
    
    muts frame = 0
    while frame < 20 {
        lt spin_char = spinner_frames[frame % 10]
        lt spin_color = colors[frame % 6]
        
        print(f"\r  {spin_color}{spin_char}\033[0m Traitement en cours... ")
        sysf("")
        
        muts wait = 0
        while wait < 10000000 {
            wait = wait + 1
        }
        
        frame = frame + 1
    }
    println("\r  \033[32m✓\033[0m Terminé!               \n")
    
    // ============================================
    // 8. MESSAGES DE LOG STYLÉS
    // ============================================
    println("\033[1m=== 8. MESSAGES DE LOG ===\033[0m\n")
    
    fn log_info(msg: string) {
        println(f"\033[34mℹ INFO:\033[0m {msg}")
    }
    
    fn log_success(msg: string) {
        println(f"\033[32m✓ SUCCESS:\033[0m {msg}")
    }
    
    fn log_warning(msg: string) {
        println(f"\033[33m⚠ WARNING:\033[0m {msg}")
    }
    
    fn log_error(msg: string) {
        println(f"\033[1;31m✗ ERROR:\033[0m \033[31m{msg}\033[0m")
    }
    
    fn log_debug(msg: string) {
        println(f"\033[35m🐛 DEBUG:\033[0m {msg}")
    }
    
    log_info("Application démarrée")
    log_debug("Variables initialisées")
    log_success("Connexion établie")
    log_warning("Mémoire presque pleine")
    log_error("Fichier introuvable")
    
    // ============================================
    // 9. BOÎTE DE DIALOGUE
    // ============================================
    println("\n\033[1m=== 9. BOÎTE DE DIALOGUE ===\033[0m\n")
    
    fn box(title: string, content: string, border_color: string) {
        lt width = 50
        lt title_len = strlen_c(title)
        lt content_len = strlen_c(content)
        
        // Ligne du haut
        println(f"{border_color}┌{title}")
        muts i = title_len
        while i < width - 2 {
            print("─")
            i = i + 1
        }
        println("┐\033[0m")
        
        // Contenu
        println(f"{border_color}│\033[0m {content}")
        muts j = content_len
        while j < width - 3 {
            print(" ")
            j = j + 1
        }
        println(f"{border_color}│\033[0m")
        
        // Ligne du bas
        print(f"{border_color}└")
        muts k = 0
        while k < width - 2 {
            print("─")
            k = k + 1
        }
        println("┘\033[0m")
    }
    
    box(" ATTENTION ", "Ceci est un message important!", "\033[33m")
    println("")
    box(" SUCCÈS ", "Opération réussie!", "\033[32m")
    println("")
    box(" ERREUR ", "Une erreur est survenue!", "\033[31m")
    
    // ============================================
    // 10. DÉGRADÉ DE COULEURS
    // ============================================
    println("\n\033[1m=== 10. DÉGRADÉ DE COULEURS ===\033[0m\n")
    
    lt gradient_colors = [31, 33, 32, 36, 34, 35]
    lt text = "GOSCRIPT"
    
    muts pos = 0
    while pos < strlen_c(text) {
        lt color_code = gradient_colors[pos % 6]
        lt char = substr(text, pos, 1)
        print(f"\033[1;{color_code}m{char}\033[0m")
        pos = pos + 1
    }
    println("\n")
    
    // ============================================
    // 11. TEST DES SÉQUENCES D'ÉCHAPPEMENT
    // ============================================
    println("\033[1m=== 11. SÉQUENCES D'ÉCHAPPEMENT BRUTES ===\033[0m\n")
    
    // Ces séquences doivent être correctement interprétées
    println("Séquence \\033[31m: \033[31mRouge\033[0m")
    println("Séquence \\x1b[32m: \x1b[32mVert\x1b[0m")
    println("Séquence \\033[1;33m: \033[1;33mGras Jaune\033[0m")
    println("Séquence \\x1b[4;34m: \x1b[4;34mSouligné Bleu\x1b[0m")
    
    // ============================================
    // FIN
    // ============================================
    println("\n╔══════════════════════════════════════════════════════════════╗")
    println("\033[32m║                    TEST ANSI RÉUSSI !                        ║\033[0m")
    println("╚══════════════════════════════════════════════════════════════╝\n")
    
    ret 0
}

// ============================================
// FONCTIONS UTILITAIRES
// ============================================



fn substr(s: string, start: int, length: int): string {
    if s == nil || start < 0 {
        ret ""
    }
    
    muts result = ""
    muts i = start
    muts count = 0
    
    while count < length {
        if s[i] == nil {
            break
        }
        // Ajoute le caractère à la chaîne résultat
        muts char = ""
        char = char + s[i]
        result = result + char
        i = i + 1
        count = count + 1
    }
    
    ret result
}
