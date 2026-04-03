fn main() {
    println("=== TEST DU BUILTIN 100% GOSCRIPT ===")

    // 1. Mathématiques
    println("\n-- 1. Mathematiques --")
    print("PI = ")
    println(PI)
    
    print("abs(-42) = ")
    println(abs(-42))

    print("max(10, 25) = ")
    println(max(10, 25))

    print("pow(2, 3) = ")
    println(pow(2, 3))

    print("clamp(15, 0, 10) = ")
    println(clamp(15, 0, 10))

    // 2. Chaînes de caractères
    println("\n-- 2. Chaines (Strings) --")
    
    lt cmp1 = str_compare("test", "test")
    lt cmp2 = str_compare("test", "fail")
    
    print("str_compare('test', 'test') = ")
    println(cmp1)
    
    print("str_compare('test', 'fail') = ")
    println(cmp2)

    // 3. Assertions
    println("\n-- 3. Assertions --")
    assert(10 > 5, "10 est bien superieur a 5")
    assert(str_compare("A", "B"), "A devrait etre egal a B (Ceci doit afficher une erreur)")

    println("\n=== FIN DU TEST ===")
    ret 0
}
