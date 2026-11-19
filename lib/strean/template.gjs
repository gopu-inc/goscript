golem template

// Replace {{key}} placeholders from a dictionary. Values must be strings.
pub fn render(source: string, values: any): string {
    muts rendered = source
    while rendered.contains("{{") {
        lt before = rendered.split_once("{{")
        lt token = before[1].split_once("}}")
        if !before[1].contains("}}") {
            ret rendered
        }
        lt replacement = values[token[0]]
        rendered = before[0] + replacement + token[1]
    }
    ret rendered
}
