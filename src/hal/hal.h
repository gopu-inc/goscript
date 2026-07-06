/**
 * hal.h — Hardware Abstraction Layer (HAL) multiplateforme
 * Goscript — GOPU inc.
 *
 * Fournit une API unifiée pour :
 *   - Chargement dynamique de librairies (dlopen/LoadLibrary)
 *   - Sockets TCP/UDP (POSIX / Winsock)
 *   - Threads (pthreads / Win32 threads)
 *   - Timers haute résolution
 *   - Informations système (CPU, mémoire, OS)
 *
 * Utilisation :
 *   #include "hal.h"
 *   void* lib = gs_dlopen("libmylib.so");
 *   void* fn  = gs_dlsym(lib, "my_function");
 *   gs_dlclose(lib);
 */

#ifndef GS_HAL_H
#define GS_HAL_H

#include <stddef.h>
#include <stdint.h>

/* ============================================================
 *  DÉTECTION DE PLATEFORME
 * ============================================================ */
#if defined(_WIN32) || defined(_WIN64)
    #define GS_PLATFORM_WINDOWS 1
    #include <windows.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET gs_socket_t;
    #define GS_INVALID_SOCKET INVALID_SOCKET
    #define GS_SOCKET_ERROR   SOCKET_ERROR
#elif defined(__APPLE__) || defined(__MACH__)
    #define GS_PLATFORM_MACOS 1
    #define GS_PLATFORM_UNIX  1
    #include <dlfcn.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    typedef int gs_socket_t;
    #define GS_INVALID_SOCKET (-1)
    #define GS_SOCKET_ERROR   (-1)
#elif defined(__linux__) || defined(__unix__)
    #define GS_PLATFORM_LINUX 1
    #define GS_PLATFORM_UNIX  1
    #include <dlfcn.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    typedef int gs_socket_t;
    #define GS_INVALID_SOCKET (-1)
    #define GS_SOCKET_ERROR   (-1)
#else
    #warning "Plateforme non reconnue — utilisation des APIs POSIX par défaut"
    #define GS_PLATFORM_UNIX 1
    #include <dlfcn.h>
    #include <unistd.h>
    typedef int gs_socket_t;
    #define GS_INVALID_SOCKET (-1)
    #define GS_SOCKET_ERROR   (-1)
#endif

/* ============================================================
 *  CHARGEMENT DYNAMIQUE DE LIBRAIRIES
 * ============================================================ */
#ifdef GS_PLATFORM_WINDOWS
    #define gs_dlopen(path)        ((void*)LoadLibraryA(path))
    #define gs_dlsym(handle, sym)  ((void*)GetProcAddress((HMODULE)(handle), (sym)))
    #define gs_dlclose(handle)     FreeLibrary((HMODULE)(handle))
    static inline const char* gs_dlerror(void) {
        static char buf[256];
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
                       0, buf, sizeof(buf), NULL);
        return buf;
    }
#else
    #define gs_dlopen(path)        dlopen((path), RTLD_LAZY | RTLD_GLOBAL)
    #define gs_dlsym(handle, sym)  dlsym((handle), (sym))
    #define gs_dlclose(handle)     dlclose(handle)
    #define gs_dlerror()           dlerror()
#endif

/* Retourne 1 si la lib est disponible, 0 sinon */
static inline int gs_lib_available(const char* path) {
    void* h = gs_dlopen(path);
    if (!h) return 0;
    gs_dlclose(h);
    return 1;
}

/* Charge un symbole typé depuis un handle */
#define GS_DLSYM_TYPED(handle, sym, type) \
    ((type)(uintptr_t)gs_dlsym((handle), (sym)))

/* ============================================================
 *  TIMERS HAUTE RÉSOLUTION
 * ============================================================ */
#ifdef GS_PLATFORM_WINDOWS
    #include <time.h>
    static inline uint64_t gs_time_ns(void) {
        LARGE_INTEGER freq, count;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&count);
        return (uint64_t)(count.QuadPart * 1000000000ULL / freq.QuadPart);
    }
    static inline void gs_sleep_ms(uint32_t ms) { Sleep(ms); }
#else
    #include <time.h>
    static inline uint64_t gs_time_ns(void) {
        struct timespec ts;
    #ifdef CLOCK_MONOTONIC_RAW
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    #else
        clock_gettime(CLOCK_MONOTONIC, &ts);
    #endif
        return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
    }
    static inline void gs_sleep_ms(uint32_t ms) {
        struct timespec ts = { ms / 1000, (ms % 1000) * 1000000L };
        nanosleep(&ts, NULL);
    }
#endif

static inline uint64_t gs_time_us(void) { return gs_time_ns() / 1000; }
static inline uint64_t gs_time_ms(void) { return gs_time_ns() / 1000000; }

/* ============================================================
 *  INFOS SYSTÈME
 * ============================================================ */
typedef struct {
    const char* os_name;       /* "linux", "macos", "windows" */
    const char* arch;          /* "x86_64", "arm64", "arm" */
    int         cpu_count;     /* Nombre de cœurs logiques */
    uint64_t    total_ram;     /* RAM totale en octets */
    uint64_t    free_ram;      /* RAM libre en octets */
} GSSysInfo;

void gs_sysinfo(GSSysInfo* info);

/* ============================================================
 *  THREADS PORTABLES
 * ============================================================ */
#ifdef GS_PLATFORM_WINDOWS
    typedef HANDLE          gs_thread_t;
    typedef CRITICAL_SECTION gs_mutex_t;
    typedef void* gs_thread_fn_t;

    static inline int gs_thread_create(gs_thread_t* t, void* (*fn)(void*), void* arg) {
        *t = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)fn, arg, 0, NULL);
        return (*t == NULL) ? -1 : 0;
    }
    static inline int  gs_thread_join(gs_thread_t t)   { WaitForSingleObject(t, INFINITE); CloseHandle(t); return 0; }
    static inline void gs_mutex_init(gs_mutex_t* m)    { InitializeCriticalSection(m); }
    static inline void gs_mutex_lock(gs_mutex_t* m)    { EnterCriticalSection(m); }
    static inline void gs_mutex_unlock(gs_mutex_t* m)  { LeaveCriticalSection(m); }
    static inline void gs_mutex_destroy(gs_mutex_t* m) { DeleteCriticalSection(m); }
#else
    #include <pthread.h>
    typedef pthread_t       gs_thread_t;
    typedef pthread_mutex_t gs_mutex_t;

    static inline int  gs_thread_create(gs_thread_t* t, void* (*fn)(void*), void* arg) {
        return pthread_create(t, NULL, fn, arg);
    }
    static inline int  gs_thread_join(gs_thread_t t)   { return pthread_join(t, NULL); }
    static inline void gs_mutex_init(gs_mutex_t* m)    { pthread_mutex_init(m, NULL); }
    static inline void gs_mutex_lock(gs_mutex_t* m)    { pthread_mutex_lock(m); }
    static inline void gs_mutex_unlock(gs_mutex_t* m)  { pthread_mutex_unlock(m); }
    static inline void gs_mutex_destroy(gs_mutex_t* m) { pthread_mutex_destroy(m); }
#endif

/* ============================================================
 *  SOCKETS PORTABLES (abstraction minimale)
 * ============================================================ */
int  gs_hal_init(void);     /* Initialise Winsock sur Windows, no-op sur Unix */
void gs_hal_shutdown(void); /* Nettoie Winsock */

gs_socket_t gs_socket_tcp(void);
gs_socket_t gs_socket_udp(void);
int         gs_socket_connect(gs_socket_t s, const char* host, int port);
int         gs_socket_bind(gs_socket_t s, int port);
int         gs_socket_listen(gs_socket_t s, int backlog);
gs_socket_t gs_socket_accept(gs_socket_t s);
int         gs_socket_send(gs_socket_t s, const void* buf, int len);
int         gs_socket_recv(gs_socket_t s, void* buf, int len);
void        gs_socket_close(gs_socket_t s);
int         gs_socket_set_timeout(gs_socket_t s, int timeout_ms);
int         gs_socket_set_reuseaddr(gs_socket_t s);

/* ============================================================
 *  MACROS UTILITAIRES
 * ============================================================ */
#define GS_UNUSED(x)  ((void)(x))
#define GS_LIKELY(x)  __builtin_expect(!!(x), 1)
#define GS_UNLIKELY(x) __builtin_expect(!!(x), 0)
#define GS_ALIGNAS(n) __attribute__((aligned(n)))
#define GS_INLINE     static inline __attribute__((always_inline))
#define GS_NOINLINE   __attribute__((noinline))
#define GS_COLD       __attribute__((cold))
#define GS_HOT        __attribute__((hot))
#define GS_NORETURN   __attribute__((noreturn))

/* Min/Max portables */
#define GS_MIN(a, b) ((a) < (b) ? (a) : (b))
#define GS_MAX(a, b) ((a) > (b) ? (a) : (b))

#endif /* GS_HAL_H */
