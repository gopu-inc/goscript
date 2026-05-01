// lib/json.gjs
module json

pub fn get(data: string, key: string): string {
    // On affine le regex pour exclure les accolades à la fin [^",}]
    lt cmd = "printf '" + data + "' | sed -n 's/.*\"" + key + "\": *\"\\?\\([^\",}]*\\)\"\\?.*/\\1/p' | sed 's/\"//g'"
    ret sysf(cmd)
}

pub fn format(data: string): string {
    lt cmd = "printf '" + data + "' | sed 's/,/,\\n /g; s/{/{\\n /g; s/}/\\n}/g'"
    ret sysf(cmd)
}

pub fn is_json(data: string): string {
    ret sysf("printf '" + data + "' | grep -qE '^[ \t]*[\{\[]' && echo 'True' || echo 'False'")
}

