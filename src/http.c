#include "http.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tcp.h"

struct http_req *parse_request(const char *request) {}

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
