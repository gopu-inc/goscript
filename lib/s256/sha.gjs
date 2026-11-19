golem sha
pub fn sha256(value: string): string { ret gs_hash_data(value, "sha256") }
pub fn file_sha256(path: string): string { ret gs_hash_file(path, "sha256") }
