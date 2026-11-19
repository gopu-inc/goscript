golem json
pub fn get(data: string, key: string): string { ret gs_json_get(data, key) }
pub fn format(data: string): string { ret gs_json_format(data) }
pub fn is_json(data: string): bool { ret gs_json_is(data) == 1 }
