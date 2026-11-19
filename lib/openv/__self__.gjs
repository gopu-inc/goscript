golem openv

import openv.get as getmod
import openv.post as postmod
import openv.set as setmod

pub cn VERSION = "0.1.1"

pub fn get(name: string): string {
    ret getmod::env(name, ".openv")
}

pub fn get_from(name: string, path: string): string {
    ret getmod::env(name, path)
}

pub fn has(name: string): bool {
    ret getmod::has(name, ".openv")
}

pub fn add(name: string, value: string): bool {
    ret postmod::env(name, value)
}

pub fn set(name: string, value: string): bool {
    ret setmod::env(name, value, ".openv")
}
