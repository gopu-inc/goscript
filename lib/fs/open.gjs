module open

fn escape(s: string): string {
    // Remplacer ' par '\'' (fermer la chaîne, échapper, rouvrir)
    lt cmd = f"echo -n \"{s}\" | sed \"s/'/'\\\\''/g\""
    lt result = await cmd
    ret result
}

pub fn read_file(path: string): string {
    lt cmd = f"cat {path} 2>/dev/null"
    lt result = await cmd
    ret result
}

pub fn read_lines(path: string): string {
    lt cmd = f"cat {path} 2>/dev/null"
    lt result = await cmd
    ret result
}

pub fn read_first_line(path: string): string {
    lt cmd = f"head -n 1 {path} 2>/dev/null"
    lt result = await cmd
    ret result
}
