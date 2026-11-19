fn main() {
    lt path = "/tmp/goscript-native-api-check.txt"
    if gs_fs_write(path, "native API") != 1 {
        println("Native filesystem API check failed")
        ret
    }
    println("Native filesystem API check passed: " + gs_fs_read(path))
}
