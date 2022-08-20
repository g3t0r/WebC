#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "server.h"

void show_usage() { puts("Usage: webc [IPv4] [PORT] [DIR]"); }

int main(int argc, char **argv) {
  char *ip, *dir;
  u_int16_t port;

  if (argc != 4) {
    show_usage();
    return -1;
  }
  
  ip = argv[1];
  port = (u_int16_t) strtol(argv[2], NULL, 10);
  dir = argv[3];
  start_server(ip, port, dir);
  return 0;
}