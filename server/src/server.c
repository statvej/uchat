#include "../inc/server.h"
#include "../inc/queue.h"



// void init_queue(q_node_t ** head, q_node_t ** tail){

// }
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

    ret.sock_len = sizeof(address);
    ret.socket = server_fd;
    ret.addr = address;
    return ret;
}
int server_loop(server_init_data_t server_data) {
    q_node_t *head = NULL;
    q_node_t *tail = NULL;

    int new_socket;
    while (true) {

        if (listen(server_data.socket, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_data.socket, (struct sockaddr *)&server_data.addr, &server_data.sock_len)) <
            0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        int *client_sock = malloc(sizeof(int));
        *client_sock = new_socket;
        pthread_t thread;
        void *data_packet;
        pthread_create(&thread, NULL, accept_message, (void *)client_sock);
        pthread_join(thread, &data_packet);
        // printf("%s\n", (char *)data_packet);
        free(data_packet);
        // char *message = accept_message(client_sock);
        // printf("Message is : %s", message);
        // free(message);
        close(new_socket);
    }
}

void *accept_message(void *p_socket_fd) {
    int socket_fd = *(int *)p_socket_fd;
    free(p_socket_fd);
    char *buffer = (char *)malloc(sizeof(char) * 1024);
    read(socket_fd, buffer, 1024);
    printf("%s\n", buffer);
    return (void *)buffer;
}
