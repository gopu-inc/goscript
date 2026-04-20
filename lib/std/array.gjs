// lib/std/array.gjs
pub fn mape(arr, f) {
    muts result = []
    for i in strlen_c(arr) {
        result[i] = f(arr[i])
    }
    ret result
}

pub fn filter(arr, f) {
    muts result = []
    for i in strlen_c(arr) {
        if f(arr[i]) {
            result[result.length] = arr[i]
        }
    }
    ret result
}

pub fn reduce(arr, f, initial) {
    muts acc = initial
    for i in strlen_c(arr) {
        acc = f(acc, arr[i])
    }
    ret acc
}
