#include "queue.h"
#include <stdlib.h>


int_queue *create_queue() {
    int_queue *tmp = (int_queue *) malloc(sizeof(int_queue));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->buf = (int *) malloc(sizeof(int) * MAX_SIZE);
    if (tmp == NULL) {
        exit(1);
    }
    tmp->init_head = tmp->buf;
    tmp->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        *(tmp->buf + i) = 0;
    }
    return tmp;
}

bool is_empty(int_queue *q) {
    return q->size == 0;
}

int length(int_queue *q) {
    return q->size;
}

bool push(int_queue *q, int val) {
    if (q->size == MAX_SIZE) {
        return false;
    }
    *(q->buf + q->size) = val;
    q->size++;
    return true;
}

int pop(int_queue *q) {
    if (q->size == 0) {
        exit(2);
    }
    q->buf += 1;
    q->size--;
    return *(q->buf - 1);
}

void destroy(int_queue *q) {
    free(q->init_head);
    q->init_head = NULL;
    free(q);
}