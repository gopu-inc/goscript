#include "tensor.h"
#include "interpreter/interpreter.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Portable row-major CPU reference backend. All operators fail explicitly on
 * incompatible shapes; this backend deliberately does not pretend to support
 * CUDA/OpenBLAS/GGML when they were not compiled in. */
static GsTensorBackend active_backend = GS_TENSOR_BACKEND_NAIVE;
static char tensor_error[256];
static unsigned rng_state = 0x9e3779b9u;

static void set_error(const char* message) {
    snprintf(tensor_error, sizeof(tensor_error), "%s", message ? message : "tensor error");
}
const char* gs_tensor_last_error(void) { return tensor_error; }

static int64_t elem_count(int ndim, const int64_t* shape) {
    if (ndim < 1 || ndim > GS_TENSOR_MAX_DIMS || !shape) return -1;
    int64_t n = 1;
    for (int i = 0; i < ndim; ++i) {
        if (shape[i] < 0 || (shape[i] && n > INT64_MAX / shape[i])) return -1;
        n *= shape[i];
    }
    return n;
}
static size_t elem_offset(const GsTensor* t, const int64_t* idx) {
    int64_t off = t->offset;
    for (int i = 0; i < t->ndim; ++i) off += idx[i] * t->strides[i];
    return (size_t)off;
}
static double read_at(const GsTensor* t, size_t i) {
    if (!t || !t->data) return 0.0;
    switch (t->dtype) {
        case GS_FLOAT32: return ((float*)t->data)[i];
        case GS_FLOAT64: return ((double*)t->data)[i];
        case GS_INT8: return ((int8_t*)t->data)[i];
        case GS_INT16: return ((int16_t*)t->data)[i];
        case GS_INT32: return ((int32_t*)t->data)[i];
        case GS_INT64: return (double)((int64_t*)t->data)[i];
        case GS_UINT8: return ((uint8_t*)t->data)[i];
        case GS_BOOL: return ((uint8_t*)t->data)[i] != 0;
        case GS_FLOAT16: default: return 0.0; /* fp16 conversion is not available yet */
    }
}
static void write_at(GsTensor* t, size_t i, double v) {
    if (!t || !t->data) return;
    switch (t->dtype) {
        case GS_FLOAT32: ((float*)t->data)[i] = (float)v; break;
        case GS_FLOAT64: ((double*)t->data)[i] = v; break;
        case GS_INT8: ((int8_t*)t->data)[i] = (int8_t)v; break;
        case GS_INT16: ((int16_t*)t->data)[i] = (int16_t)v; break;
        case GS_INT32: ((int32_t*)t->data)[i] = (int32_t)v; break;
        case GS_INT64: ((int64_t*)t->data)[i] = (int64_t)v; break;
        case GS_UINT8: ((uint8_t*)t->data)[i] = (uint8_t)v; break;
        case GS_BOOL: ((uint8_t*)t->data)[i] = v != 0.0; break;
        case GS_FLOAT16: default: break;
    }
}
static void unravel(const GsTensor* t, int64_t flat, int64_t* idx) {
    for (int i = t->ndim - 1; i >= 0; --i) {
        idx[i] = t->shape[i] ? flat % t->shape[i] : 0;
        if (t->shape[i]) flat /= t->shape[i];
    }
}
static GsTensor* alloc_tensor(int ndim, const int64_t* shape, GsDType dtype) {
    int64_t n = elem_count(ndim, shape);
    size_t width = gs_dtype_size(dtype);
    if (n < 0 || !width || dtype == GS_FLOAT16) { set_error("invalid shape or unsupported dtype"); return NULL; }
    GsTensor* t = calloc(1, sizeof(*t));
    if (!t) { set_error("out of memory allocating tensor"); return NULL; }
    t->ndim = ndim; t->numel = n; t->dtype = dtype; t->device = GS_DEVICE_CPU;
    t->owns_data = 1; t->ref_count = 1;
    for (int i = 0; i < ndim; ++i) t->shape[i] = shape[i];
    int64_t stride = 1;
    for (int i = ndim - 1; i >= 0; --i) { t->strides[i] = stride; stride *= shape[i]; }
    t->data = n ? calloc((size_t)n, width) : NULL;
    if (n && !t->data) { free(t); set_error("out of memory allocating tensor data"); return NULL; }
    return t;
}
static void attach_graph(GsTensor* out, int op, const GsTensor* a, const GsTensor* b) {
    if (!out) return;
    out->requires_grad = (a && a->requires_grad) || (b && b->requires_grad);
    if (!out->requires_grad) return;
    out->grad_op = op;
    out->grad_input_a = (GsTensor*)a;
    out->grad_input_b = (GsTensor*)b;
    if (out->grad_input_a) gs_tensor_retain(out->grad_input_a);
    if (out->grad_input_b) gs_tensor_retain(out->grad_input_b);
}

int gs_tensor_init(GsTensorBackend backend) {
    if (backend != GS_TENSOR_BACKEND_NAIVE) { set_error("requested tensor backend was not compiled in"); return 0; }
    active_backend = backend; tensor_error[0] = 0; return 1;
}
void gs_tensor_shutdown(void) { }
GsTensorBackend gs_tensor_active_backend(void) { return active_backend; }
const char* gs_tensor_backend_name(GsTensorBackend b) { return b == GS_TENSOR_BACKEND_NAIVE ? "naive-cpu" : "unavailable"; }
GsTensor* gs_tensor_create(int ndim, const int64_t* shape, GsDType dtype, GsDevice dev) {
    if (dev != GS_DEVICE_CPU) { set_error("only CPU tensors are available"); return NULL; }
    return alloc_tensor(ndim, shape, dtype);
}
GsTensor* gs_tensor_create_1d(int64_t n, GsDType d) { return gs_tensor_create(1, &n, d, GS_DEVICE_CPU); }
GsTensor* gs_tensor_create_2d(int64_t r, int64_t c, GsDType d) { int64_t s[2]={r,c}; return gs_tensor_create(2,s,d,GS_DEVICE_CPU); }
GsTensor* gs_tensor_create_3d(int64_t a,int64_t b,int64_t c,GsDType d) { int64_t s[3]={a,b,c}; return gs_tensor_create(3,s,d,GS_DEVICE_CPU); }
GsTensor* gs_tensor_create_4d(int64_t a,int64_t b,int64_t c,int64_t d0,GsDType d) { int64_t s[4]={a,b,c,d0}; return gs_tensor_create(4,s,d,GS_DEVICE_CPU); }
GsTensor* gs_tensor_full(int n,const int64_t* s,GsDType d,double v) { GsTensor* t=gs_tensor_create(n,s,d,GS_DEVICE_CPU); if(t) gs_tensor_fill(t,v); return t; }
GsTensor* gs_tensor_zeros(int n,const int64_t* s,GsDType d) { return gs_tensor_full(n,s,d,0); }
GsTensor* gs_tensor_ones(int n,const int64_t* s,GsDType d) { return gs_tensor_full(n,s,d,1); }
GsTensor* gs_tensor_rand(int n,const int64_t* s,GsDType d) {
    GsTensor* t=gs_tensor_create(n,s,d,GS_DEVICE_CPU); if(!t) return NULL;
    for(int64_t i=0;i<t->numel;i++){ rng_state ^= rng_state<<13; rng_state ^= rng_state>>17; rng_state ^= rng_state<<5; write_at(t,(size_t)i,(double)(rng_state&0xffffff)/16777216.0*2.0-1.0); }
    return t;
}
GsTensor* gs_tensor_eye(int64_t n,GsDType d) { GsTensor* t=gs_tensor_zeros(2,(int64_t[]){n,n},d); if(t) for(int64_t i=0;i<n;i++) write_at(t,(size_t)(i*n+i),1); return t; }
GsTensor* gs_tensor_arange(double a,double b,double step,GsDType d) { if(step==0){set_error("arange step cannot be zero");return NULL;} int64_t n=(int64_t)ceil((b-a)/step); if(n<0)n=0; GsTensor*t=gs_tensor_create_1d(n,d); if(t)for(int64_t i=0;i<n;i++)write_at(t,i,a+i*step);return t; }
GsTensor* gs_tensor_from_data(const void* data,int n,const int64_t*s,GsDType d) { GsTensor*t=gs_tensor_create(n,s,d,GS_DEVICE_CPU); if(t&&data)memcpy(t->data,data,(size_t)t->numel*gs_dtype_size(d)); return t; }
GsTensor* gs_tensor_clone(const GsTensor*t) { if(!t)return NULL; GsTensor*out=gs_tensor_create(t->ndim,t->shape,t->dtype,GS_DEVICE_CPU); if(!out)return NULL; int64_t idx[GS_TENSOR_MAX_DIMS]; for(int64_t i=0;i<t->numel;i++){unravel(t,i,idx);write_at(out,i,read_at(t,elem_offset(t,idx)));} out->requires_grad=t->requires_grad; return out; }
GsTensor* gs_tensor_view(GsTensor*t,int n,const int64_t*s) { if(!t||elem_count(n,s)!=t->numel){set_error("view must preserve element count");return NULL;} GsTensor*out=calloc(1,sizeof(*out));if(!out)return NULL;out->ndim=n;out->numel=t->numel;out->dtype=t->dtype;out->device=t->device;out->data=t->data;out->owns_data=0;out->storage_owner=t;out->ref_count=1;gs_tensor_retain(t);for(int i=0;i<n;i++)out->shape[i]=s[i];int64_t st=1;for(int i=n-1;i>=0;i--){out->strides[i]=st;st*=s[i];}return out; }
void gs_tensor_retain(GsTensor*t){if(t)t->ref_count++;}
void gs_tensor_release(GsTensor*t){if(!t||--t->ref_count>0)return;gs_tensor_release(t->grad);gs_tensor_release(t->grad_input_a);gs_tensor_release(t->grad_input_b);gs_tensor_release(t->storage_owner);if(t->owns_data)free(t->data);free(t);}
void* gs_tensor_data_ptr(GsTensor*t,const int64_t*idx){return t&&idx?(char*)t->data+elem_offset(t,idx)*gs_dtype_size(t->dtype):NULL;}
float gs_tensor_get_f32(const GsTensor*t,const int64_t*i){return (float)(t&&i?read_at(t,elem_offset(t,i)):0);}
void gs_tensor_set_f32(GsTensor*t,const int64_t*i,float v){if(t&&i)write_at(t,elem_offset(t,i),v);}
double gs_tensor_get_f64(const GsTensor*t,const int64_t*i){return t&&i?read_at(t,elem_offset(t,i)):0;}
void gs_tensor_set_f64(GsTensor*t,const int64_t*i,double v){if(t&&i)write_at(t,elem_offset(t,i),v);}
int64_t gs_tensor_get_i64(const GsTensor*t,const int64_t*i){return (int64_t)gs_tensor_get_f64(t,i);}
void gs_tensor_set_i64(GsTensor*t,const int64_t*i,int64_t v){gs_tensor_set_f64(t,i,(double)v);}

static GsTensor* elemwise(const GsTensor*a,const GsTensor*b,int op){
    if(!a||!b||a->ndim!=b->ndim||memcmp(a->shape,b->shape,(size_t)a->ndim*sizeof(int64_t))){set_error("elementwise operands must have identical shapes");return NULL;}
    GsTensor*out=gs_tensor_create(a->ndim,a->shape,GS_FLOAT32,GS_DEVICE_CPU);if(!out)return NULL;int64_t ia[GS_TENSOR_MAX_DIMS],ib[GS_TENSOR_MAX_DIMS];
    for(int64_t k=0;k<a->numel;k++){unravel(a,k,ia);unravel(b,k,ib);double x=read_at(a,elem_offset(a,ia)),y=read_at(b,elem_offset(b,ib));if(op==GS_AUTOGRAD_DIV&&y==0){gs_tensor_release(out);set_error("division by zero");return NULL;}double z=op==GS_AUTOGRAD_ADD?x+y:op==GS_AUTOGRAD_SUB?x-y:op==GS_AUTOGRAD_MUL?x*y:x/y;write_at(out,k,z);}
    attach_graph(out,op,a,b);return out;
}
GsTensor*gs_tensor_add(const GsTensor*a,const GsTensor*b){return elemwise(a,b,GS_AUTOGRAD_ADD);} GsTensor*gs_tensor_sub(const GsTensor*a,const GsTensor*b){return elemwise(a,b,GS_AUTOGRAD_SUB);} GsTensor*gs_tensor_mul(const GsTensor*a,const GsTensor*b){return elemwise(a,b,GS_AUTOGRAD_MUL);} GsTensor*gs_tensor_div(const GsTensor*a,const GsTensor*b){return elemwise(a,b,GS_AUTOGRAD_DIV);}
GsTensor*gs_tensor_pow(const GsTensor*a,double e){if(!a)return NULL;GsTensor*out=gs_tensor_create(a->ndim,a->shape,GS_FLOAT32,GS_DEVICE_CPU);if(out)for(int64_t i=0;i<a->numel;i++)write_at(out,i,pow(read_at(a,(size_t)i),e));return out;}
static GsTensor* unary(const GsTensor*a,int op){if(!a)return NULL;GsTensor*out=gs_tensor_create(a->ndim,a->shape,GS_FLOAT32,GS_DEVICE_CPU);if(!out)return NULL;for(int64_t i=0;i<a->numel;i++){double x=read_at(a,(size_t)i),y=x;if(op==1)y=sqrt(x);if(op==2)y=exp(x);if(op==3)y=log(x);if(op==4)y=fabs(x);if(op==5)y=-x;if(op==6)y=x>0?x:0;if(op==7)y=1/(1+exp(-x));if(op==8)y=tanh(x);write_at(out,i,y);}int g=op==5?GS_AUTOGRAD_NEG:op==6?GS_AUTOGRAD_RELU:op==7?GS_AUTOGRAD_SIGMOID:op==8?GS_AUTOGRAD_TANH:0;if(g)attach_graph(out,g,a,NULL);return out;}
GsTensor*gs_tensor_sqrt(const GsTensor*a){return unary(a,1);} GsTensor*gs_tensor_exp(const GsTensor*a){return unary(a,2);} GsTensor*gs_tensor_log(const GsTensor*a){return unary(a,3);} GsTensor*gs_tensor_abs(const GsTensor*a){return unary(a,4);} GsTensor*gs_tensor_neg(const GsTensor*a){return unary(a,5);} GsTensor*gs_tensor_relu(const GsTensor*a){return unary(a,6);} GsTensor*gs_tensor_sigmoid(const GsTensor*a){return unary(a,7);} GsTensor*gs_tensor_tanh(const GsTensor*a){return unary(a,8);}
GsTensor*gs_tensor_add_scalar(const GsTensor*a,double s){if(!a)return NULL;GsTensor*out=gs_tensor_clone(a);if(out){for(int64_t i=0;i<out->numel;i++)write_at(out,i,read_at(out,i)+s);out->requires_grad=0;}return out;} GsTensor*gs_tensor_mul_scalar(const GsTensor*a,double s){if(!a)return NULL;GsTensor*out=gs_tensor_create(a->ndim,a->shape,GS_FLOAT32,GS_DEVICE_CPU);if(out)for(int64_t i=0;i<a->numel;i++)write_at(out,i,read_at(a,i)*s);return out;}
void gs_tensor_fill(GsTensor*t,double v){if(t)for(int64_t i=0;i<t->numel;i++)write_at(t,i,v);} void gs_tensor_mul_inplace(GsTensor*t,double s){if(t)for(int64_t i=0;i<t->numel;i++)write_at(t,i,read_at(t,i)*s);} void gs_tensor_add_inplace(GsTensor*a,const GsTensor*b){if(a&&b&&a->numel==b->numel)for(int64_t i=0;i<a->numel;i++)write_at(a,i,read_at(a,i)+read_at(b,i));} void gs_tensor_clip(GsTensor*t,double lo,double hi){if(t)for(int64_t i=0;i<t->numel;i++){double x=read_at(t,i);write_at(t,i,x<lo?lo:x>hi?hi:x);}}
GsTensor*gs_tensor_matmul(const GsTensor*a,const GsTensor*b){if(!a||!b||a->ndim!=2||b->ndim!=2||a->shape[1]!=b->shape[0]){set_error("matmul requires [m,k] and [k,n]");return NULL;}GsTensor*out=gs_tensor_zeros(2,(int64_t[]){a->shape[0],b->shape[1]},GS_FLOAT32);if(!out)return NULL;for(int64_t i=0;i<a->shape[0];i++)for(int64_t j=0;j<b->shape[1];j++){double s=0;for(int64_t k=0;k<a->shape[1];k++)s+=read_at(a,(size_t)(i*a->strides[0]+k*a->strides[1]))*read_at(b,(size_t)(k*b->strides[0]+j*b->strides[1]));write_at(out,(size_t)(i*out->shape[1]+j),s);}attach_graph(out,GS_AUTOGRAD_MATMUL,a,b);return out;}
void gs_tensor_gemm(GsTensor*c,const GsTensor*a,const GsTensor*b,double alpha,double beta){GsTensor*p=gs_tensor_matmul(a,b);if(c&&p&&c->numel==p->numel)for(int64_t i=0;i<c->numel;i++)write_at(c,i,alpha*read_at(p,i)+beta*read_at(c,i));gs_tensor_release(p);}
double gs_tensor_dot(const GsTensor*a,const GsTensor*b){if(!a||!b||a->numel!=b->numel){set_error("dot operands must have same element count");return 0;}double s=0;for(int64_t i=0;i<a->numel;i++)s+=read_at(a,i)*read_at(b,i);return s;} double gs_tensor_sum_all(const GsTensor*t){double s=0;if(t)for(int64_t i=0;i<t->numel;i++)s+=read_at(t,i);return s;} double gs_tensor_mean_all(const GsTensor*t){return t&&t->numel?gs_tensor_sum_all(t)/t->numel:0;} double gs_tensor_norm(const GsTensor*t){return t?sqrt(gs_tensor_dot(t,t)):0;}
GsTensor*gs_tensor_transpose_2d(const GsTensor*t){if(!t||t->ndim!=2)return NULL;GsTensor*out=gs_tensor_create_2d(t->shape[1],t->shape[0],t->dtype);if(out)for(int64_t i=0;i<t->shape[0];i++)for(int64_t j=0;j<t->shape[1];j++)write_at(out,(size_t)(j*out->shape[1]+i),read_at(t,(size_t)(i*t->strides[0]+j*t->strides[1])));return out;} GsTensor*gs_tensor_transpose(const GsTensor*t){return gs_tensor_transpose_2d(t);}
GsTensor*gs_tensor_sum(const GsTensor*t,int axis,int keep){if(!t||axis<0||axis>=t->ndim)return NULL;int64_t shape[GS_TENSOR_MAX_DIMS];int nd=t->ndim-(keep?0:1);for(int i=0,j=0;i<t->ndim;i++){if(i==axis){if(keep)shape[j++]=1;}else shape[j++]=t->shape[i];}if(nd==0){shape[0]=1;nd=1;}GsTensor*out=gs_tensor_zeros(nd,shape,GS_FLOAT32);if(!out)return NULL;int64_t idx[GS_TENSOR_MAX_DIMS],oi[GS_TENSOR_MAX_DIMS];for(int64_t k=0;k<t->numel;k++){unravel(t,k,idx);for(int i=0,j=0;i<t->ndim;i++)if(i!=axis)oi[j++]=idx[i];else if(keep)oi[j++]=0;int64_t flat=0;for(int i=0;i<nd;i++)flat=flat*out->shape[i]+oi[i];write_at(out,flat,read_at(out,flat)+read_at(t,elem_offset(t,idx)));}attach_graph(out,GS_AUTOGRAD_SUM,t,NULL);out->grad_axis=axis;return out;}
GsTensor*gs_tensor_mean(const GsTensor*t,int axis,int keep){GsTensor*out=gs_tensor_sum(t,axis,keep);if(out&&t&&t->shape[axis]){for(int64_t i=0;i<out->numel;i++)write_at(out,i,read_at(out,i)/t->shape[axis]);out->grad_op=GS_AUTOGRAD_MEAN;out->grad_axis=axis;}return out;}
void gs_tensor_zero_grad(GsTensor*t){if(t&&t->grad)gs_tensor_fill(t->grad,0);}
GsTensor*gs_tensor_detach(const GsTensor*t){GsTensor*out=gs_tensor_clone(t);if(out){out->requires_grad=0;out->grad_op=GS_AUTOGRAD_NONE;}return out;}
static void topo_visit(GsTensor*t,GsTensor***list,int*n,int*cap){if(!t)return;for(int i=0;i<*n;i++)if((*list)[i]==t)return;topo_visit(t->grad_input_a,list,n,cap);topo_visit(t->grad_input_b,list,n,cap);if(*n==*cap){*cap=*cap?*cap*2:32;*list=realloc(*list,(size_t)*cap*sizeof(**list));}(*list)[(*n)++]=t;}
static void grad_add(GsTensor*t,int64_t i,double v){if(!t||!t->requires_grad)return;if(!t->grad)t->grad=gs_tensor_zeros(t->ndim,t->shape,GS_FLOAT32);if(t->grad)write_at(t->grad,i,read_at(t->grad,i)+v);}
void gs_tensor_backward(GsTensor*loss){if(!loss||!loss->requires_grad){set_error("backward requires a result connected to a grad-enabled tensor");return;}GsTensor**list=NULL;int n=0,cap=0;topo_visit(loss,&list,&n,&cap);for(int i=0;i<n;i++){gs_tensor_release(list[i]->grad);list[i]->grad=NULL;}loss->grad=gs_tensor_ones(loss->ndim,loss->shape,GS_FLOAT32);for(int q=n-1;q>=0;q--){GsTensor*t=list[q],*a=t->grad_input_a,*b=t->grad_input_b;if(!t->grad||!a)continue;switch(t->grad_op){case GS_AUTOGRAD_ADD:case GS_AUTOGRAD_SUB:case GS_AUTOGRAD_MUL:case GS_AUTOGRAD_DIV:for(int64_t i=0;i<t->grad->numel;i++){double g=read_at(t->grad,i),x=read_at(a,i),y=b?read_at(b,i):0;if(t->grad_op==GS_AUTOGRAD_ADD){grad_add(a,i,g);grad_add(b,i,g);}else if(t->grad_op==GS_AUTOGRAD_SUB){grad_add(a,i,g);grad_add(b,i,-g);}else if(t->grad_op==GS_AUTOGRAD_MUL){grad_add(a,i,g*y);grad_add(b,i,g*x);}else{grad_add(a,i,g/y);grad_add(b,i,-g*x/(y*y));}}break;case GS_AUTOGRAD_NEG:case GS_AUTOGRAD_RELU:case GS_AUTOGRAD_SIGMOID:case GS_AUTOGRAD_TANH:for(int64_t i=0;i<t->grad->numel;i++){double g=read_at(t->grad,i),v=read_at(a,i);if(t->grad_op==GS_AUTOGRAD_NEG)g=-g;else if(t->grad_op==GS_AUTOGRAD_RELU&&v<=0)g=0;else if(t->grad_op==GS_AUTOGRAD_SIGMOID){double y=read_at(t,i);g*=y*(1-y);}else if(t->grad_op==GS_AUTOGRAD_TANH){double y=read_at(t,i);g*=1-y*y;}grad_add(a,i,g);}break;case GS_AUTOGRAD_SUM:case GS_AUTOGRAD_MEAN:{int axis=t->grad_axis;int64_t ix[GS_TENSOR_MAX_DIMS],ox[GS_TENSOR_MAX_DIMS];for(int64_t i=0;i<a->numel;i++){unravel(a,i,ix);for(int d=0,j=0;d<a->ndim;d++)if(d!=axis)ox[j++]=ix[d];else if(t->ndim==a->ndim)ox[j++]=0;int64_t oi=0;for(int d=0;d<t->ndim;d++)oi=oi*t->shape[d]+ox[d];double g=read_at(t->grad,oi);if(t->grad_op==GS_AUTOGRAD_MEAN)g/=a->shape[axis];grad_add(a,i,g);}break;}case GS_AUTOGRAD_MATMUL:{int64_t m=a->shape[0],k=a->shape[1],nn=b->shape[1];for(int64_t r=0;r<m;r++)for(int64_t c=0;c<k;c++){double z=0;for(int64_t j=0;j<nn;j++)z+=read_at(t->grad,(size_t)(r*nn+j))*read_at(b,(size_t)(c*nn+j));grad_add(a,r*k+c,z);}for(int64_t r=0;r<k;r++)for(int64_t c=0;c<nn;c++){double z=0;for(int64_t i=0;i<m;i++)z+=read_at(a,(size_t)(i*k+r))*read_at(t->grad,(size_t)(i*nn+c));grad_add(b,r*nn+c,z);}break;}default:break;}}free(list);}
int gs_tensor_save(const GsTensor*t,const char*path){if(!t||!path)return 0;FILE*f=fopen(path,"wb");if(!f)return 0;uint32_t magic=0x47535431;int32_t n=t->ndim,d=t->dtype;int ok=fwrite(&magic,4,1,f)==1&&fwrite(&n,4,1,f)==1&&fwrite(&d,4,1,f)==1&&fwrite(t->shape,8,(size_t)n,f)==(size_t)n;for(int64_t i=0;ok&&i<t->numel;i++){double x=read_at(t,(size_t)i);ok=fwrite(&x,sizeof(x),1,f)==1;}if(fclose(f)!=0)ok=0;return ok;}
GsTensor*gs_tensor_load(const char*path){FILE*f=fopen(path,"rb");if(!f)return NULL;uint32_t magic;int32_t n,d;int64_t s[GS_TENSOR_MAX_DIMS];if(fread(&magic,4,1,f)!=1||magic!=0x47535431||fread(&n,4,1,f)!=1||fread(&d,4,1,f)!=1||n<1||n>GS_TENSOR_MAX_DIMS||fread(s,8,(size_t)n,f)!=(size_t)n){fclose(f);set_error("invalid tensor file");return NULL;}GsTensor*t=gs_tensor_create(n,s,(GsDType)d,GS_DEVICE_CPU);if(t)for(int64_t i=0;i<t->numel;i++){double x;if(fread(&x,sizeof(x),1,f)!=1){gs_tensor_release(t);t=NULL;set_error("truncated tensor file");break;}write_at(t,(size_t)i,x);}fclose(f);return t;}
void gs_tensor_print_shape(const GsTensor*t){if(!t)return;printf("[");for(int i=0;i<t->ndim;i++)printf("%s%lld",i?",":"",(long long)t->shape[i]);printf("] %s\n",gs_dtype_name(t->dtype));}
void gs_tensor_print(const GsTensor*t){if(!t)return;gs_tensor_print_shape(t);for(int64_t i=0;i<t->numel;i++)printf("%s%.6g",i?" ":"",read_at(t,(size_t)i));printf("\n");}
char*gs_tensor_to_string(const GsTensor*t){if(!t)return strdup("<null tensor>");char buf[128];snprintf(buf,sizeof(buf),"Tensor(ndim=%d, numel=%lld, dtype=%s)",t->ndim,(long long)t->numel,gs_dtype_name(t->dtype));return strdup(buf);}
GsTensorVersion gs_tensor_version(void){GsTensorVersion v={0,1,0,__DATE__,0,0,0};return v;}

static GsTensor* reduce_extreme(const GsTensor*t,int axis,int is_max){
    if(!t||axis<0||axis>=t->ndim)return NULL;int64_t shape[GS_TENSOR_MAX_DIMS];int nd=t->ndim-1;if(nd==0){nd=1;shape[0]=1;}else for(int i=0,j=0;i<t->ndim;i++)if(i!=axis)shape[j++]=t->shape[i];
    GsTensor*out=gs_tensor_create(nd,shape,GS_FLOAT32,GS_DEVICE_CPU);if(!out)return NULL;for(int64_t i=0;i<out->numel;i++)write_at(out,i,is_max?-INFINITY:INFINITY);
    int64_t idx[GS_TENSOR_MAX_DIMS],oi[GS_TENSOR_MAX_DIMS];for(int64_t k=0;k<t->numel;k++){unravel(t,k,idx);for(int i=0,j=0;i<t->ndim;i++)if(i!=axis)oi[j++]=idx[i];int64_t f=0;for(int i=0;i<nd;i++)f=f*out->shape[i]+oi[i];double v=read_at(t,elem_offset(t,idx));if((is_max&&v>read_at(out,f))||(!is_max&&v<read_at(out,f)))write_at(out,f,v);}return out;
}
GsTensor*gs_tensor_max(const GsTensor*t,int axis,int keep){(void)keep;return reduce_extreme(t,axis,1);} GsTensor*gs_tensor_min(const GsTensor*t,int axis,int keep){(void)keep;return reduce_extreme(t,axis,0);}
static GsTensor* reduce_arg(const GsTensor*t,int axis,int is_max){if(!t||axis<0||axis>=t->ndim)return NULL;GsTensor*vals=reduce_extreme(t,axis,is_max);if(!vals)return NULL;GsTensor*out=gs_tensor_create(vals->ndim,vals->shape,GS_INT64,GS_DEVICE_CPU);if(!out){gs_tensor_release(vals);return NULL;}int64_t idx[GS_TENSOR_MAX_DIMS],oi[GS_TENSOR_MAX_DIMS];for(int64_t f=0;f<vals->numel;f++){int64_t rem=f;for(int d=vals->ndim-1;d>=0;d--){idx[d]=rem%vals->shape[d];rem/=vals->shape[d];}for(int d=0,j=0;d<t->ndim;d++)if(d!=axis)oi[d]=idx[j++];int64_t best=0;double wanted=read_at(vals,f);for(int64_t a=0;a<t->shape[axis];a++){int64_t ti[GS_TENSOR_MAX_DIMS];for(int d=0,j=0;d<t->ndim;d++)ti[d]=d==axis?a:oi[j++];if(read_at(t,elem_offset(t,ti))==wanted){best=a;break;}}write_at(out,f,best);}gs_tensor_release(vals);return out;}
GsTensor*gs_tensor_argmax(const GsTensor*t,int axis){return reduce_arg(t,axis,1);} GsTensor*gs_tensor_argmin(const GsTensor*t,int axis){return reduce_arg(t,axis,0);}
GsTensor*gs_tensor_relu6(const GsTensor*t){GsTensor*out=gs_tensor_relu(t);if(out)for(int64_t i=0;i<out->numel;i++)if(read_at(out,i)>6)write_at(out,i,6);return out;}
GsTensor*gs_tensor_gelu(const GsTensor*t){if(!t)return NULL;GsTensor*out=gs_tensor_create(t->ndim,t->shape,GS_FLOAT32,GS_DEVICE_CPU);if(out)for(int64_t i=0;i<t->numel;i++){double x=read_at(t,i);write_at(out,i,0.5*x*(1+tanh(0.7978845608*(x+0.044715*x*x*x))));}return out;}
GsTensor*gs_tensor_silu(const GsTensor*t){if(!t)return NULL;GsTensor*out=gs_tensor_create(t->ndim,t->shape,GS_FLOAT32,GS_DEVICE_CPU);if(out)for(int64_t i=0;i<t->numel;i++){double x=read_at(t,i);write_at(out,i,x/(1+exp(-x)));}return out;}
void gs_tensor_relu_inplace(GsTensor*t){if(t)for(int64_t i=0;i<t->numel;i++)if(read_at(t,i)<0)write_at(t,i,0);} void gs_tensor_sigmoid_inplace(GsTensor*t){if(t)for(int64_t i=0;i<t->numel;i++){double x=read_at(t,i);write_at(t,i,1/(1+exp(-x)));}}
GsTensor*gs_tensor_softmax(const GsTensor*t,int axis){if(!t||axis<0||axis>=t->ndim)return NULL;GsTensor*out=gs_tensor_create(t->ndim,t->shape,GS_FLOAT32,GS_DEVICE_CPU);if(!out)return NULL;int64_t idx[GS_TENSOR_MAX_DIMS];int64_t outer=t->numel/t->shape[axis];for(int64_t o=0;o<outer;o++){int64_t base_rem=o,base[GS_TENSOR_MAX_DIMS]={0};for(int d=t->ndim-1;d>=0;d--)if(d!=axis){base[d]=base_rem%t->shape[d];base_rem/=t->shape[d];}double mx=-INFINITY;for(int64_t a=0;a<t->shape[axis];a++){memcpy(idx,base,sizeof(idx));idx[axis]=a;double x=read_at(t,elem_offset(t,idx));if(x>mx)mx=x;}double sum=0;for(int64_t a=0;a<t->shape[axis];a++){memcpy(idx,base,sizeof(idx));idx[axis]=a;sum+=exp(read_at(t,elem_offset(t,idx))-mx);}for(int64_t a=0;a<t->shape[axis];a++){memcpy(idx,base,sizeof(idx));idx[axis]=a;write_at(out,elem_offset(out,idx),exp(read_at(t,elem_offset(t,idx))-mx)/sum);}}return out;}
GsTensor*gs_tensor_log_softmax(const GsTensor*t,int axis){GsTensor*out=gs_tensor_softmax(t,axis);if(out)for(int64_t i=0;i<out->numel;i++)write_at(out,i,log(read_at(out,i)));return out;}
GsTensor*gs_tensor_reshape(const GsTensor*t,int n,const int64_t*s){if(!t||elem_count(n,s)!=t->numel)return NULL;GsTensor*out=gs_tensor_create(n,s,GS_FLOAT32,GS_DEVICE_CPU);if(out)for(int64_t i=0;i<t->numel;i++)write_at(out,i,read_at(t,i));return out;}
GsTensor*gs_tensor_flatten(const GsTensor*t,int start,int end){if(!t||start<0||end<start||end>=t->ndim)return NULL;int64_t shape[GS_TENSOR_MAX_DIMS];int n=0;for(int i=0;i<t->ndim;i++){if(i==start){int64_t v=1;for(int j=start;j<=end;j++)v*=t->shape[j];shape[n++]=v;}else if(i<start||i>end)shape[n++]=t->shape[i];}return gs_tensor_reshape(t,n,shape);}
GsTensor*gs_tensor_squeeze(const GsTensor*t,int axis){if(!t||axis<0||axis>=t->ndim||t->shape[axis]!=1)return NULL;int64_t s[GS_TENSOR_MAX_DIMS];int n=0;for(int i=0;i<t->ndim;i++)if(i!=axis)s[n++]=t->shape[i];if(!n){s[0]=1;n=1;}return gs_tensor_reshape(t,n,s);}
GsTensor*gs_tensor_unsqueeze(const GsTensor*t,int axis){if(!t||axis<0||axis>t->ndim||t->ndim>=GS_TENSOR_MAX_DIMS)return NULL;int64_t s[GS_TENSOR_MAX_DIMS];for(int i=0,j=0;i<t->ndim+1;i++)s[i]=i==axis?1:t->shape[j++];return gs_tensor_reshape(t,t->ndim+1,s);}
GsTensor*gs_tensor_cast(const GsTensor*t,GsDType d){if(!t)return NULL;GsTensor*out=gs_tensor_create(t->ndim,t->shape,d,GS_DEVICE_CPU);if(out)for(int64_t i=0;i<t->numel;i++)write_at(out,i,read_at(t,i));return out;}
GsTensor*gs_tensor_to_device(const GsTensor*t,GsDevice dev){if(dev!=GS_DEVICE_CPU){set_error("CUDA and Metal devices are not available in this build");return NULL;}return gs_tensor_clone(t);}
GsTensor*gs_tensor_inv(const GsTensor*t){(void)t;set_error("matrix inverse is not implemented in naive backend");return NULL;} int gs_tensor_eig(const GsTensor*t,GsTensor**v,GsTensor**m){(void)t;if(v)*v=NULL;if(m)*m=NULL;set_error("eigen decomposition is not implemented in naive backend");return 0;}
GsTensor*gs_tensor_conv2d(const GsTensor*i,const GsTensor*w,const GsTensor*b,const int s[2],const int p[2],const int d[2]){(void)i;(void)w;(void)b;(void)s;(void)p;(void)d;set_error("conv2d kernel is not implemented yet");return NULL;}
GsTensor*gs_tensor_maxpool2d(const GsTensor*i,const int k[2],const int s[2],const int p[2]){(void)i;(void)k;(void)s;(void)p;set_error("maxpool2d kernel is not implemented yet");return NULL;}
GsTensor*gs_tensor_avgpool2d(const GsTensor*i,const int k[2],const int s[2],const int p[2]){(void)i;(void)k;(void)s;(void)p;set_error("avgpool2d kernel is not implemented yet");return NULL;}
GsTensor*gs_tensor_batchnorm(const GsTensor*i,const GsTensor*m,const GsTensor*v,const GsTensor*w,const GsTensor*b,double e){(void)i;(void)m;(void)v;(void)w;(void)b;(void)e;set_error("batchnorm kernel is not implemented yet");return NULL;}
GsTensor*gs_tensor_transpose_2d(const GsTensor*t);
int gs_tensor_save_npy(const GsTensor*t,const char*p){(void)t;(void)p;set_error("NumPy serialization is not implemented yet");return 0;} GsTensor*gs_tensor_load_npy(const char*p){(void)p;set_error("NumPy serialization is not implemented yet");return NULL;}

/* Remaining extended operations are deliberately not advertised by the
 * language bindings until their kernels/autograd rules are implemented. */
