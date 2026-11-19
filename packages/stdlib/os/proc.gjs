golem proc
pub fn my_pid(): int { ret gs_process_pid() }
pub fn ppid(): int { ret gs_process_parent_id() }
pub fn list(): string { ret gs_process_list() }
