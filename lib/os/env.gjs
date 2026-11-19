golem env

pub fn user(): string { ret gs_env_get("USER") }
pub fn home(): string { ret gs_env_get("HOME") }
pub fn shell(): string { ret gs_env_get("SHELL") }
pub fn pwd(): string { ret gs_cwd() }
pub fn path(): string { ret gs_env_get("PATH") }
pub fn getenv(name: string): string { ret gs_env_get(name) }
