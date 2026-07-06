/**
 * hal.c — Implémentation du Hardware Abstraction Layer
 * Goscript — GOPU inc.
 */

#include "hal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef GS_PLATFORM_UNIX
    #include <sys/sysinfo.h>
    #include <sys/utsname.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

/* ============================================================
 *  INITIALISATION / SHUTDOWN
 * ============================================================ */

int gs_hal_init(void) {
#ifdef GS_PLATFORM_WINDOWS
    WSADATA wsa;
    int rc = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (rc != 0) {
        fprintf(stderr, "[HAL] WSAStartup échoué : %d\n", rc);
        return -1;
    }
#endif
    return 0;
}

void gs_hal_shutdown(void) {
#ifdef GS_PLATFORM_WINDOWS
    WSACleanup();
#endif
}

/* ============================================================
 *  INFORMATIONS SYSTÈME
 * ============================================================ */

void gs_sysinfo(GSSysInfo* info) {
    if (!info) return;
    memset(info, 0, sizeof(GSSysInfo));

#if defined(GS_PLATFORM_LINUX)
    info->os_name = "linux";
    info->cpu_count = (int)sysconf(_SC_NPROCESSORS_ONLN);

    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        info->total_ram = (uint64_t)si.totalram * si.mem_unit;
        info->free_ram  = (uint64_t)si.freeram  * si.mem_unit;
    }

    struct utsname un;
    if (uname(&un) == 0) {
        if      (strstr(un.machine, "x86_64"))  info->arch = "x86_64";
        else if (strstr(un.machine, "aarch64")) info->arch = "arm64";
        else if (strstr(un.machine, "armv7"))   info->arch = "arm";
        else                                    info->arch = un.machine;
    }

#elif defined(GS_PLATFORM_MACOS)
    info->os_name   = "macos";
    info->cpu_count = (int)sysconf(_SC_NPROCESSORS_ONLN);
    info->arch      = sizeof(void*) == 8 ? "x86_64" : "arm64";
    /* Pour macOS, on lirait sysctlbyname pour la RAM */

#elif defined(GS_PLATFORM_WINDOWS)
    info->os_name = "windows";
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    info->cpu_count = (int)si.dwNumberOfProcessors;
    info->arch = (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) ? "x86_64" :
                 (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) ? "arm64" : "x86";

    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    info->total_ram = (uint64_t)mem.ullTotalPhys;
    info->free_ram  = (uint64_t)mem.ullAvailPhys;
#else
    info->os_name   = "unknown";
    info->arch      = "unknown";
    info->cpu_count = 1;
#endif
}

/* ============================================================
 *  SOCKETS TCP/UDP PORTABLES
 * ============================================================ */

gs_socket_t gs_socket_tcp(void) {
#ifdef GS_PLATFORM_WINDOWS
    return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd >= 0) fcntl(fd, F_SETFD, FD_CLOEXEC);
    return fd;
#endif
}

gs_socket_t gs_socket_udp(void) {
#ifdef GS_PLATFORM_WINDOWS
    return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#else
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd >= 0) fcntl(fd, F_SETFD, FD_CLOEXEC);
    return fd;
#endif
}

int gs_socket_set_reuseaddr(gs_socket_t s) {
    int opt = 1;
#ifdef GS_PLATFORM_WINDOWS
    return setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
                      (const char*)&opt, sizeof(opt));
#else
    return setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif
}

int gs_socket_set_timeout(gs_socket_t s, int timeout_ms) {
#ifdef GS_PLATFORM_WINDOWS
    DWORD tv = (DWORD)timeout_ms;
    int rc1 = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    int rc2 = setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof(tv));
    return (rc1 == 0 && rc2 == 0) ? 0 : -1;
#else
    struct timeval tv;
    tv.tv_sec  = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    int rc1 = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    int rc2 = setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    return (rc1 == 0 && rc2 == 0) ? 0 : -1;
#endif
}

int gs_socket_connect(gs_socket_t s, const char* host, int port) {
    struct addrinfo hints, *res;
    char port_str[16];
    snprintf(port_str, sizeof(port_str), "%d", port);
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port_str, &hints, &res) != 0) return -1;
    int rc = connect(s, res->ai_addr, (int)res->ai_addrlen);
    freeaddrinfo(res);
    return rc;
}

int gs_socket_bind(gs_socket_t s, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons((uint16_t)port);
    gs_socket_set_reuseaddr(s);
    return bind(s, (struct sockaddr*)&addr, sizeof(addr));
}

int gs_socket_listen(gs_socket_t s, int backlog) {
    return listen(s, backlog);
}

gs_socket_t gs_socket_accept(gs_socket_t s) {
    struct sockaddr_in client;
#ifdef GS_PLATFORM_WINDOWS
    int len = sizeof(client);
#else
    socklen_t len = sizeof(client);
#endif
    return accept(s, (struct sockaddr*)&client, &len);
}

int gs_socket_send(gs_socket_t s, const void* buf, int len) {
#ifdef GS_PLATFORM_WINDOWS
    return send(s, (const char*)buf, len, 0);
#else
    return (int)send(s, buf, (size_t)len, MSG_NOSIGNAL);
#endif
}

int gs_socket_recv(gs_socket_t s, void* buf, int len) {
#ifdef GS_PLATFORM_WINDOWS
    return recv(s, (char*)buf, len, 0);
#else
    return (int)recv(s, buf, (size_t)len, 0);
#endif
}

void gs_socket_close(gs_socket_t s) {
#ifdef GS_PLATFORM_WINDOWS
    closesocket(s);
#else
    close(s);
#endif
}
