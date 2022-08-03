#include "errno.h"
#include "poll.h"
#include "string.h"
#include "unistd.h"
#include "stdio.h"

#define MAX_REQUEST_SIZE 2048

int read_tcp_message(int peer_sd, const char **dst) {
  char *response = (const char *)malloc(sizeof(char) * MAX_REQUEST_SIZE);
  memset(response, 0, MAX_REQUEST_SIZE);

  struct pollfd pfds[1];
  int rc;

  while (1) {
    initialize_reading_pfd(&pfds[0], peer_sd);
    rc = poll(&pfds[0], 1, 0);
    if (rc == -1) {
      perror(strerror(errno));
      return rc;
    }
    if (rc == 0) {

      perror(strerror(errno));
      break;
    }

    rc = read(peer_sd, response, MAX_REQUEST_SIZE);
    if (rc == -1) {
      return -1;
    }
    if (rc == 0) {
      break;
    }
  }
  response[MAX_REQUEST_SIZE - 1] = '\0';
  printf("boi wtf: %s", response);
  *dst = (const char *)response;
  printf("boi wtf 2: %s", *dst);
  return 0;
}

int write_tcp_message(int peer_sd, const char *src) {
  return write(peer_sd, src, strlen(src) + 1);
}

void initialize_reading_pfd(struct pollfd *const pfd, int peer_sd) {
  pfd->fd = peer_sd;
  pfd->events = 0;
  pfd->events |= POLLIN;
}