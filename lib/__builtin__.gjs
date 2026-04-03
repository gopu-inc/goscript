module __builtin__

// =========================================================
// 1. CHAÎNES
// =========================================================

pub fn len(s) {
    ret strlen_c(s)
}

pub fn str_compare(s1, s2) {
    ret strcmp_c(s1, s2) == 0
}

// =========================================================
// 2. MATHÉMATIQUES
// =========================================================

pub cn PI = 3.14159265359
pub cn E  = 2.71828182846

pub fn abs(n) {
    if n < 0 { ret -n }
    ret n
}

pub fn max(a, b) {
    if a > b { ret a }
    ret b
}

pub fn now() {
    ret time_c(0)
}

// =========================================================
// 3. FICHIERS (Retrait de 'pub' devant struct pour le parser)
// =========================================================

struct File {
    path: string,
    handle: int,
    is_open: bool
}

impl File {
    pub fn open(path, mode) {
        lt fd = fopen_c(path, mode)
        ret new File {
            path: path,
            handle: fd,
            is_open: fd != 0
        }
    }

    pub fn write(self, content) {
        if self.is_open {
            ret fputs_c(content, self.handle)
        }
        ret -1
    }
}
