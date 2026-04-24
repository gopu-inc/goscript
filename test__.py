def trim(s):
    # 1. Vérification de sécurité
    if s is None or len(s) == 0: 
        return ""
    
    l = len(s)
    st = 0
    en = l - 1
    
    # Caractères blancs à filtrer
    whitespace = [" ", "\t", "\n", "\r"]
    
    # 2. Trouver le premier caractère non-espace (en avançant)
    while st < l:
        c = s[st]
        if c in whitespace:
            st += 1
        else: 
            break
            
    # 3. Trouver le premier caractère non-espace (en reculant)
    while en >= 0:
        c = s[en]
        if c in whitespace:
            en -= 1
        else: 
            break
            
    # Si la chaîne n'était composée que de caractères blancs
    if st > en: 
        return ""
    
    # 4. Reconstruire la sous-chaîne nettoyée
    # (En Python, on utiliserait le slicing s[st:en+1], 
    # mais voici la version boucle pour coller à ton code)
    res = ""
    i = st
    while i <= en:
        res += s[i]
        i += 1
        
    return res

# Test
if __name__ == "__main__":
    local = trim("  bonjour  ")
    print(f"[{local}]")

