#include "queue_on_list.h"
#include <stdlib.h>

int_queue *create_queue() {
    int_queue *tmp = (int_queue *) malloc(sizeof(int_queue));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->last = NULL;
    return tmp;
}

bool is_empty(int_queue *q) {
    return q->size == 0;
}

int size(int_queue *q) {
    return q->size;
}

void push(int_queue *q, int val) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = val;
    new_node->prev = q->last;
    new_node->next = NULL;
    if (q->last) {
        q->last->next = new_node;
    }
    q->last = new_node;
    if (q->head == NULL) {
        q->head = new_node;
    }
    q->size++;
}

int pop(int_queue *q) {
    node *prev = q->head;
    q->head = q->head->next;
    if (q->head) {
        q->head->prev = NULL;
    }
    if (prev == q->last) {
        q->last = NULL;
    }
    int val = prev->value;
    free(prev);
    q->size--;
    return val;
}

void destroy(int_queue *q) {
    node *next = NULL;
    while (q->head) {
        next = q->head->next;
        free(q->head);
        q->head = next;
    }
    free (q);
    q = NULL;
}