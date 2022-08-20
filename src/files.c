#include "files.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"

int isDirectory(const char *path) {
  struct stat statbuf;
  if (stat(path, &statbuf) != 0)
    return 0;
  return S_ISDIR(statbuf.st_mode);
}

FILE* find(const char *full_path) {
  FILE *file;

  file = fopen(full_path, "r");
  if (file != NULL && !isDirectory(full_path)) {
    return file;
  } else {
    char *path_with_index = calloc(strlen(full_path) + 11, sizeof *path_with_index);
    sprintf(path_with_index, "%s%s", full_path, "index.html");
    file = fopen(path_with_index, "r");
    if (file == NULL) {
      return NULL;
    }
    return file;
  }
}

const char *load_file(const char *webc_files_dir, const char *path) {
  int i = 0;
  char *full_path = NULL;
  if( asprintf(&full_path, "%s%s", webc_files_dir, path) == -1 ) {
    perror("asprintf");
  }
  char *content = calloc(10000000, sizeof *content);
  FILE *file = find(full_path);
  free(full_path);
  if (file == NULL) {
    perror("file");
    return NULL;
  }

  fseek(file, 0L, SEEK_END);
  int bytes_n = ftell(file);
  fseek(file, 0L, SEEK_SET);

  fread(content, sizeof(char), bytes_n, file);
  fclose(file);
  return content;
}
