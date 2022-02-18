#include "server.h"

typedef struct q_node_s {
    struct q_node_s *next;
    int *client_sock;
} q_node_t;

typedef struct queue_s{
    q_node_t * head, *tail;
}queue_t;
queue_t *init_queue();
void add_to_queue(int *client_sock, queue_t * queue);
int *out_of_queue(queue_t * queue);
