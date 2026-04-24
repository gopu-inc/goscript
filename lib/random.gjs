// lib/random.gjs
module random

pub fn int(max: int): string {
    ret sysf("awk -v max=" + max + " 'BEGIN { srand(); print int(rand() * max) }'")
}

pub fn string(length: int): string {
    ret sysf("cat /dev/urandom | tr -dc 'a-zA-Z0-0' | fold -w " + length + " | head -n 1")
}

// UUID fait maison (Compatible tout système Linux/BusyBox)
pub fn uuid(): string {
    // On génère 16 octets aléatoires et on les formate
    lt cmd = "hexdump -vn 16 -e '4/1 \"%02x\" \"-\" 2/1 \"%02x\" \"-\" 2/1 \"%02x\" \"-\" 2/1 \"%02x\" \"-\" 6/1 \"%02x\"' /dev/urandom"
    ret sysf(cmd)
}

