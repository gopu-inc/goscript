golem nn

pub fn dense(input_size: int, output_size: int): int {
    ret model_create(input_size, output_size)
}
pub fn forward(model: int, inputs: int): int { ret model_forward(model, inputs) }
pub fn forward_activation(model: int, inputs: int, activation: int): int {
    ret model_forward_activation(model, inputs, activation)
}
pub fn train_file(model: int, path: string, input_size: int, target_size: int,
                  epochs: int, learning_rate: float): float {
    ret model_train_file(model, path, input_size, target_size, epochs, learning_rate)
}
pub fn train_text(model: int, source: string, input_size: int, target_size: int,
                  epochs: int, learning_rate: float): float {
    ret model_train_text(model, source, input_size, target_size, epochs, learning_rate)
}
pub fn save_model(model: int, path: string): int { ret model_save_native(model, path) }
