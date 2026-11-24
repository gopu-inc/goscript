#ifndef GOSCRIPT_TOKEN_CACHE_H
#define GOSCRIPT_TOKEN_CACHE_H

#include <stddef.h>

/* Prepare a cached lexer stream for the next yyparse() call. */
int gs_token_cache_prepare(const char* source_path, const char* source, size_t source_len);
/* Load a token cache explicitly, without a source file for hash validation. */
int gs_token_cache_load_file(const char* cache_path);
void gs_token_cache_finish(void);

#endif
