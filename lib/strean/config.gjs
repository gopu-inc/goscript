golem config

muts values = {}

pub fn set(name: string, value: any) {
    values[name] = value
}

pub fn get(name: string): any {
    ret values[name]
}

pub fn has(name: string): bool {
    for key in values {
        if key == name { ret true }
    }
    ret false
}
