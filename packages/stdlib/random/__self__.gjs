golem random

pub fn is_int(max: int): int { ret gs_random_int(max) }
pub fn is_string(length: int): string { ret gs_random_string(length) }
pub fn uuid(): string { ret gs_uuid() }
