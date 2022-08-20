#include "errno.h"
#include "poll.h"
#include "string.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_REQUEST_SIZE 2048
void initialize_reading_pfd(struct pollfd *const pfd, int peer_sd);

char * read_tcp_message(int peer_sd) {
  char *response = malloc(MAX_REQUEST_SIZE * sizeof response);
  memset(response, 0, MAX_REQUEST_SIZE);

  struct pollfd pfds[1];
  int rc;

  while (1) {
    initialize_reading_pfd((struct pollfd * const) &pfds[0], peer_sd);
    rc = poll(&pfds[0], 1, 10);
    if (rc == -1) {
      return NULL;
    }
    if (rc == 0) {
      break;
    }

    rc = read(peer_sd, response, MAX_REQUEST_SIZE);
    if (rc == -1) {
      return NULL;
    }
    if (rc == 0) {
      break;
    }
  }
  response[MAX_REQUEST_SIZE - 1] = '\0';
  return response;
}

int write_tcp_message(int peer_sd, const char *src) {
  return write(peer_sd, src, strlen(src) + 1);
}

void initialize_reading_pfd(struct pollfd *const pfd, int peer_sd) {
  pfd->fd = peer_sd;
  pfd->events = 0;
  pfd->events |= POLLIN;
}