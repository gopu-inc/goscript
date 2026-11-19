import openv

fn main() {
    if openv::add("OPENV_TEST", "first=value") == false { exit(1) }
    if openv::get("OPENV_TEST") != "first=value" { exit(1) }
    if openv::has("OPENV_TEST") == false { exit(1) }
    if openv::add("OPENV_TEST", "duplicate") == true { exit(1) }
    if openv::set("OPENV_TEST", "updated=value") == false { exit(1) }
    if openv::get("OPENV_TEST") != "updated=value" { exit(1) }
    println("OpenV checks passed")
}
