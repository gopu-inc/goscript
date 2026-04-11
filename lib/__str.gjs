// Module __str - Version fonctionnelle

pub fn len(s: string): int {
    
    ret strlen_c(s)
}

pub fn to_upper(s: string): string {
    if s == nil {
        ret ""
    }
    muts res = ""
    muts i = 0
    muts l = len(s)
    while i < l {
        muts c = s[i]
        if c >= 97 && c <= 122 {
            c = c - 32
        }
        res = res + string(c)
        i = i + 1
    }
    ret res
}

pub fn to_lower(s: string): string {
    if s == nil {
        ret ""
    }
    muts res = ""
    muts i = 0
    muts l = len(s)
    while i < l {
        muts c = s[i]
        if c >= 65 && c <= 90 {
            c = c + 32
        }
        res = res + string(c)
        i = i + 1
    }
    ret res
}

pub fn contains(s: string, sub: string): bool {
    if s == nil || sub == nil {
        ret false
    }
    muts sl = len(s)
    muts subl = len(sub)
    if subl == 0 {
        ret true
    }
    if subl > sl {
        ret false
    }
    muts i = 0
    while i <= sl - subl {
        muts j = 0
        muts ok = true
        while j < subl {
            if s[i + j] != sub[j] {
                ok = false
                break
            }
            j = j + 1
        }
        if ok == true {
            ret true
        }
        i = i + 1
    }
    ret false
}

pub fn substring(s: string, start: int, end: int): string {
    if s == nil {
        ret ""
    }
    muts sl = len(s)
    muts st = start
    muts en = end
    if st < 0 { st = 0 }
    if en > sl { en = sl }
    if st >= en {
        ret ""
    }
    muts res = ""
    muts i = st
    while i < en {
        res = res + string(s[i])
        i = i + 1
    }
    ret res
}

pub fn trim(s: string): string {
    if s == nil {
        ret ""
    }
    muts sl = len(s)
    muts st = 0
    muts en = sl - 1
    while st < sl {
        if s[st] == 32 || s[st] == 9 || s[st] == 10 {
            st = st + 1
        } else {
            break
        }
    }
    while en >= 0 {
        if s[en] == 32 || s[en] == 9 || s[en] == 10 {
            en = en - 1
        } else {
            break
        }
    }
    if st > en {
        ret ""
    }
    ret substring(s, st, en + 1)
}

pub fn to_int(s: string): int {
    if s == nil {
        ret 0
    }
    muts res = 0
    muts i = 0
    muts sign = 1
    muts sl = len(s)
    if sl > 0 && s[0] == 45 {
        sign = -1
        i = 1
    }
    while i < sl {
        muts c = s[i]
        if c >= 48 && c <= 57 {
            res = res * 10 + (c - 48)
        } else {
            break
        }
        i = i + 1
    }
    ret res * sign
}
