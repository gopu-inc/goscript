/**
 * ffi_sandbox.c — Implémentation du sandboxing FFI
 * Goscript — GOPU inc.
 *
 * Technique POSIX :
 *   1. sigaction() pour capturer SIGSEGV, SIGBUS, SIGFPE, SIGILL
 *   2. sigsetjmp() au point d'entrée du call sandbox
 *   3. siglongjmp() depuis le gestionnaire de signal → retour propre
 *   4. Restauration des handlers précédents après chaque appel
 *
 * Thread safety :
 *   Le rescue_point est déclaré __thread (thread-local storage).
 *   Chaque thread dispose de son propre point de rescue.
 */

#include "ffi_sandbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    /* Sur Windows, on utilise AddVectoredExceptionHandler */
    static PVOID gs_veh_handle = NULL;
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <signal.h>
    #include <setjmp.h>
#endif

/* ============================================================
 *  ÉTAT THREAD-LOCAL DU SANDBOX
 * ============================================================ */

#ifdef _WIN32
    #define TLS __declspec(thread)
#else
    #define TLS __thread
#endif

typedef struct {
#ifndef _WIN32
    sigjmp_buf rescue_point;
#endif
    int        in_call;
    int        caught_signal;
} FFISandboxState;

static TLS FFISandboxState ffi_state = {
#ifndef _WIN32
    .rescue_point  = {},
#endif
    .in_call       = 0,
    .caught_signal = 0
};

/* ============================================================
 *  GESTIONNAIRES DE SIGNAUX (POSIX)
 * ============================================================ */

#ifndef _WIN32

/* Handlers précédents (pour restauration) */
static struct sigaction old_sa_segv;
static struct sigaction old_sa_bus;
static struct sigaction old_sa_fpe;
static struct sigaction old_sa_ill;
static struct sigaction old_sa_alrm;

static void ffi_signal_handler(int sig) {
    if (ffi_state.in_call) {
        ffi_state.caught_signal = sig;
        siglongjmp(ffi_state.rescue_point, sig);
    }
    /* Si on n'est pas dans un appel FFI, restaurer le handler par défaut */
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sigaction(sig, &sa, NULL);
    raise(sig);  /* Re-lever le signal pour le comportement par défaut */
}

#else /* Windows */

static LONG WINAPI gs_veh_handler(PEXCEPTION_POINTERS info) {
    if (!ffi_state.in_call) return EXCEPTION_CONTINUE_SEARCH;
    DWORD code = info->ExceptionRecord->ExceptionCode;
    switch (code) {
        case EXCEPTION_ACCESS_VIOLATION:    ffi_state.caught_signal = SIGSEGV; break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        case EXCEPTION_INT_DIVIDE_BY_ZERO:  ffi_state.caught_signal = SIGFPE;  break;
        case EXCEPTION_ILLEGAL_INSTRUCTION: ffi_state.caught_signal = SIGILL;  break;
        case EXCEPTION_DATATYPE_MISALIGNMENT: ffi_state.caught_signal = SIGBUS; break;
        default: return EXCEPTION_CONTINUE_SEARCH;
    }
    /* longjmp équivalent Windows : pas de siglongjmp sur Windows,
     * on utilise à la place RtlUnwindEx / __try/__except normalement.
     * Cette implémentation est une approximation — voir note ci-dessous. */
    ffi_state.in_call = 0;
    return EXCEPTION_EXECUTE_HANDLER;
}

#endif

/* ============================================================
 *  INITIALISATION / SHUTDOWN
 * ============================================================ */

void gs_ffi_sandbox_init(void) {
#ifndef _WIN32
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = ffi_signal_handler;
    sigemptyset(&sa.sa_mask);
    /* SA_RESETHAND : le handler est désinstallé après le premier déclenchement
     * (évite les boucles infinies). On le réinstalle manuellement avant chaque appel. */
    sa.sa_flags = SA_RESETHAND | SA_NODEFER;

    sigaction(SIGSEGV, &sa, &old_sa_segv);
    sigaction(SIGBUS,  &sa, &old_sa_bus);
    sigaction(SIGFPE,  &sa, &old_sa_fpe);
    sigaction(SIGILL,  &sa, &old_sa_ill);
    sigaction(SIGALRM, &sa, &old_sa_alrm);
#else
    gs_veh_handle = AddVectoredExceptionHandler(1, gs_veh_handler);
#endif
}

void gs_ffi_sandbox_shutdown(void) {
#ifndef _WIN32
    sigaction(SIGSEGV, &old_sa_segv, NULL);
    sigaction(SIGBUS,  &old_sa_bus,  NULL);
    sigaction(SIGFPE,  &old_sa_fpe,  NULL);
    sigaction(SIGILL,  &old_sa_ill,  NULL);
    sigaction(SIGALRM, &old_sa_alrm, NULL);
#else
    if (gs_veh_handle) {
        RemoveVectoredExceptionHandler(gs_veh_handle);
        gs_veh_handle = NULL;
    }
#endif
}

/* ============================================================
 *  APPEL FFI SÉCURISÉ
 * ============================================================ */

GsFFIStatus gs_ffi_call_safe(GsFFIResult* result,
                              GsFFIFn fn,
                              void** args,
                              int nargs) {
    if (!result) return GS_FFI_ERROR;
    memset(result, 0, sizeof(GsFFIResult));

    if (!fn) {
        snprintf(result->error_msg, sizeof(result->error_msg),
                 "gs_ffi_call_safe: pointeur de fonction NULL");
        result->status = GS_FFI_ERROR;
        return GS_FFI_ERROR;
    }

#ifndef _WIN32
    /* Réinstaller les handlers (ils ont pu être réinitialisés par SA_RESETHAND) */
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = ffi_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS,  &sa, NULL);
    sigaction(SIGFPE,  &sa, NULL);
    sigaction(SIGILL,  &sa, NULL);

    /* Marquer l'entrée dans l'appel FFI */
    ffi_state.in_call       = 1;
    ffi_state.caught_signal = 0;

    /* Point de rescue */
    int caught = sigsetjmp(ffi_state.rescue_point, 1);
    if (caught != 0) {
        /* On est ici suite à un signal capturé par ffi_signal_handler */
        ffi_state.in_call = 0;

        /* Restaurer les handlers */
        sigaction(SIGSEGV, &old_sa_segv, NULL);
        sigaction(SIGBUS,  &old_sa_bus,  NULL);
        sigaction(SIGFPE,  &old_sa_fpe,  NULL);
        sigaction(SIGILL,  &old_sa_ill,  NULL);

        GsFFIStatus st;
        switch (caught) {
            case SIGSEGV: st = GS_FFI_SIGSEGV; break;
            case SIGBUS:  st = GS_FFI_SIGBUS;  break;
            case SIGFPE:  st = GS_FFI_SIGFPE;  break;
            case SIGILL:  st = GS_FFI_SIGILL;  break;
            default:      st = GS_FFI_ERROR;   break;
        }
        result->status    = st;
        result->signal_no = caught;
        snprintf(result->error_msg, sizeof(result->error_msg),
                 "GoscriptNativeException: signal %d (%s) pendant l'appel FFI",
                 caught, gs_ffi_status_name(st));
        return st;
    }

    /* ── Appel de la fonction native ── */
    fn(args, nargs, result->return_value);

    ffi_state.in_call = 0;

    /* Restaurer les handlers précédents */
    sigaction(SIGSEGV, &old_sa_segv, NULL);
    sigaction(SIGBUS,  &old_sa_bus,  NULL);
    sigaction(SIGFPE,  &old_sa_fpe,  NULL);
    sigaction(SIGILL,  &old_sa_ill,  NULL);

    result->status = GS_FFI_OK;
    return GS_FFI_OK;

#else /* Windows */
    ffi_state.in_call       = 1;
    ffi_state.caught_signal = 0;

    __try {
        fn(args, nargs, result->return_value);
        result->status = GS_FFI_OK;
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        GsFFIStatus st = GS_FFI_SIGSEGV;
        result->status    = st;
        result->signal_no = GetExceptionCode();
        snprintf(result->error_msg, sizeof(result->error_msg),
                 "GoscriptNativeException: exception Windows 0x%08X pendant l'appel FFI",
                 (unsigned)GetExceptionCode());
    }
    ffi_state.in_call = 0;
    return result->status;
#endif
}

/* ============================================================
 *  APPEL FFI AVEC TIMEOUT (POSIX uniquement)
 * ============================================================ */

GsFFIStatus gs_ffi_call_timed(GsFFIResult* result,
                               GsFFIFn fn,
                               void** args,
                               int nargs,
                               int timeout_ms) {
#ifdef _WIN32
    /* Sur Windows, on ignore le timeout pour l'instant */
    (void)timeout_ms;
    return gs_ffi_call_safe(result, fn, args, nargs);
#else
    /* Configurer un alarm POSIX (granularité : secondes) */
    unsigned int secs = (unsigned int)((timeout_ms + 999) / 1000);
    if (secs < 1) secs = 1;

    /* Réinstaller le handler SIGALRM */
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = ffi_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags   = SA_NODEFER;
    sigaction(SIGALRM, &sa, NULL);

    alarm(secs);
    GsFFIStatus st = gs_ffi_call_safe(result, fn, args, nargs);
    alarm(0);  /* Annuler l'alarm si l'appel a réussi */

    if (result->signal_no == SIGALRM) {
        result->status = GS_FFI_TIMEOUT;
        snprintf(result->error_msg, sizeof(result->error_msg),
                 "GoscriptNativeException: timeout (%d ms) dépassé pendant l'appel FFI",
                 timeout_ms);
        return GS_FFI_TIMEOUT;
    }
    return st;
#endif
}

/* ============================================================
 *  UTILITAIRES
 * ============================================================ */

const char* gs_ffi_status_name(GsFFIStatus status) {
    switch (status) {
        case GS_FFI_OK:      return "OK";
        case GS_FFI_SIGSEGV: return "SIGSEGV (violation d'accès)";
        case GS_FFI_SIGBUS:  return "SIGBUS  (erreur d'alignement)";
        case GS_FFI_SIGFPE:  return "SIGFPE  (erreur FPU)";
        case GS_FFI_SIGILL:  return "SIGILL  (instruction illégale)";
        case GS_FFI_TIMEOUT: return "TIMEOUT (délai dépassé)";
        case GS_FFI_ERROR:   return "ERROR   (erreur générique)";
        default:             return "INCONNU";
    }
}

int gs_ffi_in_call(void) {
    return ffi_state.in_call;
}
