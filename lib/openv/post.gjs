golem post

import fs
import openv.get as getmod

pub fn env(name: string, value: string): bool {
    if name == "" || name.contains("=") || name.contains("\n") || value.contains("\n") {
        ret false
    }
    if getmod::has(name, ".openv") {
        ret false
    }
    ret fs::append(".openv", name + "=" + value + "\n")
}

pub fn Env(name: string, value: string): bool {
    ret env(name, value)
}
