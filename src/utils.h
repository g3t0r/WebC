#ifndef WEBC_UTILS
#define WEBC_UTILS

#include "string.h"
#include "sys/types.h"
#include "stddef.h"

char* malloc_s(const char *string);


size_t str_size(const char* string);

#endif