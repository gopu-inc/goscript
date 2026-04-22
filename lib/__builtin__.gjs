module __builtin__

pub fn inputln(): string {
    // Utilisation de -r pour éviter les problèmes avec les backslashes
    ret sysf("read -r _tmp_var && echo $_tmp_var")
}

pub fn ints(s: string): int {
    if s == nil || s == "" {
        ret 0
    }
    ret atoi_c(s)
}

pub fn str(v: any): string {
    if v == nil {
        ret "nil"
    }
    // Utilisation de %s pour être plus propre avec printf si dispo, 
    // sinon echo -n est très bien
    ret sysf("echo -n \"" + v + "\"")
}

// Ajout du support void pour les fonctions système
pub fn exit(code: int): void {
    sh("exit " + str(code))
}

