/*
 * interpreter_net.c — Module réseau natif pour Goscript
 *
 * Implémente des fonctions haut niveau pour :
 *   - TCP client/serveur
 *   - WebSocket (handshake HTTP Upgrade + frames)
 *   - Proxy HTTP transparent
 *   - SQLite via dlopen (pas de dépendance à la compilation)
 *
 * Toutes les fonctions sont enregistrées dans l'environnement Goscript
 * via register_net_functions(env).
 */

#include "interpreter.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <dlfcn.h>
#include <ffi.h>
#include <pthread.h>

/* ========================================================================
 * TABLE DE HANDLES (évite la troncature de pointeur int 32 bits)
 * ======================================================================== */

#define GS_MAX_HANDLES 1024

typedef enum {
    GS_HANDLE_FREE = 0,
    GS_HANDLE_SOCKET,
    GS_HANDLE_DB,
    GS_HANDLE_STMT
} GsHandleType;

typedef struct {
    GsHandleType type;
    void*        ptr;    /* pointeur natif (socket fd ou sqlite3*) */
    int          fd;     /* descripteur fichier (pour les sockets) */
} GsHandle;

static GsHandle gs_handles[GS_MAX_HANDLES];
static int      gs_handle_init = 0;

static void init_handle_table(void) {
    if (!gs_handle_init) {
        memset(gs_handles, 0, sizeof(gs_handles));
        gs_handle_init = 1;
    }
}

/* Alloue un slot de handle, retourne l'id (1-based) ou -1 si plein */
static int alloc_handle(GsHandleType type, void* ptr, int fd) {
    init_handle_table();
    for (int i = 1; i < GS_MAX_HANDLES; i++) {
        if (gs_handles[i].type == GS_HANDLE_FREE) {
            gs_handles[i].type = type;
            gs_handles[i].ptr  = ptr;
            gs_handles[i].fd   = fd;
            return i;
        }
    }
    return -1;
}

static GsHandle* get_handle(int id, GsHandleType type) {
    if (id <= 0 || id >= GS_MAX_HANDLES) return NULL;
    if (gs_handles[id].type != type) return NULL;
    return &gs_handles[id];
}

static void free_handle(int id) {
    if (id > 0 && id < GS_MAX_HANDLES)
        memset(&gs_handles[id], 0, sizeof(GsHandle));
}

/* ========================================================================
 * TCP — CLIENT / SERVEUR
 * ======================================================================== */

/*
 * gs_tcp_connect(host, port_str) → handle_id (-1 si erreur)
 * Ouvre une connexion TCP vers host:port.
 */
static int gs_tcp_connect(const char* host, const char* port_str) {
    struct addrinfo hints, *res, *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, port_str, &hints, &res) != 0) {
        fprintf(stderr, "[net] gs_tcp_connect: résolution DNS échouée pour %s:%s\n", host, port_str);
        return -1;
    }

    int fd = -1;
    for (rp = res; rp; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd < 0) continue;
        if (connect(fd, rp->ai_addr, rp->ai_addrlen) == 0) break;
        close(fd);
        fd = -1;
    }
    freeaddrinfo(res);

    if (fd < 0) {
        fprintf(stderr, "[net] gs_tcp_connect: connexion impossible à %s:%s\n", host, port_str);
        return -1;
    }

    int hid = alloc_handle(GS_HANDLE_SOCKET, NULL, fd);
    if (hid < 0) { close(fd); return -1; }
    return hid;
}

/*
 * gs_tcp_server(port) → handle_id (-1 si erreur)
 * Crée un socket serveur TCP lié au port donné.
 */
static int gs_tcp_server(int port) {
    int fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (fd < 0) {
        /* fallback IPv4 */
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0) {
            perror("[net] gs_tcp_server: socket");
            return -1;
        }
        int opt = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        struct sockaddr_in addr4;
        memset(&addr4, 0, sizeof(addr4));
        addr4.sin_family      = AF_INET;
        addr4.sin_port        = htons((uint16_t)port);
        addr4.sin_addr.s_addr = INADDR_ANY;

        if (bind(fd, (struct sockaddr*)&addr4, sizeof(addr4)) < 0) {
            perror("[net] gs_tcp_server: bind IPv4");
            close(fd);
            return -1;
        }
    } else {
        int opt = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        /* Accepte IPv4 et IPv6 sur le même socket */
        int v6only = 0;
        setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &v6only, sizeof(v6only));

        struct sockaddr_in6 addr6;
        memset(&addr6, 0, sizeof(addr6));
        addr6.sin6_family = AF_INET6;
        addr6.sin6_port   = htons((uint16_t)port);
        addr6.sin6_addr   = in6addr_any;

        if (bind(fd, (struct sockaddr*)&addr6, sizeof(addr6)) < 0) {
            perror("[net] gs_tcp_server: bind IPv6");
            close(fd);
            return -1;
        }
    }

    if (listen(fd, 128) < 0) {
        perror("[net] gs_tcp_server: listen");
        close(fd);
        return -1;
    }

    int hid = alloc_handle(GS_HANDLE_SOCKET, NULL, fd);
    if (hid < 0) { close(fd); return -1; }
    return hid;
}

/*
 * gs_tcp_accept(server_hid) → client_hid (-1 si erreur)
 * Accepte une connexion entrante (bloquant).
 */
static int gs_tcp_accept(int server_hid) {
    GsHandle* h = get_handle(server_hid, GS_HANDLE_SOCKET);
    if (!h) { fprintf(stderr, "[net] gs_tcp_accept: handle invalide %d\n", server_hid); return -1; }

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    int client_fd = accept(h->fd, (struct sockaddr*)&addr, &addrlen);
    if (client_fd < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
            perror("[net] gs_tcp_accept");
        return -1;
    }

    int hid = alloc_handle(GS_HANDLE_SOCKET, NULL, client_fd);
    if (hid < 0) { close(client_fd); return -1; }
    return hid;
}

/* Buffer statique pour gs_tcp_recv (thread-unsafe, adapté aux scripts séquentiels) */
static char gs_recv_buf[65536];

/*
 * gs_tcp_send(hid, message) → octets envoyés (-1 si erreur)
 */
static int gs_tcp_send(int hid, const char* message) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h || !message) return -1;
    int len = (int)strlen(message);
    int sent = (int)send(h->fd, message, len, 0);
    return sent;
}

/*
 * gs_tcp_recv(hid, maxlen) → chaîne reçue (buffer statique) ou NULL
 */
static const char* gs_tcp_recv(int hid, int maxlen) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h) return NULL;
    if (maxlen <= 0 || maxlen > (int)sizeof(gs_recv_buf) - 1)
        maxlen = sizeof(gs_recv_buf) - 1;
    int n = (int)recv(h->fd, gs_recv_buf, maxlen, 0);
    if (n <= 0) { gs_recv_buf[0] = '\0'; return gs_recv_buf; }
    gs_recv_buf[n] = '\0';
    return gs_recv_buf;
}

/*
 * gs_tcp_close(hid) → 0 OK, -1 erreur
 */
static int gs_tcp_close(int hid) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h) return -1;
    close(h->fd);
    free_handle(hid);
    return 0;
}

/*
 * gs_tcp_set_timeout(hid, seconds) → 0 OK
 * Définit un timeout de lecture/écriture en secondes.
 */
static int gs_tcp_set_timeout(int hid, int seconds) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h) return -1;
    struct timeval tv;
    tv.tv_sec  = seconds;
    tv.tv_usec = 0;
    setsockopt(h->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(h->fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    return 0;
}

/*
 * gs_tcp_peer_addr(hid) → "ip:port" ou "?" si erreur
 */
static char gs_peer_addr_buf[64];
static const char* gs_tcp_peer_addr(int hid) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h) { strcpy(gs_peer_addr_buf, "?"); return gs_peer_addr_buf; }
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);
    if (getpeername(h->fd, (struct sockaddr*)&addr, &len) != 0) {
        strcpy(gs_peer_addr_buf, "?");
        return gs_peer_addr_buf;
    }
    char ip[INET6_ADDRSTRLEN] = "?";
    int port = 0;
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in* s = (struct sockaddr_in*)&addr;
        inet_ntop(AF_INET, &s->sin_addr, ip, sizeof(ip));
        port = ntohs(s->sin_port);
    } else if (addr.ss_family == AF_INET6) {
        struct sockaddr_in6* s = (struct sockaddr_in6*)&addr;
        inet_ntop(AF_INET6, &s->sin6_addr, ip, sizeof(ip));
        port = ntohs(s->sin6_port);
    }
    snprintf(gs_peer_addr_buf, sizeof(gs_peer_addr_buf), "%s:%d", ip, port);
    return gs_peer_addr_buf;
}

/* ========================================================================
 * WEBSOCKET — HANDSHAKE + FRAMES (RFC 6455)
 * ======================================================================== */

/* SHA-1 minimal (RFC 3174) */
typedef struct { uint32_t state[5]; uint32_t count[2]; uint8_t buffer[64]; } GsSha1Ctx;

#define GS_SHA1_ROL(n,b) (((n) << (b)) | ((n) >> (32 - (b))))
#define GS_SHA1_BLK(i) ( \
    blk[i & 15] = GS_SHA1_ROL(blk[(i+13)&15]^blk[(i+8)&15]^blk[(i+2)&15]^blk[i&15], 1))

#define GS_SHA1_R0(v,w,x,y,z,i) \
    z += ((w & (x ^ y)) ^ y) + blk[i] + 0x5A827999 + GS_SHA1_ROL(v, 5); \
    w = GS_SHA1_ROL(w, 30);
#define GS_SHA1_R1(v,w,x,y,z,i) \
    z += ((w & (x ^ y)) ^ y) + GS_SHA1_BLK(i) + 0x5A827999 + GS_SHA1_ROL(v, 5); \
    w = GS_SHA1_ROL(w, 30);
#define GS_SHA1_R2(v,w,x,y,z,i) \
    z += (w ^ x ^ y) + GS_SHA1_BLK(i) + 0x6ED9EBA1 + GS_SHA1_ROL(v, 5); \
    w = GS_SHA1_ROL(w, 30);
#define GS_SHA1_R3(v,w,x,y,z,i) \
    z += (((w | x) & y) | (w & x)) + GS_SHA1_BLK(i) + 0x8F1BBCDC + GS_SHA1_ROL(v, 5); \
    w = GS_SHA1_ROL(w, 30);
#define GS_SHA1_R4(v,w,x,y,z,i) \
    z += (w ^ x ^ y) + GS_SHA1_BLK(i) + 0xCA62C1D6 + GS_SHA1_ROL(v, 5); \
    w = GS_SHA1_ROL(w, 30);

static void gs_sha1_transform(uint32_t state[5], const uint8_t buf[64]) {
    uint32_t a,b,c,d,e, blk[16];
    for (int i=0;i<16;i++)
        blk[i]=((uint32_t)buf[i*4]<<24)|((uint32_t)buf[i*4+1]<<16)|
               ((uint32_t)buf[i*4+2]<<8)|(uint32_t)buf[i*4+3];
    a=state[0]; b=state[1]; c=state[2]; d=state[3]; e=state[4];
    GS_SHA1_R0(a,b,c,d,e, 0); GS_SHA1_R0(e,a,b,c,d, 1);
    GS_SHA1_R0(d,e,a,b,c, 2); GS_SHA1_R0(c,d,e,a,b, 3);
    GS_SHA1_R0(b,c,d,e,a, 4); GS_SHA1_R0(a,b,c,d,e, 5);
    GS_SHA1_R0(e,a,b,c,d, 6); GS_SHA1_R0(d,e,a,b,c, 7);
    GS_SHA1_R0(c,d,e,a,b, 8); GS_SHA1_R0(b,c,d,e,a, 9);
    GS_SHA1_R0(a,b,c,d,e,10); GS_SHA1_R0(e,a,b,c,d,11);
    GS_SHA1_R0(d,e,a,b,c,12); GS_SHA1_R0(c,d,e,a,b,13);
    GS_SHA1_R0(b,c,d,e,a,14); GS_SHA1_R0(a,b,c,d,e,15);
    GS_SHA1_R1(e,a,b,c,d,16); GS_SHA1_R1(d,e,a,b,c,17);
    GS_SHA1_R1(c,d,e,a,b,18); GS_SHA1_R1(b,c,d,e,a,19);
    GS_SHA1_R2(a,b,c,d,e,20); GS_SHA1_R2(e,a,b,c,d,21);
    GS_SHA1_R2(d,e,a,b,c,22); GS_SHA1_R2(c,d,e,a,b,23);
    GS_SHA1_R2(b,c,d,e,a,24); GS_SHA1_R2(a,b,c,d,e,25);
    GS_SHA1_R2(e,a,b,c,d,26); GS_SHA1_R2(d,e,a,b,c,27);
    GS_SHA1_R2(c,d,e,a,b,28); GS_SHA1_R2(b,c,d,e,a,29);
    GS_SHA1_R2(a,b,c,d,e,30); GS_SHA1_R2(e,a,b,c,d,31);
    GS_SHA1_R2(d,e,a,b,c,32); GS_SHA1_R2(c,d,e,a,b,33);
    GS_SHA1_R2(b,c,d,e,a,34); GS_SHA1_R2(a,b,c,d,e,35);
    GS_SHA1_R2(e,a,b,c,d,36); GS_SHA1_R2(d,e,a,b,c,37);
    GS_SHA1_R2(c,d,e,a,b,38); GS_SHA1_R2(b,c,d,e,a,39);
    GS_SHA1_R3(a,b,c,d,e,40); GS_SHA1_R3(e,a,b,c,d,41);
    GS_SHA1_R3(d,e,a,b,c,42); GS_SHA1_R3(c,d,e,a,b,43);
    GS_SHA1_R3(b,c,d,e,a,44); GS_SHA1_R3(a,b,c,d,e,45);
    GS_SHA1_R3(e,a,b,c,d,46); GS_SHA1_R3(d,e,a,b,c,47);
    GS_SHA1_R3(c,d,e,a,b,48); GS_SHA1_R3(b,c,d,e,a,49);
    GS_SHA1_R3(a,b,c,d,e,50); GS_SHA1_R3(e,a,b,c,d,51);
    GS_SHA1_R3(d,e,a,b,c,52); GS_SHA1_R3(c,d,e,a,b,53);
    GS_SHA1_R3(b,c,d,e,a,54); GS_SHA1_R3(a,b,c,d,e,55);
    GS_SHA1_R3(e,a,b,c,d,56); GS_SHA1_R3(d,e,a,b,c,57);
    GS_SHA1_R3(c,d,e,a,b,58); GS_SHA1_R3(b,c,d,e,a,59);
    GS_SHA1_R4(a,b,c,d,e,60); GS_SHA1_R4(e,a,b,c,d,61);
    GS_SHA1_R4(d,e,a,b,c,62); GS_SHA1_R4(c,d,e,a,b,63);
    GS_SHA1_R4(b,c,d,e,a,64); GS_SHA1_R4(a,b,c,d,e,65);
    GS_SHA1_R4(e,a,b,c,d,66); GS_SHA1_R4(d,e,a,b,c,67);
    GS_SHA1_R4(c,d,e,a,b,68); GS_SHA1_R4(b,c,d,e,a,69);
    GS_SHA1_R4(a,b,c,d,e,70); GS_SHA1_R4(e,a,b,c,d,71);
    GS_SHA1_R4(d,e,a,b,c,72); GS_SHA1_R4(c,d,e,a,b,73);
    GS_SHA1_R4(b,c,d,e,a,74); GS_SHA1_R4(a,b,c,d,e,75);
    GS_SHA1_R4(e,a,b,c,d,76); GS_SHA1_R4(d,e,a,b,c,77);
    GS_SHA1_R4(c,d,e,a,b,78); GS_SHA1_R4(b,c,d,e,a,79);
    state[0]+=a; state[1]+=b; state[2]+=c; state[3]+=d; state[4]+=e;
}

static void gs_sha1(const uint8_t* data, size_t len, uint8_t digest[20]) {
    uint32_t state[5] = {0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476,0xC3D2E1F0};
    uint8_t  buf[64];
    size_t   i, rem = len & 63;

    for (i = 0; i + 64 <= len; i += 64)
        gs_sha1_transform(state, data + i);

    memcpy(buf, data + i, rem);
    buf[rem++] = 0x80;
    if (rem > 56) {
        memset(buf + rem, 0, 64 - rem);
        gs_sha1_transform(state, buf);
        rem = 0;
    }
    memset(buf + rem, 0, 56 - rem);
    uint64_t bits = (uint64_t)len << 3;
    for (int j=7;j>=0;j--) { buf[56+j]=(uint8_t)(bits&0xFF); bits>>=8; }
    gs_sha1_transform(state, buf);

    for (int j=0;j<5;j++) {
        digest[j*4+0]=(uint8_t)(state[j]>>24);
        digest[j*4+1]=(uint8_t)(state[j]>>16);
        digest[j*4+2]=(uint8_t)(state[j]>>8);
        digest[j*4+3]=(uint8_t)(state[j]);
    }
}

static const char b64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void gs_base64_encode(const uint8_t* src, size_t len, char* dst) {
    size_t i = 0, j = 0;
    uint8_t t[3]; uint8_t q[4];
    while (i < len) {
        size_t rem = len - i;
        t[0] = src[i]; t[1] = rem>1?src[i+1]:0; t[2] = rem>2?src[i+2]:0;
        q[0]=t[0]>>2; q[1]=((t[0]&3)<<4)|(t[1]>>4);
        q[2]=((t[1]&15)<<2)|(t[2]>>6); q[3]=t[2]&63;
        for (int k=0;k<4;k++)
            dst[j++]=(k<=rem)?b64_chars[q[k]]:'=';
        i+=3;
    }
    dst[j]='\0';
}

/* Extrait la valeur d'un header HTTP depuis une requête brute */
static int extract_header(const char* req, const char* name, char* out, int maxlen) {
    char search[128];
    snprintf(search, sizeof(search), "%s: ", name);
    const char* p = req;
    while (*p) {
        /* Comparaison insensible à la casse */
        size_t slen = strlen(search);
        int match = 1;
        for (size_t k=0; k<slen && p[k]; k++) {
            char a = p[k], b = search[k];
            if (a>='A'&&a<='Z') a+='a'-'A';
            if (b>='A'&&b<='Z') b+='a'-'A';
            if (a!=b) { match=0; break; }
        }
        if (match) {
            const char* val = p + slen;
            const char* end = strstr(val, "\r\n");
            if (!end) end = val + strlen(val);
            int n = (int)(end - val);
            if (n >= maxlen) n = maxlen-1;
            memcpy(out, val, n);
            out[n] = '\0';
            return 1;
        }
        p++;
    }
    return 0;
}

/* Buffer statique pour gs_ws_recv */
static char gs_ws_recv_buf[65536];

/*
 * gs_ws_accept(hid) → 1 si le handshake réussit, 0 sinon
 * Lit la requête HTTP Upgrade et répond avec le bon Sec-WebSocket-Accept.
 */
static int gs_ws_accept(int hid) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h) return 0;

    /* Lire la requête HTTP */
    char req[4096];
    int n = (int)recv(h->fd, req, sizeof(req)-1, 0);
    if (n <= 0) return 0;
    req[n] = '\0';

    /* Vérifier que c'est un Upgrade WebSocket */
    if (!strstr(req, "Upgrade: websocket") && !strstr(req, "Upgrade: WebSocket"))
        return 0;

    char ws_key[128] = "";
    if (!extract_header(req, "Sec-WebSocket-Key", ws_key, sizeof(ws_key)))
        return 0;

    /* Calcul du Sec-WebSocket-Accept = base64(sha1(key + GUID)) */
    const char* guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    char combined[256];
    snprintf(combined, sizeof(combined), "%s%s", ws_key, guid);

    uint8_t  digest[20];
    gs_sha1((uint8_t*)combined, strlen(combined), digest);

    char accept[64];
    gs_base64_encode(digest, 20, accept);

    /* Répondre */
    char response[512];
    snprintf(response, sizeof(response),
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Accept: %s\r\n\r\n",
        accept);

    send(h->fd, response, strlen(response), 0);
    return 1;
}

/*
 * gs_ws_send(hid, message) → octets envoyés (-1 si erreur)
 * Encode le message dans une frame WebSocket text (non-masquée, serveur→client).
 */
static int gs_ws_send(int hid, const char* message) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h || !message) return -1;

    size_t len = strlen(message);
    uint8_t frame[65546];
    int    flen = 0;

    frame[flen++] = 0x81; /* FIN + opcode TEXT */

    if (len <= 125) {
        frame[flen++] = (uint8_t)len;
    } else if (len <= 65535) {
        frame[flen++] = 126;
        frame[flen++] = (uint8_t)(len >> 8);
        frame[flen++] = (uint8_t)(len & 0xFF);
    } else {
        frame[flen++] = 127;
        for (int i=7;i>=0;i--) frame[flen++]=(uint8_t)((len>>(i*8))&0xFF);
    }

    memcpy(frame + flen, message, len);
    flen += (int)len;

    return (int)send(h->fd, frame, flen, 0);
}

/*
 * gs_ws_recv(hid) → chaîne décodée (buffer statique) ou NULL si erreur/fermeture
 * Décode une frame WebSocket (supporte les frames masquées depuis le client).
 */
static const char* gs_ws_recv(int hid) {
    GsHandle* h = get_handle(hid, GS_HANDLE_SOCKET);
    if (!h) return NULL;

    uint8_t header[2];
    if (recv(h->fd, header, 2, MSG_WAITALL) != 2) return NULL;

    uint8_t  masked  = (header[1] >> 7) & 1;
    uint64_t pay_len = header[1] & 0x7F;

    if (pay_len == 126) {
        uint8_t ext[2];
        if (recv(h->fd, ext, 2, MSG_WAITALL) != 2) return NULL;
        pay_len = ((uint64_t)ext[0]<<8) | ext[1];
    } else if (pay_len == 127) {
        uint8_t ext[8];
        if (recv(h->fd, ext, 8, MSG_WAITALL) != 8) return NULL;
        pay_len = 0;
        for (int i=0;i<8;i++) pay_len = (pay_len<<8)|ext[i];
    }

    uint8_t mask[4] = {0};
    if (masked) {
        if (recv(h->fd, mask, 4, MSG_WAITALL) != 4) return NULL;
    }

    if (pay_len >= sizeof(gs_ws_recv_buf)-1) pay_len = sizeof(gs_ws_recv_buf)-2;
    uint8_t* payload = (uint8_t*)gs_ws_recv_buf;

    ssize_t got = recv(h->fd, payload, (size_t)pay_len, MSG_WAITALL);
    if (got <= 0) return NULL;

    if (masked) {
        for (ssize_t i=0;i<got;i++)
            payload[i] ^= mask[i%4];
    }
    payload[got] = '\0';

    /* Opcode 8 = close */
    if ((header[0] & 0x0F) == 8) return NULL;

    return gs_ws_recv_buf;
}

/* ========================================================================
 * PROXY HTTP TRANSPARENT
 * ======================================================================== */

typedef struct {
    int  client_fd;
    char target_host[256];
    int  target_port;
} GsProxyArgs;

/* Relaie les données entre deux descripteurs de fichier (both ways) */
static void proxy_relay(int a, int b) {
    char buf[4096];
    fd_set fds;
    int maxfd = (a > b ? a : b) + 1;

    while (1) {
        FD_ZERO(&fds);
        FD_SET(a, &fds);
        FD_SET(b, &fds);
        struct timeval tv = {30, 0};
        int r = select(maxfd, &fds, NULL, NULL, &tv);
        if (r <= 0) break;

        if (FD_ISSET(a, &fds)) {
            int n = (int)recv(a, buf, sizeof(buf), 0);
            if (n <= 0) break;
            if (send(b, buf, n, 0) <= 0) break;
        }
        if (FD_ISSET(b, &fds)) {
            int n = (int)recv(b, buf, sizeof(buf), 0);
            if (n <= 0) break;
            if (send(a, buf, n, 0) <= 0) break;
        }
    }
    close(a); close(b);
}

static void* proxy_thread(void* arg) {
    GsProxyArgs* pa = (GsProxyArgs*)arg;

    /* Connexion vers la cible */
    char port_str[16];
    snprintf(port_str, sizeof(port_str), "%d", pa->target_port);
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(pa->target_host, port_str, &hints, &res) != 0) {
        close(pa->client_fd); free(pa); return NULL;
    }

    int target_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (target_fd < 0 || connect(target_fd, res->ai_addr, res->ai_addrlen) != 0) {
        freeaddrinfo(res); close(pa->client_fd); free(pa); return NULL;
    }
    freeaddrinfo(res);

    proxy_relay(pa->client_fd, target_fd);
    free(pa);
    return NULL;
}

/*
 * gs_proxy_start(listen_port, target_host, target_port) → server_hid
 * Lance un proxy TCP transparent : toute connexion entrante est relayée
 * vers target_host:target_port dans un thread séparé.
 * Retourne le handle du serveur (à fermer avec gs_tcp_close).
 */
static int gs_proxy_start(int listen_port, const char* target_host, int target_port) {
    int srv_hid = gs_tcp_server(listen_port);
    if (srv_hid < 0) return -1;

    GsHandle* h = get_handle(srv_hid, GS_HANDLE_SOCKET);
    if (!h) return -1;

    /* Ignorer SIGPIPE pour éviter les crashs sur socket fermée */
    signal(SIGPIPE, SIG_IGN);

    /* Boucle d'acceptation non-bloquante lancée dans un thread */
    /* Pour un script Goscript, on accepte en boucle dans le thread principal */
    /* Pour une utilisation asynchrone, l'utilisateur appelle gs_tcp_accept lui-même */
    fprintf(stderr, "[net] Proxy TCP :%d → %s:%d démarré (handle=%d)\n",
            listen_port, target_host, target_port, srv_hid);
    return srv_hid;
}

/*
 * gs_proxy_accept_and_relay(server_hid, target_host, target_port) → 1 ok
 * Accepte une connexion et la relaie dans un thread POSIX.
 * Appeler en boucle depuis Goscript.
 */
static int gs_proxy_accept_and_relay(int srv_hid, const char* target_host, int target_port) {
    GsHandle* h = get_handle(srv_hid, GS_HANDLE_SOCKET);
    if (!h) return -1;

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    int cfd = accept(h->fd, (struct sockaddr*)&addr, &addrlen);
    if (cfd < 0) return -1;

    GsProxyArgs* pa = malloc(sizeof(GsProxyArgs));
    pa->client_fd   = cfd;
    pa->target_port = target_port;
    strncpy(pa->target_host, target_host, sizeof(pa->target_host)-1);
    pa->target_host[sizeof(pa->target_host)-1] = '\0';

    pthread_t tid;
    pthread_create(&tid, NULL, proxy_thread, pa);
    pthread_detach(tid);
    return 1;
}

/* ========================================================================
 * SQLITE — via dlopen (pas de dépendance à la compilation)
 * ======================================================================== */

/* Types opaques sqlite3 */
typedef struct sqlite3      GsSqlite3;
typedef struct sqlite3_stmt GsSqliteStmt;

/* Pointeurs de fonctions sqlite3 */
static void* gs_sqlite_lib   = NULL;
static int   gs_sqlite_ready = 0;

typedef int  (*fn_sqlite3_open)(const char*, GsSqlite3**);
typedef int  (*fn_sqlite3_close)(GsSqlite3*);
typedef int  (*fn_sqlite3_exec)(GsSqlite3*, const char*, void*, void*, char**);
typedef void (*fn_sqlite3_free)(void*);
typedef int  (*fn_sqlite3_prepare_v2)(GsSqlite3*, const char*, int, GsSqliteStmt**, const char**);
typedef int  (*fn_sqlite3_step)(GsSqliteStmt*);
typedef int  (*fn_sqlite3_finalize)(GsSqliteStmt*);
typedef int  (*fn_sqlite3_column_count)(GsSqliteStmt*);
typedef const unsigned char* (*fn_sqlite3_column_text)(GsSqliteStmt*, int);
typedef const char* (*fn_sqlite3_column_name)(GsSqliteStmt*, int);
typedef int  (*fn_sqlite3_column_type)(GsSqliteStmt*, int);
typedef double (*fn_sqlite3_column_double)(GsSqliteStmt*, int);
typedef int  (*fn_sqlite3_column_int)(GsSqliteStmt*, int);
typedef const char* (*fn_sqlite3_errmsg)(GsSqlite3*);

static fn_sqlite3_open         gs_fn_open;
static fn_sqlite3_close        gs_fn_close;
static fn_sqlite3_exec         gs_fn_exec;
static fn_sqlite3_free         gs_fn_free;
static fn_sqlite3_prepare_v2   gs_fn_prepare;
static fn_sqlite3_step         gs_fn_step;
static fn_sqlite3_finalize     gs_fn_finalize;
static fn_sqlite3_column_count gs_fn_col_count;
static fn_sqlite3_column_text  gs_fn_col_text;
static fn_sqlite3_column_name  gs_fn_col_name;
static fn_sqlite3_column_type  gs_fn_col_type;
static fn_sqlite3_column_double gs_fn_col_double;
static fn_sqlite3_column_int   gs_fn_col_int;
static fn_sqlite3_errmsg       gs_fn_errmsg;

static int load_sqlite_lib(void) {
    if (gs_sqlite_ready) return 1;
    const char* candidates[] = {
        "libsqlite3.so.0", "libsqlite3.so", "libsqlite3.dylib", NULL
    };
    for (int i = 0; candidates[i]; i++) {
        gs_sqlite_lib = dlopen(candidates[i], RTLD_LAZY);
        if (gs_sqlite_lib) break;
    }
    if (!gs_sqlite_lib) {
        fprintf(stderr, "[db] SQLite non disponible (libsqlite3 introuvable)\n");
        return 0;
    }
    #define LSYM(var, type, sym) \
        var = (type)dlsym(gs_sqlite_lib, sym); \
        if (!var) { fprintf(stderr, "[db] Symbole manquant: %s\n", sym); return 0; }

    LSYM(gs_fn_open,      fn_sqlite3_open,         "sqlite3_open")
    LSYM(gs_fn_close,     fn_sqlite3_close,        "sqlite3_close")
    LSYM(gs_fn_exec,      fn_sqlite3_exec,         "sqlite3_exec")
    LSYM(gs_fn_free,      fn_sqlite3_free,         "sqlite3_free")
    LSYM(gs_fn_prepare,   fn_sqlite3_prepare_v2,   "sqlite3_prepare_v2")
    LSYM(gs_fn_step,      fn_sqlite3_step,         "sqlite3_step")
    LSYM(gs_fn_finalize,  fn_sqlite3_finalize,     "sqlite3_finalize")
    LSYM(gs_fn_col_count, fn_sqlite3_column_count, "sqlite3_column_count")
    LSYM(gs_fn_col_text,  fn_sqlite3_column_text,  "sqlite3_column_text")
    LSYM(gs_fn_col_name,  fn_sqlite3_column_name,  "sqlite3_column_name")
    LSYM(gs_fn_col_type,  fn_sqlite3_column_type,  "sqlite3_column_type")
    LSYM(gs_fn_col_double,fn_sqlite3_column_double,"sqlite3_column_double")
    LSYM(gs_fn_col_int,   fn_sqlite3_column_int,   "sqlite3_column_int")
    LSYM(gs_fn_errmsg,    fn_sqlite3_errmsg,       "sqlite3_errmsg")
    #undef LSYM

    gs_sqlite_ready = 1;
    return 1;
}

/*
 * gs_db_open(path) → db_hid (-1 si erreur)
 * Ouvre (ou crée) une base SQLite au chemin donné.
 */
static int gs_db_open(const char* path) {
    if (!load_sqlite_lib()) return -1;
    GsSqlite3* db = NULL;
    int rc = gs_fn_open(path, &db);
    if (rc != 0 || !db) {
        fprintf(stderr, "[db] gs_db_open: impossible d'ouvrir %s\n", path);
        return -1;
    }
    int hid = alloc_handle(GS_HANDLE_DB, db, -1);
    if (hid < 0) { gs_fn_close(db); return -1; }
    return hid;
}

/*
 * gs_db_close(db_hid) → 0 OK
 */
static int gs_db_close(int db_hid) {
    GsHandle* h = get_handle(db_hid, GS_HANDLE_DB);
    if (!h) return -1;
    gs_fn_close((GsSqlite3*)h->ptr);
    free_handle(db_hid);
    return 0;
}

/* Échappe une chaîne pour JSON */
static void json_escape(const char* src, char* dst, int dstlen) {
    int j = 0;
    dst[j++] = '"';
    for (int i=0; src && src[i] && j<dstlen-4; i++) {
        unsigned char c = (unsigned char)src[i];
        if      (c == '"')  { dst[j++]='\\'; dst[j++]='"'; }
        else if (c == '\\') { dst[j++]='\\'; dst[j++]='\\'; }
        else if (c == '\n') { dst[j++]='\\'; dst[j++]='n'; }
        else if (c == '\r') { dst[j++]='\\'; dst[j++]='r'; }
        else if (c == '\t') { dst[j++]='\\'; dst[j++]='t'; }
        else                  dst[j++]=c;
    }
    dst[j++] = '"';
    dst[j]   = '\0';
}

static char gs_db_result_buf[1 << 20]; /* 1 Mo pour les résultats */

/*
 * gs_db_query(db_hid, sql) → JSON string (tableau d'objets) ou NULL
 * Exécute une requête SELECT et retourne les résultats en JSON.
 */
static const char* gs_db_query(int db_hid, const char* sql) {
    GsHandle* h = get_handle(db_hid, GS_HANDLE_DB);
    if (!h) return "[]";

    GsSqlite3*     db = (GsSqlite3*)h->ptr;
    GsSqliteStmt*  stmt = NULL;

    if (gs_fn_prepare(db, sql, -1, &stmt, NULL) != 0) {
        fprintf(stderr, "[db] Erreur SQL: %s\n", gs_fn_errmsg(db));
        return "[]";
    }

    int ncol = gs_fn_col_count(stmt);
    int pos  = 0;
    int cap  = (int)sizeof(gs_db_result_buf) - 4;

    gs_db_result_buf[pos++] = '[';
    int first_row = 1;

    /* SQLITE_ROW = 100 */
    while (gs_fn_step(stmt) == 100) {
        if (!first_row) gs_db_result_buf[pos++] = ',';
        first_row = 0;
        gs_db_result_buf[pos++] = '{';

        for (int c = 0; c < ncol && pos < cap-128; c++) {
            if (c > 0) gs_db_result_buf[pos++] = ',';

            /* Nom de colonne */
            const char* cname = gs_fn_col_name(stmt, c);
            char key_buf[128];
            json_escape(cname ? cname : "col", key_buf, sizeof(key_buf));
            int klen = (int)strlen(key_buf);
            memcpy(gs_db_result_buf + pos, key_buf, klen);
            pos += klen;
            gs_db_result_buf[pos++] = ':';

            /* Valeur */
            int ctype = gs_fn_col_type(stmt, c); /* 1=INT 2=FLOAT 3=TEXT 4=BLOB 5=NULL */
            if (ctype == 5) {
                memcpy(gs_db_result_buf + pos, "null", 4); pos += 4;
            } else if (ctype == 1) {
                pos += snprintf(gs_db_result_buf + pos, cap - pos, "%d",
                                gs_fn_col_int(stmt, c));
            } else if (ctype == 2) {
                pos += snprintf(gs_db_result_buf + pos, cap - pos, "%g",
                                gs_fn_col_double(stmt, c));
            } else {
                const unsigned char* txt = gs_fn_col_text(stmt, c);
                char val_buf[1024];
                json_escape(txt ? (const char*)txt : "", val_buf, sizeof(val_buf));
                int vlen = (int)strlen(val_buf);
                if (pos + vlen < cap) { memcpy(gs_db_result_buf+pos, val_buf, vlen); pos+=vlen; }
            }
        }
        gs_db_result_buf[pos++] = '}';
    }

    gs_fn_finalize(stmt);
    gs_db_result_buf[pos++] = ']';
    gs_db_result_buf[pos]   = '\0';
    return gs_db_result_buf;
}

/*
 * gs_db_exec(db_hid, sql) → 0 OK, -1 erreur
 * Exécute une instruction SQL sans résultat (INSERT, CREATE, etc.).
 */
static int gs_db_exec(int db_hid, const char* sql) {
    GsHandle* h = get_handle(db_hid, GS_HANDLE_DB);
    if (!h) return -1;
    GsSqlite3* db = (GsSqlite3*)h->ptr;
    char* errmsg = NULL;
    /* SQLITE_OK = 0 */
    int rc = gs_fn_exec(db, sql, NULL, NULL, &errmsg);
    if (rc != 0) {
        fprintf(stderr, "[db] Erreur exec SQL: %s\n", errmsg ? errmsg : "?");
        if (errmsg) gs_fn_free(errmsg);
        return -1;
    }
    return 0;
}

/*
 * gs_db_version() → version string de SQLite
 */
static const char* gs_db_version(void) {
    if (!load_sqlite_lib()) return "SQLite non disponible";
    typedef const char* (*fn_ver)(void);
    fn_ver f = (fn_ver)dlsym(gs_sqlite_lib, "sqlite3_libversion");
    if (!f) return "?";
    return f();
}

/* ========================================================================
 * ENREGISTREMENT DES FONCTIONS DANS L'ENVIRONNEMENT GOSCRIPT
 * ======================================================================== */

/*
 * Macro helper pour enregistrer une fonction C pure (retour int ou string)
 * sans passer par libffi (évite le problème de troncature pointeur sur 64 bits).
 * On encapsule chaque gs_* dans une Value de type 5 (C-func) via register_c_function,
 * OU on crée directement un type de valeur personnalisé.
 *
 * Ici, on utilise des wrappers qui stockent les fonctions dans des Values de type 4
 * (lambda) avec un nœud NULL et un pointeur spécial — mais la voie la plus propre
 * est d'utiliser une Value.type == 5 avec ffi_cif préparé.
 *
 * Pour éviter la complexité des pointeurs 64 bits, on expose chaque fonction
 * avec ffi_type_sint32 en entrée/sortie quand possible, et ffi_type_pointer
 * pour les chaînes de caractères.
 */

#define REG(name, fn, ret, nargs, ...) \
    register_c_function(env, name, (void*)(fn), ret, nargs, ##__VA_ARGS__)

void register_net_functions(Environment* env) {
    init_handle_table();

    /* ---- TCP ---- */
    REG("gs_tcp_connect",   gs_tcp_connect,   "int", 2, "string", "string");
    REG("gs_tcp_server",    gs_tcp_server,    "int", 1, "int");
    REG("gs_tcp_accept",    gs_tcp_accept,    "int", 1, "int");
    REG("gs_tcp_send",      gs_tcp_send,      "int", 2, "int", "string");
    REG("gs_tcp_recv",      gs_tcp_recv,      "string", 2, "int", "int");
    REG("gs_tcp_close",     gs_tcp_close,     "int", 1, "int");
    REG("gs_tcp_set_timeout", gs_tcp_set_timeout, "int", 2, "int", "int");
    REG("gs_tcp_peer_addr", gs_tcp_peer_addr, "string", 1, "int");

    /* ---- WebSocket ---- */
    REG("gs_ws_accept",     gs_ws_accept,     "int",    1, "int");
    REG("gs_ws_send",       gs_ws_send,       "int",    2, "int", "string");
    REG("gs_ws_recv",       gs_ws_recv,       "string", 1, "int");

    /* ---- Proxy ---- */
    REG("gs_proxy_start",          gs_proxy_start,          "int", 3, "int", "string", "int");
    REG("gs_proxy_accept_and_relay", gs_proxy_accept_and_relay, "int", 3, "int", "string", "int");

    /* ---- SQLite ---- */
    REG("gs_db_open",    gs_db_open,    "int",    1, "string");
    REG("gs_db_close",   gs_db_close,   "int",    1, "int");
    REG("gs_db_exec",    gs_db_exec,    "int",    2, "int", "string");
    REG("gs_db_query",   gs_db_query,   "string", 2, "int", "string");
    REG("gs_db_version", gs_db_version, "string", 0);
}
#undef REG
