#include "utils.h"
#include "stdlib.h"


char* malloc_s(const char *string) {
  return (const char *) malloc(char_size(string));
}

size_t str_size(const char* string) {
    return strlen(string) * sizeof(char);
}

size_t str_size_w_null(const char* string) {
  return str_size + sizeof(char);
}