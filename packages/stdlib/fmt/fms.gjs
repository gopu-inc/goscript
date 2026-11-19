golem fms

pub fn to_str(value: string): string { ret value }
pub fn to_int(value: string): int { ret atoi_c(value) }
pub fn to_float(value: string): float { ret atof_c(value) }
pub fn to_bool(value: string): bool {
    ret value != "" && value != "0" && value != "false" && value != "nil"
}
pub fn is_int(value: string): bool { ret gs_is_integer_text(value) == 1 }
pub fn is_float(value: string): bool { ret gs_is_float_text(value) == 1 }
pub fn is_bool(value: string): bool { ret value == "true" || value == "false" }
