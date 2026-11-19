golem os_info
pub fn version(): string { ret gs_kernel_release() }
pub fn name(): string { ret gs_platform() }
pub fn arch(): string { ret gs_architecture() }
pub fn hostname(): string { ret gs_hostname() }
pub fn user(): string { ret gs_current_user() }
pub fn uptime(): string { ret gs_system_uptime() }
pub fn datetime(): string { ret gs_time_format("%Y-%m-%d %H:%M:%S") }
pub fn timestamp(): int { ret gs_time_epoch() }
pub fn pid(): int { ret gs_process_pid() }
pub fn getenv(key: string): string { ret gs_env_get(key) }
pub fn cwd(): string { ret gs_cwd() }
pub fn home(): string { ret gs_env_get("HOME") }
pub fn temp(): string { ret gs_temp_dir() }
