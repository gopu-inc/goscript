// lib/sys.gjs
module sys

// Get the list of command line arguments
pub fn argv(): string {
    // Returns arguments as a comma-separated string
    lt py_code = "import sys; print(', '.join(sys.argv))"
    ret sysf("python3 -c \"" + py_code + "\"")
}

// Exit the script with a specific status code
pub fn exit(code: int) {
    lt py_code = "import sys; sys.exit(" + code + ")"
    sysf("python3 -c \"" + py_code + "\"")
}

// Get Python/System platform (linux, darwin, win32)
pub fn platform(): string {
    lt py_code = "import sys; print(sys.platform)"
    ret sysf("python3 -c \"" + py_code + "\"")
}

// Get Python version powering GoScript's backend
pub fn version(): string {
    ver = "0.2.0 (goscript season)"
    ret ver
}

