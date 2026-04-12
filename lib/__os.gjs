// Module __os - Informations système via await
// Pas de FFI, uniquement des commandes shell

// Version de l'OS
pub fn version(): string {
    lt v = await "cat /etc/os-release 2>/dev/null | grep VERSION_ID | cut -d= -f2 | tr -d '\"'"
    if v == nil || v == "" {
        v = await "uname -r"
    }
    ret trim(v)
}

// Nom de l'OS
pub fn name(): string {
    lt n = await "cat /etc/os-release 2>/dev/null | grep NAME | head -1 | cut -d= -f2 | tr -d '\"'"
    if n == nil || n == "" {
        n = await "uname -s"
    }
    ret trim(n)
}

// Architecture
pub fn arch(): string {
    ret trim(await "uname -m")
}

// Nom d'hôte
pub fn hostname(): string {
    ret trim(await "hostname")
}

// Utilisateur courant
pub fn user(): string {
    ret trim(await "whoami")
}

// Uptime système
pub fn uptime(): string {
    ret trim(await "uptime")
}

// Date et heure
pub fn datetime(): string {
    ret trim(await "date")
}

// Timestamp Unix
pub fn timestamp(): int {
    lt ts = await "date +%s"
    ret to_int(trim(ts))
}

// PID du processus courant
pub fn pid(): int {
    lt p = await "echo $$"
    ret to_int(trim(p))
}

// Variables d'environnement
pub fn getenv(key: string): string {
    ret trim(await "echo $" + key)
}

// Chemins système
pub fn cwd(): string {
    ret trim(await "pwd")
}

pub fn home(): string {
    ret trim(await "echo $HOME")
}

pub fn temp(): string {
    ret trim(await "echo /tmp")
}

// Fonction helper
fn trim(s: string): string {
    if s == nil { ret "" }
    muts l = len(s)
    muts st = 0
    muts en = l - 1
    while st < l {
        if s[st] == 10 || s[st] == 13 {
            st = st + 1
        } else { break }
    }
    while en >= 0 {
        if s[en] == 10 || s[en] == 13 {
            en = en - 1
        } else { break }
    }
    if st > en { ret "" }
    muts res = ""
    muts i = st
    while i <= en {
        res = res + s[i]
        i = i + 1
    }
    ret res
}

fn to_int(s: string): int {
    if s == nil { ret 0 }
    muts res = 0
    muts i = 0
    while i < len(s) {
        muts c = s[i]
        if c >= 48 && c <= 57 {
            res = res * 10 + (c - 48)
        } else { break }
        i = i + 1
    }
    ret res
}

fn len(s: string): int {
    if s == nil { ret 0 }
    muts count = 0
    muts i = 0
    loop {
        if s[i] == nil { break }
        count = count + 1
        i = i + 1
    }
    ret count
}
