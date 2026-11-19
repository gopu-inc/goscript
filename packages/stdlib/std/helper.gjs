golem helper

pub fn repeat_str(value: string, count: int): string {
    muts result = ""
    muts index = 0
    while index < count {
        result = result + value
        index = index + 1
    }
    ret result
}

pub fn join(values: array, separator: string): string {
    muts result = ""
    muts index = 0
    for value in values {
        if index > 0 { result = result + separator }
        result = result + value
        index = index + 1
    }
    ret result
}

pub fn map_array(values: array, transform): array {
    muts result = []
    for value in values {
        result = result + [transform(value)]
    }
    ret result
}

pub fn filter_array(values: array, predicate): array {
    muts result = []
    for value in values {
        if predicate(value) { result = result + [value] }
    }
    ret result
}

pub fn reduce_array(values: array, initial: any, reducer): any {
    muts result = initial
    for value in values {
        result = reducer(result, value)
    }
    ret result
}

pub fn len(value: any): int {
    muts count = 0
    try {
        for item in value {
            count = count + 1
        }
    } catch (e) {
        ret 0
    }
    ret count
}

pub fn reverse(values: array): array {
    muts result = []
    muts index = len(values) - 1
    while index >= 0 {
        result = result + [values[index]]
        index = index - 1
    }
    ret result
}

pub fn keys(value: any): array {
    muts result = []
    for key in value {
        result = result + [key]
    }
    ret result
}

pub fn values(value: any): array {
    muts result = []
    for key in value {
        result = result + [value[key]]
    }
    ret result
}

pub fn has_key(value: any, key: any): bool {
    for candidate in value {
        if candidate == key { ret true }
    }
    ret false
}

pub fn get_or(value: any, key: any, fallback: any): any {
    if has_key(value, key) { ret value[key] }
    ret fallback
}
