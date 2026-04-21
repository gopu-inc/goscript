// lib/sys.gjs
module sys

pub fn exec(cmd) {
    ret sh(cmd)
}

pub fn capture(cmd) {
    ret sysf(cmd)
}

pub fn exists(path) {
    ret sh("test -e '" + path + "'") == 0
}

pub fn is_file(path) {
    ret sh("test -f '" + path + "'") == 0
}

pub fn is_dir(path) {
    ret sh("test -d '" + path + "'") == 0
}

pub fn mkdir(path) {
    ret sh("mkdir -p '" + path + "'")
}

pub fn rm(path) {
    ret sh("rm -rf '" + path + "'")
}

pub fn ls(path) {
    if path {
        ret sysf("ls -la '" + path + "'")
    }
    ret sysf("ls -la")
}

pub fn cat(file) {
    ret sysf("cat '" + file + "'")
}

pub fn write(file, content) {
    ret sh("echo '" + content + "' > '" + file + "'")
}

pub fn which(cmd) {
    ret sysf("which '" + cmd + "' 2>/dev/null")
}

pub fn hostname() {
    ret sysf("hostname")
}

pub fn pwd() {
    ret sysf("pwd")
}
// sys.gjs - ajouts
pub fn cp(src, dst) {
    ret sh("cp -r '" + src + "' '" + dst + "'")
}

pub fn mv(src, dst) {
    ret sh("mv '" + src + "' '" + dst + "'")
}

pub fn env(name) {
    ret sysf("echo $" + name)
}

pub fn which(cmd) {
    ret sysf("which '" + cmd + "' 2>/dev/null")
}

pub fn ps() {
    ret sysf("ps aux")
}

pub fn kill(pid) {
    ret sh("kill -9 " + pid)
}
