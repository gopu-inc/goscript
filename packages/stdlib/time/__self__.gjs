golem time

pub fn now(): string { ret gs_time_format("%Y-%m-%d %H:%M:%S") }
pub fn timestamp(): int { ret gs_time_epoch() }
pub fn format(format_string: string): string { ret gs_time_format(format_string) }
pub fn sleep(seconds: int) { gs_sleep(seconds) }
