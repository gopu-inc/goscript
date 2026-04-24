import os

fn main() {
    println("--- Testing OS Module ---")

    // 1. Get Current Directory
    lt cwd = os::getcwd()
    println("Current Directory: " + cwd)

    // 2. List files
    println("Files in current directory:")
    lt files = os::list_dir(".")
    println(files)

    // 3. Check for a specific file (the one we created with IO)
    lt target = "test_data.txt"
    if (os::exists(target) == "True") {
        println("File '" + target + "' exists. Deleting it...")
        os::remove(target)
        println("File deleted.")
    } else {
        println("File '" + target + "' not found.")
    }

    // 4. Check environment variable
    lt user = os::getenv("USER")
    println("System User: " + user)

    ret 0
}

