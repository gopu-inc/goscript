/**
 * tensor.h — API Tensor pour Goscript (Machine Learning)
 * Goscript — GOPU inc.
 *
 * Ce header prépare l'intégration avec OpenBLAS ou GGML
 * pour les calculs de Machine Learning de gopu.inc.
 *
 * Backends supportés :
 *   GS_TENSOR_BACKEND_NAIVE   — implémentation C pure (référence)
 *   GS_TENSOR_BACKEND_OPENBLAS — accélération CPU via OpenBLAS
 *   GS_TENSOR_BACKEND_GGML     — modèles LLM via ggml
 *   GS_TENSOR_BACKEND_CUDA     — GPU NVIDIA (à venir)
 *
 * Usage :
 *   gs_tensor_init(GS_TENSOR_BACKEND_OPENBLAS);
 *
 *   GsTensor* a = gs_tensor_create_2d(3, 4, GS_FLOAT32);
 *   GsTensor* b = gs_tensor_create_2d(4, 2, GS_FLOAT32);
 *   GsTensor* c = gs_tensor_matmul(a, b);
 *   gs_tensor_print(c);
 *   gs_tensor_free(c);
 *   gs_tensor_free(b);
 *   gs_tensor_free(a);
 *   gs_tensor_shutdown();
 */

#ifndef GS_TENSOR_H
#define GS_TENSOR_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 *  TYPES DE DONNÉES
 * ============================================================ */
typedef enum {
    GS_FLOAT32 = 0,   /* float 32 bits (IEEE 754) */
    GS_FLOAT16,       /* half precision (bfloat16 / fp16) */
    GS_FLOAT64,       /* double 64 bits */
    GS_INT8,          /* entier signé 8 bits */
    GS_INT16,         /* entier signé 16 bits */
    GS_INT32,         /* entier signé 32 bits */
    GS_INT64,         /* entier signé 64 bits */
    GS_UINT8,         /* entier non signé 8 bits */
    GS_BOOL,          /* booléen (1 octet) */
    GS_DTYPE_COUNT
} GsDType;

/* Taille en octets d'un dtype */
static inline size_t gs_dtype_size(GsDType dt) {
    static const size_t sizes[GS_DTYPE_COUNT] = {4, 2, 8, 1, 2, 4, 8, 1, 1};
    return (dt < GS_DTYPE_COUNT) ? sizes[dt] : 0;
}

static inline const char* gs_dtype_name(GsDType dt) {
    static const char* names[GS_DTYPE_COUNT] = {
        "float32","float16","float64","int8","int16","int32","int64","uint8","bool"
    };
    return (dt < GS_DTYPE_COUNT) ? names[dt] : "unknown";
}

/* ============================================================
 *  DISPOSITIF DE CALCUL
 * ============================================================ */
typedef enum {
    GS_DEVICE_CPU  = 0,
    GS_DEVICE_CUDA = 1,   /* GPU NVIDIA */
    GS_DEVICE_METAL= 2,   /* GPU Apple Metal */
} GsDevice;

/* ============================================================
 *  STRUCTURE TENSOR (N-dimensionnel)
 *  Représentation en mémoire : row-major (C order), strides explicites.
 * ============================================================ */
#define GS_TENSOR_MAX_DIMS 8

typedef struct GsTensor {
    /* Forme */
    int      ndim;                      /* Nombre de dimensions */
    int64_t  shape[GS_TENSOR_MAX_DIMS]; /* Taille de chaque dimension */
    int64_t  strides[GS_TENSOR_MAX_DIMS]; /* Strides en éléments */
    int64_t  offset;                    /* Offset dans les données */
    int64_t  numel;                     /* Nombre total d'éléments */

    /* Données */
    void*    data;                      /* Pointeur vers les données */
    int      owns_data;                 /* 1 = ce tensor possède les données */

    /* Métadonnées */
    GsDType  dtype;
    GsDevice device;
    char     name[64];                  /* Nom optionnel (debug) */

    /* Gradient (autograd) */
    struct GsTensor* grad;              /* Gradient (si requires_grad) */
    int              requires_grad;

    /* GC */
    int ref_count;
} GsTensor;

/* ============================================================
 *  BACKENDS
 * ============================================================ */
typedef enum {
    GS_TENSOR_BACKEND_NAIVE   = 0,
    GS_TENSOR_BACKEND_OPENBLAS= 1,
    GS_TENSOR_BACKEND_GGML    = 2,
    GS_TENSOR_BACKEND_CUDA    = 3
} GsTensorBackend;

/* ============================================================
 *  INITIALISATION
 * ============================================================ */
int  gs_tensor_init(GsTensorBackend backend);
void gs_tensor_shutdown(void);
GsTensorBackend gs_tensor_active_backend(void);
const char*     gs_tensor_backend_name(GsTensorBackend b);

/* ============================================================
 *  CRÉATION / DESTRUCTION
 * ============================================================ */
GsTensor* gs_tensor_create(int ndim, const int64_t* shape, GsDType dtype, GsDevice dev);
GsTensor* gs_tensor_create_1d(int64_t n, GsDType dtype);
GsTensor* gs_tensor_create_2d(int64_t rows, int64_t cols, GsDType dtype);
GsTensor* gs_tensor_create_3d(int64_t d0, int64_t d1, int64_t d2, GsDType dtype);
GsTensor* gs_tensor_create_4d(int64_t d0, int64_t d1, int64_t d2, int64_t d3, GsDType dtype);

GsTensor* gs_tensor_zeros(int ndim, const int64_t* shape, GsDType dtype);
GsTensor* gs_tensor_ones(int ndim, const int64_t* shape, GsDType dtype);
GsTensor* gs_tensor_rand(int ndim, const int64_t* shape, GsDType dtype);
GsTensor* gs_tensor_full(int ndim, const int64_t* shape, GsDType dtype, double fill_val);
GsTensor* gs_tensor_eye(int64_t n, GsDType dtype);
GsTensor* gs_tensor_arange(double start, double stop, double step, GsDType dtype);

GsTensor* gs_tensor_from_data(const void* data, int ndim, const int64_t* shape, GsDType dtype);
GsTensor* gs_tensor_clone(const GsTensor* t);
GsTensor* gs_tensor_view(GsTensor* t, int ndim, const int64_t* new_shape);

void  gs_tensor_retain(GsTensor* t);
void  gs_tensor_release(GsTensor* t);
#define gs_tensor_free(t) gs_tensor_release(t)

/* ============================================================
 *  ACCÈS AUX DONNÉES
 * ============================================================ */
void*  gs_tensor_data_ptr(GsTensor* t, const int64_t* idx);
float  gs_tensor_get_f32(const GsTensor* t, const int64_t* idx);
void   gs_tensor_set_f32(GsTensor* t, const int64_t* idx, float val);
double gs_tensor_get_f64(const GsTensor* t, const int64_t* idx);
void   gs_tensor_set_f64(GsTensor* t, const int64_t* idx, double val);
int64_t gs_tensor_get_i64(const GsTensor* t, const int64_t* idx);
void    gs_tensor_set_i64(GsTensor* t, const int64_t* idx, int64_t val);

/* Accès 2D raccourcis */
static inline float gs_tensor_at_2d(const GsTensor* t, int64_t r, int64_t c) {
    int64_t idx[2] = {r, c};
    return gs_tensor_get_f32(t, idx);
}

/* ============================================================
 *  ALGÈBRE LINÉAIRE (BLAS niveau 1/2/3)
 * ============================================================ */

/** Produit matriciel : C = A × B (BLAS GEMM) */
GsTensor* gs_tensor_matmul(const GsTensor* a, const GsTensor* b);

/** Produit matriciel avec accumulateur : C = alpha*A*B + beta*C */
void gs_tensor_gemm(GsTensor* c,
                    const GsTensor* a, const GsTensor* b,
                    double alpha, double beta);

/** Produit scalaire (1D) */
double gs_tensor_dot(const GsTensor* a, const GsTensor* b);

/** Norme L2 */
double gs_tensor_norm(const GsTensor* t);

/** Transposition */
GsTensor* gs_tensor_transpose(const GsTensor* t);
GsTensor* gs_tensor_transpose_2d(const GsTensor* t);

/** Inversion de matrice (n×n) */
GsTensor* gs_tensor_inv(const GsTensor* t);

/** Valeurs propres et vecteurs propres */
int gs_tensor_eig(const GsTensor* t, GsTensor** eigenvalues, GsTensor** eigenvectors);

/* ============================================================
 *  OPÉRATIONS ÉLÉMENT PAR ÉLÉMENT
 * ============================================================ */
GsTensor* gs_tensor_add(const GsTensor* a, const GsTensor* b);
GsTensor* gs_tensor_sub(const GsTensor* a, const GsTensor* b);
GsTensor* gs_tensor_mul(const GsTensor* a, const GsTensor* b);  /* Element-wise */
GsTensor* gs_tensor_div(const GsTensor* a, const GsTensor* b);
GsTensor* gs_tensor_pow(const GsTensor* a, double exponent);
GsTensor* gs_tensor_sqrt(const GsTensor* a);
GsTensor* gs_tensor_exp(const GsTensor* a);
GsTensor* gs_tensor_log(const GsTensor* a);
GsTensor* gs_tensor_abs(const GsTensor* a);
GsTensor* gs_tensor_neg(const GsTensor* a);

GsTensor* gs_tensor_add_scalar(const GsTensor* a, double s);
GsTensor* gs_tensor_mul_scalar(const GsTensor* a, double s);

/* Opérations en place */
void gs_tensor_add_inplace(GsTensor* a, const GsTensor* b);
void gs_tensor_mul_inplace(GsTensor* a, double scalar);
void gs_tensor_fill(GsTensor* t, double val);
void gs_tensor_clip(GsTensor* t, double min_val, double max_val);

/* ============================================================
 *  FONCTIONS D'ACTIVATION (Deep Learning)
 * ============================================================ */
GsTensor* gs_tensor_relu(const GsTensor* t);
GsTensor* gs_tensor_relu6(const GsTensor* t);
GsTensor* gs_tensor_sigmoid(const GsTensor* t);
GsTensor* gs_tensor_tanh(const GsTensor* t);
GsTensor* gs_tensor_softmax(const GsTensor* t, int axis);
GsTensor* gs_tensor_log_softmax(const GsTensor* t, int axis);
GsTensor* gs_tensor_gelu(const GsTensor* t);
GsTensor* gs_tensor_silu(const GsTensor* t);      /* Swish */

/* En place */
void gs_tensor_relu_inplace(GsTensor* t);
void gs_tensor_sigmoid_inplace(GsTensor* t);

/* ============================================================
 *  CONVOLUTIONS (CNN)
 * ============================================================ */

/** Convolution 2D (entrée NCHW)
 *  @param input   [N, C_in,  H_in,  W_in]
 *  @param weight  [C_out, C_in, kH, kW]
 *  @param bias    [C_out] ou NULL
 *  @param stride  [stride_H, stride_W]
 *  @param padding [pad_H, pad_W]
 *  @param dilation [dil_H, dil_W]
 *  @return        [N, C_out, H_out, W_out]
 */
GsTensor* gs_tensor_conv2d(const GsTensor* input,
                            const GsTensor* weight,
                            const GsTensor* bias,
                            const int stride[2],
                            const int padding[2],
                            const int dilation[2]);

/** Max Pooling 2D */
GsTensor* gs_tensor_maxpool2d(const GsTensor* input,
                               const int kernel[2],
                               const int stride[2],
                               const int padding[2]);

/** Average Pooling 2D */
GsTensor* gs_tensor_avgpool2d(const GsTensor* input,
                               const int kernel[2],
                               const int stride[2],
                               const int padding[2]);

/** Batch Normalization */
GsTensor* gs_tensor_batchnorm(const GsTensor* input,
                               const GsTensor* mean,
                               const GsTensor* var,
                               const GsTensor* weight,
                               const GsTensor* bias,
                               double eps);

/* ============================================================
 *  RÉDUCTION
 * ============================================================ */
GsTensor* gs_tensor_sum(const GsTensor* t, int axis, int keepdim);
GsTensor* gs_tensor_mean(const GsTensor* t, int axis, int keepdim);
GsTensor* gs_tensor_max(const GsTensor* t, int axis, int keepdim);
GsTensor* gs_tensor_min(const GsTensor* t, int axis, int keepdim);
GsTensor* gs_tensor_argmax(const GsTensor* t, int axis);
GsTensor* gs_tensor_argmin(const GsTensor* t, int axis);
double    gs_tensor_sum_all(const GsTensor* t);
double    gs_tensor_mean_all(const GsTensor* t);

/* ============================================================
 *  MANIPULATION DE FORME
 * ============================================================ */
GsTensor* gs_tensor_reshape(const GsTensor* t, int ndim, const int64_t* new_shape);
GsTensor* gs_tensor_squeeze(const GsTensor* t, int axis);
GsTensor* gs_tensor_unsqueeze(const GsTensor* t, int axis);
GsTensor* gs_tensor_flatten(const GsTensor* t, int start_dim, int end_dim);
GsTensor* gs_tensor_permute(const GsTensor* t, const int* order, int ndim);
GsTensor* gs_tensor_concat(GsTensor** tensors, int count, int axis);
GsTensor* gs_tensor_stack(GsTensor** tensors, int count, int axis);
GsTensor* gs_tensor_split(const GsTensor* t, int chunks, int axis, GsTensor** out);
GsTensor* gs_tensor_slice(const GsTensor* t, int axis, int64_t start, int64_t end, int64_t step);

/* ============================================================
 *  CONVERSION DE TYPES (CAST)
 * ============================================================ */
GsTensor* gs_tensor_cast(const GsTensor* t, GsDType new_dtype);
GsTensor* gs_tensor_to_device(const GsTensor* t, GsDevice dev);

/* ============================================================
 *  SÉRIALISATION / I/O
 * ============================================================ */

/** Sauvegarde binaire (format natif Goscript) */
int gs_tensor_save(const GsTensor* t, const char* path);

/** Chargement depuis le format natif */
GsTensor* gs_tensor_load(const char* path);

/** Export / Import NumPy .npy */
int       gs_tensor_save_npy(const GsTensor* t, const char* path);
GsTensor* gs_tensor_load_npy(const char* path);

/** Affichage lisible */
void gs_tensor_print(const GsTensor* t);
void gs_tensor_print_shape(const GsTensor* t);
char* gs_tensor_to_string(const GsTensor* t);  /* Alloué, à libérer */

/* ============================================================
 *  AUTOGRAD (différentiation automatique — stub)
 * ============================================================ */
void gs_tensor_backward(GsTensor* loss);
void gs_tensor_zero_grad(GsTensor* t);
GsTensor* gs_tensor_detach(const GsTensor* t);

/* ============================================================
 *  INTÉGRATION GGML (LLM — Large Language Models)
 * ============================================================ */
#ifdef GS_WITH_GGML
    #include <ggml.h>

    /** Convertit un GsTensor en ggml_tensor (partage la mémoire si possible) */
    struct ggml_tensor* gs_tensor_to_ggml(struct ggml_context* ctx, const GsTensor* t);

    /** Convertit un ggml_tensor en GsTensor (copie des données) */
    GsTensor* gs_tensor_from_ggml(const struct ggml_tensor* ggml_t);
#endif

/* ============================================================
 *  INTÉGRATION OPENBLAS
 * ============================================================ */
#ifdef GS_WITH_OPENBLAS
    #include <cblas.h>

    /** Active le backend OpenBLAS avec un nombre de threads */
    void gs_tensor_openblas_set_threads(int nthreads);

    /** Retourne la version OpenBLAS */
    const char* gs_tensor_openblas_version(void);
#endif

/* ============================================================
 *  INFORMATIONS DE VERSION
 * ============================================================ */
typedef struct {
    int major, minor, patch;
    const char* build_date;
    int has_openblas;
    int has_ggml;
    int has_cuda;
} GsTensorVersion;

GsTensorVersion gs_tensor_version(void);

#ifdef __cplusplus
}
#endif

#endif /* GS_TENSOR_H */
