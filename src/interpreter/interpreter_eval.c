#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "interpreter.h"
#include <dlfcn.h>
#include <ffi.h>


extern void register_native_c_functions(Environment* env);
extern Value evaluate_expr(ASTNode* node, Environment* env);
extern int evaluate_statement(ASTNode* node, Environment* env, char* current_file);
/* static char* current_source_file = NULL; */
// ======================== GESTION DES IMPLÉMENTATIONS ====================

typedef struct {
    char* struct_name;
    ASTNode* impl_node;
} ImplEntry;

static ImplEntry* impl_table = NULL;
static int impl_count = 0;
static int impl_capacity = 0;

typedef struct NnlContext {
    char* label;
    jmp_buf env;
    Value return_value;
    struct NnlContext* next;
} NnlContext;

// Pile de contextes
static NnlContext* nnl_stack = NULL;
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
    Value error;
    int is_thrown;
    jmp_buf env;
} ExceptionContext;

static ExceptionContext* current_exception = NULL;

// Créer une promesse pour une commande shell
Promise* create_promise(char* command) {
    Promise* p = malloc(sizeof(Promise));
    p->state = 0;  // pending
    p->command = strdup(command);
    p->pid = -1;
    p->pipe_fd = -1;
    p->next = NULL;
    memset(&p->result, 0, sizeof(Value));
    return p;
}

// Exécuter une commande en arrière-plan
Promise* run_async_command(char* command) {
    Promise* p = create_promise(command);
    
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        p->state = 2;  // rejected
        return p;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Processus enfant
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);
        
        execl("/bin/sh", "sh", "-c", command, NULL);
        exit(1);
    } else if (pid > 0) {
        // Processus parent
        close(pipefd[1]);
        p->pid = pid;
        p->pipe_fd = pipefd[0];
        
        // Mettre le pipe en mode non-bloquant
        int flags = fcntl(pipefd[0], F_GETFL, 0);
        fcntl(pipefd[0], F_SETFL, flags | O_NONBLOCK);
    } else {
        p->state = 2;  // rejected
    }
    
    return p;
}




// Structure pour await qui préserve stdin
Value builtin_await(Value* args, int arg_count) {
    Value result = {0};
    result.type = 2;
    
    if (arg_count < 1) {
        result.string_val = strdup("");
        return result;
    }
    
    // Si c'est une promesse
    if (args[0].type == VALUE_TYPE_PROMISE) {
        Promise* p = (Promise*)args[0].int_val;
        result = await_promise(p, NULL);
        return result;
    }
    
    // Si c'est une commande string
    if (args[0].type == 2 && args[0].string_val) {
        char* cmd = args[0].string_val;
        
        // Utiliser un template modifiable
        char temp_out[] = "/tmp/goscript_await_XXXXXX";
        int fd = mkstemp(temp_out);
        if (fd == -1) {
            perror("mkstemp");
            result.string_val = strdup("");
            return result;
        }
        close(fd);  // On ferme le fd car on va rouvrir avec fopen
        
        // Créer la commande complète avec redirection
        char* full_cmd = malloc(strlen(cmd) + strlen(temp_out) + 20);
        if (!full_cmd) {
            unlink(temp_out);
            result.string_val = strdup("");
            return result;
        }
        sprintf(full_cmd, "(%s) > %s 2>&1", cmd, temp_out);
        
        // Exécuter avec system()
        int ret = system(full_cmd);
        free(full_cmd);
        
        // Lire le résultat
        FILE* f = fopen(temp_out, "r");
        if (f) {
            fseek(f, 0, SEEK_END);
            long size = ftell(f);
            fseek(f, 0, SEEK_SET);
            
            char* output = malloc(size + 1);
            if (output) {
                size_t read_size = fread(output, 1, size, f);
                output[read_size] = '\0';
                
                // Enlever le \n final si présent
                if (read_size > 0 && output[read_size-1] == '\n') {
                    output[read_size-1] = '\0';
                }
                result.string_val = output;
            } else {
                result.string_val = strdup("");
            }
            fclose(f);
        } else {
            result.string_val = strdup("");
        }
        
        unlink(temp_out);
        return result;
    }
    
    result.string_val = strdup("");
    return result;
}
// Vérifier si une promesse est résolue
int poll_promise(Promise* p) {
    if (p->state != 0) return 1;
    
    int status;
    pid_t result = waitpid(p->pid, &status, WNOHANG);
    
    if (result == p->pid) {
        // Lire la sortie
        char buffer[4096];
        ssize_t n = read(p->pipe_fd, buffer, sizeof(buffer) - 1);
        
        if (n > 0) {
            buffer[n] = '\0';
            p->result.type = 2;  // string
            p->result.string_val = strdup(buffer);
        } else {
            p->result.type = 0;  // int
            p->result.int_val = WEXITSTATUS(status);
        }
        
        close(p->pipe_fd);
        p->state = 1;  // resolved
        return 1;
    }
    
    return 0;
}

// Attendre une promesse
Value await_promise(Promise* p, Environment* env) {
    // Boucle d'attente non-bloquante
    while (p->state == 0) {
        poll_promise(p);
        usleep(1000000000);  // 1000ms
    }
    
    return p->result;
}

// Boucle d'événements
void run_event_loop(AsyncContext* ctx) {
    int pending = 1;
    
    while (pending) {
        pending = 0;
        
        for (Promise* p = ctx->pending_promises; p; p = p->next) {
            if (p->state == 0) {
                poll_promise(p);
                pending = 1;
            }
        }
        
        if (pending) {
            usleep(1000000);  // 1200ms
        }
    }
}


// ==================== FONCTIONS UTILITAIRES ====================

int values_equal(Value a, Value b) {
    if (a.type != b.type) return 0;
    
    switch (a.type) {
        case 0: return a.int_val == b.int_val;
        case 1: return a.float_val == b.float_val;
        case 2: 
            if (!a.string_val && !b.string_val) return 1;
            if (!a.string_val || !b.string_val) return 0;
            return strcmp(a.string_val, b.string_val) == 0;
        case 3: return a.bool_val == b.bool_val;
        default: return 0;
    }
}

// Fonction pour chercher un contexte
static NnlContext* find_nnl_context(char* label) {
    NnlContext* ctx = nnl_stack;
    while (ctx) {
        if (strcmp(ctx->label, label) == 0) {
            return ctx;
        }
        ctx = ctx->next;
    }
    return NULL;
}

// Dans interpreter_eval.c

Value async_curl(char* url, Environment* env) {
    char command[1024];
    snprintf(command, sizeof(command), "curl -s '%s'", url);
    Promise* p = run_async_command(command);
    
    Value result;
    result.type = VALUE_TYPE_PROMISE;
    result.int_val = (int)p;
    return result;
}

Value async_wget(char* url, char* output, Environment* env) {
    char command[1024];
    if (output) {
        snprintf(command, sizeof(command), "wget -q -O '%s' '%s'", output, url);
    } else {
        snprintf(command, sizeof(command), "wget -q '%s'", url);
    }
    Promise* p = run_async_command(command);
    
    Value result;
    result.type = VALUE_TYPE_PROMISE;
    result.int_val = (int)p;
    return result;
}

Value async_tar(char* flags, char* archive, Environment* env) {
    char command[1024];
    snprintf(command, sizeof(command), "tar %s '%s'", flags, archive);
    Promise* p = run_async_command(command);
    
    Value result;
    result.type = VALUE_TYPE_PROMISE;
    result.int_val = (int)p;
    return result;
}

// Enregistrer une implémentation
void register_impl(char* struct_name, ASTNode* impl_node) {
    if (impl_count >= impl_capacity) {
        impl_capacity = impl_capacity == 0 ? 10 : impl_capacity * 2;
        impl_table = realloc(impl_table, impl_capacity * sizeof(ImplEntry));
    }
    impl_table[impl_count].struct_name = strdup(struct_name);
    impl_table[impl_count].impl_node = impl_node;
    impl_count++;
}
void dump_module_env(LoadedModule* mod) {
    if (!mod || !mod->env) return;
    printf("--- Symboles dans le module [%s] ---\n", mod->module_name);
    for (int i = 0; i < mod->env->var_count; i++) {
        printf("  [%d] %s (Type: %d)\n", i, mod->env->vars[i].name, mod->env->vars[i].value.type);
    }
    printf("-----------------------------------\n");
}

// Trouver une implémentation par nom de structure
ASTNode* find_impl(char* struct_name) {
    for (int i = 0; i < impl_count; i++) {
        if (strcmp(impl_table[i].struct_name, struct_name) == 0) {
            return impl_table[i].impl_node;
        }
    }
    return NULL;
}

static ModuleRegistry* module_registry = NULL;

ModuleRegistry* get_module_registry(void) {
    if (!module_registry) {
        module_registry = init_module_registry();
    }
    return module_registry;
}

// Handle global pour la libc (ouvert une seule fois)
extern ASTNode* program_root;
static void* libc_handle = NULL;
static int libc_initialized = 0;

// Initialiser le handle de la libc
void init_libc() {
    if (!libc_initialized) {
        // Sur Alpine Linux, la libc est musl
        libc_handle = dlopen("libc.musl-x86.so.1", RTLD_LAZY);
        if (!libc_handle) {
            // Essayer avec le nom standard
            libc_handle = dlopen("libc.so.6", RTLD_LAZY);
        }
        if (!libc_handle) {
            // Essayer avec NULL pour le programme courant
            libc_handle = dlopen("libc*", RTLD_LAZY);
        }
        if (!libc_handle) {
            // Essayer avec NULL pour le programme courant
            libc_handle = dlopen(NULL, RTLD_LAZY);
        }
        libc_initialized = 1;
    }
}

// Fonction pour appeler une fonction C via FFI
Value call_c_function_ffi(void* func_ptr, Value* args, int arg_count, ffi_type* ret_type, ffi_type** arg_types) {
    Value result = {0};
    
    if (!func_ptr) {
        fprintf(stderr, "Error: NULL function pointer\n");
        return result;
    }
    
    // Préparer la CIF (Call Interface)
    ffi_cif cif;
    ffi_status status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, arg_count, ret_type, arg_types);
    
    if (status != FFI_OK) {
        fprintf(stderr, "Error: ffi_prep_cif failed with status %d\n", status);
        return result;
    }
    
    // Préparer les valeurs
    void** values = malloc(arg_count * sizeof(void*));
    void* ret_val = malloc(32);
    
    for (int i = 0; i < arg_count; i++) {
        switch (args[i].type) {
            case 0: values[i] = &args[i].int_val; break;
            case 1: values[i] = &args[i].float_val; break;
            case 2: values[i] = &args[i].string_val; break;
            case 3: values[i] = &args[i].bool_val; break;
            default: values[i] = NULL;
        }
    }
    
    ffi_call(&cif, FFI_FN(func_ptr), ret_val, values);
    
    if (ret_type == &ffi_type_sint32 || ret_type == &ffi_type_sint) {
        result.type = 0;
        result.int_val = *(int*)ret_val;
    } else if (ret_type == &ffi_type_sint64) {
        result.type = 0;
        result.int_val = *(long long*)ret_val;
    } else if (ret_type == &ffi_type_float) {
        result.type = 1;
        result.float_val = *(float*)ret_val;
    } else if (ret_type == &ffi_type_double) {
        result.type = 1;
        result.float_val = *(double*)ret_val;
    } else if (ret_type == &ffi_type_pointer) {
        result.type = 2;
        char* str = *(char**)ret_val;
        result.string_val = str ? strdup(str) : strdup("");
    } else if (ret_type == &ffi_type_void) {
        result.type = 0;
        result.int_val = 0;
    }
    
    free(values);
    free(ret_val);
    return result;
}

// Fonction pour appeler puts
Value call_puts(Value* args, int arg_count) {
    Value result = {0};
    if (arg_count > 0 && args[0].type == 2) {
        printf("%s\n", args[0].string_val);
    }
    return result;
}

// Fonction pour appeler putchar
Value call_putchar(Value* args, int arg_count) {
    Value result = {0};
    if (arg_count > 0 && args[0].type == 0) {
        putchar(args[0].int_val);
        result.int_val = args[0].int_val;
    }
    return result;
}

void print_value(Value val, int newline) {
    switch (val.type) {
        case 0: printf("%d", val.int_val); break;
        case 1: printf("%f", val.float_val); break;
        case 2: printf("%s", val.string_val); break;
        case 3: printf("%s", val.bool_val ? "true" : "false"); break;
        case 8: {
            // Tableau
            printf("[");
            for (int i = 0; i < val.array_val.count; i++) {
                if (i > 0) printf(", ");
                Value elem = evaluate_expr(val.array_val.elements->nodes[i], NULL);
                print_value(elem, 0);
            }
            printf("]");
            break;
        }
        case 9: printf("<lambda>"); break;
        case 10: {
            // Dictionnaire
            printf("{");
            for (int i = 0; i < val.dict_val.count; i++) {
                if (i > 0) printf(", ");
                print_value(*(val.dict_val.entries[i].key), 0);
                printf(": ");
                print_value(*(val.dict_val.entries[i].value), 0);
            }
            printf("}");
            break;
        }
        default: printf("unknown(%d)", val.type);
    }
    if (newline) printf("\n");
}

void register_native_c_functions(Environment* env) {
    init_libc();
    
    if (!libc_handle) {
        fprintf(stderr, "Warning: libc handle not available\n");
        return;
    }
    
    // ============================================
    // STRING FUNCTIONS (string.h)
    // ============================================
    
    void* strlen_ptr = dlsym(libc_handle, "strlen");
    if (strlen_ptr) register_c_function(env, "strlen_c", strlen_ptr, "int", 1, "string");
    
    void* strcmp_ptr = dlsym(libc_handle, "strcmp");
    if (strcmp_ptr) register_c_function(env, "strcmp_c", strcmp_ptr, "int", 2, "string", "string");
    
    void* strncmp_ptr = dlsym(libc_handle, "strncmp");
    if (strncmp_ptr) register_c_function(env, "strncmp_c", strncmp_ptr, "int", 3, "string", "string", "int");
    
    void* strcpy_ptr = dlsym(libc_handle, "strcpy");
    if (strcpy_ptr) register_c_function(env, "strcpy_c", strcpy_ptr, "string", 2, "string", "string");
    
    void* strncpy_ptr = dlsym(libc_handle, "strncpy");
    if (strncpy_ptr) register_c_function(env, "strncpy_c", strncpy_ptr, "string", 3, "string", "string", "int");
    
    void* strcat_ptr = dlsym(libc_handle, "strcat");
    if (strcat_ptr) register_c_function(env, "strcat_c", strcat_ptr, "string", 2, "string", "string");
    
    void* strncat_ptr = dlsym(libc_handle, "strncat");
    if (strncat_ptr) register_c_function(env, "strncat_c", strncat_ptr, "string", 3, "string", "string", "int");
    
    void* strchr_ptr = dlsym(libc_handle, "strchr");
    if (strchr_ptr) register_c_function(env, "strchr_c", strchr_ptr, "string", 2, "string", "int");
    
    void* strrchr_ptr = dlsym(libc_handle, "strrchr");
    if (strrchr_ptr) register_c_function(env, "strrchr_c", strrchr_ptr, "string", 2, "string", "int");
    
    void* strstr_ptr = dlsym(libc_handle, "strstr");
    if (strstr_ptr) register_c_function(env, "strstr_c", strstr_ptr, "string", 2, "string", "string");
    
    void* strtok_ptr = dlsym(libc_handle, "strtok");
    if (strtok_ptr) register_c_function(env, "strtok_c", strtok_ptr, "string", 2, "string", "string");
    
    void* strspn_ptr = dlsym(libc_handle, "strspn");
    if (strspn_ptr) register_c_function(env, "strspn_c", strspn_ptr, "int", 2, "string", "string");
    
    void* strcspn_ptr = dlsym(libc_handle, "strcspn");
    if (strcspn_ptr) register_c_function(env, "strcspn_c", strcspn_ptr, "int", 2, "string", "string");
    
    void* strpbrk_ptr = dlsym(libc_handle, "strpbrk");
    if (strpbrk_ptr) register_c_function(env, "strpbrk_c", strpbrk_ptr, "string", 2, "string", "string");
    
    void* strdup_ptr = dlsym(libc_handle, "strdup");
    if (strdup_ptr) register_c_function(env, "strdup_c", strdup_ptr, "string", 1, "string");
    
    // ============================================
    // MEMORY FUNCTIONS (string.h)
    // ============================================
    
    void* memcpy_ptr = dlsym(libc_handle, "memcpy");
    if (memcpy_ptr) register_c_function(env, "memcpy_c", memcpy_ptr, "int", 3, "int", "int", "int");
    
    void* memmove_ptr = dlsym(libc_handle, "memmove");
    if (memmove_ptr) register_c_function(env, "memmove_c", memmove_ptr, "int", 3, "int", "int", "int");
    
    void* memset_ptr = dlsym(libc_handle, "memset");
    if (memset_ptr) register_c_function(env, "memset_c", memset_ptr, "int", 3, "int", "int", "int");
    
    void* memcmp_ptr = dlsym(libc_handle, "memcmp");
    if (memcmp_ptr) register_c_function(env, "memcmp_c", memcmp_ptr, "int", 3, "int", "int", "int");
    
    void* memchr_ptr = dlsym(libc_handle, "memchr");
    if (memchr_ptr) register_c_function(env, "memchr_c", memchr_ptr, "int", 3, "int", "int", "int");
    
    // ============================================
    // STDIO FUNCTIONS (stdio.h)
    // ============================================
    
    void* fopen_ptr = dlsym(libc_handle, "fopen");
    if (fopen_ptr) register_c_function(env, "fopen_c", fopen_ptr, "int", 2, "string", "string");
    
    void* fclose_ptr = dlsym(libc_handle, "fclose");
    if (fclose_ptr) register_c_function(env, "fclose_c", fclose_ptr, "int", 1, "int");
    
    void* fread_ptr = dlsym(libc_handle, "fread");
    if (fread_ptr) register_c_function(env, "fread_c", fread_ptr, "int", 4, "int", "int", "int", "int");
    
    void* fwrite_ptr = dlsym(libc_handle, "fwrite");
    if (fwrite_ptr) register_c_function(env, "fwrite_c", fwrite_ptr, "int", 4, "int", "int", "int", "int");
    
    void* fseek_ptr = dlsym(libc_handle, "fseek");
    if (fseek_ptr) register_c_function(env, "fseek_c", fseek_ptr, "int", 3, "int", "int", "int");
    
    void* ftell_ptr = dlsym(libc_handle, "ftell");
    if (ftell_ptr) register_c_function(env, "ftell_c", ftell_ptr, "int", 1, "int");
    
    void* rewind_ptr = dlsym(libc_handle, "rewind");
    if (rewind_ptr) register_c_function(env, "rewind_c", rewind_ptr, "void", 1, "int");
    
    void* fgetc_ptr = dlsym(libc_handle, "fgetc");
    if (fgetc_ptr) register_c_function(env, "fgetc_c", fgetc_ptr, "int", 1, "int");
    
    void* fputc_ptr = dlsym(libc_handle, "fputc");
    if (fputc_ptr) register_c_function(env, "fputc_c", fputc_ptr, "int", 2, "int", "int");
    
    void* fgets_ptr = dlsym(libc_handle, "fgets");
    if (fgets_ptr) register_c_function(env, "fgets_c", fgets_ptr, "string", 3, "string", "int", "int");
    
    void* fputs_ptr = dlsym(libc_handle, "fputs");
    if (fputs_ptr) register_c_function(env, "fputs_c", fputs_ptr, "int", 2, "string", "int");
    
    void* fprintf_ptr = dlsym(libc_handle, "fprintf");
    if (fprintf_ptr) register_c_function(env, "fprintf_c", fprintf_ptr, "int", 2, "int", "string");
    
    void* printf_ptr = dlsym(libc_handle, "printf");
    if (printf_ptr) register_c_function(env, "printf_c", printf_ptr, "int", 1, "string");
    
    void* sprintf_ptr = dlsym(libc_handle, "sprintf");
    if (sprintf_ptr) register_c_function(env, "sprintf_c", sprintf_ptr, "int", 2, "string", "string");
    
    void* scanf_ptr = dlsym(libc_handle, "scanf");
    if (scanf_ptr) register_c_function(env, "scanf_c", scanf_ptr, "int", 1, "string");
    
    void* sscanf_ptr = dlsym(libc_handle, "sscanf");
    if (sscanf_ptr) register_c_function(env, "sscanf_c", sscanf_ptr, "int", 3, "string", "string", "int");
    
    void* remove_ptr = dlsym(libc_handle, "remove");
    if (remove_ptr) register_c_function(env, "remove_c", remove_ptr, "int", 1, "string");
    
    void* rename_ptr = dlsym(libc_handle, "rename");
    if (rename_ptr) register_c_function(env, "rename_c", rename_ptr, "int", 2, "string", "string");
    
    void* tmpfile_ptr = dlsym(libc_handle, "tmpfile");
    if (tmpfile_ptr) register_c_function(env, "tmpfile_c", tmpfile_ptr, "int", 0);
    
    void* tmpnam_ptr = dlsym(libc_handle, "tmpnam");
    if (tmpnam_ptr) register_c_function(env, "tmpnam_c", tmpnam_ptr, "string", 1, "string");
    
    // ============================================
    // STD LIB FUNCTIONS (stdlib.h)
    // ============================================
    
    void* atoi_ptr = dlsym(libc_handle, "atoi");
    if (atoi_ptr) register_c_function(env, "atoi_c", atoi_ptr, "int", 1, "string");
    
    void* atol_ptr = dlsym(libc_handle, "atol");
    if (atol_ptr) register_c_function(env, "atol_c", atol_ptr, "int", 1, "string");
    
    void* atoll_ptr = dlsym(libc_handle, "atoll");
    if (atoll_ptr) register_c_function(env, "atoll_c", atoll_ptr, "int", 1, "string");
    
    void* atof_ptr = dlsym(libc_handle, "atof");
    if (atof_ptr) register_c_function(env, "atof_c", atof_ptr, "double", 1, "string");
    
    void* strtol_ptr = dlsym(libc_handle, "strtol");
    if (strtol_ptr) register_c_function(env, "strtol_c", strtol_ptr, "int", 3, "string", "int", "int");
    
    void* strtoll_ptr = dlsym(libc_handle, "strtoll");
    if (strtoll_ptr) register_c_function(env, "strtoll_c", strtoll_ptr, "int", 3, "string", "int", "int");
    
    void* strtoul_ptr = dlsym(libc_handle, "strtoul");
    if (strtoul_ptr) register_c_function(env, "strtoul_c", strtoul_ptr, "int", 3, "string", "int", "int");
    
    void* strtod_ptr = dlsym(libc_handle, "strtod");
    if (strtod_ptr) register_c_function(env, "strtod_c", strtod_ptr, "double", 2, "string", "int");
    
    void* malloc_ptr = dlsym(libc_handle, "malloc");
    if (malloc_ptr) register_c_function(env, "malloc_c", malloc_ptr, "int", 1, "int");
    
    void* calloc_ptr = dlsym(libc_handle, "calloc");
    if (calloc_ptr) register_c_function(env, "calloc_c", calloc_ptr, "int", 2, "int", "int");
    
    void* realloc_ptr = dlsym(libc_handle, "realloc");
    if (realloc_ptr) register_c_function(env, "realloc_c", realloc_ptr, "int", 2, "int", "int");
    
    void* free_ptr = dlsym(libc_handle, "free");
    if (free_ptr) register_c_function(env, "free_c", free_ptr, "void", 1, "int");
    
    void* abort_ptr = dlsym(libc_handle, "abort");
    if (abort_ptr) register_c_function(env, "abort_c", abort_ptr, "void", 0);
    
    void* exit_ptr = dlsym(libc_handle, "exit");
    if (exit_ptr) register_c_function(env, "exit_c", exit_ptr, "void", 1, "int");
    
    void* _exit_ptr = dlsym(libc_handle, "_exit");
    if (_exit_ptr) register_c_function(env, "_exit_c", _exit_ptr, "void", 1, "int");
    
    void* system_ptr = dlsym(libc_handle, "system");
    if (system_ptr) register_c_function(env, "system_c", system_ptr, "int", 1, "string");
    
    void* getenv_ptr = dlsym(libc_handle, "getenv");
    if (getenv_ptr) register_c_function(env, "getenv_c", getenv_ptr, "string", 1, "string");
    
    void* setenv_ptr = dlsym(libc_handle, "setenv");
    if (setenv_ptr) register_c_function(env, "setenv_c", setenv_ptr, "int", 3, "string", "string", "int");
    
    void* unsetenv_ptr = dlsym(libc_handle, "unsetenv");
    if (unsetenv_ptr) register_c_function(env, "unsetenv_c", unsetenv_ptr, "int", 1, "string");
    
    void* clearenv_ptr = dlsym(libc_handle, "clearenv");
    if (clearenv_ptr) register_c_function(env, "clearenv_c", clearenv_ptr, "int", 0);
    
    void* qsort_ptr = dlsym(libc_handle, "qsort");
    if (qsort_ptr) register_c_function(env, "qsort_c", qsort_ptr, "void", 4, "int", "int", "int", "int");
    
    void* bsearch_ptr = dlsym(libc_handle, "bsearch");
    if (bsearch_ptr) register_c_function(env, "bsearch_c", bsearch_ptr, "int", 5, "int", "int", "int", "int", "int");
    
    void* rand_ptr = dlsym(libc_handle, "rand");
    if (rand_ptr) register_c_function(env, "rand_c", rand_ptr, "int", 0);
    
    void* srand_ptr = dlsym(libc_handle, "srand");
    if (srand_ptr) register_c_function(env, "srand_c", srand_ptr, "void", 1, "int");
    
    void* rand_r_ptr = dlsym(libc_handle, "rand_r");
    if (rand_r_ptr) register_c_function(env, "rand_r_c", rand_r_ptr, "int", 1, "int");
    
    // ============================================
    // TIME FUNCTIONS (time.h)
    // ============================================
    
    void* time_ptr = dlsym(libc_handle, "time");
    if (time_ptr) register_c_function(env, "time_c", time_ptr, "int", 1, "int");
    
    void* clock_ptr = dlsym(libc_handle, "clock");
    if (clock_ptr) register_c_function(env, "clock_c", clock_ptr, "int", 0);
    
    void* difftime_ptr = dlsym(libc_handle, "difftime");
    if (difftime_ptr) register_c_function(env, "difftime_c", difftime_ptr, "double", 2, "int", "int");
    
    void* mktime_ptr = dlsym(libc_handle, "mktime");
    if (mktime_ptr) register_c_function(env, "mktime_c", mktime_ptr, "int", 1, "int");
    
    void* asctime_ptr = dlsym(libc_handle, "asctime");
    if (asctime_ptr) register_c_function(env, "asctime_c", asctime_ptr, "string", 1, "int");
    
    void* ctime_ptr = dlsym(libc_handle, "ctime");
    if (ctime_ptr) register_c_function(env, "ctime_c", ctime_ptr, "string", 1, "int");
    
    void* gmtime_ptr = dlsym(libc_handle, "gmtime");
    if (gmtime_ptr) register_c_function(env, "gmtime_c", gmtime_ptr, "int", 1, "int");
    
    void* localtime_ptr = dlsym(libc_handle, "localtime");
    if (localtime_ptr) register_c_function(env, "localtime_c", localtime_ptr, "int", 1, "int");
    
    void* strftime_ptr = dlsym(libc_handle, "strftime");
    if (strftime_ptr) register_c_function(env, "strftime_c", strftime_ptr, "int", 5, "string", "int", "string", "int", "int");
    
    void* nanosleep_ptr = dlsym(libc_handle, "nanosleep");
    if (nanosleep_ptr) register_c_function(env, "nanosleep_c", nanosleep_ptr, "int", 2, "int", "int");
    
    // ============================================
    // UNISTD FUNCTIONS (unistd.h)
    // ============================================
    
    void* getpid_ptr = dlsym(libc_handle, "getpid");
    if (getpid_ptr) register_c_function(env, "getpid_c", getpid_ptr, "int", 0);
    
    void* getppid_ptr = dlsym(libc_handle, "getppid");
    if (getppid_ptr) register_c_function(env, "getppid_c", getppid_ptr, "int", 0);
    
    void* getuid_ptr = dlsym(libc_handle, "getuid");
    if (getuid_ptr) register_c_function(env, "getuid_c", getuid_ptr, "int", 0);
    
    void* geteuid_ptr = dlsym(libc_handle, "geteuid");
    if (geteuid_ptr) register_c_function(env, "geteuid_c", geteuid_ptr, "int", 0);
    
    void* getgid_ptr = dlsym(libc_handle, "getgid");
    if (getgid_ptr) register_c_function(env, "getgid_c", getgid_ptr, "int", 0);
    
    void* getegid_ptr = dlsym(libc_handle, "getegid");
    if (getegid_ptr) register_c_function(env, "getegid_c", getegid_ptr, "int", 0);
    
    void* getcwd_ptr = dlsym(libc_handle, "getcwd");
    if (getcwd_ptr) register_c_function(env, "getcwd_c", getcwd_ptr, "string", 2, "string", "int");
    
    void* chdir_ptr = dlsym(libc_handle, "chdir");
    if (chdir_ptr) register_c_function(env, "chdir_c", chdir_ptr, "int", 1, "string");
    
    void* sleep_ptr = dlsym(libc_handle, "sleep");
    if (sleep_ptr) register_c_function(env, "sleep_c", sleep_ptr, "int", 1, "int");
    
    void* usleep_ptr = dlsym(libc_handle, "usleep");
    if (usleep_ptr) register_c_function(env, "usleep_c", usleep_ptr, "int", 1, "int");
    
    void* fork_ptr = dlsym(libc_handle, "fork");
    if (fork_ptr) register_c_function(env, "fork_c", fork_ptr, "int", 0);
    
    void* execv_ptr = dlsym(libc_handle, "execv");
    if (execv_ptr) register_c_function(env, "execv_c", execv_ptr, "int", 2, "string", "int");
    
    void* execvp_ptr = dlsym(libc_handle, "execvp");
    if (execvp_ptr) register_c_function(env, "execvp_c", execvp_ptr, "int", 2, "string", "int");
    
    void* wait_ptr = dlsym(libc_handle, "wait");
    if (wait_ptr) register_c_function(env, "wait_c", wait_ptr, "int", 1, "int");
    
    void* waitpid_ptr = dlsym(libc_handle, "waitpid");
    if (waitpid_ptr) register_c_function(env, "waitpid_c", waitpid_ptr, "int", 3, "int", "int", "int");
    
    void* pipe_ptr = dlsym(libc_handle, "pipe");
    if (pipe_ptr) register_c_function(env, "pipe_c", pipe_ptr, "int", 1, "int");
    
    void* read_ptr = dlsym(libc_handle, "read");
    if (read_ptr) register_c_function(env, "read_c", read_ptr, "int", 3, "int", "int", "int");
    
    void* write_ptr = dlsym(libc_handle, "write");
    if (write_ptr) register_c_function(env, "write_c", write_ptr, "int", 3, "int", "int", "int");
    
    void* close_ptr = dlsym(libc_handle, "close");
    if (close_ptr) register_c_function(env, "close_c", close_ptr, "int", 1, "int");
    
    void* lseek_ptr = dlsym(libc_handle, "lseek");
    if (lseek_ptr) register_c_function(env, "lseek_c", lseek_ptr, "int", 3, "int", "int", "int");
    
    void* unlink_ptr = dlsym(libc_handle, "unlink");
    if (unlink_ptr) register_c_function(env, "unlink_c", unlink_ptr, "int", 1, "string");
    
    // ============================================
    // FCNTL FUNCTIONS (fcntl.h)
    // ============================================
    
    void* open_ptr = dlsym(libc_handle, "open");
    if (open_ptr) register_c_function(env, "open_c", open_ptr, "int", 3, "string", "int", "int");
    
    void* creat_ptr = dlsym(libc_handle, "creat");
    if (creat_ptr) register_c_function(env, "creat_c", creat_ptr, "int", 2, "string", "int");
    
    void* fcntl_ptr = dlsym(libc_handle, "fcntl");
    if (fcntl_ptr) register_c_function(env, "fcntl_c", fcntl_ptr, "int", 3, "int", "int", "int");
    
    // ============================================
    // STAT FUNCTIONS (sys/stat.h)
    // ============================================
    
    void* stat_ptr = dlsym(libc_handle, "stat");
    if (stat_ptr) register_c_function(env, "stat_c", stat_ptr, "int", 2, "string", "int");
    
    void* lstat_ptr = dlsym(libc_handle, "lstat");
    if (lstat_ptr) register_c_function(env, "lstat_c", lstat_ptr, "int", 2, "string", "int");
    
    void* fstat_ptr = dlsym(libc_handle, "fstat");
    if (fstat_ptr) register_c_function(env, "fstat_c", fstat_ptr, "int", 2, "int", "int");
    
    void* chmod_ptr = dlsym(libc_handle, "chmod");
    if (chmod_ptr) register_c_function(env, "chmod_c", chmod_ptr, "int", 2, "string", "int");
    
    void* mkdir_ptr = dlsym(libc_handle, "mkdir");
    if (mkdir_ptr) register_c_function(env, "mkdir_c", mkdir_ptr, "int", 2, "string", "int");
    
    void* rmdir_ptr = dlsym(libc_handle, "rmdir");
    if (rmdir_ptr) register_c_function(env, "rmdir_c", rmdir_ptr, "int", 1, "string");
    
    // ============================================
    // DLFCN FUNCTIONS (dlfcn.h)
    // ============================================
    
    void* dlopen_ptr = dlsym(libc_handle, "dlopen");
    if (dlopen_ptr) register_c_function(env, "dlopen_c", dlopen_ptr, "int", 2, "string", "int");
    
    void* dlsym_ptr = dlsym(libc_handle, "dlsym");
    if (dlsym_ptr) register_c_function(env, "dlsym_c", dlsym_ptr, "int", 2, "int", "string");
    
    void* dlclose_ptr = dlsym(libc_handle, "dlclose");
    if (dlclose_ptr) register_c_function(env, "dlclose_c", dlclose_ptr, "int", 1, "int");
    
    void* dlerror_ptr = dlsym(libc_handle, "dlerror");
    if (dlerror_ptr) register_c_function(env, "dlerror_c", dlerror_ptr, "string", 0);
    
    // ============================================
    // SIGNAL FUNCTIONS (signal.h)
    // ============================================
    
    void* signal_ptr = dlsym(libc_handle, "signal");
    if (signal_ptr) register_c_function(env, "signal_c", signal_ptr, "int", 2, "int", "int");
    
    void* raise_ptr = dlsym(libc_handle, "raise");
    if (raise_ptr) register_c_function(env, "raise_c", raise_ptr, "int", 1, "int");
    
    // ============================================
    // MATH FUNCTIONS (math.h)
    // ============================================
    
    void* sin_ptr = dlsym(libc_handle, "sin");
    if (sin_ptr) register_c_function(env, "sin_c", sin_ptr, "double", 1, "double");
    
    void* cos_ptr = dlsym(libc_handle, "cos");
    if (cos_ptr) register_c_function(env, "cos_c", cos_ptr, "double", 1, "double");
    
    void* tan_ptr = dlsym(libc_handle, "tan");
    if (tan_ptr) register_c_function(env, "tan_c", tan_ptr, "double", 1, "double");
    
    void* sqrt_ptr = dlsym(libc_handle, "sqrt");
    if (sqrt_ptr) register_c_function(env, "sqrt_c", sqrt_ptr, "double", 1, "double");
    
    void* pow_ptr = dlsym(libc_handle, "pow");
    if (pow_ptr) register_c_function(env, "pow_c", pow_ptr, "double", 2, "double", "double");
    
    void* exp_ptr = dlsym(libc_handle, "exp");
    if (exp_ptr) register_c_function(env, "exp_c", exp_ptr, "double", 1, "double");
    
    void* log_ptr = dlsym(libc_handle, "log");
    if (log_ptr) register_c_function(env, "log_c", log_ptr, "double", 1, "double");
    
    void* log10_ptr = dlsym(libc_handle, "log10");
    if (log10_ptr) register_c_function(env, "log10_c", log10_ptr, "double", 1, "double");
    
    void* fabs_ptr = dlsym(libc_handle, "fabs");
    if (fabs_ptr) register_c_function(env, "fabs_c", fabs_ptr, "double", 1, "double");
    
    void* ceil_ptr = dlsym(libc_handle, "ceil");
    if (ceil_ptr) register_c_function(env, "ceil_c", ceil_ptr, "double", 1, "double");
    
    void* floor_ptr = dlsym(libc_handle, "floor");
    if (floor_ptr) register_c_function(env, "floor_c", floor_ptr, "double", 1, "double");
    
    // ============================================
    // CTYPE FUNCTIONS (ctype.h)
    // ============================================
    
    void* isalnum_ptr = dlsym(libc_handle, "isalnum");
    if (isalnum_ptr) register_c_function(env, "isalnum_c", isalnum_ptr, "int", 1, "int");
    
    void* isalpha_ptr = dlsym(libc_handle, "isalpha");
    if (isalpha_ptr) register_c_function(env, "isalpha_c", isalpha_ptr, "int", 1, "int");
    
    void* isdigit_ptr = dlsym(libc_handle, "isdigit");
    if (isdigit_ptr) register_c_function(env, "isdigit_c", isdigit_ptr, "int", 1, "int");
    
    void* isspace_ptr = dlsym(libc_handle, "isspace");
    if (isspace_ptr) register_c_function(env, "isspace_c", isspace_ptr, "int", 1, "int");
    
    void* isupper_ptr = dlsym(libc_handle, "isupper");
    if (isupper_ptr) register_c_function(env, "isupper_c", isupper_ptr, "int", 1, "int");
    
    void* islower_ptr = dlsym(libc_handle, "islower");
    if (islower_ptr) register_c_function(env, "islower_c", islower_ptr, "int", 1, "int");
    
    void* toupper_ptr = dlsym(libc_handle, "toupper");
    if (toupper_ptr) register_c_function(env, "toupper_c", toupper_ptr, "int", 1, "int");
    
    void* tolower_ptr = dlsym(libc_handle, "tolower");
    if (tolower_ptr) register_c_function(env, "tolower_c", tolower_ptr, "int", 1, "int");


    // ============================================
    // SOCKET FUNCTIONS (sys/socket.h)
    // ============================================
    
    void* socket_ptr = dlsym(libc_handle, "socket");
    if (socket_ptr) register_c_function(env, "socket_c", socket_ptr, "int", 3, "int", "int", "int");
    
    void* bind_ptr = dlsym(libc_handle, "bind");
    if (bind_ptr) register_c_function(env, "bind_c", bind_ptr, "int", 3, "int", "int", "int");
    
    void* listen_ptr = dlsym(libc_handle, "listen");
    if (listen_ptr) register_c_function(env, "listen_c", listen_ptr, "int", 2, "int", "int");
    
    void* accept_ptr = dlsym(libc_handle, "accept");
    if (accept_ptr) register_c_function(env, "accept_c", accept_ptr, "int", 3, "int", "int", "int");
    
    void* connect_ptr = dlsym(libc_handle, "connect");
    if (connect_ptr) register_c_function(env, "connect_c", connect_ptr, "int", 3, "int", "int", "int");
    
    void* send_ptr = dlsym(libc_handle, "send");
    if (send_ptr) register_c_function(env, "send_c", send_ptr, "int", 4, "int", "int", "int", "int");
    
    void* recv_ptr = dlsym(libc_handle, "recv");
    if (recv_ptr) register_c_function(env, "recv_c", recv_ptr, "int", 4, "int", "int", "int", "int");
    
    // ============================================
    // PUTS & PUTCHAR (wrapper functions)
    // ============================================
    
    Value puts_func;
    puts_func.type = 5;
    puts_func.cfunc_val.func_ptr = (void*)call_puts;
    puts_func.cfunc_val.ret_type = &ffi_type_sint32;
    puts_func.cfunc_val.arg_count = 1;
    puts_func.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
    puts_func.cfunc_val.arg_types[0] = &ffi_type_pointer;
    ffi_prep_cif(&puts_func.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, (ffi_type*[]){&ffi_type_pointer});
    env_set(env, "puts", puts_func);
    
    Value putchar_func;
    putchar_func.type = 5;
    putchar_func.cfunc_val.func_ptr = (void*)call_putchar;
    putchar_func.cfunc_val.ret_type = &ffi_type_sint32;
    putchar_func.cfunc_val.arg_count = 1;
    putchar_func.cfunc_val.arg_types = malloc(sizeof(ffi_type*));
    putchar_func.cfunc_val.arg_types[0] = &ffi_type_sint32;
    ffi_prep_cif(&putchar_func.cfunc_val.cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, (ffi_type*[]){&ffi_type_sint32});
    env_set(env, "putchar", putchar_func);
}
// cette fonction pour trouver une méthode dans une implémentation
ASTNode* find_method(ASTNode* impl_node, char* method_name) {
    if (!impl_node || impl_node->type != NODE_IMPL) return NULL;
    
    for (int i = 0; i < impl_node->impl.methods->count; i++) {
        ASTNode* method = impl_node->impl.methods->nodes[i];
        if (method->type == NODE_FUNCTION && 
            strcmp(method->function.name, method_name) == 0) {
            return method;
        }
    }
    return NULL;
}


Value call_method(Value* obj, char* method_name, ASTNodeList* args, Environment* env) {
    Value result = {0};
    
    if (obj->type != 6) return result;
    
    ASTNode* impl_node = find_impl(obj->struct_val.struct_name);
    if (!impl_node) return result;
    
    ASTNode* method = find_method(impl_node, method_name);
    if (!method) return result;
    
    Environment* method_env = create_env(env);
    env_set(method_env, "self", *obj);
    
    if (args) {
        for (int i = 0; i < args->count; i++) {
            Value arg_val = evaluate_expr(args->nodes[i], env);
            if (method->function.params && i < method->function.params->count) {
                ASTNode* param = method->function.params->nodes[i];
                env_set(method_env, param->identifier.name, arg_val);
            }
        }
    }
    
    for (int i = 0; i < method->function.body->count; i++) {
        ASTNode* stmt = method->function.body->nodes[i];
        if (stmt->type == NODE_RETURN) {
            result = evaluate_expr(stmt->return_stmt.value, method_env);
            break;
        } else {
            evaluate_statement(stmt, method_env, NULL);  // Ajoutez NULL comme current_file
        }
    }
    
    free(method_env);
    return result;
}

Value evaluate_expr(ASTNode* node, Environment* env) {
    Value result = {0};
    
    switch (node->type) {
        // ==================== VALEURS LITTÉRALES ====================
       case NODE_RETURN_STRUCT_FIELD: {
    // Chercher la structure dans l'environnement
    char* struct_name = node->return_struct_field.struct_name;
    char* field_name = node->return_struct_field.field_name;
    
    Value* struct_val = env_get(env, struct_name);
    if (struct_val && struct_val->type == 6) {
        // Chercher le champ dans la structure
        for (int i = 0; i < struct_val->struct_val.field_count; i++) {
            if (struct_val->struct_val.fields[i].name && 
                strcmp(struct_val->struct_val.fields[i].name, field_name) == 0) {
                return *struct_val->struct_val.fields[i].value;
            }
        }
    }
    
    fprintf(stderr, "Error: Field '%s' not found in struct '%s'\n", 
            field_name, struct_name);
    return (Value){.type = 0, .int_val = 0};
}
        case NODE_NUMBER:
            result.type = 0;
            result.int_val = node->number.value;
            break;
            
        case NODE_FLOAT:
            result.type = 1;
            result.float_val = node->float_val.value;
            break;
            
        case NODE_STRING:
            result.type = 2;
            result.string_val = strdup(node->string_val.value);
            break;
            
        case NODE_BOOL:
            result.type = 3;
            result.bool_val = node->bool_val.value;
            break;
            
        case NODE_NIL:
            result.type = 0;
            result.int_val = 0;
            break;
            
        // ==================== IDENTIFIANT ====================
        case NODE_IDENTIFIER: {
    Value* val = env_get(env, node->identifier.name);
    if (val) {
        return *val;
    }
    // Si ce n'est pas une variable, peut-être que c'est une fonction ?
    // Les fonctions sont déjà dans l'environnement
    fprintf(stderr, "Undefined: %s\n", node->identifier.name);
    return (Value){.type = 0, .int_val = 0};
}
        
        // ==================== OPÉRATIONS BINAIRES ====================
        
    
    // Opérations binaires standard
    case NODE_BINARY_OP: {
    // Gestion des assignations composées
    if (node->binary.op == OP_ADD_ASSIGN ||
        node->binary.op == OP_SUB_ASSIGN ||
        node->binary.op == OP_MUL_ASSIGN ||
        node->binary.op == OP_DIV_ASSIGN ||
        node->binary.op == OP_MOD_ASSIGN) {
        
        if (node->binary.left->type == NODE_IDENTIFIER) {
            char* var_name = node->binary.left->identifier.name;
            Value* current = env_get(env, var_name);
            Value right_val = evaluate_expr(node->binary.right, env);
            Value new_val = {0};
            
            if (current) {
                switch (node->binary.op) {
                    case OP_ADD_ASSIGN:
                        if (current->type == 0 && right_val.type == 0) {
                            new_val.type = 0;
                            new_val.int_val = current->int_val + right_val.int_val;
                        }
                        break;
                    case OP_SUB_ASSIGN:
                        if (current->type == 0 && right_val.type == 0) {
                            new_val.type = 0;
                            new_val.int_val = current->int_val - right_val.int_val;
                        }
                        break;
                    case OP_MUL_ASSIGN:
                        if (current->type == 0 && right_val.type == 0) {
                            new_val.type = 0;
                            new_val.int_val = current->int_val * right_val.int_val;
                        }
                        break;
                    case OP_DIV_ASSIGN:
                        if (current->type == 0 && right_val.type == 0 && right_val.int_val != 0) {
                            new_val.type = 0;
                            new_val.int_val = current->int_val / right_val.int_val;
                        }
                        break;
                    case OP_MOD_ASSIGN:
                        if (current->type == 0 && right_val.type == 0 && right_val.int_val != 0) {
                            new_val.type = 0;
                            new_val.int_val = current->int_val % right_val.int_val;
                        }
                        break;
                }
                env_set(env, var_name, new_val);
                result = new_val;
            }
        }
        break;
    }
    
    // Assignation simple
    
if (node->binary.op == OP_ASSIGN) {
    // Cas 1: Assignation à un identifiant
    if (node->binary.left->type == NODE_IDENTIFIER) {
        char* var_name = node->binary.left->identifier.name;
        Value right_val = evaluate_expr(node->binary.right, env);
        env_set(env, var_name, right_val);
        result = right_val;
    }
    // Cas 2: Assignation à un élément de tableau/dictionnaire (a[2] = 99 ou dict["key"] = value)
    else if (node->binary.left->type == NODE_ARRAY_ACCESS) {
        ASTNode* array_access = node->binary.left;
        
        // Évaluer le container
        Value container = evaluate_expr(array_access->array_access.array, env);
        Value idx = evaluate_expr(array_access->array_access.index, env);
        Value right_val = evaluate_expr(node->binary.right, env);
        
        // Cas 2a: Tableau
        if (container.type == 8 && idx.type == 0) {
            int index = idx.int_val;
            if (index >= 0 && index < container.array_val.count) {
                ASTNode* element = container.array_val.elements->nodes[index];
                if (element->type == NODE_NUMBER) {
                    element->number.value = right_val.int_val;
                } else if (element->type == NODE_STRING) {
                    free(element->string_val.value);
                    element->string_val.value = right_val.string_val ? strdup(right_val.string_val) : strdup("");
                } else if (element->type == NODE_FLOAT) {
                    element->float_val.value = right_val.float_val;
                } else if (element->type == NODE_BOOL) {
                    element->bool_val.value = right_val.bool_val;
                }
                result = right_val;
            }
        }
        // Cas 2b: Dictionnaire
        else if (container.type == 10) {
            int found = 0;
            
            printf("DEBUG: Modifying dictionary, looking for key\n");
            
            // Chercher la clé existante
            for (int i = 0; i < container.dict_val.count; i++) {
                Value* k = container.dict_val.entries[i].key;
                
                // Utiliser la fonction de comparaison
                if (values_equal(*k, idx)) {
                    // Modifier la valeur existante
                    printf("DEBUG: Found key, updating value\n");
                    if (right_val.type == 2) {
                        if (container.dict_val.entries[i].value->string_val) 
                            free(container.dict_val.entries[i].value->string_val);
                        container.dict_val.entries[i].value->type = 2;
                        container.dict_val.entries[i].value->string_val = strdup(right_val.string_val);
                    } else {
                        *(container.dict_val.entries[i].value) = right_val;
                    }
                    found = 1;
                    break;
                }
            }
            
            // Si la clé n'existe pas, l'ajouter
            if (!found) {
                printf("DEBUG: Key not found, adding new entry\n");
                
                // Agrandir le tableau si nécessaire
                if (container.dict_val.count >= container.dict_val.capacity) {
                    container.dict_val.capacity = container.dict_val.capacity == 0 ? 8 : container.dict_val.capacity * 2;
                    container.dict_val.entries = realloc(container.dict_val.entries,
                        container.dict_val.capacity * sizeof(*container.dict_val.entries));
                    printf("DEBUG: Reallocated to capacity %d\n", container.dict_val.capacity);
                }
                
                // Ajouter la nouvelle clé
                container.dict_val.entries[container.dict_val.count].key = malloc(sizeof(Value));
                if (idx.type == 2) {
                    container.dict_val.entries[container.dict_val.count].key->type = 2;
                    container.dict_val.entries[container.dict_val.count].key->string_val = strdup(idx.string_val);
                } else {
                    *(container.dict_val.entries[container.dict_val.count].key) = idx;
                }
                
                // Ajouter la nouvelle valeur
                container.dict_val.entries[container.dict_val.count].value = malloc(sizeof(Value));
                if (right_val.type == 2) {
                    container.dict_val.entries[container.dict_val.count].value->type = 2;
                    container.dict_val.entries[container.dict_val.count].value->string_val = strdup(right_val.string_val);
                } else {
                    *(container.dict_val.entries[container.dict_val.count].value) = right_val;
                }
                
                container.dict_val.count++;
                printf("DEBUG: Added entry, count = %d\n", container.dict_val.count);
            }
            
            // CRUCIAL: Sauvegarder le dictionnaire modifié dans l'environnement
            if (array_access->array_access.array->type == NODE_IDENTIFIER) {
                printf("DEBUG: Saving dictionary back to variable '%s'\n", 
                       array_access->array_access.array->identifier.name);
                env_set(env, array_access->array_access.array->identifier.name, container);
            }
            else if (array_access->array_access.array->type == NODE_MEMBER_ACCESS) {
                // Gestion des dictionnaires imbriqués dans des structures
                ASTNode* member_access = array_access->array_access.array;
                Value obj = evaluate_expr(member_access->member.object, env);
                char* member_name = member_access->member.member;
                
                if (obj.type == 6) {
                    for (int i = 0; i < obj.struct_val.field_count; i++) {
                        if (obj.struct_val.fields[i].name && 
                            strcmp(obj.struct_val.fields[i].name, member_name) == 0) {
                            *(obj.struct_val.fields[i].value) = container;
                            if (member_access->member.object->type == NODE_IDENTIFIER) {
                                env_set(env, member_access->member.object->identifier.name, obj);
                            }
                            break;
                        }
                    }
                }
            }
            
            result = right_val;
        }
    }
        // Cas 3: Assignation à un membre de structure
        else if (node->binary.left->type == NODE_MEMBER_ACCESS) {
            ASTNode* member_access = node->binary.left;
            Value obj = evaluate_expr(member_access->member.object, env);
            Value right_val = evaluate_expr(node->binary.right, env);
            char* member_name = member_access->member.member;
            
            if (obj.type == 6) {
                int found = 0;
                for (int i = 0; i < obj.struct_val.field_count; i++) {
                    if (obj.struct_val.fields[i].name && 
                        strcmp(obj.struct_val.fields[i].name, member_name) == 0) {
                        if (right_val.type == 2) {
                            if (obj.struct_val.fields[i].value->string_val) free(obj.struct_val.fields[i].value->string_val);
                            obj.struct_val.fields[i].value->string_val = strdup(right_val.string_val);
                            obj.struct_val.fields[i].value->type = 2;
                        } else {
                            *(obj.struct_val.fields[i].value) = right_val;
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    fprintf(stderr, "Error: Field '%s' not found in struct\n", member_name);
                }
                if (member_access->member.object->type == NODE_IDENTIFIER) {
                    env_set(env, member_access->member.object->identifier.name, obj);
                }
                result = right_val;
            }
        }
        break;
    }
    
    // Opérations binaires standard
    Value left = evaluate_expr(node->binary.left, env);
    Value right = evaluate_expr(node->binary.right, env);
    
    switch (node->binary.op) {
        case OP_ADD:
            if (left.type == 0 && right.type == 0) {
                result.type = 0;
                result.int_val = left.int_val + right.int_val;
            } else if (left.type == 1 && right.type == 1) {
                result.type = 1;
                result.float_val = left.float_val + right.float_val;
            } else if (left.type == 2 || right.type == 2 || left.type == 8 || right.type == 8 || left.type == 10 || right.type == 10) {
                char buf1[1024], buf2[1024];
                char* left_str = "";
                char* right_str = "";
                int left_alloc = 0, right_alloc = 0;
                
                // Conversion de left
                if (left.type == 0) { sprintf(buf1, "%d", left.int_val); left_str = buf1; }
                else if (left.type == 1) { sprintf(buf1, "%f", left.float_val); left_str = buf1; }
                else if (left.type == 2) left_str = left.string_val;
                else if (left.type == 3) left_str = left.bool_val ? "true" : "false";
                else if (left.type == 8) {
                    char* temp = malloc(4096);
                    char* ptr = temp;
                    ptr += sprintf(ptr, "[");
                    for (int i = 0; i < left.array_val.count; i++) {
                        if (i > 0) ptr += sprintf(ptr, ", ");
                        Value elem = evaluate_expr(left.array_val.elements->nodes[i], NULL);
                        if (elem.type == 0) ptr += sprintf(ptr, "%d", elem.int_val);
                        else if (elem.type == 1) ptr += sprintf(ptr, "%f", elem.float_val);
                        else if (elem.type == 2) ptr += sprintf(ptr, "%s", elem.string_val);
                        else if (elem.type == 3) ptr += sprintf(ptr, "%s", elem.bool_val ? "true" : "false");
                        else ptr += sprintf(ptr, "?");
                    }
                    ptr += sprintf(ptr, "]");
                    left_str = strdup(temp);
                    left_alloc = 1;
                    free(temp);
                }
                else if (left.type == 10) {
                    char* temp = malloc(4096);
                    char* ptr = temp;
                    ptr += sprintf(ptr, "{");
                    for (int i = 0; i < left.dict_val.count; i++) {
                        if (i > 0) ptr += sprintf(ptr, ", ");
                        Value* k = left.dict_val.entries[i].key;
                        Value* v = left.dict_val.entries[i].value;
                        if (k->type == 0) ptr += sprintf(ptr, "%d: ", k->int_val);
                        else if (k->type == 1) ptr += sprintf(ptr, "%f: ", k->float_val);
                        else if (k->type == 2) ptr += sprintf(ptr, "%s: ", k->string_val);
                        else if (k->type == 3) ptr += sprintf(ptr, "%s: ", k->bool_val ? "true" : "false");
                        else ptr += sprintf(ptr, "?: ");
                        if (v->type == 0) ptr += sprintf(ptr, "%d", v->int_val);
                        else if (v->type == 1) ptr += sprintf(ptr, "%f", v->float_val);
                        else if (v->type == 2) ptr += sprintf(ptr, "%s", v->string_val);
                        else if (v->type == 3) ptr += sprintf(ptr, "%s", v->bool_val ? "true" : "false");
                        else ptr += sprintf(ptr, "?");
                    }
                    ptr += sprintf(ptr, "}");
                    left_str = strdup(temp);
                    left_alloc = 1;
                    free(temp);
                }
                
                // Conversion de right
                if (right.type == 0) { sprintf(buf2, "%d", right.int_val); right_str = buf2; }
                else if (right.type == 1) { sprintf(buf2, "%f", right.float_val); right_str = buf2; }
                else if (right.type == 2) right_str = right.string_val;
                else if (right.type == 3) right_str = right.bool_val ? "true" : "false";
                else if (right.type == 8) {
                    char* temp = malloc(4096);
                    char* ptr = temp;
                    ptr += sprintf(ptr, "[");
                    for (int i = 0; i < right.array_val.count; i++) {
                        if (i > 0) ptr += sprintf(ptr, ", ");
                        Value elem = evaluate_expr(right.array_val.elements->nodes[i], NULL);
                        if (elem.type == 0) ptr += sprintf(ptr, "%d", elem.int_val);
                        else if (elem.type == 1) ptr += sprintf(ptr, "%f", elem.float_val);
                        else if (elem.type == 2) ptr += sprintf(ptr, "%s", elem.string_val);
                        else if (elem.type == 3) ptr += sprintf(ptr, "%s", elem.bool_val ? "true" : "false");
                        else ptr += sprintf(ptr, "?");
                    }
                    ptr += sprintf(ptr, "]");
                    right_str = strdup(temp);
                    right_alloc = 1;
                    free(temp);
                }
                else if (right.type == 10) {
                    char* temp = malloc(4096);
                    char* ptr = temp;
                    ptr += sprintf(ptr, "{");
                    for (int i = 0; i < right.dict_val.count; i++) {
                        if (i > 0) ptr += sprintf(ptr, ", ");
                        Value* k = right.dict_val.entries[i].key;
                        Value* v = right.dict_val.entries[i].value;
                        if (k->type == 0) ptr += sprintf(ptr, "%d: ", k->int_val);
                        else if (k->type == 1) ptr += sprintf(ptr, "%f: ", k->float_val);
                        else if (k->type == 2) ptr += sprintf(ptr, "%s: ", k->string_val);
                        else if (k->type == 3) ptr += sprintf(ptr, "%s: ", k->bool_val ? "true" : "false");
                        else ptr += sprintf(ptr, "?: ");
                        if (v->type == 0) ptr += sprintf(ptr, "%d", v->int_val);
                        else if (v->type == 1) ptr += sprintf(ptr, "%f", v->float_val);
                        else if (v->type == 2) ptr += sprintf(ptr, "%s", v->string_val);
                        else if (v->type == 3) ptr += sprintf(ptr, "%s", v->bool_val ? "true" : "false");
                        else ptr += sprintf(ptr, "?");
                    }
                    ptr += sprintf(ptr, "}");
                    right_str = strdup(temp);
                    right_alloc = 1;
                    free(temp);
                }
                
                result.type = 2;
                result.string_val = malloc(strlen(left_str) + strlen(right_str) + 1);
                strcpy(result.string_val, left_str);
                strcat(result.string_val, right_str);
                
                if (left_alloc) free((void*)left_str);
                if (right_alloc) free((void*)right_str);
            }
            break;
            
        case OP_SUB:
            if (left.type == 0 && right.type == 0) {
                result.type = 0;
                result.int_val = left.int_val - right.int_val;
            } else if (left.type == 1 && right.type == 1) {
                result.type = 1;
                result.float_val = left.float_val - right.float_val;
            }
            break;
            
        case OP_MUL:
            if (left.type == 0 && right.type == 0) {
                result.type = 0;
                result.int_val = left.int_val * right.int_val;
            } else if (left.type == 1 && right.type == 1) {
                result.type = 1;
                result.float_val = left.float_val * right.float_val;
            }
            break;
            
        case OP_DIV:
            if (left.type == 0 && right.type == 0 && right.int_val != 0) {
                result.type = 0;
                result.int_val = left.int_val / right.int_val;
            } else if (left.type == 1 && right.type == 1 && right.float_val != 0) {
                result.type = 1;
                result.float_val = left.float_val / right.float_val;
            }
            break;
            
        case OP_MOD:
            if (left.type == 0 && right.type == 0 && right.int_val != 0) {
                result.type = 0;
                result.int_val = left.int_val % right.int_val;
            }
            break;
            
        case OP_LT:
            result.type = 3;
            if (left.type == 0 && right.type == 0) result.bool_val = left.int_val < right.int_val;
            else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val < right.float_val;
            break;
            
        case OP_GT:
            result.type = 3;
            if (left.type == 0 && right.type == 0) result.bool_val = left.int_val > right.int_val;
            else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val > right.float_val;
            break;
            
        case OP_LTE:
            result.type = 3;
            if (left.type == 0 && right.type == 0) result.bool_val = left.int_val <= right.int_val;
            else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val <= right.float_val;
            break;
            
        case OP_GTE:
            result.type = 3;
            if (left.type == 0 && right.type == 0) result.bool_val = left.int_val >= right.int_val;
            else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val >= right.float_val;
            break;
            
        case OP_EQ:
            result.type = 3;
            if (left.type == 0 && right.type == 0) result.bool_val = left.int_val == right.int_val;
            else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val == right.float_val;
            else if (left.type == 2 && right.type == 2) result.bool_val = strcmp(left.string_val, right.string_val) == 0;
            else if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val == right.bool_val;
            else if (left.type == 8 && right.type == 8) result.bool_val = (left.array_val.elements == right.array_val.elements);
            else if (left.type == 10 && right.type == 10) result.bool_val = (left.dict_val.entries == right.dict_val.entries);
            break;
            
        case OP_NEQ:
            result.type = 3;
            if (left.type == 0 && right.type == 0) result.bool_val = left.int_val != right.int_val;
            else if (left.type == 1 && right.type == 1) result.bool_val = left.float_val != right.float_val;
            else if (left.type == 2 && right.type == 2) result.bool_val = strcmp(left.string_val, right.string_val) != 0;
            else if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val != right.bool_val;
            break;
            
        case OP_AND:
            result.type = 3;
            if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val && right.bool_val;
            break;
            
        case OP_OR:
            result.type = 3;
            if (left.type == 3 && right.type == 3) result.bool_val = left.bool_val || right.bool_val;
            break;
            
        case OP_RANGE:
            result.type = 0;
            result.int_val = 0;
            break;
            
        case OP_PIPE:
            result = right;
            break;
            
        default:
            result.type = 0;
            result.int_val = 0;
            break;
    }
    break;
}
        case NODE_DICT: {
    result.type = VALUE_TYPE_DICT;
    result.dict_val.entries = NULL;
    result.dict_val.count = 0;
    result.dict_val.capacity = 0;
    
    if (node->dict.entries) {
        for (int i = 0; i < node->dict.entries->count; i++) {
            ASTNode* pair = node->dict.entries->nodes[i];
            if (pair->type == NODE_BINARY_OP && pair->binary.op == OP_ASSIGN) {
                Value key = evaluate_expr(pair->binary.left, env);
                Value val = evaluate_expr(pair->binary.right, env);
                
                // Ajouter au dictionnaire
                if (result.dict_val.count >= result.dict_val.capacity) {
                    result.dict_val.capacity = result.dict_val.capacity == 0 ? 8 : result.dict_val.capacity * 2;
                    result.dict_val.entries = realloc(result.dict_val.entries, 
                        result.dict_val.capacity * sizeof(*result.dict_val.entries));
                }
                
                result.dict_val.entries[result.dict_val.count].key = malloc(sizeof(Value));
                result.dict_val.entries[result.dict_val.count].value = malloc(sizeof(Value));
                *(result.dict_val.entries[result.dict_val.count].key) = key;
                *(result.dict_val.entries[result.dict_val.count].value) = val;
                result.dict_val.count++;
            }
        }
    }
    break;
}

case NODE_DICT_ACCESS: {
    Value dict_val = evaluate_expr(node->dict_access.dict, env);
    Value key_val = evaluate_expr(node->dict_access.key, env);
    
    if (dict_val.type == VALUE_TYPE_DICT) {
        for (int i = 0; i < dict_val.dict_val.count; i++) {
            Value* k = dict_val.dict_val.entries[i].key;
            // Comparaison des clés
            int match = 0;
            if (k->type == key_val.type) {
                if (k->type == 0) match = (k->int_val == key_val.int_val);
                else if (k->type == 1) match = (k->float_val == key_val.float_val);
                else if (k->type == 2) match = (strcmp(k->string_val, key_val.string_val) == 0);
                else if (k->type == 3) match = (k->bool_val == key_val.bool_val);
            }
            if (match) {
                result = *(dict_val.dict_val.entries[i].value);
                break;
            }
        }
    }
    break;
}
        case NODE_F_STRING: {
    char* template = node->f_string.template;
    char* result_str = malloc(strlen(template) * 4 + 4096);
    char* ptr = template;
    char* out = result_str;
    
    // Fonction helper pour trimmer
    #define TRIM(s) do { \
        while (*s == ' ') s++; \
        char* _end = s + strlen(s) - 1; \
        while (_end > s && *_end == ' ') *_end-- = '\0'; \
    } while(0)
    
    while (*ptr) {
        if (*ptr == '{' && (ptr == template || *(ptr-1) != '\\')) {
            char* start = ptr + 1;
            char* end = strchr(start, '}');
            if (end) {
                int len = end - start;
                char* expr_str = malloc(len + 1);
                strncpy(expr_str, start, len);
                expr_str[len] = '\0';
                
                // Trim
                char* trimmed = expr_str;
                TRIM(trimmed);
                
                char val_str[1024] = "";
                int evaluated = 0;
                
                // 1. Variable simple
                Value* val = env_get(env, trimmed);
                if (val) {
                    if (val->type == 0) {
                        sprintf(val_str, "%d", val->int_val);
                        evaluated = 1;
                    } else if (val->type == 1) {
                        sprintf(val_str, "%f", val->float_val);
                        evaluated = 1;
                    } else if (val->type == 2) {
                        sprintf(val_str, "%s", val->string_val);
                        evaluated = 1;
                    } else if (val->type == 3) {
                        sprintf(val_str, "%s", val->bool_val ? "true" : "false");
                        evaluated = 1;
                    }
                }
                
                // 2. Chercher tous les opérateurs
                if (!evaluated) {
                    char* op = NULL;
                    char op_char = 0;
                    
                    // Priorité: +, -, *, /
                    if ((op = strstr(trimmed, "*"))) op_char = '*';
                    else if ((op = strstr(trimmed, "/"))) op_char = '/';
                    else if ((op = strstr(trimmed, "+"))) op_char = '+';
                    else if ((op = strstr(trimmed, "-"))) op_char = '-';
                    
                    if (op) {
                        *op = '\0';
                        char* left = trimmed;
                        char* right = op + 1;
                        
                        TRIM(left);
                        TRIM(right);
                        
                        Value* v1 = env_get(env, left);
                        Value* v2 = env_get(env, right);
                        
                        if (v1 && v2) {
                            if (v1->type == 0 && v2->type == 0) {
                                int l = v1->int_val;
                                int r = v2->int_val;
                                
                                switch (op_char) {
                                    case '+': sprintf(val_str, "%d", l + r); break;
                                    case '-': sprintf(val_str, "%d", l - r); break;
                                    case '*': sprintf(val_str, "%d", l * r); break;
                                    case '/': 
                                        if (r != 0) sprintf(val_str, "%d", l / r);
                                        else sprintf(val_str, "ERR");
                                        break;
                                }
                                evaluated = 1;
                            } else if (v1->type == 2 && v2->type == 2 && op_char == '+') {
                                sprintf(val_str, "%s%s", v1->string_val, v2->string_val);
                                evaluated = 1;
                            }
                        }
                        
                        // Si pas de variables, essayer comme nombres
                        if (!evaluated) {
                            int l = atoi(left);
                            int r = atoi(right);
                            
                            // Vérifier que c'est vraiment des nombres
                            if ((l != 0 || left[0] == '0') && (r != 0 || right[0] == '0')) {
                                switch (op_char) {
                                    case '+': sprintf(val_str, "%d", l + r); break;
                                    case '-': sprintf(val_str, "%d", l - r); break;
                                    case '*': sprintf(val_str, "%d", l * r); break;
                                    case '/': 
                                        if (r != 0) sprintf(val_str, "%d", l / r);
                                        else sprintf(val_str, "ERR");
                                        break;
                                }
                                evaluated = 1;
                            }
                        }
                        
                        *op = op_char; // Restaurer
                    }
                }
                
                if (!evaluated) {
                    snprintf(val_str, sizeof(val_str), "{%s}", trimmed);
                }
                
                strcpy(out, val_str);
                out += strlen(val_str);
                
                free(expr_str);
                ptr = end + 1;
                continue;
            }
        } else if (*ptr == '\\' && *(ptr+1) == '{') {
            ptr++;
        }
        
        *out++ = *ptr++;
    }
    *out = '\0';
    
    result.type = 2;
    result.string_val = result_str;
    break;
}
        // ==================== OPÉRATIONS UNAIRES ====================
        case NODE_UNARY_OP: {
            Value operand = evaluate_expr(node->unary.operand, env);
            switch (node->unary.op) {
                case OP_NOT:
                    result.type = 3;
                    result.bool_val = !operand.bool_val;
                    break;
                case OP_NEG:
                    if (operand.type == 0) {
                        result.type = 0;
                        result.int_val = -operand.int_val;
                    }
                    break;
                default:
                    result.type = 0;
                    result.int_val = 0;
                    break;
            }
            break;
        }
        
        // ==================== STRUCTURE INIT ====================
        case NODE_STRUCT_INIT: {
            result.type = 6;
            result.struct_val.struct_name = strdup(node->struct_init.name);
            
            int field_count = 0;
            if (node->struct_init.fields) {
                field_count = node->struct_init.fields->count;
            }
            
            result.struct_val.field_count = field_count;
            result.struct_val.fields = malloc(field_count * sizeof(*result.struct_val.fields));
            
            for (int i = 0; i < field_count; i++) {
                ASTNode* field_node = node->struct_init.fields->nodes[i];
                if (field_node->type == NODE_FIELD_INIT) {
                    result.struct_val.fields[i].name = strdup(field_node->field_init.name);
                    result.struct_val.fields[i].value = malloc(sizeof(Value));
                    *(result.struct_val.fields[i].value) = evaluate_expr(field_node->field_init.value, env);
                } else {
                    result.struct_val.fields[i].name = NULL;
                    result.struct_val.fields[i].value = NULL;
                }
            }
            break;
        }

        

case NODE_ARRAY: {
    Value arr_val;
    arr_val.type = 8; // Type array
    arr_val.array_val.elements = node->array.elements;
    arr_val.array_val.count = node->array.elements ? node->array.elements->count : 0;
    return arr_val;
}
case NODE_SYSF:
case NODE_SH: {
    Value cmd_val = evaluate_expr(node->sysf.command, env);
    
    if (cmd_val.type != 2) {
        fprintf(stderr, "Error: sysf/sh expects a string command\n");
        result.type = 0;
        result.int_val = -1;
        break;
    }
    
    char* command = cmd_val.string_val;
    
    if (node->type == NODE_SYSF) {
        // sysf - capturer la sortie
        char buffer[4096];
        FILE* pipe = popen(command, "r");
        if (pipe) {
            char* output = malloc(1);
            output[0] = '\0';
            size_t total = 0;
            
            while (fgets(buffer, sizeof(buffer), pipe)) {
                size_t len = strlen(buffer);
                output = realloc(output, total + len + 1);
                memcpy(output + total, buffer, len);
                total += len;
                output[total] = '\0';
            }
            pclose(pipe);
            
            // Enlever le \n final si présent
            if (total > 0 && output[total-1] == '\n') {
                output[total-1] = '\0';
            }
            
            result.type = 2;
            result.string_val = output;
        } else {
            result.type = 2;
            result.string_val = strdup("");
        }
    } else {
        // sh - exécuter sans capture, retourner le code de sortie
        int ret = system(command);
        result.type = 0;
        result.int_val = WEXITSTATUS(ret);
    }
    break;
}

case NODE_AWAIT: {
    Value val = evaluate_expr(node->await.expr, env);
    
    if (val.type == VALUE_TYPE_PROMISE) {
        Promise* p = (Promise*)val.int_val;
        result = await_promise(p, env);
        free(p->command);
        free(p);
    } else if (val.type == 2 && val.string_val) {
        // Utiliser la nouvelle fonction builtin_await
        Value args[1];
        args[0] = val;
        result = builtin_await(args, 1);
    } else {
        result = val;
    }
    break;
}

case NODE_AWAIT_BLOCK: {
    // Exécuter un bloc de manière asynchrone
    Promise* p = create_promise(NULL);
    p->state = 1;  // resolved immediately
    
    // Exécuter le bloc dans un thread séparé (simplifié)
    for (int i = 0; i < node->await_block.body->count; i++) {
        evaluate_statement(node->await_block.body->nodes[i], env, NULL);
    }
    
    result.type = VALUE_TYPE_PROMISE;
    result.int_val = (int)p;
    break;
}

case NODE_SPAWN: {
    // Lancer une tâche en parallèle
    Value task = evaluate_expr(node->spawn.expr, env);
    
    Promise* p = create_promise(NULL);
    
    if (task.type == 4) {  // function
        // Exécuter la fonction dans un processus séparé
        pid_t pid = fork();
        
        if (pid == 0) {
            // Enfant
            Environment* child_env = create_env(env);
            Value result = {0};
            
            // Exécuter la fonction
            for (int i = 0; i < task.func_val.node->function.body->count; i++) {
                ASTNode* stmt = task.func_val.node->function.body->nodes[i];
                if (stmt->type == NODE_RETURN) {
                    result = evaluate_expr(stmt->return_stmt.value, child_env);
                    break;
                } else {
                    evaluate_statement(stmt, child_env, NULL);
                }
            }
            
            // Envoyer le résultat au parent (via pipe)
            exit(result.int_val);
        } else {
            p->pid = pid;
            p->state = 0;
        }
    }
    
    result.type = VALUE_TYPE_PROMISE;
    result.int_val = (int)p;
    break;
}

case NODE_ARRAY_ACCESS: {
    Value container = evaluate_expr(node->array_access.array, env);
    Value idx = evaluate_expr(node->array_access.index, env);
    
    // Cas 1: Tableau
    if (container.type == 8 && idx.type == 0) {
        int index = idx.int_val;
        if (index >= 0 && index < container.array_val.count) {
            return evaluate_expr(container.array_val.elements->nodes[index], env);
        }
    }
    // Cas 2: Dictionnaire
    else if (container.type == 10) {
        for (int i = 0; i < container.dict_val.count; i++) {
            Value* k = container.dict_val.entries[i].key;
            int match = 0;
            if (k->type == idx.type) {
                if (k->type == 0) match = (k->int_val == idx.int_val);
                else if (k->type == 1) match = (k->float_val == idx.float_val);
                else if (k->type == 2) match = (strcmp(k->string_val, idx.string_val) == 0);
                else if (k->type == 3) match = (k->bool_val == idx.bool_val);
            }
            if (match) {
                // Retourner une COPIE de la valeur
                return *(container.dict_val.entries[i].value);
            }
        }
        // Clé non trouvée, retourner nil
        return (Value){.type = 0, .int_val = 0};
    }
    return (Value){.type = 0, .int_val = 0};
}
case NODE_LAMBDA: {
    Value lambda_val;
    lambda_val.type = 9; // Type lambda
    lambda_val.lambda_val.node = node;
    lambda_val.lambda_val.closure = env;
    return lambda_val;
}
        // ==================== ACCÈS MEMBRE ====================
        case NODE_MEMBER_ACCESS: {
            Value obj = evaluate_expr(node->member.object, env);
            
            if (obj.type == 6) {
                char* member_name = node->member.member;
                Value* found = NULL;
                for (int i = 0; i < obj.struct_val.field_count; i++) {
                    if (obj.struct_val.fields[i].name && 
                        strcmp(obj.struct_val.fields[i].name, member_name) == 0) {
                        found = obj.struct_val.fields[i].value;
                        break;
                    }
                }
                if (found) {
                    result = *found;
                } else {
                    result.type = 0;
                    result.int_val = 0;
                }
            }
            break;
        }
        
        // ==================== ACCÈS STATIQUE (MODULE) ====================
        case NODE_STATIC_ACCESS: {
    Value obj = evaluate_expr(node->static_access.object, env);
    
    if (obj.type == 7) {
        LoadedModule* mod = (LoadedModule*)obj.int_val;
        
        Value* val = env_get(mod->env, node->static_access.member);
        if (val) {
            
            return *val;
        }
        printf("ERROR: %s NOT found in module\n", node->static_access.member);
    }
    return (Value){.type = 0};
}
        // ==================== APPEL DE MÉTHODE ====================
case NODE_METHOD_CALL: {
    Value obj = evaluate_expr(node->method_call.object, env);
    
    // Cas 1: Structure (type 6)
    if (obj.type == 6) {
        char* method_name = node->method_call.method;
        ASTNode* impl_node = find_impl(obj.struct_val.struct_name);
        
        if (impl_node) {
            ASTNode* method = find_method(impl_node, method_name);
            if (method) {
                Environment* method_env = create_env(env);
                if (method->function.params && method->function.params->count > 0) {
                    ASTNode* first_param = method->function.params->nodes[0];
                    env_set(method_env, first_param->identifier.name, obj);
                    if (node->method_call.args) {
                        for (int i = 0; i < node->method_call.args->count && (i + 1) < method->function.params->count; i++) {
                            Value arg_val = evaluate_expr(node->method_call.args->nodes[i], env);
                            ASTNode* param = method->function.params->nodes[i + 1];
                            env_set(method_env, param->identifier.name, arg_val);
                        }
                    }
                } else {
                    env_set(method_env, "self", obj);
                }
                
                for (int i = 0; i < method->function.body->count; i++) {
                    ASTNode* stmt = method->function.body->nodes[i];
                    if (stmt->type == NODE_RETURN) {
                        result = evaluate_expr(stmt->return_stmt.value, method_env);
                        break;
                    } else {
                        evaluate_statement(stmt, method_env, NULL);
                    }
                }
                free(method_env);
            }
        }
    }
    // === NOUVEAU : Cas 2: Module (type 7) ===
    else if (obj.type == 7) {
        LoadedModule* module = (LoadedModule*)obj.int_val;
        char* method_name = node->method_call.method;
        Value* func = env_get(module->env, method_name);
        
        if (func && func->type == 4) {
            Environment* func_env = create_env(func->func_val.closure);
            
            if (node->method_call.args && func->func_val.node->function.params) {
                int arg_count = node->method_call.args->count;
                int param_count = func->func_val.node->function.params->count;
                for (int i = 0; i < arg_count && i < param_count; i++) {
                    Value arg_val = evaluate_expr(node->method_call.args->nodes[i], env);
                    ASTNode* param = func->func_val.node->function.params->nodes[i];
                    env_set(func_env, param->identifier.name, arg_val);
                }
            }
            
            for (int i = 0; i < func->func_val.node->function.body->count; i++) {
                ASTNode* stmt = func->func_val.node->function.body->nodes[i];
                if (stmt->type == NODE_RETURN) {
                    result = evaluate_expr(stmt->return_stmt.value, func_env);
                    break;
                } else {
                    evaluate_statement(stmt, func_env, NULL);
                }
            }
            free(func_env);
        } else {
            fprintf(stderr, "Error: Function '%s' not found in module\n", method_name);
        }
    }
    break;
}
        
        // ==================== APPEL DE FONCTION ====================
        case NODE_CALL: {
    char* func_name = node->call.callee->identifier.name;
    Value* func = env_get(env, func_name);
    
    if (func && func->type == 4) {
        Environment* func_env = create_env(func->func_val.closure);
        
        if (node->call.args && func->func_val.node->function.params) {
            for (int i = 0; i < node->call.args->count && i < func->func_val.node->function.params->count; i++) {
                Value arg_val = evaluate_expr(node->call.args->nodes[i], env);
                ASTNode* param = func->func_val.node->function.params->nodes[i];
                env_set(func_env, param->identifier.name, arg_val);
            }
        }
        
        for (int i = 0; i < func->func_val.node->function.body->count; i++) {
            ASTNode* stmt = func->func_val.node->function.body->nodes[i];
            if (stmt->type == NODE_RETURN) {
                result = evaluate_expr(stmt->return_stmt.value, func_env);
                break;
            } else {
                evaluate_statement(stmt, func_env, NULL);
            }
        }
        free(func_env);
    } 
    else if (func && func->type == 5) {
        int arg_count = node->call.args ? node->call.args->count : 0;
        Value* args = malloc(arg_count * sizeof(Value));
        for (int i = 0; i < arg_count; i++) {
            args[i] = evaluate_expr(node->call.args->nodes[i], env);
        }
        result = call_c_function_ffi(func->cfunc_val.func_ptr, args, arg_count,
                                     func->cfunc_val.ret_type, func->cfunc_val.arg_types);
        free(args);
    } 
    // Gestion des lambdas
    else if (func && func->type == 9) {
        // Une lambda est un Value avec type 9 contenant un node lambda
        ASTNode* lambda_node = func->lambda_val.node;
        
        if (lambda_node && lambda_node->type == NODE_LAMBDA) {
            Environment* lambda_env = create_env(func->lambda_val.closure);
            
            // Passage des paramètres
            if (node->call.args && lambda_node->lambda.params) {
                for (int i = 0; i < node->call.args->count && 
                           i < lambda_node->lambda.params->count; i++) {
                    Value arg_val = evaluate_expr(node->call.args->nodes[i], env);
                    ASTNode* param = lambda_node->lambda.params->nodes[i];
                    env_set(lambda_env, param->identifier.name, arg_val);
                }
            }
            
            // Exécution du corps de la lambda
            for (int i = 0; i < lambda_node->lambda.body->count; i++) {
                ASTNode* stmt = lambda_node->lambda.body->nodes[i];
                if (stmt->type == NODE_RETURN) {
                    result = evaluate_expr(stmt->return_stmt.value, lambda_env);
                    break;
                } else {
                    evaluate_statement(stmt, lambda_env, NULL);
                }
            }
            free(lambda_env);
        } else {
            fprintf(stderr, "Error: Lambda value corrupted\n");
            result.type = 0;
            result.int_val = 0;
        }
    }
    else if (strcmp(func_name, "print") == 0) {
        if (node->call.args && node->call.args->count > 0) {
            Value arg = evaluate_expr(node->call.args->nodes[0], env);
            print_value(arg, 0);
        }
        result.type = 0;
        result.int_val = 0;
    } 
    else if (strcmp(func_name, "println") == 0) {
        if (node->call.args && node->call.args->count > 0) {
            Value arg = evaluate_expr(node->call.args->nodes[0], env);
            print_value(arg, 1);
        } else {
            printf("\n");
        }
        result.type = 0;
        result.int_val = 0;
    } 
    else {
        fprintf(stderr, "Error: Undefined function '%s'\n", func_name);
        result.type = 0;
        result.int_val = 0;
    }
    break;
}
        
        default:
            break;
    }
    
    return result;
}
int evaluate_statement(ASTNode* node, Environment* env, char* current_file) {
    switch (node->type) {
        case NODE_LET:
        case NODE_CONST: {
            Value val = evaluate_expr(node->var_decl.value, env);
            env_set(env, node->var_decl.name, val);
            return 0;
        }
        
        case NODE_RETURN: {
            Value val = evaluate_expr(node->return_stmt.value, env);
            return 1;  // retourne 1 pour indiquer un return
        }
        
        case NODE_IF: {
            Value cond = evaluate_expr(node->if_stmt.condition, env);
            if (cond.type == 3 && cond.bool_val) {
                for (int i = 0; i < node->if_stmt.then_branch->count; i++) {
                    int ret = evaluate_statement(node->if_stmt.then_branch->nodes[i], env, current_file);
                    if (ret == 1) return 1;
                    if (ret == 2) return 2;
                }
            } else if (node->if_stmt.else_branch) {
                for (int i = 0; i < node->if_stmt.else_branch->count; i++) {
                    int ret = evaluate_statement(node->if_stmt.else_branch->nodes[i], env, current_file);
                    if (ret == 1) return 1;
                    if (ret == 2) return 2;
                }
            }
            return 0;
        }


        // Structure pour stocker les contextes de saut

case NODE_NNL: {
    // Créer un nouveau contexte
    NnlContext* ctx = malloc(sizeof(NnlContext));
    ctx->label = node->nnl_stmt.label;
    ctx->next = nnl_stack;
    
    // Sauvegarder le contexte
    if (setjmp(ctx->env) == 0) {
        // Premier passage
        nnl_stack = ctx;
        
        // Exécuter le corps
        for (int i = 0; i < node->nnl_stmt.body->count; i++) {
            int ret = evaluate_statement(node->nnl_stmt.body->nodes[i], env, current_file);
            if (ret == 1) { // return
                // Nettoyer la pile
                nnl_stack = ctx->next;
                free(ctx);
                return 1;
            }
        }
        
        // Nettoyer
        nnl_stack = ctx->next;
        free(ctx);
    } else {
        // Retour après longjmp
        Value val = ctx->return_value;
        nnl_stack = ctx->next;
        free(ctx);
        
        // Si c'est un return, propager
        return 1;
    }
    return 0;
}
// Structure pour les exceptions
case NODE_TRY: {
    ExceptionContext ctx;
    ctx.is_thrown = 0;
    ctx.error.type = 0;
    ctx.error.int_val = 0;
    
    ExceptionContext* old_ctx = current_exception;
    current_exception = &ctx;
    
    if (setjmp(ctx.env) == 0) {
        // Exécuter le bloc try
        for (int i = 0; i < node->try_stmt.try_body->count; i++) {
            int ret = evaluate_statement(node->try_stmt.try_body->nodes[i], env, current_file);
            if (ret == 1) {
                current_exception = old_ctx;
                return 1;
            }
        }
    } else {
        // Exception attrapée
        if (node->try_stmt.catch_block) {
            ASTNode* catch_node = node->try_stmt.catch_block;
            env_set(env, catch_node->catch_block.error_var, ctx.error);
            for (int i = 0; i < catch_node->catch_block.body->count; i++) {
                evaluate_statement(catch_node->catch_block.body->nodes[i], env, current_file);
            }
        }
    }
    
    // Finally block
    if (node->try_stmt.finally_block) {
        for (int i = 0; i < node->try_stmt.finally_block->finally_block.body->count; i++) {
            evaluate_statement(node->try_stmt.finally_block->finally_block.body->nodes[i], env, current_file);
        }
    }
    
    current_exception = old_ctx;
    
    // Si l'exception n'a pas été attrapée, la propager
    if (ctx.is_thrown && !node->try_stmt.catch_block) {
        if (current_exception) {
            current_exception->is_thrown = 1;
            current_exception->error = ctx.error;
            longjmp(current_exception->env, 1);
        }
    }
    
    return 0;
}

case NODE_THROW: {
    Value error = evaluate_expr(node->throw_stmt.value, env);
    if (current_exception) {
        current_exception->is_thrown = 1;
        current_exception->error = error;
        longjmp(current_exception->env, 1);
    } else {
        fprintf(stderr, "Uncaught exception: ");
        print_value(error, 1);
        exit(1);
    }
    return 0;
}

case NODE_JMP: {
    char* label = node->jmp_stmt.label;
    NnlContext* ctx = find_nnl_context(label);
    
    if (ctx) {
        // Stocker la valeur de retour
        if (node->jmp_stmt.value) {
            ctx->return_value = evaluate_expr(node->jmp_stmt.value, env);
        } else {
            ctx->return_value = (Value){.type = 0, .int_val = 0};
        }
        
        // Sauter
        longjmp(ctx->env, 1);
    } else {
        fprintf(stderr, "Error: No nnl context for label '%s'\n", label);
    }
    return 0;
}
        case NODE_WHILE: {
            while (1) {
                Value cond = evaluate_expr(node->while_stmt.condition, env);
                if (cond.type != 3 || !cond.bool_val) break;
                for (int i = 0; i < node->while_stmt.body->count; i++) {
                    int ret = evaluate_statement(node->while_stmt.body->nodes[i], env, current_file);
                    if (ret == 1) return 1;
                    if (ret == 2) break;
                }
            }
            return 0;
        }
        case NODE_MUTS: {
            Value val = evaluate_expr(node->muts_decl.value, env);
            env_set(env, node->muts_decl.name, val);
            return 0;
        }
        case NODE_LOOP: {
            while (1) {
                for (int i = 0; i < node->loop_stmt.body->count; i++) {
                    int ret = evaluate_statement(node->loop_stmt.body->nodes[i], env, current_file);
                    if (ret == 1) return 1;
                    if (ret == 2) break;
                }
            }
            return 0;
        }
        
        case NODE_FOR: {
            // Initialisation
            if (node->for_range.start) {
                evaluate_statement(node->for_range.start, env, current_file);
            }
            
            // Boucle
            while (1) {
                if (node->for_range.end) {
                    Value cond = evaluate_expr(node->for_range.end, env);
                    if (cond.type != 3 || !cond.bool_val) break;
                }
                
                for (int i = 0; i < node->for_range.body->count; i++) {
                    int ret = evaluate_statement(node->for_range.body->nodes[i], env, current_file);
                    if (ret == 1) return 1;
                    if (ret == 2) return 0;
                }
                
                // Incrémentation
                if (node->for_range.var) {
                    // L'incrémentation est déjà dans le corps de la boucle
                }
            }
            return 0;
        }
        
        case NODE_BREAK:
            return 2;
        
        case NODE_CONTINUE:
            return 2;  // Code pour continue (saut à l'itération suivante)

case NODE_FOR_IN: {
    Value collection = evaluate_expr(node->for_in.collection, env);
    
    if (collection.type == 8) {  // Tableau
        for (int idx = 0; idx < collection.array_val.count; idx++) {
            Value elem = evaluate_expr(collection.array_val.elements->nodes[idx], env);
            Environment* loop_env = create_env(env);
            env_set(loop_env, node->for_in.var, elem);
            
            int should_break = 0;
            for (int i = 0; i < node->for_in.body->count; i++) {
                int ret = evaluate_statement(node->for_in.body->nodes[i], loop_env, current_file);
                if (ret == 1) { free(loop_env); return 1; }
                if (ret == 2) break;      // continue
                if (ret == 3) { should_break = 1; break; }  // break
            }
            free(loop_env);
            if (should_break) break;
        }
    }
    else if (collection.type == 10) {  // Dictionnaire
        for (int idx = 0; idx < collection.dict_val.count; idx++) {
            Value key = *(collection.dict_val.entries[idx].key);
            Value val = *(collection.dict_val.entries[idx].value);
            
            Environment* loop_env = create_env(env);
            env_set(loop_env, node->for_in.var, key);   // ou une paire key/value
            
            int should_break = 0;
            for (int i = 0; i < node->for_in.body->count; i++) {
                int ret = evaluate_statement(node->for_in.body->nodes[i], loop_env, current_file);
                if (ret == 1) { free(loop_env); return 1; }
                if (ret == 2) break;
                if (ret == 3) { should_break = 1; break; }
            }
            free(loop_env);
            if (should_break) break;
        }
    }
    else if (collection.type == 2) {  // String - itérer sur les caractères
        char* str = collection.string_val;
        for (int idx = 0; str[idx]; idx++) {
            Value char_val;
            char_val.type = 2;
            char_val.string_val = malloc(2);
            char_val.string_val[0] = str[idx];
            char_val.string_val[1] = '\0';
            
            Environment* loop_env = create_env(env);
            env_set(loop_env, node->for_in.var, char_val);
            
            int should_break = 0;
            for (int i = 0; i < node->for_in.body->count; i++) {
                int ret = evaluate_statement(node->for_in.body->nodes[i], loop_env, current_file);
                if (ret == 1) { free(char_val.string_val); free(loop_env); return 1; }
                if (ret == 2) break;
                if (ret == 3) { should_break = 1; break; }
            }
            free(char_val.string_val);
            free(loop_env);
            if (should_break) break;
        }
    }
    return 0;
}
        
        case NODE_MATCH: {
            Value target = evaluate_expr(node->match_stmt.value, env);
            for (int i = 0; i < node->match_stmt.cases->count; i++) {
                ASTNode* case_node = node->match_stmt.cases->nodes[i];
                if (case_node->type == NODE_MATCH_CASE) {
                    Value pattern = evaluate_expr(case_node->match_case.pattern, env);
                    int match = 0;
                    if (target.type == pattern.type) {
                        if (target.type == 0 && target.int_val == pattern.int_val) match = 1;
                        else if (target.type == 1 && target.float_val == pattern.float_val) match = 1;
                        else if (target.type == 2 && strcmp(target.string_val, pattern.string_val) == 0) match = 1;
                        else if (target.type == 3 && target.bool_val == pattern.bool_val) match = 1;
                    }
                    if (match) {
                        evaluate_expr(case_node->match_case.value, env);
                        return 0;
                    }
                }
            }
            return 0;
        }
        
        case NODE_UNSAFE: {
            for (int i = 0; i < node->unsafe_block.body->count; i++) {
                int ret = evaluate_statement(node->unsafe_block.body->nodes[i], env, current_file);
                if (ret == 1) return 1;
                if (ret == 2) return 2;
            }
            return 0;
        }
        
        case NODE_IMPORT: {
            ModuleRegistry* reg = get_module_registry();
            LoadedModule* module = load_module(
                reg,
                env,
                current_file,
                node->import.path,
                node->import.alias,
                node->import.constraints
            );
            
            if (module) {
                return 0;
            } else {
                fprintf(stderr, "Failed to load module: %s\n", node->import.path);
                return 0;
            }
        }
        
        case NODE_EXPR_STMT: {
            evaluate_expr(node->expr_stmt.expr, env);
            return 0;
        }
        
        default:
            return 0;
    }
}
void init_interpreter() {
    init_libc();
}
void interpret_program(ASTNode* program) {
    Environment* global = create_env(NULL);
    init_interpreter();
    register_native_c_functions(global);
    
    // ============================================
    // CHARGEMENT AUTOMATIQUE DU MODULE BUILTIN
    // ============================================
    ModuleRegistry* reg = get_module_registry();
    
    char* builtin_path = resolve_module_path(NULL, "__builtin__");
    if (!builtin_path) {
        builtin_path = resolve_module_path(NULL, "./lib/__builtin__");
    }
    
    if (builtin_path) {
        LoadedModule* builtin = load_module(
            reg, global, builtin_path, "__builtin__", NULL, NULL
        );
        if (builtin && builtin->env) {
            for (int i = 0; i < builtin->env->var_count; i++) {
                env_set(global, builtin->env->vars[i].name, builtin->env->vars[i].value);
            }
        }
        free(builtin_path);
    }
    
    // ============================================
    // ENREGISTREMENT DES STRUCTURES ET FONCTIONS
    // ============================================
    
    // 1. Enregistrer les fonctions
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION || stmt->type == NODE_PUBLIC_FUNCTION) {
            Value func_val;
            func_val.type = 4;
            func_val.func_val.node = stmt;
            func_val.func_val.closure = global;
            env_set(global, stmt->function.name, func_val);
        }
    }
    
    // 2. Enregistrer les structures
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_STRUCT) {
            Value struct_val;
            struct_val.type = 6;
            struct_val.struct_val.struct_name = strdup(stmt->struct_def.name);
            struct_val.struct_val.fields = NULL;
            struct_val.struct_val.field_count = 0;
            env_set(global, stmt->struct_def.name, struct_val);
        }
    }
    
    // 3. Enregistrer les implémentations
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_IMPL) {
            register_impl(stmt->impl.name, stmt);
        }
    }
    
    // 4. Exécuter les imports
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_IMPORT) {
            evaluate_statement(stmt, global, NULL);
        }
    }
    
    // 5. Chercher la fonction main
    ASTNode* main_func = NULL;
    for (int i = 0; i < program->program.statements->count; i++) {
        ASTNode* stmt = program->program.statements->nodes[i];
        if (stmt->type == NODE_FUNCTION && strcmp(stmt->function.name, "main") == 0) {
            main_func = stmt;
            break;
        }
    }
    
    // 6. Exécuter le programme
    if (main_func) {
        Environment* main_env = create_env(global);
        for (int i = 0; i < main_func->function.body->count; i++) {
            int ret = evaluate_statement(main_func->function.body->nodes[i], main_env, NULL);
            if (ret) break;
        }
        free(main_env);
    } else {
        // ============================================
        // CORRECTION : Exécuter TOUS les statements du niveau global
        // ============================================
        for (int i = 0; i < program->program.statements->count; i++) {
            ASTNode* stmt = program->program.statements->nodes[i];
            
            // Ignorer les déclarations déjà traitées (fonctions, structs, impls)
            // et exécuter tout le reste
            switch (stmt->type) {
                case NODE_FUNCTION:
                case NODE_PUBLIC_FUNCTION:
                case NODE_STRUCT:
                case NODE_IMPL:
                case NODE_IMPORT:
                    // Déjà traités, on ignore
                    break;
                    
                default:
                    // Exécuter : LET, CONST, EXPR_STMT, IF, FOR, etc.
                    evaluate_statement(stmt, global, NULL);
                    break;
            }
        }
    }
    
    free(global);
}
// ==================== NETTOYAGE DE LA MÉMOIRE ====================

void free_impl_table() {
    for (int i = 0; i < impl_count; i++) {
        free(impl_table[i].struct_name);
    }
    free(impl_table);
    impl_table = NULL;
    impl_count = 0;
    impl_capacity = 0;
}
