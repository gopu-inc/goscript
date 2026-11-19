fn main() {
    lt path = "/tmp/upload.txt"
    if gs_fs_write(path, "test content") == 1 {
        println("Native file upload input prepared: " + path)
    } else {
        println("Could not prepare upload input")
    }
}
