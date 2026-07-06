/**
 * ffi_sandbox.h — Sandboxing des appels FFI (fonctions C natives)
 * Goscript — GOPU inc.
 *
 * Problème : un appel FFI vers une librairie C externe peut provoquer :
 *   - SIGSEGV (accès mémoire invalide)
 *   - SIGBUS  (alignement mémoire)
 *   - SIGFPE  (division par zéro FPU)
 *   - SIGILL  (instruction illégale)
 *
 * Solution : encapsuler l'appel dans un "rescue point" via sigsetjmp/siglongjmp.
 * En cas de signal pendant l'appel, on revient proprement au point de rescue
 * et on remonte une "GoscriptNativeException" au lieu de crasher le runtime.
 *
 * Usage :
 *   gs_ffi_sandbox_init();  // Une fois au démarrage
 *
 *   GsFFIResult result;
 *   int status = gs_ffi_call_safe(&result, my_ffi_fn, args, nargs);
 *   if (status != GS_FFI_OK) {
 *       // Récupérer l'erreur : result.error_msg
 *   }
 */

#ifndef GS_FFI_SANDBOX_H
#define GS_FFI_SANDBOX_H

#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <signal.h>

/* ============================================================
 *  CODES DE RETOUR FFI
 * ============================================================ */
typedef enum {
    GS_FFI_OK         = 0,   /* Appel réussi */
    GS_FFI_SIGSEGV    = 1,   /* Violation d'accès mémoire */
    GS_FFI_SIGBUS     = 2,   /* Erreur d'alignement bus */
    GS_FFI_SIGFPE     = 3,   /* Erreur FPU (division par zéro) */
    GS_FFI_SIGILL     = 4,   /* Instruction illégale */
    GS_FFI_TIMEOUT    = 5,   /* Timeout dépassé (via alarm) */
    GS_FFI_ERROR      = 99   /* Autre erreur */
} GsFFIStatus;

/* ============================================================
 *  RÉSULTAT D'UN APPEL FFI SANDBOXÉ
 * ============================================================ */
typedef struct {
    GsFFIStatus  status;
    char         error_msg[512];
    int          signal_no;
    void*        return_value;     /* Valeur de retour (si succès) */
} GsFFIResult;

/* ============================================================
 *  PROTOTYPE D'UNE FONCTION FFI
 * ============================================================ */
typedef void (*GsFFIFn)(void** args, int nargs, void* ret_buf);

/* ============================================================
 *  API PUBLIQUE
 * ============================================================ */

/** Initialise le sandbox FFI (installe les gestionnaires de signaux).
 *  À appeler une fois au démarrage du runtime. */
void gs_ffi_sandbox_init(void);

/** Restaure les gestionnaires de signaux par défaut. */
void gs_ffi_sandbox_shutdown(void);

/** Exécute un appel FFI de manière sécurisée.
 *  @param result  Résultat (rempli par la fonction)
 *  @param fn      Fonction FFI à appeler
 *  @param args    Tableau de pointeurs vers les arguments
 *  @param nargs   Nombre d'arguments
 *  @return GS_FFI_OK si l'appel a réussi, autre code en cas d'exception
 */
GsFFIStatus gs_ffi_call_safe(GsFFIResult* result,
                              GsFFIFn fn,
                              void**  args,
                              int     nargs);

/** Exécute une fonction C quelconque avec timeout (en millisecondes).
 *  Retourne GS_FFI_TIMEOUT si la fonction prend trop de temps.
 *  POSIX uniquement (utilise alarm + SIGALRM). */
GsFFIStatus gs_ffi_call_timed(GsFFIResult* result,
                               GsFFIFn fn,
                               void**  args,
                               int     nargs,
                               int     timeout_ms);

/** Retourne le nom lisible d'un code FFI */
const char* gs_ffi_status_name(GsFFIStatus status);

/** Retourne 1 si un appel FFI est actuellement en cours (depuis le thread courant) */
int gs_ffi_in_call(void);

/* ============================================================
 *  MACRO DE COMMODITÉ
 * ============================================================ */

/** Wrapper pour appel FFI avec gestion d'erreur inline */
#define GS_FFI_SAFE(fn, args, nargs, on_error) \
    do { \
        GsFFIResult _gs_ffi_res; \
        GsFFIStatus _gs_ffi_st = gs_ffi_call_safe(&_gs_ffi_res, (fn), (args), (nargs)); \
        if (_gs_ffi_st != GS_FFI_OK) { \
            on_error; \
        } \
    } while(0)

#endif /* GS_FFI_SANDBOX_H */
