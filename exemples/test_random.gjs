import random
import ui

fn main() {
    ui::banner(ui::bold(ui::blue("RANDOM GENERATOR TEST")))

    // 1. Test Nombre Aléatoire
    lt num = random::int(1000)
    println("Nombre chanceux (0-1000) : " + ui::green(num))

    // 2. Test Mot de Passe / Token
    lt pass = random::string(12)
    println("Token généré (12 chars)  : " + ui::yellow(pass))

    // 3. Test UUID
    lt id = random::uuid()
    println("UUID Unique du système   : " + ui::blue(id))

    ret 0
}

