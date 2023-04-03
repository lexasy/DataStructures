#include "dyn_queue.h"
#include <stdlib.h>

int_queue *create_queue() {
    int_queue *tmp = (int_queue *) malloc(sizeof(int_queue));
    tmp->buf = (int *) malloc(sizeof(int));
    tmp->init_head = tmp->buf;
    tmp->size = 0;
    *(tmp->buf) = 0;
    return tmp;
}

bool is_empty(int_queue *q) {
    return q->size == 0;
}

int length(int_queue *q) {
    return q->size;
}

bool push(int_queue *q, int val) {
    int *tmp;
    tmp = realloc(q->buf, (q->size + 1) * sizeof(int));
    if (tmp == NULL) {
        return false;
    }
    q->buf = tmp;
    *(q->buf + q->size) = val;
    q->size++;
    return true;
}

int pop(int_queue *q) {
    q->buf += 1;
    q->size--;
    return *(q->buf - 1);
}

void destroy(int_queue *q) {
    free(q->init_head);
    q->init_head = NULL;
    free(q);
}