#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/socket.h"
#include "netinet/ip.h"
#include "arpa/inet.h"
#include "errno.h"
#include "unistd.h"

void printErrIfBad(int val)
{
  if (val == -1)
  {
    printf("%s", strerror(errno));
  }
}

int main(int argc, char **argv)
{
  printf("Starting WebC\n");

  struct sockaddr_in socketAddress;
  socketAddress.sin_family = AF_INET;
  socketAddress.sin_port = htons(8080);

  struct in_addr ipAddress;
  ipAddress.s_addr = inet_addr("127.0.0.1");

  socketAddress.sin_addr = ipAddress;

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  printErrIfBad(sock);
  int bRes = bind(sock, (const struct sockaddr *)&socketAddress, sizeof(socketAddress));
  printf("Socket: %x\n", sock);
  printf("Bind res: %d\n", bRes);
  printErrIfBad(bRes);

  listen(sock, 1);
  struct sockaddr *peerAddr = NULL;
  socklen_t *peerAddrSize = NULL;

  char buff[100];

  printf("Reading packet:\n");

  int acceptedSock = accept(sock, peerAddr, peerAddrSize);
  while (1)
  {

    printf("%s\n", strerror(errno));
    printf("\nFinished Reading\n");
    printf("\nSENDING\n");
    char *resp = "HTTP/1.1 200 OK\n"
                 "Content-Type: text/html\n"
                 "Content-Length: 5\n"
                 "Accept-Ranges: bytes\n"
                 "Connection: close\n"
                 "\n"
                 "abcd";

    char *reply =
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "Server: Apache/2.2.3\n"
        "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: 16\n"
        "Accept-Ranges: bytes\n"
        "Connection: keep-alive\n"
        "\n"
        "sdfkjsdnbfkjbsf";

    int wrote = 0;
    while ((wrote = send(acceptedSock, resp, strlen(resp), 0)) != -1)
    {
      printf("Wrote: %d bytes\n", wrote);
    }

    printf("%s\n", strerror(errno));
    printf("\nFinished SENDING\n");
  }

  return 0;
}
