#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/socket.h"
#include "netinet/ip.h"
#include "arpa/inet.h"
#include "errno.h"
#include "unistd.h"
#include "poll.h"
#include "sys/ioctl.h"
#define PORT 8081

void pifin(int res, const char* name) {
  if (res == -1) {
    printf("Problem with %s: %s\n", name, strerror(errno));
  }
}

const char* get_response() {
  return "HTTP/1.1 200 OK\n"
    "Content-Type: text/html\n"
    "Content-Length: 5\n"
    "Accept-Ranges: bytes\n"
    "Connection: close\n"
    "\n"
    "abcd\n";
}

const char* get_peer_ip(const struct sockaddr_in* const peer_addr) {
  const char* decoded_peer_ip = inet_ntoa(peer_addr->sin_addr);
  return decoded_peer_ip;
}

void handle_connection(int server_sd)
{
  struct sockaddr_in peer_addr;
  socklen_t peer_addr_size;
  char request[4096];
  char buff[2048];
  struct pollfd pfds[1];
  int rc, ret, transfered;
  const char* response = get_response();

  int peer_sd = accept(server_sd, NULL, NULL);
  pifin(peer_sd, "peer_sd");
  if (peer_sd == -1) {
    return;
  }

  printf("DEBUG: peer_addr - %s\n", get_peer_ip(&peer_addr));
  printf("DEBUG: peer_addr_size - %d\n", peer_addr_size);

  //reading

  transfered = 0;
  while (1) {
    pfds[0].fd = peer_sd;
    pfds[0].events = 0;
    pfds[0].events |= POLLIN;

    rc = poll(pfds, 1, 10);

    if (rc == 0) {
      printf("  Finished reading\n");
      break;
    }
    else {
      memset(buff, 0, sizeof(buff));
      ret = read(peer_sd, buff, sizeof(buff));
      pifin(ret, "ret");
      if (ret == -1) {
        break;
      }

      memcpy(request + transfered, buff, ret);
      transfered += ret;
    }
  } //end while

  request[sizeof(request) - 1] = '\0';
  printf("Full request: %s", request);

  // write response

  ret = 0;
  transfered = 0;
  ret = write(peer_sd, response, strlen(response) + 1);
  pifin(ret, "write");
  printf("write: %d", ret);

  // ret = write(peer_sd, "\0", 1);
  // pifin(ret, "write");
  // printf("write: %d" ,ret);


}

int main(int argc, char** argv)
{
  printf("Starting WebC\n");

  struct sockaddr_in socketAddress;
  socketAddress.sin_family = AF_INET;
  socketAddress.sin_port = htons(PORT);

  struct in_addr ipAddress;
  ipAddress.s_addr = inet_addr("0.0.0.0");

  socketAddress.sin_addr = ipAddress;
  int on = 1;
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  int rc = 0;

  // rc = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR,
  //   (char*)&on, sizeof(on));
  // pifin(rc, "socketopt");

  // rc = ioctl(sock_fd, FIONBIO, &on);
  // pifin(rc, "socketopt");

  rc = bind(sock_fd, (const struct sockaddr*)&socketAddress, sizeof(socketAddress));
  pifin(rc, "bind");

  while (1)
  {
    rc = listen(sock_fd, 1);
    pifin(rc, "listen");

    handle_connection(sock_fd);

    printf("\nSENDING\n");

  }
  return 0;
}
