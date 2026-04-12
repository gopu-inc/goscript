module_name mv

pub fn file(src: string, dst: string): string {
    lt cmd = f"mv '{src}' '{dst}'"
    lt result = await cmd
    ret "ok"
}

pub fn dir(src: string, dst: string): string {
    lt cmd = f"mv '{src}' '{dst}'"
    lt result = await cmd
    ret "ok"
}

pub fn rename(old_name: string, new_name: string): string {
    lt cmd = f"mv '{old_name}' '{new_name}'"
    lt result = await cmd
    ret "ok"
}
