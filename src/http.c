#include "http.h"
#include "stdio.h"


void handle_request(int peer_sd) {
    
}

struct http_req *parse_request(const char *request) {
}

int send_response(const struct http_resp *const response) {
    
}

const struct http_resp *const create_405_response(const char *body) {
    
}

const struct http_resp *const create_404_response(const char *body) {
    
}

const struct http_resp *const create_ok_response(const char *body) {
    
}
