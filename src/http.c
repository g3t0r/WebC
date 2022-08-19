#include "http.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tcp.h"
char* get_first_line(const char *request);

struct http_req *parse_request(const char *request) {
  char *fl = get_first_line(request);
  struct http_req *rq = calloc(1, sizeof *rq);

  rq->method = strtok(fl, " ");
  rq->path = strtok(NULL, " ");
  printf("Method: %s\n", rq->method);
  printf("Path: %s\n", rq->path);
  free((void *)fl);
  return rq;
}

const char *resp_to_str(const struct http_resp *const response) {
  char *bfc;
  asprintf(&bfc, "HTTP/1.1 %u %s\nContent-Length: %d\n\n%s",
           response->status_code, response->status_text, strlen(response->body),
           response->body);

  return bfc;
}

const struct http_resp *const create_405_response(const char *body) {}

const struct http_resp *const create_404_response() {
  struct http_resp *resp = malloc(sizeof *resp);
  resp->body = "<html><body>"
               "<img src=\"https://http.cat/404\"/>"
               "</body></html>\n";
  resp->status_code = 404;
  resp->status_text = "Not Found";
  return resp;
}

const struct http_resp *const create_ok_response(const char *body) {
  struct http_resp *resp = malloc(sizeof *resp);
  resp->body = body;
  resp->status_code = 200;
  resp->status_text = "OK";
  return resp;
}


char* get_first_line(const char *request) {
  int i = 0;
  char delim[] = "\n";
  char *tmp = NULL;
  char *fl = calloc((strlen(request) + 1), sizeof *fl);

  strncpy(fl, request, strlen(request) + 1);
  fl = strtok(fl, delim);
  if((tmp = realloc(fl, (strlen(fl) + 1) * sizeof *tmp))) {
    fl = tmp;
  }

  return tmp;
}
