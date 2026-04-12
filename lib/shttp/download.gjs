module download

pub fn file(url: string, output: string): string {
    lt cmd = "sh -c \"curl -L -o " + output + " " + url + "\""
    lt result = await cmd
    ret "ok"
}

pub fn file_silent(url: string, output: string): string {
    lt cmd = "sh -c \"curl -s -L -o " + output + " " + url + "\""
    lt result = await cmd
    ret "ok"
}

pub fn file_with_progress(url: string, output: string): string {
    lt cmd = "sh -c \"curl -# -L -o " + output + " " + url + "\""
    lt result = await cmd
    ret "ok"
}

pub fn resume(url: string, output: string): string {
    lt cmd = "sh -c \"curl -C - -L -o " + output + " " + url + "\""
    lt result = await cmd
    ret "ok"
}

pub fn multiple(urls: string, output_dir: string): string {
    lt cmd = "sh -c \"cd " + output_dir + " && curl -O " + urls + "\""
    lt result = await cmd
    ret "ok"
}
