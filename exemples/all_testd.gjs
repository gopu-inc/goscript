fn add(a, b) {
    ret a + b;
}

fn subtract(a, b) {
    ret a - b;
}

fn multiply(a, b) {
    ret a * b;
}

fn divide(a, b) {
    ret a / b;
}

fn main() {
    lt a = 10;
    lt b = 5;
    
    lt sum = add(a, b);
    lt diff = subtract(a, b);
    lt prod = multiply(a, b);
    lt quot = divide(a, b);
    
    if sum > 10 {
        lt final = sum + diff + prod + quot;
        ret final;
    } else {
        ret 0;
    }
}
