fn main() {
    println("Nombre d'arguments: " + len(ARGV))
    
    lt i = 0
    while i < len(ARGV) {
        println("ARGV[" + i + "] = " + ARGV[i])
        i = i + 1
    }
}
