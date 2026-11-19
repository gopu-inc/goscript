golem math

pub fn sqrt(value: float): float { ret gs_math_sqrt(value) }
pub fn pow(value: float, exponent: float): float { ret gs_math_pow(value, exponent) }
pub fn round(value: float): int { ret gs_math_round(value) }
pub fn abs(value: float): float { ret gs_math_abs(value) }
pub fn random(max: int): int { ret gs_random_int(max) }
