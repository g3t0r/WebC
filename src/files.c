#include "files.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"
#include "utils.h"

int isDirectory(const char *path) {
  struct stat statbuf;
  if (stat(path, &statbuf) != 0)
    return 0;
  return S_ISDIR(statbuf.st_mode);
}

const char *load_file(const char *webc_files_dir, const char *path) {
  int dir_l = strlen(webc_files_dir) * sizeof *path;
  int path_l = strlen(path) * sizeof *path;
  char *full_path = malloc(dir_l + path_l + sizeof *full_path);
  char *content = malloc(10000 * sizeof *content);
  memset(full_path, 0, dir_l + path_l + sizeof *full_path);
  strcat(full_path, webc_files_dir);
  strcat(full_path, path);

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

int find(const char *full_path) {
  FILE *file;

  file = fopen(full_path, "r");
  if (file != NULL && !isDirectory(full_path)) {
    return file;
  } else {
    const char *path_with_index = malloc(strlen(full_path) + 11);
    strcat(path_with_index, full_path);
    strcat(path_with_index, "index.html");
    file = fopen(path_with_index, "r");
    if (file == NULL) {
      return NULL;
    }
    return file;
  }
}