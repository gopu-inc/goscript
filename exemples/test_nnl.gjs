// Test des sauts non-locaux (nnl)

fn main() {
    println("=== TEST NNL ===\n")
    
    // Test simple avec saut
    nnl mylabel {
        println("Inside nnl block")
        println("About to jump...")
        jmp mylabel
        println("This line will never execute")
    }
    
    println("After nnl block\n")
    
    // Test avec condition
    nnl error_handler {
        muts x = 10
        
        if x > 5 {
            println("x > 5, jumping to error_handler")
            jmp error_handler
        }
        
        println("This won't print")
    }
    
    println("After error handler\n")
    
    // Test avec valeur
    nnl found {
        muts arr = [1, 2, 3, 4, 5]
        muts target = 3
        muts i = 0
        
        while i < 5 {
            if arr[i] == target {
                println("Found " + target + " at index " + i)
                jmp found
            }
            i = i + 1
        }
        
        println("Not found")
    }
    
    println("\n=== FIN ===")
    
    ret 0
}
