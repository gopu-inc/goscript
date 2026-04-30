
fn types(s) {
    muts i = 0
    for i in i {
        ret i = i + 1
    }
    if s == ARGV[0] {
       
        ret "type 0 ( 0x800880 mov x0x )"
    }
    
    ret "unknow"
}

fn main() {
    lt arg0 = ARGV[0]
    println("arg0 = " + arg0)
    println("type de arg0 = " + types(arg0))
}
