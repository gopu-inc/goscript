golem io
pub fn read_file(path: string): string { ret gs_fs_read(path) }
pub fn write_file(path: string, content: string): bool { ret gs_fs_write(path, content) == 1 }
pub fn append_file(path: string, content: string): bool { ret gs_fs_append(path, content) == 1 }
