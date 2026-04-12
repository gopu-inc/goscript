// Importer directement le module depuis son fichier
import rm from "./rm"
import cp from "./cp"
import mv from "./mv"
import search from "./search"

fn main() {
    // Utilisation
    lt result = search::search_path(".")
    println(result)
    
    println(rm::file("/tmp/test.txt"))
    
    println(cp::file("src.txt", "dst.txt"))
}
