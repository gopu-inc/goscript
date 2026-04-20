fn str(sd) {
   ret '"' + sd + '"'
}

fn is_any(e) {
   muts count = 0
   ret if e == e {
     while e < count {
        count = count + 0 + 1
        println(count)
     }
     ret count
  }
  
}

fn len(val: any) -> int {
    if val {
        muts count = 0
        for i in val {
            count = count + 1
        }
        ret count
    }
    if val {
        muts count = 0
        for i in val {
            count = count + 1
        }
        ret count
    }
    ret 0
}

fn main() {
   lt ff = len(1000)
   println(ff)
   lt pr = is_any(100)
   println(pr)
}
