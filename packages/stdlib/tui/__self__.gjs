golem tui

lt ESC = "\033"

fn repeat_chars(text: string, count: int): string {
    muts result = ""
    muts index = 0
    while (index < count) {
        result = result + text
        index = index + 1
    }
    ret result
}

pub fn reset(): string { ret ESC + "[0m" }
pub fn bold(text: string): string { ret ESC + "[1m" + text + reset() }
pub fn dim(text: string): string { ret ESC + "[2m" + text + reset() }
pub fn italic(text: string): string { ret ESC + "[3m" + text + reset() }
pub fn underline(text: string): string { ret ESC + "[4m" + text + reset() }
pub fn inverse(text: string): string { ret ESC + "[7m" + text + reset() }
pub fn red(text: string): string { ret ESC + "[31m" + text + reset() }
pub fn green(text: string): string { ret ESC + "[32m" + text + reset() }
pub fn yellow(text: string): string { ret ESC + "[33m" + text + reset() }
pub fn blue(text: string): string { ret ESC + "[34m" + text + reset() }
pub fn magenta(text: string): string { ret ESC + "[35m" + text + reset() }
pub fn cyan(text: string): string { ret ESC + "[36m" + text + reset() }
pub fn rgb(red: int, green: int, blue: int, text: string): string {
    ret gpm_tui_rgb(red, green, blue, text)
}
pub fn background(red: int, green: int, blue: int, text: string): string {
    ret gpm_tui_bg_rgb(red, green, blue, text)
}

pub fn clear() { print(ESC + "[2J" + ESC + "[H") }
pub fn home() { print(ESC + "[H") }
pub fn hide_cursor() { print(ESC + "[?25l") }
pub fn show_cursor() { print(ESC + "[?25h") }
pub fn width(): int { ret gpm_tui_width() }

pub fn repeat(text: string, count: int): string {
    ret repeat_chars(text, count)
}

pub fn truncate(text: string, size: int): string {
    ret gpm_tui_truncate(text, size)
}

pub fn rule(title: string): string {
    lt columns = gpm_tui_width()
    if (columns < 10) { columns = 80 }
    lt text = ""
    if (title != "") { text = " " + title + " " }
    lt side = columns - strlen_c(text)
    if (side < 2) { side = 2 }
    lt left = side / 2
    lt right = side - left
    ret ESC + "[2m" + repeat_chars("─", left) + ESC + "[0m" + ESC + "[1m" + text + ESC + "[0m" + ESC + "[2m" + repeat_chars("─", right) + ESC + "[0m"
}

pub fn heading(title: string, subtitle: string): string {
    lt result = bold(cyan(title))
    if (subtitle != "") { result = result + "\n" + dim(subtitle) }
    ret rule("") + "\n" + result + "\n" + rule("")
}

pub fn panel(title: string, text: string): string {
    lt columns = gpm_tui_width()
    if (columns > 88) { columns = 88 }
    if (columns < 24) { columns = 24 }
    lt inner = columns - 4
    lt top = "╭─ " + ESC + "[1m" + title + ESC + "[0m " + repeat_chars("─", columns - strlen_c(title) - 5) + "╮"
    lt output = top
    lt lines = text.split("\n")
    lt i = 0
    while (i < lines.len()) {
        lt line = gpm_tui_truncate(lines[i], inner)
        lt used = strlen_c(line)
        lt padding = inner - used
        if (padding < 0) { padding = 0 }
        output = output + "\n│ " + line + repeat_chars(" ", padding) + " │"
        i = i + 1
    }
    output = output + "\n╰" + repeat_chars("─", columns - 2) + "╯"
    ret output
}

pub fn table(headers: string, rows: string): string {
    lt columns = headers.split("|")
    lt count = columns.len()
    if (count == 0) { ret "" }
    muts width0 = strlen_c(columns[0].trim())
    muts width1 = 0
    muts width2 = 0
    if (count > 1) { width1 = strlen_c(columns[1].trim()) }
    if (count > 2) { width2 = strlen_c(columns[2].trim()) }
    lt records = rows.split("\n")
    muts i = 0
    while (i < records.len()) {
        lt cells = records[i].split("|")
        if (cells.len() > 0) {
            lt c0 = cells[0].trim()
            lt s0 = strlen_c(c0)
            if (s0 > width0) { width0 = s0 }
        }
        if (count > 1 && cells.len() > 1) {
            lt c1 = cells[1].trim()
            lt s1 = strlen_c(c1)
            if (s1 > width1) { width1 = s1 }
        }
        if (count > 2 && cells.len() > 2) {
            lt c2 = cells[2].trim()
            lt s2 = strlen_c(c2)
            if (s2 > width2) { width2 = s2 }
        }
        i = i + 1
    }
    muts output = "┌" + repeat_chars("─", width0 + 2)
    if (count > 1) { output = output + "┬" + repeat_chars("─", width1 + 2) }
    if (count > 2) { output = output + "┬" + repeat_chars("─", width2 + 2) }
    output = output + "┐"
    output = output + "\n│"
    lt title0 = columns[0].trim()
    output = output + " " + ESC + "[1m" + title0 + ESC + "[0m" + repeat_chars(" ", width0 - strlen_c(title0)) + " "
    if (count > 1) {
        lt title1 = columns[1].trim()
        output = output + "│ " + ESC + "[1m" + title1 + ESC + "[0m" + repeat_chars(" ", width1 - strlen_c(title1)) + " "
    }
    if (count > 2) {
        lt title2 = columns[2].trim()
        output = output + "│ " + ESC + "[1m" + title2 + ESC + "[0m" + repeat_chars(" ", width2 - strlen_c(title2)) + " "
    }
    output = output + "│"
    output = output + "\n├"
    output = output + repeat_chars("─", width0 + 2)
    if (count > 1) { output = output + "┼" + repeat_chars("─", width1 + 2) }
    if (count > 2) { output = output + "┼" + repeat_chars("─", width2 + 2) }
    output = output + "┤"
    i = 0
    while (i < records.len()) {
        lt cells = records[i].split("|")
        output = output + "\n│"
        lt cell0 = ""
        if (cells.len() > 0) { cell0 = cells[0].trim() }
        output = output + " " + cell0 + repeat_chars(" ", width0 - strlen_c(cell0)) + " "
        if (count > 1) {
            lt cell1 = ""
            if (cells.len() > 1) { cell1 = cells[1].trim() }
            output = output + "│ " + cell1 + repeat_chars(" ", width1 - strlen_c(cell1)) + " "
        }
        if (count > 2) {
            lt cell2 = ""
            if (cells.len() > 2) { cell2 = cells[2].trim() }
            output = output + "│ " + cell2 + repeat_chars(" ", width2 - strlen_c(cell2)) + " "
        }
        output = output + "│"
        i = i + 1
    }
    output = output + "\n└"
    output = output + repeat_chars("─", width0 + 2)
    if (count > 1) { output = output + "┴" + repeat_chars("─", width1 + 2) }
    if (count > 2) { output = output + "┴" + repeat_chars("─", width2 + 2) }
    output = output + "┘"
    ret output
}

pub fn progress(percent: int, label: string): string {
    lt value = percent
    if (value < 0) { value = 0 }
    if (value > 100) { value = 100 }
    lt columns = gpm_tui_width()
    if (columns > 64) { columns = 64 }
    lt prefix = ""
    if (label != "") { prefix = label + " " }
    lt bar_width = columns - strlen_c(prefix) - 8
    if (bar_width < 10) { bar_width = 10 }
    lt filled = bar_width * value / 100
    lt result = prefix + ESC + "[32m" + repeat_chars("━", filled) + ESC + "[0m" + ESC + "[2m" + repeat_chars("━", bar_width - filled) + ESC + "[0m" + " " + gpm_tui_number(value) + "%"
    ret result
}

pub fn progress_bar(percent: int) { print("\r" + progress(percent, "")) }

pub fn markdown(text: string): string {
    lt lines = text.split("\n")
    lt output = ""
    lt i = 0
    while (i < lines.len()) {
        lt line = lines[i].trim()
        if (gs_string_starts(line, "### ") == 1) {
            output = output + ESC + "[1m" + ESC + "[36m" + gs_string_slice(line, "5", "999") + ESC + "[0m"
        } else if (gs_string_starts(line, "## ") == 1) {
            output = output + ESC + "[1m" + gs_string_slice(line, "4", "999") + ESC + "[0m"
        } else if (gs_string_starts(line, "# ") == 1) {
            output = output + ESC + "[1m" + gpm_tui_rgb(88, 166, 255, gs_string_slice(line, "3", "999")) + ESC + "[0m"
        } else if (gs_string_starts(line, "- ") == 1 || gs_string_starts(line, "* ") == 1) {
            output = output + ESC + "[36m•" + ESC + "[0m " + gs_string_slice(line, "3", "999")
        } else if (gs_string_starts(line, "```") == 1) {
            output = output + dim("──── code ────")
        } else if (line != "") {
            output = output + line
        }
        if (i < lines.len() - 1) { output = output + "\n" }
        i = i + 1
    }
    ret output
}

pub fn prompt(text: string): string {
    print(cyan("? ") + bold(text) + " ")
    ret gs_read_line()
}

pub fn confirm(text: string, default_yes: bool): bool {
    lt hint = "[y/N]"
    if (default_yes) { hint = "[Y/n]" }
    lt answer = prompt(text + " " + hint)
    lt lower = gs_string_lower(answer, 0)
    if (answer == "") { ret default_yes }
    ret lower == "y" || lower == "yes" || lower == "oui"
}

pub fn status(label: string, text: string, success: bool): string {
    lt icon = red("●")
    if (success) { icon = green("●") }
    lt prefix = dim(label)
    if (prefix != "") { prefix = prefix + " " }
    ret prefix + icon + " " + text
}
