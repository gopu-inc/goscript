import sha from "s256/sha"

fn main() {
   lt r = sha::sum("newP.sha", "new.sha")
   println(r)
}
