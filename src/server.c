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
#include "version_info.h"

void show_startup_info(uint16_t port) {
  printf("Started webC server v%s on port: %u\n", VERSION, port);
}

int start_server(const char *ip, u_int16_t port, const char *dir) {
  int sock_fd, r;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_fd == NULL) {
    perror("socket");
    exit(1);
  }
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  if(r = bind(sock_fd, (const struct sockaddr *)&addr, sizeof(addr))) {
    perror("Error while binding");
    exit(1);
  }
  
  show_startup_info(port);

  r = listen(sock_fd, 1);
  handle_connections(sock_fd, dir);
  close(sock_fd);
}

int handle_connections(int sock_fd, const char * files_dir) {
  int r, peer_sd;
  const char *message;
  struct http_req * request;
  struct http_resp *rsp = NULL;
  const char *rawrsp;

  while (1) {

    peer_sd = accept(sock_fd, NULL, NULL);

    message = read_tcp_message(peer_sd);
    request = parse_request(message);
    free(message);
    if(strcmp(request->method, "GET")) {
      free(request->method);
      free(request->path);
      free(request); 

      rsp = create_405_response();
      rawrsp = resp_to_str(rsp);
      
      free(rsp->body);
      free(rsp->status_text);
      free(rsp);
      
      write_tcp_message(peer_sd, rawrsp);
      continue;
    }

    const char *content = NULL;
    content = load_file(files_dir, request->path);

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
    rsp = NULL;
    content = NULL;
  }
}
