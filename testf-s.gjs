fn main() {
    lt name = "Alice"
    lt age = 30
    
    println(f"Hello {name}, you are {age} years old")
    
    lt x = 10
    lt y = 20
    println(f"{x} + {y} = {x + y}")
    println(f"{x} * {y} = {x * y}")
    println(f"{y} - {x} = {y - x}")
    println(f"{y} / {x} = {y / x}")
    
    // Concaténation de strings
    lt first = "Hello"
    lt last = "World"
    println(f"{first} + {last} = {first + last}")
    
    // Nombres littéraux
    println(f"100 + 50 = {100 + 50}")
}
