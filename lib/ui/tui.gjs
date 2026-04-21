// ============================================
// MODULE TUI - Interface utilisateur terminal
// ============================================

module ui.tui

// ============================================
// COULEURS
// ============================================

pub cn RESET = "\033[0m"
pub cn BOLD = "\033[1m"
pub cn DIM = "\033[2m"
pub cn ITALIC = "\033[3m"
pub cn UNDERLINE = "\033[4m"
pub cn BLINK = "\033[5m"
pub cn REVERSE = "\033[7m"
pub cn HIDDEN = "\033[8m"
pub cn STRIKE = "\033[9m"

// Couleurs de texte
pub cn BLACK = "\033[30m"
pub cn RED = "\033[31m"
pub cn GREEN = "\033[32m"
pub cn YELLOW = "\033[33m"
pub cn BLUE = "\033[34m"
pub cn MAGENTA = "\033[35m"
pub cn CYAN = "\033[36m"
pub cn WHITE = "\033[37m"

// Couleurs vives
pub cn BRIGHT_BLACK = "\033[90m"
pub cn BRIGHT_RED = "\033[91m"
pub cn BRIGHT_GREEN = "\033[92m"
pub cn BRIGHT_YELLOW = "\033[93m"
pub cn BRIGHT_BLUE = "\033[94m"
pub cn BRIGHT_MAGENTA = "\033[95m"
pub cn BRIGHT_CYAN = "\033[96m"
pub cn BRIGHT_WHITE = "\033[97m"

// Couleurs de fond
pub cn BG_BLACK = "\033[40m"
pub cn BG_RED = "\033[41m"
pub cn BG_GREEN = "\033[42m"
pub cn BG_YELLOW = "\033[43m"
pub cn BG_BLUE = "\033[44m"
pub cn BG_MAGENTA = "\033[45m"
pub cn BG_CYAN = "\033[46m"
pub cn BG_WHITE = "\033[47m"

// ============================================
// FONCTIONS DE COULEUR
// ============================================

pub fn red(text: string): string {
    ret RED + text + RESET
}

pub fn green(text: string): string {
    ret GREEN + text + RESET
}

pub fn blue(text: string): string {
    ret BLUE + text + RESET
}

pub fn yellow(text: string): string {
    ret YELLOW + text + RESET
}

pub fn cyan(text: string): string {
    ret CYAN + text + RESET
}

pub fn magenta(text: string): string {
    ret MAGENTA + text + RESET
}

pub fn bold(text: string): string {
    ret BOLD + text + RESET
}

pub fn underline(text: string): string {
    ret UNDERLINE + text + RESET
}

// ============================================
// BOÎTES ET CADRES
// ============================================

pub fn box_top(width: int, title: string): string {
    muts result = "┌"
    muts i = 0
    while i < width - 2 {
        result = result + "─"
        i = i + 1
    }
    result = result + "┐"
    if title != "" {
        result = result + " " + title
    }
    ret result
}

pub fn box_bottom(width: int): string {
    muts result = "└"
    muts i = 0
    while i < width - 2 {
        result = result + "─"
        i = i + 1
    }
    result = result + "┘"
    ret result
}

pub fn box_line(text: string, width: int): string {
    lt content = "│ " + text
    muts padding = width - strlen_c(text) - 4
    muts i = 0
    while i < padding {
        content = content + " "
        i = i + 1
    }
    content = content + " │"
    ret content
}

pub fn box_separator(width: int): string {
    muts result = "├"
    muts i = 0
    while i < width - 2 {
        result = result + "─"
        i = i + 1
    }
    result = result + "┤"
    ret result
}

// Affiche un message dans une boîte
pub fn message_box(title: string, lines: []string) {
    lt max_width = strlen_c(title) + 4
    
    // Trouver la largeur maximale
    muts i = 0
    while i < len(lines) {
        lt line_len = strlen_c(lines[i])
        if line_len > max_width {
            max_width = line_len
        }
        i = i + 1
    }
    
    max_width = max_width + 6
    
    println(box_top(max_width, title))
    
    muts j = 0
    while j < len(lines) {
        println(box_line(lines[j], max_width))
        j = j + 1
    }
    
    println(box_bottom(max_width))
}

// ============================================
// MENUS
// ============================================

pub fn menu(title: string, options: []string, default: int): int {
    println("")
    println(bold(underline(title)))
    println("")
    
    muts i = 0
    while i < len(options) {
        if i == default {
            print(green("  > "))
        } else {
            print("    ")
        }
        println("[" + (i + 1) + "] " + options[i])
        i = i + 1
    }
    
    println("")
    print("Choix [" + (default + 1) + "]: ")
    
    lt input = inputln()
    if input == "" {
        ret default
    }
    
    lt choice = atoi_c(input) - 1
    if choice >= 0 && choice < len(options) {
        ret choice
    }
    
    ret default
}

// ============================================
// SPINNER (Indicateur de chargement)
// ============================================

pub fn spinner_start(message: string) {
    print(message + " ")
}

pub fn spinner_stop(message: string) {
    println("✓ " + message)
}

pub fn spinner_fail(message: string) {
    println("✗ " + message)
}

// ============================================
// TABLEAUX
// ============================================

pub fn table(headers: []string, rows: []string) {
    // Affiche un tableau formaté
    muts col_widths = []
    muts i = 0
    
    // Calculer les largeurs de colonnes
    while i < len(headers) {
        col_widths = push_int(col_widths, strlen_c(headers[i]))
        i = i + 1
    }
    
    // TODO: Calculer les largeurs max des données
    
    // Afficher l'en-tête
    print("┌")
    muts j = 0
    while j < len(headers) {
        muts k = 0
        while k < col_widths[j] + 2 {
            print("─")
            k = k + 1
        }
        if j < len(headers) - 1 {
            print("┬")
        }
        j = j + 1
    }
    println("┐")
    
    // Afficher les titres
    print("│")
    muts h = 0
    while h < len(headers) {
        print(" " + bold(headers[h]) +
