#ifndef GS_NN_H
#define GS_NN_H
#include "tensor.h"

typedef struct {
    int input_size, output_size;
    GsTensor* weights; /* [input, output] */
    GsTensor* bias;    /* [output] */
} GsDense;
typedef enum { GS_ACT_LINEAR=0, GS_ACT_RELU=1, GS_ACT_SIGMOID=2, GS_ACT_TANH=3 } GsActivation;
typedef struct { GsTensor* inputs; GsTensor* targets; int rows; int input_size; int target_size; } GsDataset;

int gs_dense_init(GsDense* layer, int input_size, int output_size);
void gs_dense_free(GsDense* layer);
GsTensor* gs_dense_forward(const GsDense* layer, const GsTensor* input, GsActivation activation);
double gs_train_dense_mse(GsDense* layer, const GsTensor* inputs,
                          const GsTensor* targets, int epochs, double learning_rate);
int gs_dense_save(const GsDense* layer, const char* path);
int gs_dense_load(GsDense* layer, const char* path);
int gs_dense_save_model(const GsDense* layer, const char* path);
int gs_dense_load_model(GsDense* layer, const char* path);
GsDataset* gs_dataset_load_numeric(const char* path, int input_size, int target_size);
void gs_dataset_free(GsDataset* dataset);
double gs_train_dense_dataset(GsDense* layer, const GsDataset* dataset,
                              int epochs, double learning_rate);

#endif
