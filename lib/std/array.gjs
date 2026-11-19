golem array

pub fn map_array(arr: array, transform): array {
    muts result = []
    for item in arr {
        result = result + [transform(item)]
    }
    ret result
}

pub fn filter_array(arr: array, predicate): array {
    muts result = []
    for item in arr {
        if predicate(item) {
            result = result + [item]
        }
    }
    ret result
}

pub fn reduce_array(arr: array, reducer, initial: any): any {
    muts accumulator = initial
    for item in arr {
        accumulator = reducer(accumulator, item)
    }
    ret accumulator
}

pub fn mape(arr: array, transform): array {
    ret map_array(arr, transform)
}
