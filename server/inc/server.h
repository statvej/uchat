#pragma once


#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#include <pthread.h>
#include <stdbool.h>

#define THREAD_POOL_SIZE 10
#define PORT 8080

typedef struct q_node_s {
    struct q_node_s *next;
    int *client_sock;
} q_node_t;

typedef struct server_init_data_s {
    int socket;
    socklen_t sock_len;
    struct sockaddr_in addr;
} server_init_data_t;

server_init_data_t init_server(char *ip);
int server_loop(server_init_data_t server_data);