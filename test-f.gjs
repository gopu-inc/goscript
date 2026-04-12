fn main() {
    lt name = "Alice"
    lt age = 30
    
    // f-string avec guillemets doubles
    lt msg1 = f"Hello {name}, you are {age} years old"
    println(msg1)
    
    // f-string avec apostrophes
    lt msg2 = f'User {name} has age {age}'
    println(msg2)
    
    // Expressions mathématiques dans f-string
    lt x = 10
    lt y = 20
    lt sum = f"{x} + {y} = {x + y}"
    println(sum)
}
