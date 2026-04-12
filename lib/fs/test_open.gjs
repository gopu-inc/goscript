import open from "./open"

fn main() {
    println("=== TEST OPEN ===\n")
    lt content = open::read_file("search.gjs")
    println(content)
}
