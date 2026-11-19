golem os

pub fn getcwd(): string { ret gs_cwd() }
pub fn list_dir(path: string): string { ret gs_fs_list_dir(path) }
pub fn exists(path: string): bool { ret gs_fs_exists(path) == 1 }
pub fn getenv(name: string): string { ret gs_env_get(name) }
pub fn remove(path: string): bool { ret gs_fs_remove(path) == 1 }
pub fn mkdir(path: string): bool { ret gs_fs_mkdir(path) == 1 }
