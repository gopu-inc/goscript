import tar
import os

fn main() {
    println("--- Testing TarZip Module ---")

    lt source_folder = "lib"
    lt archive_name = "backup_lib.tar.gz"

    // 1. Pack the lib folder
    tar::pack(source_folder, archive_name)

    // 2. Check if it exists using our OS module
    if (os::exists(archive_name) == "True") {
        println("✅ Success: Archive created!")
    } else {
        println("❌ Error: Archive not found.")
    }

    // 3. Optional: Test extraction
    // println("Testing extraction...")
    // tar::unpack(archive_name, "extracted_backup")

    ret 0
}

