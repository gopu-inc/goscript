// Example: JSONL numeric rows such as {"x":0.5,"y":1.0}.
import nn

fn train(data: string) {
    muts model = nn::dense(1, 1)
    muts loss = nn::train_text(model, data, 1, 1, 500, 0.01)
    println("loss=" + loss)
    nn::save_model(model, "model.gsm")
}

fn main() {
    with open("train.jsonl") as data: train(data)
}
