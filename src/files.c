#include "files.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const char *load_file(const char *webc_files_dir, const char *path) {
  char *full_path = (char *)malloc(strlen(webc_files_dir) + strlen(path) + 1);
  memset(full_path, 0, strlen(webc_files_dir) + strlen(path) + 1);
  strcat(full_path, webc_files_dir);
  strcat(full_path, path);

  FILE *file = find(full_path);
}

int find(const char *full_path) {
  FILE *file;

  file = fopen(full_path, "r");
  if (file != NULL) {
    return file;
  } else {
    const char* path_with_index = malloc(strlen(full_path) + 7);
    strcat(path_with_index, full_path);
    strcat(path_with_index, "/index.html");
    file = fopen(path_with_index, "r");
    if(file == NULL) {
      exit(1);
    }
    return file;
  }
}