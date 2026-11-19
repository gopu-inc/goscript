golem sys
pub fn argv(): string { ret gs_argv() }
pub fn exit(code: int) { exit_c(code) }
pub fn platform(): string { ret gs_platform() }
pub fn version(): string { ret "0.2.0 (goscript season)" }
