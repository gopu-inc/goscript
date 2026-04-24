pub fn trim(s: string): string {
    // 1. Vérification de sécurité
    if s == nil || len(s) == 0 { 
        ret "" 
    }
    
    muts l = len(s)
    muts st = 0
    muts en = l - 1
    
    // 2. Trouver le premier caractère non-espace (en avançant)
    while st < l {
        muts c = s[st]
        // On vérifie les espaces, tabulations, sauts de ligne et retours chariot
        if c == " " || c == "\t" || c == "\n" || c == "\r" {
            st = st + 1
        } else { 
            break 
        }
    }
    
    // 3. Trouver le premier caractère non-espace (en reculant)
    while en >= 0 {
        muts c = s[en]
        if c == " " || c == "\t" || c == "\n" || c == "\r" {
            en = en - 1
        } else { 
            break 
        }
    }
    
    // Si la chaîne n'était composée que de caractères blancs
    if st > en { 
        ret "" 
    }
    
    // 4. Reconstruire la sous-chaîne nettoyée
    muts res = ""
    muts i = st
    while i <= en {
        res = res + s[i]
        i = i + 1
    }
    
    ret res
}


fn main() {
   lt local = trim(" bonjour")
   println(local)
}
