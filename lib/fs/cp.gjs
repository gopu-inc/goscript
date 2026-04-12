module_name cp

pub fn file(src: string, dst: string): string {
    lt cmd = f"cp '{src}' '{dst}'"
    lt result = await cmd
    ret "ok"
}

pub fn dir(src: string, dst: string): string {
    lt cmd = f"cp -r '{src}' '{dst}'"
    lt result = await cmd
    ret "ok"
}

pub fn recursive(src: string, dst: string): string {
    lt cmd = f"cp -r '{src}' '{dst}'"
    lt result = await cmd
    ret "ok"
}

pub fn force(src: string, dst: string): string {
    lt cmd = f"cp -f '{src}' '{dst}'"
    lt result = await cmd
    ret "ok"
}
