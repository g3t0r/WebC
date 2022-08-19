#ifndef WEBC_SERVER_H
#define WEBC_SERVER_H

#include "stdlib.h"

/**
 * @brief start_server
 *
 * @param ip ip server should listen on
 * @param port port server should listen on
 * @param dir dir of static files to look for
 * @return 0 on success, -1 on failure
 */
int start_server(const char *ip, u_int16_t port, const char *dir);

/**
 * @brief handle_connection
 *
 * @param peer_sd peer socket of active connection
 * @return int 0 on success, -1 on failure
 */
int handle_connections(int peer_sd);

#endif