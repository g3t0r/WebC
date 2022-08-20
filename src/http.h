#ifndef WEBC_HTTP
#define WEBC_HTTP

#include "stdint.h"

struct http_req {
  char *method;
  char *path;
};

struct http_resp {
  uint16_t status_code;
  char *status_text;
  char *body;
};

struct http_req *parse_request(const char *request);

char* resp_to_str(const struct http_resp *const response);

struct http_resp *create_405_response();

struct http_resp *create_404_response();

struct http_resp *create_ok_response(const char *body);

struct http_resp *create_response(uint16_t status_code,
                                              const char *status_text,
                                              const char *body);

#endif
