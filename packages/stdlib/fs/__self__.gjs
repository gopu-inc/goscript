golem fs

pub cn VERSION = "0.2.0"

pub fn write(path: string, content: string): bool {
    ret gs_fs_write(path, content) == 1
}

pub fn append(path: string, content: string): bool {
    ret gs_fs_append(path, content) == 1
}

pub fn read(path: string): string {
    ret gs_fs_read(path)
}

pub fn size(path: string): int {
    ret gs_fs_size(path)
}

pub fn exists(path: string): bool {
    ret gs_fs_exists(path) == 1
}

pub fn mkdir(path: string): bool {
    ret gs_fs_mkdir(path) == 1
}

pub fn remove(path: string): bool {
    ret gs_fs_remove(path) == 1
}
