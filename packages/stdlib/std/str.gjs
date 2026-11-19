golem str

pub fn quote(value: string): string {
    ret "\"" + value + "\""
}

pub fn length(value: string): int {
    muts count = 0
    for character in value {
        count = count + 1
    }
    ret count
}

pub fn is_empty(value: string): bool {
    ret value == ""
}

pub fn repeat(value: string, count: int): string {
    muts result = ""
    muts index = 0
    while index < count {
        result = result + value
        index = index + 1
    }
    ret result
}
