golem db

pub fn set(file: string, key: string, value: string): bool {
    ret gs_kv_set(file, key, value) == 1
}

pub fn get(file: string, key: string): string {
    ret gs_kv_get(file, key)
}

pub fn exists(file: string, key: string): bool {
    ret gs_kv_exists(file, key) == 1
}

pub fn delete(file: string, key: string): bool {
    ret gs_kv_delete(file, key) == 1
}

pub fn count(file: string): int {
    ret gs_kv_count(file)
}

pub fn search(file: string, pattern: string): string {
    ret gs_kv_search(file, pattern)
}
