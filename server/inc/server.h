#pragma once

#ifndef UCHAT_SERVER_H
#define UCHAT_SERVER_H

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
#include <ctype.h>
#include "cJSON.h"

#define THREAD_POOL_SIZE 20
#define PORT 8080
#define INVALID_IP "IP address in invalid\n"


typedef struct server_init_data_s {
    int socket;
    socklen_t sock_len;
    struct sockaddr_in addr;
} server_init_data_t;

//Continious loop with threads actions
void *thread_loop(void *data);

//This function initialases server(used once)
server_init_data_t init_server(char *ip);

//Continios server loop
int server_loop(server_init_data_t server_data);

//accepts message using socket file descriptor
void *accept_message(void *p_socket_fd);

pthread_t *init_thread_pool(int thread_pool_size, void * data);
void init_thread_pool_global(void *data);

int validate_number(char *str);
void validate_ip(char *ip);
char * get_current_time(void);


#endif
