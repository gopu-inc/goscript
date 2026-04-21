// ============================================
// DÉMONSTRATION DU MODULE UI
// ============================================

import ui
import ui.notify
import ui.clipboard
import ui.tui

fn main() {
    tui::clear_screen()
    
    println(tui::bold(tui::underline("=== DÉMONSTRATION DU MODULE UI ===\n")))
    
    // Test des boîtes de dialogue
    if !ui::available() {
        println(tui::yellow("⚠️ Mode terminal uniquement (pas d'interface graphique détectée)"))
    }
    
    // Menu principal
    loop {
        tui::clear_screen()
        println(tui::cyan(tui::bold("╔════════════════════════════════════════╗")))
        println(tui::cyan(tui::bold("║     DÉMONSTRATION UI - GOSCRIPT       ║")))
        println(tui::cyan(tui::bold("╚════════════════════════════════════════╝")))
        println("")
        
        lt options = [
            "Message d'information",
            "Message d'avertissement", 
            "Message d'erreur",
            "Demande de confirmation",
            "Saisie de texte",
            "Mot de passe",
            "Sélection de fichier",
            "Sélection de dossier",
            "Liste de choix",
            "Notification système",
            "Copier dans le presse-papiers",
            "Coller depuis le presse-papiers",
            "Boîte de message TUI",
            "Menu TUI",
            "Quitter"
        ]
        
        lt choice = tui::menu("MENU PRINCIPAL", options, 0)
        
        match choice {
            0 => test_info()
            1 => test_warning()
            2 => test_error()
            3 => test_confirm()
            4 => test_input()
            5 => test_password()
            6 => test_open_file()
            7 => test_select_folder()
            8 => test_choose()
            9 => test_notification()
            10 => test_clipboard_copy()
            11 => test_clipboard_paste()
            12 => test_message_box()
            13 => test_tui_menu()
            14 => {
                println(tui::green("\n👋 Au revoir!"))
                break
            }
            _ => {}
        }
        
        println("\n" + tui::dim("Appuyez sur Entrée pour continuer..."))
        sysf("read")
    }
}

fn test_info() {
    tui::clear_screen()
    println(tui::bold("Test: Message d'information\n"))
    ui::info("Ceci est un message d'information.\nTout fonctionne correctement!", "Information")
    println(tui::green("✓ Message affiché"))
}

fn test_warning() {
    tui::clear_screen()
    println(tui::bold("Test: Message d'avertissement\n"))
    ui::warning("Attention! Cette action peut avoir des conséquences.", "Avertissement")
    println(tui::yellow("✓ Avertissement affiché"))
}

fn test_error() {
    tui::clear_screen()
    println(tui::bold("Test: Message d'erreur\n"))
    ui::error("Une erreur critique est survenue!\nLe fichier n'a pas pu être lu.", "Erreur")
    println(tui::red("✓ Erreur affichée"))
}

fn test_confirm() {
    tui::clear_screen()
    println(tui::bold("Test: Demande de confirmation\n"))
    lt result = ui::confirm("Voulez-vous continuer l'opération?", "Confirmation")
    
    if result {
        println(tui::green("✓ Vous avez choisi OUI"))
    } else {
        println(tui::yellow("✓ Vous avez choisi NON"))
    }
}

fn test_input() {
    tui::clear_screen()
    println(tui::bold("Test: Saisie de texte\n"))
    lt name = ui::input("Quel est votre nom?", "Saisie", "John Doe")
    
    if name != "" {
        println(tui::green("✓ Bonjour " + name + "!"))
    } else {
        println(tui::yellow("✓ Saisie annulée"))
    }
}

fn test_password() {
    tui::clear_screen()
    println(tui::bold("Test: Mot de passe\n"))
    lt pass = ui::password("Entrez votre mot de passe", "Authentification")
    
    if pass != "" {
        println(tui::green("✓ Mot de passe saisi (longueur: " + strlen_c(pass) + ")"))
    } else {
        println(tui::yellow("✓ Saisie annulée"))
    }
}

fn test_open_file() {
    tui::clear_screen()
    println(tui::bold("Test: Sélection de fichier\n"))
    lt file = ui::open_file("Choisissez un fichier", "*.gjs | *.txt")
    
    if file != "" {
        println(tui::green("✓ Fichier sélectionné: " + file))
    } else {
        println(tui::yellow("✓ Aucun fichier sélectionné"))
    }
}

fn test_select_folder() {
    tui::clear_screen()
    println(tui::bold("Test: Sélection de dossier\n"))
    lt folder = ui::select_folder("Choisissez un dossier")
    
    if folder != "" {
        println(tui::green("✓ Dossier sélectionné: " + folder))
    } else {
        println(tui::yellow("✓ Aucun dossier sélectionné"))
    }
}

fn test_choose() {
    tui::clear_screen()
    println(tui::bold("Test: Liste de choix\n"))
    lt options = ["Rouge", "Vert", "Bleu", "Jaune", "Magenta", "Cyan"]
    lt color = ui::choose(options, "Choisissez votre couleur préférée", "Couleurs")
    
    if color != "" {
        println(tui::green("✓ Vous avez choisi: " + color))
    } else {
        println(tui::yellow("✓ Aucun choix"))
    }
}

fn test_notification() {
    tui::clear_screen()
    println(tui::bold("Test: Notification système\n"))
    ui.notify::info("Goscript UI", "Ceci est une notification de test!")
    println(tui::green("✓ Notification envoyée"))
}

fn test_clipboard_copy() {
    tui::clear_screen()
    println(tui::bold("Test: Copier dans le presse-papiers\n"))
    lt text = "Texte copié depuis Goscript!"
    lt success = ui.clipboard::copy(text)
    
    if success {
        println(tui::green("✓ Texte copié: '" + text + "'"))
    } else {
        println(tui::yellow("⚠️ Presse-papiers non disponible"))
    }
}

fn test_clipboard_paste() {
    tui::clear_screen()
    println(tui::bold("Test: Coller depuis le presse-papiers\n"))
    lt text = ui.clipboard::paste()
    
    if text != "" {
        println(tui::green("✓ Contenu du presse-papiers: '" + text + "'"))
    } else {
        println(tui::yellow("⚠️ Presse-papiers vide ou non disponible"))
    }
}

fn test_message_box() {
    tui::clear_screen()
    println(tui::bold("Test: Boîte de message TUI\n"))
    
    lt lines = [
        "Bienvenue dans Goscript!",
        "",
        "Ceci est une démonstration",
        "de l'interface utilisateur",
        "en mode terminal."
    ]
    
    tui::message_box("MESSAGE", lines)
}

fn test_tui_menu() {
    tui::clear_screen()
    println(tui::bold("Test: Menu TUI avancé\n"))
    
    lt options = [
        "Option 1 - Créer un projet",
        "Option 2 - Ouvrir un projet",
        "Option 3 - Paramètres",
        "Option 4 - À propos"
    ]
    
    lt choice = tui::menu("CONFIGURATION", options, 0)
    
    println("\n" + tui::green("✓ Option choisie: " + (choice + 1)))
}
