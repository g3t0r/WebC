#ifndef WEBC_TCP
#define WEBC_TCP

/**
 * @brief read_tcp_message
 *
 * @param peer_sd peer socket of active connection
 * @param dst pointer to read message to
 * @return int 0 on success, -1 on failure
 */
int read_tcp_message(int peer_sd, const char **dst);

/**
 * @brief read_tcp_message
 *
 * @param peer_sd peer socket of active connection
 * @param src pointer to write message from
 * @return int 0 on success, -1 on failure
 */
int write_tcp_message(int peer_sd, const char *src);

#endif