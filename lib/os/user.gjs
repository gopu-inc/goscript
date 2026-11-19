golem user
pub fn current(): string { ret gs_current_user() }
pub fn id(): string { ret gs_user_id() }
pub fn groups(): string { ret gs_user_groups() }
pub fn users_list(): string { ret gs_users_list() }
pub fn is_root(): bool { ret gs_is_root() == 1 }
