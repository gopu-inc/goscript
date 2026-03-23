// Test des tableaux et lambdas

fn main() {
    println("=== TEST TABLEAUX ===\n")
    
    // Créer un tableau
    muts arr = [10, 20, 30, 40, 50]
    
    println("Tableau: " + arr)
    println("Premier élément: " + arr[0])
    println("Troisième élément: " + arr[2])
    
    // Modifier un élément
    arr[2] = 99
    println("Après modification: " + arr)
    
    println("\n=== TEST LAMBDAS ===\n")
    
    // Lambda simple
    muts add = lambda a, b {
        ret a + b
    }
    
    muts result = add(5, 3)
    println("5 + 3 = " + result)
    
    // Lambda avec closure
    muts multiplier = lambda factor {
        lambda x {
            ret x * factor
        }
    }
    
    muts double = multiplier(2)
    muts triple = multiplier(3)
    
    println("double(10) = " + double(10))
    println("triple(10) = " + triple(10))
    
    // Lambda avec tableau
    muts arr2 = [1, 2, 3, 4, 5]
    muts double_arr = lambda arr {
        muts result = []
        muts i = 0
        while i < len(arr) {
            result = push(result, arr[i] * 2)
            i = i + 1
        }
        ret result
    }
    
    muts doubled = double_arr(arr2)
    println("Original: " + arr2)
    println("Doublé: " + doubled)
    
    println("\n=== FIN ===")
    
    ret 0
}

fn len(arr) {
    ret arr[0]
}

fn push(arr, val) {
    ret arr + [val]
}
