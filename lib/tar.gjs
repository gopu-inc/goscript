// lib/tar.gjs
module tar

// Pack a directory or file: tar -czf output.tar.gz source
pub fn pack(source: string, output: string) {
    println(" Archiving: " + source + " -> " + output)
    sysf("tar -czf " + output + " " + source)
}

// Unpack an archive: tar -xzf archive.tar.gz
pub fn unpack(archive: string, destination: string) {
    println(" Extracting: " + archive + " to " + destination)
    // On s'assure que le dossier de destination existe, puis on extrait
    sysf("mkdir -p " + destination + " && tar -xzf " + archive + " -C " + destination)
}

