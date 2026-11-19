golem get

import fs

pub fn has(name: string, path: string): bool {
    if name == "" { ret false }
    lt rows = fs::read(path).split("\n")
    muts index = 0
    while index < rows.len() {
        lt row = rows[index]
        lt pair = row.split_once("=")
        if pair.len() == 2 && pair[0].trim() == name {
            ret true
        }
        index = index + 1
    }
    ret false
}

pub fn env(name: string, path: string): string {
    if name == "" { ret "" }
    lt rows = fs::read(path).split("\n")
    muts index = 0
    while index < rows.len() {
        lt row = rows[index]
        lt pair = row.split_once("=")
        if pair.len() == 2 && pair[0].trim() == name {
            ret pair[1]
        }
        index = index + 1
    }
    ret ""
}
