// ============================================
// MODULE CLIPBOARD - Gestion du presse-papiers
// ============================================

module ui.clipboard

// Copier du texte dans le presse-papiers
pub fn copy(text: string): bool {
    lt backend = detect_backend()
    
    match backend {
        "xclip" => {
            lt code = sh("echo '" + escape(text) + "' | xclip -selection clipboard")
            ret code == 0
        }
        "xsel" => {
            lt code = sh("echo '" + escape(text) + "' | xsel --clipboard --input")
            ret code == 0
        }
        "wl-copy" => {
            lt code = sh("echo '" + escape(text) + "' | wl-copy")
            ret code == 0
        }
        "pbcopy" => {
            lt code = sh("echo '" + escape(text) + "' | pbcopy")
            ret code == 0
        }
        "clip.exe" => {
            lt code = sh("echo '" + escape(text) + "' | clip.exe")
            ret code == 0
        }
        _ => {
            println("⚠️ Presse-papiers non disponible")
            ret false
        }
    }
}

// Coller le contenu du presse-papiers
pub fn paste(): string {
    lt backend = detect_backend()
    
    match backend {
        "xclip" => {
            ret trim(sysf("xclip -selection clipboard -o"))
        }
        "xsel" => {
            ret trim(sysf("xsel --clipboard --output"))
        }
        "wl-paste" => {
            ret trim(sysf("wl-paste"))
        }
        "pbpaste" => {
            ret trim(sysf("pbpaste"))
        }
        "powershell" => {
            ret trim(sysf("powershell.exe -Command \"Get-Clipboard\""))
        }
        _ => {
            ret ""
        }
    }
}

fn detect_backend(): string {
    // Linux X11
    if sh("which xclip > /dev/null 2>&1") == 0 {
        ret "xclip"
    }
    if sh("which xsel > /dev/null 2>&1") == 0 {
        ret "xsel"
    }
    // Linux Wayland
    if sh("which wl-copy > /dev/null 2>&1") == 0 {
        ret "wl-copy"
    }
    // macOS
    if sh("which pbcopy > /dev/null 2>&1") == 0 {
        ret "pbcopy"
    }
    // Windows (WSL)
    if sh("which clip.exe > /dev/null 2>&1") == 0 {
        ret "clip.exe"
    }
    if sh("which powershell.exe > /dev/null 2>&1") == 0 {
        ret "powershell"
    }
    ret "none"
}

fn escape(s: string): string {
    muts result = ""
    muts i = 0
    while i < strlen_c(s) {
        lt c = s[i]
        if c == "'" {
            result = result + "'\\''"
        } else {
            result = result + c
        }
        i = i + 1
    }
    ret result
}

fn trim(s: string): string {
    // Simplifié
    ret s
}
