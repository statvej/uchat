#include "../inc/server.h"
#include "../inc/queue.h"

int add_to_queue(int *client_sock, q_node_t **head, q_node_t **tail) {
    q_node_t *temp_tail = *tail;
    q_node_t *temp_head = *head;
    q_node_t *new_node = (q_node_t *)malloc(sizeof(q_node_t));
    new_node->client_sock = client_sock;
    new_node->next = NULL;
    if (*tail == NULL) {
        *head = new_node;
    }
    else {
        temp_tail->next = new_node;
        *tail = temp_tail;
    }
    *tail = new_node;
    return 0;
}

int *out_of_queue(q_node_t **head, q_node_t **tail) {
    q_node_t *temp_head = *head;
    if (*head == NULL) {
        return NULL;
    }
    else {
        int *result = temp_head->client_sock;
        *head = temp_head->next;
        if (*head == NULL) {
            *tail = NULL;
        }
        free(temp_head);
        return result;
    }
}

