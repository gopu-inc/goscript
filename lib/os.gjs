// lib/os.gjs
module os

// Get current working directory
pub fn getcwd(): string {
    ret sysf("pwd")
}

// List files (Compatible BusyBox / Android)
pub fn list_dir(path: string): string {
    // ls -1 (une colonne) puis tr pour remplacer \n par ", "
    ret sysf("ls -1 " + path + " | tr '\\n' ',' | sed 's/,$//'")
}

// Check if a file or directory exists
pub fn exists(path: string): string {
    ret sysf("[ -e '" + path + "' ] && echo 'True' || echo 'False'")
}

// Get an environment variable
pub fn getenv(name: string): string {
    ret sysf("echo $" + name)
}

// Remove a file or directory
pub fn remove(path: string) {
    sysf("rm -rf " + path)
}

// Create a directory
pub fn mkdir(path: string) {
    sysf("mkdir -p " + path)
}

