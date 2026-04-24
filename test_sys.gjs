import sys

fn main() {
    println("--- GoScript System Information ---")

    // 1. Platform Info
    lt os_name = sys::platform()
    lt py_ver = sys::version()
    println("OS Platform: " + os_name)
    println("Backend Version: " + py_ver)

    // 2. Command Line Arguments
    println("\nReading arguments...")
    lt args = sys::argv()
    println("Arguments received: " + args)

    // 3. Testing exit (optional)
    // println("Exiting now...")
    // sys::exit(0)

    ret 0
}

