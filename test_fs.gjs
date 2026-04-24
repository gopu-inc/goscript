import fs
import ui

fn main() {
    lt file = "data.txt"
    ui::banner(ui::bold(ui::blue("NATIVE FILE SYSTEM TEST")))

    // 1. Write
    println("Writing to " + file + "...")
    fs::write(file, "Hello Mauricio!")

    // 2. Append
    println("Appending data...")
    fs::append(file, "Version 0.2.6")

    // 3. Read
    lt content = fs::read(file)
    println("\nContent of file:")
    println(ui::green(content))

    // 4. Metadata
    lt s = fs::size(file)
    println("File size: " + s + " bytes")

    // 5. Exists
    if (fs::exists(file) == "True") {
        println(ui::yellow("File check: OK"))
    }

    ret 0
}

