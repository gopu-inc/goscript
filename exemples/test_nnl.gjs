// Test des sauts non-locaux

fn main() {
    println("=== TEST NON-LOCAL JUMPS ===\n")
    
    // nnl avec label 'error'
    nnl error {
        println("Inside nnl block")
        
        // Tester une condition
        muts x = 10
        
        if x > 5 {
            println("x > 5, jumping to error")
            jmp error "Too big value"
        }
        
        println("This won't be executed")
    }
    
    println("After nnl block\n")
    
    // nnl avec valeur de retour
    nnl found {
        muts arr = [1, 2, 3, 4, 5]
        muts target = 3
        
        muts i = 0
        while i < len(arr) {
            if arr[i] == target {
                println("Found " + target + " at index " + i)
                jmp found i
            }
            i = i + 1
        }
        
        println("Not found")
        jmp found -1
    }
    
    println("\n=== FIN ===")
    
    ret 0
}

fn len(arr) {
    ret arr[0]
}
