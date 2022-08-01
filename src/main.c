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

const char* get_peer_ip(const struct sockaddr_in* const peer_addr) {
  const char* decoded_peer_ip = inet_ntoa(peer_addr->sin_addr);
  return decoded_peer_ip;
}

void handle_connection(int* server_sd)
{
  struct sockaddr_in peer_addr;
  socklen_t peer_addr_size;
  char response[4096];



  int peer_sd = accept(*server_sd, (struct sockaddr*)&peer_addr, &peer_addr_size);

  if (peer_sd == -1)
  {
    strerror(errno);
    strerror(errno);
  }
  printf("DEBUG: peer_addr - %s\n", get_peer_ip(&peer_addr));
  printf("DEBUG: peer_addr_size - %d\n", peer_addr_size);

  int received = 0;
  int total = sizeof(response) - 1;
  struct pollfd pfd;
  pfd.events = POLLIN;
  pfd.fd = peer_sd;

  int p = poll(&pfd, 1, 10000);
  memset(response, 0, sizeof(response));
  do {
    if (pfd.revents & POLLHUP) {
      printf("HUNG\n");
      break;
    }
    if (pfd.events & POLLIN) {
      printf("POLLIN\n");
      int bytes = recv(peer_sd, response + received, total - received, 0);
      if (bytes < 0)
        perror("Problem while reading request");
      if (bytes == 0)
        break;

      received += bytes;
      printf("Strlen: %d", strlen(response));
      printf("AFTER POLL\n");
    }
  } while (received < total);

  printf("Finished reading\n");
  printf("Response: %s", response);
  close(peer_sd);
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
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  int reuse_r = setsockopt(sock, SOL_SOCKET,  SO_REUSEADDR,
                  (char *)&on, sizeof(on));

  if(reuse_r == -1) {
    puts("dupa1\n");
    perror(strerror(errno));
  }

  int ioctl_r = ioctl(sock, FIONBIO, &on);

  if(ioctl_r == -1) {
    puts("dupa2\n");
    perror(strerror(errno));
  }






  while (1)
  {
    listen(sock, 1);
    handle_connection(&sock);

    printf("\nSENDING\n");
    char* resp = "HTTP/1.1 200 OK\n"
      "Content-Type: text/html\n"
      "Content-Length: 5\n"
      "Accept-Ranges: bytes\n"
      "Connection: close\n"
      "\n"
      "abcd";

  }
  return 0;
}
