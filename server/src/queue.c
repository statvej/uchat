#include "../inc/server.h"
#include "../inc/queue.h"

queue_t *init_queue() {
    queue_t *ret = (queue_t *)malloc(sizeof(queue_t));
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

void add_to_queue(int *client_sock, queue_t *queue) {
    q_node_t *new_node = (q_node_t *)malloc(sizeof(q_node_t));
    new_node->client_sock = client_sock;
    new_node->next = NULL;
    if (queue->tail == NULL) {
        queue->head = new_node;
    }
    else {
        queue->tail->next = new_node;
    }
    queue->tail = new_node;
}

int *out_of_queue(queue_t *queue) {
    if (queue->head == NULL) {
        return NULL;
    }
    else {
        int *result = queue->head->client_sock;
        q_node_t *temp = queue->head;
        queue->head = queue->head->next;
        if (queue->head == NULL)
            queue->tail = NULL;
        else
            free(temp);

        return result;
    }
}
