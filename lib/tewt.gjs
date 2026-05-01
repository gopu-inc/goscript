fn fs(path) {
   ret system_c(f"ls -la {path}")
}

fn main() {
   f = fs(".")
   println(f)
}
