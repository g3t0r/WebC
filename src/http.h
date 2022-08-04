#ifndef WEBC_HTTP
#define WEBC_HTTP

#include "stdint.h"

struct http_req {
  const char *method;
  const char *path;
};

struct http_resp {
  uint16_t status_code;
  const char *status_text;
  const char *body;
};

void handle_request(int peer_sd);

struct http_req *parse_request(const char *request);

int send_response(const struct http_resp *const response);

const struct http_resp *const create_405_response(const char *body);

const struct http_resp *const create_404_response(const char *body);

const struct http_resp *const create_ok_response(const char *body);

const struct http_resp *const create_response(uint16_t status_code,
                                              const char *status_text,
                                              const char *body);

#endif
