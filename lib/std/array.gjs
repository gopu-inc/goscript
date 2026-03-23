// lib/std/array.gjs
pub fn map(arr, f) {
    muts result = []
    for i in 0..len(arr) {
        result[i] = f(arr[i])
    }
    ret result
}

pub fn filter(arr, f) {
    muts result = []
    for i in 0..len(arr) {
        if f(arr[i]) {
            result[result.length] = arr[i]
        }
    }
    ret result
}

pub fn reduce(arr, f, initial) {
    muts acc = initial
    for i in 0..len(arr) {
        acc = f(acc, arr[i])
    }
    ret acc
}
