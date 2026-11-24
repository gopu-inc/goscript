#define _POSIX_C_SOURCE 200809L
#include "token_cache.h"
#include "parser.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>

extern int goscript_scan_token(void);
extern int yylineno;
extern YYSTYPE yylval;
extern FILE* yyin;
extern void yyrestart(FILE* input_file);

#define GJSC_VERSION 1u
#define GJSC_MAX_TOKENS 10000000u
#define GJSC_MAX_STRING (64u * 1024u * 1024u)

typedef struct {
    int32_t token;
    int32_t line;
    int64_t integer;
    double real;
    uint32_t string_len;
    char* string;
} CachedToken;

typedef struct {
    char magic[8];
    uint32_t version;
    uint32_t token_count;
    uint64_t source_hash;
    uint64_t source_size;
} CacheHeader;

static CachedToken* tokens;
static size_t token_count;
static size_t token_capacity;
static size_t token_cursor;
static int cache_active;

static uint64_t hash_source(const char* source, size_t length) {
    uint64_t hash = UINT64_C(14695981039346656037);
    for (size_t i = 0; i < length; i++) {
        hash ^= (unsigned char)source[i];
        hash *= UINT64_C(1099511628211);
    }
    return hash;
}

static int append_token(int token, int line, const YYSTYPE* value) {
    if (token_count >= GJSC_MAX_TOKENS) return 0;
    if (token_count == token_capacity) {
        size_t capacity = token_capacity ? token_capacity * 2 : 256;
        CachedToken* grown = realloc(tokens, capacity * sizeof(*tokens));
        if (!grown) return 0;
        tokens = grown;
        token_capacity = capacity;
    }
    CachedToken item = {0};
    item.token = token;
    item.line = line > 0 ? line : 1;
    if (token == TOKEN_IDENTIFIER || token == TOKEN_STRING || token == TOKEN_F_STRING) {
        const char* text = value ? value->string : NULL;
        size_t length = text ? strlen(text) : 0;
        if (length > GJSC_MAX_STRING) return 0;
        item.string = text ? strdup(text) : strdup("");
        if (!item.string) return 0;
        item.string_len = (uint32_t)length;
    } else if (token == TOKEN_NUMBER) {
        item.integer = value ? value->number : 0;
    } else if (token == TOKEN_FLOAT) {
        item.real = value ? value->float_val : 0.0;
    }
    tokens[token_count++] = item;
    return 1;
}

static char* cache_path_for(const char* source_path) {
    if (!source_path || !*source_path || strcmp(source_path, "REPL") == 0 || source_path[0] == '<') return NULL;
    char source_copy[PATH_MAX];
    if (strlen(source_path) >= sizeof(source_copy)) return NULL;
    strcpy(source_copy, source_path);
    char* base = basename(source_copy);
    char* dir_copy = strdup(source_path);
    if (!dir_copy) return NULL;
    char* dir = dirname(dir_copy);
    const char* ext = ".gjs";
    size_t base_len = strlen(base);
    size_t stem_len = base_len >= 4 && strcmp(base + base_len - 4, ext) == 0 ? base_len - 4 : base_len;
    size_t needed = strlen(dir) + strlen("/__gocache__/") + stem_len + strlen(".goscript.gbc") + 1;
    char* result = malloc(needed);
    if (result) snprintf(result, needed, "%s/__gocache__/%.*s.goscript.gbc", dir, (int)stem_len, base);
    free(dir_copy);
    return result;
}

static int read_cache(const char* path, uint64_t hash, size_t source_len, int validate_source) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;
    CacheHeader header;
    if (fread(&header, sizeof(header), 1, f) != 1 || memcmp(header.magic, "GJSCACHE", 8) != 0 ||
        header.version != GJSC_VERSION ||
        (validate_source && (header.source_hash != hash || header.source_size != source_len)) ||
        header.token_count == 0 || header.token_count > GJSC_MAX_TOKENS) {
        fclose(f);
        return 0;
    }
    CachedToken* loaded = calloc(header.token_count, sizeof(*loaded));
    if (!loaded) { fclose(f); return 0; }
    int valid = 1;
    for (uint32_t i = 0; i < header.token_count; i++) {
        uint8_t kind;
        if (fread(&loaded[i].token, sizeof(loaded[i].token), 1, f) != 1 ||
            fread(&loaded[i].line, sizeof(loaded[i].line), 1, f) != 1 ||
            fread(&kind, sizeof(kind), 1, f) != 1) { valid = 0; break; }
        if (kind == 1) {
            if (fread(&loaded[i].integer, sizeof(loaded[i].integer), 1, f) != 1) { valid = 0; break; }
        } else if (kind == 2) {
            if (fread(&loaded[i].real, sizeof(loaded[i].real), 1, f) != 1) { valid = 0; break; }
        } else if (kind == 3) {
            if (fread(&loaded[i].string_len, sizeof(loaded[i].string_len), 1, f) != 1 || loaded[i].string_len > GJSC_MAX_STRING) { valid = 0; break; }
            loaded[i].string = malloc((size_t)loaded[i].string_len + 1);
            if (!loaded[i].string || fread(loaded[i].string, 1, loaded[i].string_len, f) != loaded[i].string_len) { valid = 0; break; }
            loaded[i].string[loaded[i].string_len] = '\0';
        } else if (kind != 0) { valid = 0; break; }
    }
    if (fgetc(f) != EOF) valid = 0;
    fclose(f);
    if (!valid || loaded[header.token_count - 1].token != 0) {
        for (uint32_t i = 0; i < header.token_count; i++) free(loaded[i].string);
        free(loaded);
        return 0;
    }
    tokens = loaded;
    token_count = token_capacity = header.token_count;
    token_cursor = 0;
    return 1;
}

static int write_cache(const char* path, uint64_t hash, size_t source_len) {
    if (!path || !token_count || token_count > UINT32_MAX) return 0;
    char* dir = strdup(path);
    if (!dir) return 0;
    char* parent = dirname(dir);
    if (mkdir(parent, 0755) != 0 && access(parent, W_OK) != 0) { free(dir); return 0; }
    size_t temp_len = strlen(path) + 16;
    char* temp = malloc(temp_len);
    if (!temp) { free(dir); return 0; }
    snprintf(temp, temp_len, "%s.tmpXXXXXX", path);
    int fd = mkstemp(temp);
    if (fd < 0) { free(temp); free(dir); return 0; }
    (void)fchmod(fd, 0644);
    FILE* f = fdopen(fd, "wb");
    if (!f) { close(fd); unlink(temp); free(temp); free(dir); return 0; }
    CacheHeader header = {{'G','J','S','C','A','C','H','E'}, GJSC_VERSION, (uint32_t)token_count, hash, source_len};
    int ok = fwrite(&header, sizeof(header), 1, f) == 1;
    for (size_t i = 0; ok && i < token_count; i++) {
        CachedToken* t = &tokens[i];
        uint8_t kind = (t->token == TOKEN_NUMBER) ? 1 : (t->token == TOKEN_FLOAT) ? 2 :
                       (t->token == TOKEN_IDENTIFIER || t->token == TOKEN_STRING || t->token == TOKEN_F_STRING) ? 3 : 0;
        ok = fwrite(&t->token, sizeof(t->token), 1, f) == 1 && fwrite(&t->line, sizeof(t->line), 1, f) == 1 && fwrite(&kind, sizeof(kind), 1, f) == 1;
        if (ok && kind == 1) ok = fwrite(&t->integer, sizeof(t->integer), 1, f) == 1;
        else if (ok && kind == 2) ok = fwrite(&t->real, sizeof(t->real), 1, f) == 1;
        else if (ok && kind == 3) ok = fwrite(&t->string_len, sizeof(t->string_len), 1, f) == 1 && fwrite(t->string, 1, t->string_len, f) == t->string_len;
    }
    if (fclose(f) != 0) ok = 0;
    if (ok) ok = rename(temp, path) == 0;
    if (!ok) unlink(temp);
    free(temp);
    free(dir);
    return ok;
}

int gs_token_cache_prepare(const char* source_path, const char* source, size_t source_len) {
    gs_token_cache_finish();
    char* path = cache_path_for(source_path);
    uint64_t hash = hash_source(source, source_len);
    if (path && read_cache(path, hash, source_len, 1)) {
        cache_active = 1;
        free(path);
        return 1;
    }
    yyrestart(yyin);
    int token, ok = 1;
    do {
        int line = yylineno;
        token = goscript_scan_token();
        int token_line = yylineno;
        if (!append_token(token, token_line >= line ? token_line : line, &yylval)) { ok = 0; break; }
    } while (token != 0);
    if (ok) {
        token_cursor = 0;
        cache_active = 1;
        if (path) write_cache(path, hash, source_len);
    }
    free(path);
    return ok;
}

int gs_token_cache_load_file(const char* cache_path) {
    gs_token_cache_finish();
    if (!cache_path || !read_cache(cache_path, 0, 0, 0)) return 0;
    token_cursor = 0;
    cache_active = 1;
    return 1;
}

int yylex(void) {
    if (!cache_active || token_cursor >= token_count) return 0;
    CachedToken* token = &tokens[token_cursor++];
    yylineno = token->line;
    memset(&yylval, 0, sizeof(yylval));
    if (token->token == TOKEN_IDENTIFIER || token->token == TOKEN_STRING || token->token == TOKEN_F_STRING) yylval.string = strdup(token->string ? token->string : "");
    else if (token->token == TOKEN_NUMBER) yylval.number = token->integer;
    else if (token->token == TOKEN_FLOAT) yylval.float_val = token->real;
    return token->token;
}

void gs_token_cache_finish(void) {
    for (size_t i = 0; i < token_count; i++) free(tokens[i].string);
    free(tokens);
    tokens = NULL;
    token_count = token_capacity = token_cursor = 0;
    cache_active = 0;
}
