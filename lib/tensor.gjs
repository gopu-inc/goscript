golem tensor

// Handles natifs gérés par le runtime; dimensions 2D pour cette API initiale.
pub fn zeros(rows: int, columns: int): int { ret tensor_zeros(rows, columns) }
pub fn rand(rows: int, columns: int): int { ret tensor_rand(rows, columns) }
pub fn set(tensor_id: int, row: int, column: int, value: float): int {
    ret tensor_set(tensor_id, row, column, value)
}
pub fn get(tensor_id: int, row: int, column: int): float {
    ret tensor_get(tensor_id, row, column)
}
pub fn add(left: int, right: int): int { ret tensor_add(left, right) }
pub fn multiply(left: int, right: int): int { ret tensor_mul(left, right) }
pub fn matmul(left: int, right: int): int { ret tensor_matmul(left, right) }
pub fn relu(value: int): int { ret tensor_relu(value) }
pub fn sigmoid(value: int): int { ret tensor_sigmoid(value) }
pub fn require_grad(value: int): int { ret tensor_require_grad(value) }
pub fn backward(value: int): int { ret tensor_backward(value) }
pub fn grad(value: int): int { ret tensor_grad(value) }
pub fn save(value: int, path: string): int { ret tensor_save(value, path) }
pub fn release(value: int): int { ret tensor_release(value) }
