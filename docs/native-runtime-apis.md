# Native Goscript runtime APIs

These names are registered by the runtime for Goscript modules. They replace
shell commands in library sources and pass values as function arguments.

## Files and process information

- `gs_fs_read`, `gs_fs_write`, `gs_fs_append`, `gs_fs_exists`, `gs_fs_size`, `gs_fs_mkdir`, `gs_fs_remove`, `gs_fs_list_dir`
- `gs_cwd`, `gs_env_get`, `gs_platform`, `gs_architecture`, `gs_kernel_release`, `gs_hostname`
- `gs_process_pid`, `gs_process_parent_id`, `gs_process_list`, `gs_process_run`, `gs_process_background`

`gs_process_run` and `gs_process_background` launch one executable directly with no shell parsing. The
`os.exec` wrappers therefore accept a program name or path rather than shell syntax.

## Data and utilities

- `gs_string_*` provides string transforms, trimming, slicing, search, replacement, reverse, and count operations.
- `gs_math_*`, `gs_random_*`, and `gs_time_*` provide math, random, time, and sleep operations.
- `gs_base64_*` and `gs_gzip_*` are implemented in the runtime.
- `gs_json_*` provides JSON string-field lookup, formatting, and a lightweight leading-token check.
- `gs_db_*` exposes SQLite operations through the runtime's SQLite adapter.

## HTTP and archives

`gs_http_*` and `gs_tar_*` provide argument-based adapters. They do not pass
command strings to a shell; the runtime currently delegates HTTP, hashing, and
tar operations to the corresponding system utility.
