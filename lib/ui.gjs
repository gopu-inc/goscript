// lib/ui.gjs
module ui

pub fn red(t: string): string { ret "\033[31m" + t + "\033[0m" }
pub fn green(t: string): string { ret "\033[32m" + t + "\033[0m" }
pub fn yellow(t: string): string { ret "\033[33m" + t + "\033[0m" }
pub fn blue(t: string): string { ret "\033[34m" + t + "\033[0m" }
pub fn bold(t: string): string { ret "\033[1m" + t + "\033[0m" }

pub fn clear() { sysf("clear") }

// Progress Bar - L'astuce des pros en AWK
pub fn progress_bar(percent: int) {
    // On passe tout à AWK : il calcule et dessine la ligne d'un coup
    lt cmd = "awk 'BEGIN { " +
             "printf \"\\r[%3d%%] \", " + percent + "; " +
             "for(i=0; i<20; i++) printf (i<" + percent + "/5 ? \"#\" : \"-\"); " +
             "}'"
    sysf(cmd)
}

pub fn banner(title: string) {
    println("========================================")
    println("   " + title)
    println("========================================")
}

// Create an interactive menu
pub fn menu(title: string, options: string): string {
    clear()
    banner(bold(blue(title)))
    
    println(yellow("Please select an option:"))
    
    // On utilise AWK pour transformer la liste "Opt1,Opt2" en menu numéroté
    lt cmd = "echo '" + options + "' | awk -F',' '{for(i=1; i<=NF; i++) printf \"  " + green("%d)") + " %s\\n\", i, $i}'"
    sysf(cmd)
    
    println("\n" + bold("Type a number: "))
    
    // Capture de l'entrée utilisateur via read en Bash
    ret sysf("read choice; echo $choice")
}

