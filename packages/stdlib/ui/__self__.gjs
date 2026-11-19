golem ui

pub fn red(text: string): string { ret "\033[31m" + text + "\033[0m" }
pub fn green(text: string): string { ret "\033[32m" + text + "\033[0m" }
pub fn yellow(text: string): string { ret "\033[33m" + text + "\033[0m" }
pub fn blue(text: string): string { ret "\033[34m" + text + "\033[0m" }
pub fn bold(text: string): string { ret "\033[1m" + text + "\033[0m" }

pub fn clear() { print("\033[2J\033[H") }

pub fn progress_bar(percent: int) {
    lt clamped = percent
    if clamped < 0 { clamped = 0 }
    if clamped > 100 { clamped = 100 }
    print("\r[" + clamped + "%] ")
    muts index = 0
    while index < 20 {
        if index < clamped / 5 { print("#") } else { print("-") }
        index = index + 1
    }
    println("")
}

pub fn banner(title: string) {
    println("========================================")
    println("   " + title)
    println("========================================")
}

pub fn menu(title: string, options: string): string {
    clear()
    banner(bold(blue(title)))
    println(yellow("Please select an option:"))
    println(options)
    print("Type a number: ")
    ret gs_read_line()
}
