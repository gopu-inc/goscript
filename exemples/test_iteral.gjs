// test_gc.gjs
fn main() {
    muts i = 0
    while i < 201 {
        lt s = "iteration " + i
        i = i + 1
        println(i)
    }
    println("GC test passed!")
    
}
