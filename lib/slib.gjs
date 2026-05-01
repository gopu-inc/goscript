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

fn main() {
   trim("hello")
}
