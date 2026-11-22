/*
 * tests/test_grammar.gjs — Précédence et ambiguïtés levées dans parser.y
 */

print("=== Tests grammaire ===")

print("[1] Opérateur ternaire (plus faible que les comparaisons et l'arithmétique) ...")
lt x = 5
lt a = x > 3 ? "grand" : "petit"
if a == "grand" {
    print("    OK  x > 3 ? ... : ...")
} else {
    print("    FAIL ternaire avec comparaison : " + a)
}
lt b = 1 + 1 == 2 ? "ok" : "ko"
if b == "ok" {
    print("    OK  1 + 1 == 2 ? ... : ...")
} else {
    print("    FAIL ternaire avec arithmétique : " + b)
}
lt c = 1 > 2 ? "a" : 2 > 1 ? "b" : "c"
if c == "b" {
    print("    OK  ternaires chaînés (associativité à droite)")
} else {
    print("    FAIL ternaires chaînés : " + c)
}

print("[2] sh(...) forme parenthésée liée avant l'opérateur ...")
if sh("true") == 0 {
    print("    OK  sh(\"true\") == 0")
} else {
    print("    FAIL sh(...) == 0")
}

print("[3] Struct vide, struct à plusieurs champs, impl vide ...")
struct Vide {}
struct Pt { x: int, y: int }
impl Vide {}
impl Pt {
    fn somme(self): int { ret self.x + self.y }
}
lt p = new Pt{ x: 3, y: 4 }
if p.somme() == 7 {
    print("    OK  struct + impl")
} else {
    print("    FAIL somme = " + str(p.somme()))
}

print("[4] ret sans valeur suivi d'une accolade ...")
fn tot(n: int) {
    if n > 0 { ret }
    print("    FAIL ret nu non pris en compte")
}
tot(1)
print("    OK  ret nu")

print("=== Fin tests grammaire ===")
