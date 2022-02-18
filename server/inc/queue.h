#include "server.h"

typedef struct q_node_s {
    struct q_node_s *next;
    int *client_sock;
} q_node_t;


int add_to_queue(int *client_sock, q_node_t **head, q_node_t **tail);
int *out_of_queue(q_node_t **head, q_node_t **tail);
