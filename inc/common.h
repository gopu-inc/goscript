#ifndef GOSCRIPT_COMMON_H
#define GOSCRIPT_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

#include "token.h"

void error(const char* message, int line);
void* allocate(size_t size);

#endif
