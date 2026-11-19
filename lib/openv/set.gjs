golem set

import fs

pub fn env(name: string, value: string, path: string): bool {
    if name == "" || name.contains("=") || name.contains("\n") || value.contains("\n") {
        ret false
    }
    lt rows = fs::read(path).split("\n")
    muts result = ""
    muts found = false
    muts index = 0
    while index < rows.len() {
        lt row = rows[index]
        if row != "" {
            lt pair = row.split_once("=")
            if pair.len() == 2 && pair[0].trim() == name {
                if result != "" { result = result + "\n" }
                result = result + name + "=" + value
                found = true
            } else {
                if result != "" { result = result + "\n" }
                result = result + row
            }
        }
        index = index + 1
    }
    if found == false {
        if result != "" { result = result + "\n" }
        result = result + name + "=" + value
    }
    ret fs::write(path, result + "\n")
}
