fn add(x, y) {
    ret x + y
}

fn main() {
    lt a = 5
    lt b = 3
    lt result = add(a, b)
    
    if result > 5 {
        ret result * 2
    } else {
        ret result
    }
}
