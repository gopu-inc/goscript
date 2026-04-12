import_name fs from "./fs"

fn main() {
    println("=== TEST FS MODULE ===\n")
    
    println("Current dir: " + fs::current_dir())
    println("")
    
    println("Files in current dir:")
    println(fs::search_path("."))
    println("")
    
    println("File 'fs.gjs' exists: " + fs::file_exists("fs.gjs"))
    println("Size of 'fs.gjs': " + fs::file_size("fs.gjs") + " bytes")
    println("")
    
    println("Create test directory:")
    lt test_dir = "/tmp/goscript_test"
    fs::mkdir(test_dir)
    println("Created: " + test_dir)
    
    println("Write test file:")
    fs::write_file(test_dir + "/test.txt", "Hello from GoScript!")
    println("Content written")
    
    println("Read test file:")
    lt content = fs::read_file(test_dir + "/test.txt")
    println("Content: " + content)
    
    println("Clean up:")
    fs::rm_dir(test_dir)
    println("Deleted: " + test_dir)
    
    println("")
    println("✅ All tests completed!")
}
