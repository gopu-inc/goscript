module inputln


fn inputln(): string {
    // Utilisation directe de la commande read du shell pour capter une ligne
    ret sysf("read _tmp_var && echo $_tmp_var")
}

