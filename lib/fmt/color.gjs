// fmt.gjs
module fmt

pub cn RED = "\x1b[31m"
pub cn GREEN = "\x1b[32m"
pub cn RESET = "\x1b[0m"

pub fn red(text) {
    ret RED + text + RESET
}

pub fn green(text) {
    ret GREEN + text + RESET
}
