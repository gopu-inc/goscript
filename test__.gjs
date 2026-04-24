pub fn trim(s: string): string {
    if s == nil || len(s) == 0 { 
        ret "" 
    }
    
    muts start_found = false
    muts res = ""
    muts trailing_spaces = ""
    
    // On utilise 'for in' pour éviter le bug du NODE(17) (indexation)
    for c in s {
        if !start_found {
            // On saute les espaces au début
            if c == " " || c == "\t" || c == "\n" || c == "\r" {
                continue
            }
            start_found = true
        }
        
        if start_found {
            if c == " " || c == "\t" || c == "\n" || c == "\r" {
                // On stocke les espaces temporairement
                // S'il y a d'autres caractères après, on les ajoutera
                trailing_spaces = trailing_spaces + c
            } else {
                // On ajoute les espaces accumulés précédemment + le caractère actuel
                res = res + trailing_spaces + c
                trailing_spaces = ""
            }
        }
    }
    
    ret res
}

fn main() {
   lt local = trim("   bonjour   ")
   println("[" + local + "]") 
   
   lt test2 = trim("\t  Hello World\n")
   println("[" + test2 + "]")
}

