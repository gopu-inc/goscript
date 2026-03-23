// Math utilities for Goscript

fn add(a: int, b: int) -> int {
    ret a + b
}

fn subtract(a: int, b: int) -> int {
    ret a - b
}

fn multiply(a: int, b: int) -> int {
    ret a * b
}

fn divide(a: int, b: int) -> int {
    if b != 0 {
        ret a / b
    }
    ret 0
}
