import sys from "./sys"

fn main() {
    println("=== TEST SYS ===\n")
    println("Hostname: " + sys::hostname())
    println("OS: " + sys::os_type())
    println("Arch: " + sys::arch())
    println("Kernel: " + sys::kernel_version())
}
