#include "queue.h"
#include <stdlib.h>


int_queue *create_queue() {
    int_queue *tmp = (int_queue *) malloc(sizeof(int_queue));
    tmp->init_head = 0;
    tmp->size = 0;
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
    q->buf[q->size] = val;
    q->size++;
    return true;
}

int pop(int_queue *q) {
    int res = q->buf[q->init_head];
    q->size--;
    q->init_head++;
    return res;
}

void destroy(int_queue *q) {
    free(q);
}