// ============================================
// MODULE NOTIFY - Notifications système
// ============================================

module ui.notify

// Envoie une notification système
pub fn send(title: string, message: string, urgency: string) {
    lt backend = detect_backend()
    
    match backend {
        "notify-send" => {
            // Linux avec libnotify
            lt cmd = "notify-send"
            if urgency == "low" || urgency == "normal" || urgency == "critical" {
                cmd = cmd + " -u " + urgency
            }
            sh(cmd + " '" + escape(title) + "' '" + escape(message) + "'")
        }
        "zenity" => {
            sh("zenity --notification --text='" + escape(title) + ": " + escape(message) + "'")
        }
        "osascript" => {
            lt script = "display notification \"" + escape(message) + "\" with title \"" + escape(title) + "\""
            sh("osascript -e '" + script + "'")
        }
        "powershell" => {
            lt ps_cmd = "[Windows.UI.Notifications.ToastNotificationManager, Windows.UI.Notifications, ContentType = WindowsRuntime]"
            sh("powershell.exe -Command \"" + ps_cmd + "\"")
        }
        _ => {
            println("🔔 " + title + ": " + message)
        }
    }
}

// Raccourcis
pub fn info(title: string, message: string) {
    send(title, message, "normal")
}

pub fn warn(title: string, message: string) {
    send(title, message, "normal")
}

pub fn error(title: string, message: string) {
    send(title, message, "critical")
}

fn detect_backend(): string {
    if sh("which notify-send > /dev/null 2>&1") == 0 {
        ret "notify-send"
    }
    if sh("which zenity > /dev/null 2>&1") == 0 {
        ret "zenity"
    }
    if sh("uname -s | grep -q Darwin") == 0 {
        ret "osascript"
    }
    ret "terminal"
}

fn escape(s: string): string {
    // Simplifié
    ret s
}
