# CPU tensor and neural network API

The public C interfaces are in `../tensor.h` and `../nn.h`. Build them into the
Goscript executable with `make`. This first implementation targets a naive CPU
backend.

```c
gs_tensor_init(GS_TENSOR_BACKEND_NAIVE);
GsDense model = {0};
gs_dense_init(&model, 2, 1);
GsDataset* data = gs_dataset_load_numeric("data.jsonl", 2, 1);
if (data) {
    double loss = gs_train_dense_dataset(&model, data, 1000, 0.01);
    gs_dense_save_model(&model, "model.gsm");
    gs_dataset_free(data);
}
gs_dense_free(&model);
```

The loader accepts delimited numeric text and JSONL lines, collecting the first
`input_size + target_size` numeric values per line as features then target.
The model currently contains one dense layer and uses full batch MSE gradient
descent. It is not a schema-aware JSON parser or a multi-layer training API.
