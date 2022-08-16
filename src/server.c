#include "server.h"
#include "arpa/inet.h"
#include "errno.h"
#include "files.h"
#include "http.h"
#include "netinet/ip.h"
#include "poll.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/socket.h"
#include "tcp.h"
#include "unistd.h"

int start_server(const char *ip, u_int16_t port, const char *dir) {
  int sock_fd, r;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");

  r = bind(sock_fd, (const struct sockaddr *)&addr, sizeof(addr));

  r = listen(sock_fd, 1);
  handle_connection(sock_fd);
  close(sock_fd);
}

int handle_connection(int sock_fd) {
  int r, peer_sd;
  const char *request;
  while (1) {

    peer_sd = accept(sock_fd, NULL, NULL);

    const char *content = NULL;
    content = load_file("static", "/");

    struct http_resp *rsp = NULL;
    const char *rawrsp;
    if(content == NULL) {
      rsp = create_404_response();
      rawrsp = resp_to_str(rsp);
    } else {
      rsp = create_ok_response(content);
      rawrsp = resp_to_str(rsp);
      free(rsp->body);
    }

    free(rsp);
    write_tcp_message(peer_sd, rawrsp);
  }
}

int main() { start_server(NULL, NULL, NULL); }