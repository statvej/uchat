#include "../inc/server.h"
#include "../inc/queue.h"

// To fix race conditions
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
//Improves cpu usage with multiple conections
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

server_init_data_t init_server(char *ip) {
    server_init_data_t ret;
    struct sockaddr_in address;

    int server_fd;
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
    // Forcefully attaching socket to the port predefined
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    ret.sock_len = sizeof(address);
    ret.socket = server_fd;
    ret.addr = address;
    return ret;
}

int server_loop(server_init_data_t server_data) {
    // queue initialisation
    queue_t *queue = init_queue();
    // Thread pool init
    pthread_t *thread_pool = init_thread_pool(THREAD_POOL_SIZE, (void *)queue);

    // initialising other variables

    int new_socket;
    // loop that handles multiple conections
    while (true) {

        if ((new_socket = accept(server_data.socket, (struct sockaddr *)&server_data.addr, &server_data.sock_len)) <
            0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        int *client_sock = malloc(sizeof(int));
        *client_sock = new_socket;

        pthread_mutex_lock(&mutex);
        add_to_queue(client_sock, queue);
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
}

pthread_t *init_thread_pool(int thread_pool_size, void *data) {
    pthread_t *thread_pool = (pthread_t *)malloc(sizeof(pthread_t) * thread_pool_size);
    for (int i = 0; i < thread_pool_size; i++) {
        pthread_create(&thread_pool[i], NULL, thread_loop, data);
    }
    return thread_pool;
}

void *accept_message(void *p_socket_fd) {
    int socket_fd = *(int *)p_socket_fd;
    char *buffer = (char *)malloc(sizeof(char) * 1024);
    read(socket_fd, buffer, 1024);
    if (buffer != NULL) {
        printf("%s\n", buffer);
    }
    close(socket_fd);
    free(buffer);
    return NULL;
}

void *thread_loop(void *data) {
    queue_t *queue = (queue_t *)data;
    while (true) {
        pthread_mutex_lock(&mutex);
        int *p_client;
        if((p_client = out_of_queue(queue)) == NULL){
            pthread_cond_wait(&cond_var, &mutex);
            p_client = out_of_queue(queue);
        }
        
        pthread_mutex_unlock(&mutex);
        if (p_client != NULL) {
            accept_message(p_client);
        }
    }
}
