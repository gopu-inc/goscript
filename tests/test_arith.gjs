/*
 * tests/test_arith.gjs — Entiers 64 bits, mélange int/float, division par zéro
 */

print("=== Tests arithmétique ===")

print("[1] Entiers 64 bits ...")
muts big = 2147483647
big = big + 1
if big == 2147483648 {
    print("    OK  2147483647 + 1 = 2147483648")
} else {
    print("    FAIL débordement 32 bits : " + str(big))
}

muts i = 0
muts s = 0
while (i < 1000000) {
    s = s + i
    i = i + 1
}
if s == 499999500000 {
    print("    OK  somme 0..999999 = 499999500000")
} else {
    print("    FAIL somme = " + str(s))
}

print("[2] Mélange int / float ...")
lt f = 1.5 + 2
if f == 3.5 {
    print("    OK  1.5 + 2 = 3.5")
} else {
    print("    FAIL 1.5 + 2 = " + str(f))
}
lt g = 2 * 1.5
if g == 3.0 {
    print("    OK  2 * 1.5 = 3.0")
} else {
    print("    FAIL 2 * 1.5 = " + str(g))
}
if 1 < 1.5 {
    print("    OK  1 < 1.5")
} else {
    print("    FAIL 1 < 1.5")
}

print("[3] Division par zéro ...")
muts caught = 0
try {
    lt x = 10 / 0
    print("    FAIL aucune exception pour 10 / 0")
} catch (e) {
    caught = 1
}
if caught == 1 {
    print("    OK  10 / 0 lève une exception")
}

muts caught2 = 0
try {
    lt y = 10 % 0
    print("    FAIL aucune exception pour 10 % 0")
} catch (e) {
    caught2 = 1
}
if caught2 == 1 {
    print("    OK  10 % 0 lève une exception")
}

print("=== Fin tests arithmétique ===")
