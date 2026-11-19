golem which

pub fn find(name: string): string { ret gs_which(name) }
pub fn exists(name: string): bool { ret gs_which(name) != "" }
