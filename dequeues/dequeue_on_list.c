#include "dequeue_on_list.h"

int_dequeue *create_dequeue() {
    int_dequeue *tmp = (int_dequeue *) malloc(sizeof(int_dequeue));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->last = NULL;
    return tmp;
}

bool is_empty(int_dequeue *d) {
    return d->size == 0;
}

int size(int_dequeue *d) {
    return d->size;
}

void push(int_dequeue *d, int val) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = val;
    new_node->prev = d->last;
    new_node->next = NULL;
    if (d->last) {
        d->last->next = new_node;
    }
    d->last = new_node;
    if (d->head == NULL) {
        d->head = new_node;
    }
    d->size++;
}

void pushf(int_dequeue *d, int val) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = val;
    new_node->next = d->head;
    new_node->prev = NULL;
    if (d->head) {
        d->head->prev = new_node;
    }
    d->head = new_node;
    if (d->last == NULL) {
        d->last = new_node;
    }
    d->size++;
}

int pop(int_dequeue *d) {
    node *next = d->last;
    d->last = d->last->prev;
    if (d->last) {
        d->last->next = NULL;
    }
    if (next == d->head) {
        d->head = NULL;
    }
    int res = next->value;
    free(next);
    d->size--;
    return res;
}

int popf(int_dequeue *d) {
    node *prev = d->head;
    d->head = d->head->next;
    if (d->head) {
        d->head->prev = NULL;
    }
    if (prev == d->last) {
        d->last = NULL;
    }
    int res = prev->value;
    free(prev);
    d->size--;
    return res;
}

void destroy(int_dequeue *d) {
    node *next = NULL;
    while (d->head) {
        next = d->head->next;
        free(d->head);
        d->head = next;
    }
    free (d);
    d = NULL;
}