import io

fn main() {
    println("--- Testing IO Module ---")

    lt filename = "test_data.txt"
    lt message = "Hello from Goscript 0.2.0!\n"

    // 1. Writing to a file
    println("Writing to: " + filename)
    io::write_file(filename, message)

    // 2. Appending data
    println("Appending data...")
    io::append_file(filename, "This is an appended line.\n")

    // 3. Reading back
    println("Reading file content:")
    lt content = io::read_file(filename)
    println("-----------------------")
    println(content)
    println("-----------------------")

    ret 0
}

