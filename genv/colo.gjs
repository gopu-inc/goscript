fn cor() {
   ret sysf("echo '\033[0;31mError: Environment not found\033[0m'") == 0
}
fn main() {
   cor()
}
