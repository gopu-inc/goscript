/*
 * tests/test_std.gjs — Tests de la lib standard Goscript
 * Mots-clés : lt (var), cn (const), ret (return), lambda (anonyme)
 */

print("=== Tests librairie standard ===")

// Test 1 : Chaînes de caractères
print("[1] Opérations sur les chaînes ...")
lt s = "Bonjour Goscript"
lt l = strlen_c(s)
if l == 16 {
    print("    OK  strlen('" + s + "') = " + str(l))
} else {
    print("    FAIL strlen=" + str(l) + " attendu 16")
}

// Test 2 : Conversion types
print("[2] Conversions de types ...")
lt n_str = str(42)
if n_str == "42" {
    print("    OK  str(42) = " + n_str)
} else {
    print("    FAIL str(42) incorrect : " + n_str)
}

// Test 3 : Tableaux
print("[3] Tableaux ...")
lt arr = [10, 20, 30, 40, 50]
lt total = 0
for i in arr {
    total = total + i
}
if total == 150 {
    print("    OK  somme du tableau = " + str(total))
} else {
    print("    FAIL somme incorrecte = " + str(total))
}

// Test 4 : Dictionnaires — syntaxe Goscript : dict { "key" => val }
print("[4] Dictionnaires ...")
lt d = dict { "nom" => "Alice", "age" => 30 }
if d["nom"] == "Alice" {
    print("    OK  dict[nom] = " + d["nom"])
} else {
    print("    FAIL dict.nom incorrect")
}

// Test 5 : Fonctions nommées
print("[5] Fonctions nommées ...")
fn somme(a, b) {
    ret a + b
}
lt r = somme(15, 27)
if r == 42 {
    print("    OK  somme(15, 27) = " + str(r))
} else {
    print("    FAIL somme = " + str(r))
}

// Test 6 : Lambdas
print("[6] Lambdas ...")
lt double = lambda(x) { ret x * 2 }
lt huit = double(4)
if huit == 8 {
    print("    OK  lambda double(4) = " + str(huit))
} else {
    print("    FAIL lambda = " + str(huit))
}

// Test 7 : Closures
print("[7] Closures ...")
fn compteur() {
    lt c = 0
    ret lambda() {
        c = c + 1
        ret c
    }
}
lt inc = compteur()
lt v1 = inc()
lt v2 = inc()
lt v3 = inc()
if v1 == 1 && v2 == 2 && v3 == 3 {
    print("    OK  closure: " + str(v1) + ", " + str(v2) + ", " + str(v3))
} else {
    print("    FAIL closure: " + str(v1) + ", " + str(v2) + ", " + str(v3))
}

// Test 8 : Conditions
print("[8] Conditions ...")
fn grade(note) {
    if note >= 90 {
        ret "A"
    } else if note >= 80 {
        ret "B"
    } else if note >= 70 {
        ret "C"
    } else {
        ret "F"
    }
}
if grade(95) == "A" && grade(82) == "B" && grade(60) == "F" {
    print("    OK  grade(95)=A, grade(82)=B, grade(60)=F")
} else {
    print("    FAIL grade(95)=" + grade(95) + " grade(82)=" + grade(82))
}

// Test 9 : Boucle while
print("[9] Boucle while ...")
lt sum = 0
lt i = 1
while i <= 10 {
    sum = sum + i
    i = i + 1
}
if sum == 55 {
    print("    OK  1+2+...+10 = " + str(sum))
} else {
    print("    FAIL somme = " + str(sum))
}

// Test 10 : Récursivité
print("[10] Récursivité (fibonacci) ...")
fn fib(n) {
    if n <= 1 { ret n }
    ret fib(n-1) + fib(n-2)
}
lt f10 = fib(10)
if f10 == 55 {
    print("    OK  fib(10) = " + str(f10))
} else {
    print("    FAIL fib(10) = " + str(f10))
}

print("=== Fin tests std ===")
