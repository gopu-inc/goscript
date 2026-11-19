golem sys
pub fn hostname(): string { ret gs_hostname() }
pub fn os_type(): string { ret gs_platform() }
pub fn arch(): string { ret gs_architecture() }
pub fn kernel_version(): string { ret gs_kernel_release() }
