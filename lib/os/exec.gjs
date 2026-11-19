golem exec

// Launch one executable directly. This API does not interpret shell syntax.
pub fn command(program: string): string { ret gs_process_run(program) }
pub fn shell(program: string): string { ret gs_process_run(program) }
pub fn background(program: string): bool { ret gs_process_background(program) == 1 }
