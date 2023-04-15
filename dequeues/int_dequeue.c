#include "int_dequeue.h"
#include <stdbool.h>
#include <stdlib.h>

int_dequeue *create_dequeue() {
    int_dequeue *tmp = (int_dequeue *) malloc(sizeof(int_dequeue));
    tmp->head = 0;
    tmp->tail = 0;
    tmp->size = 0;
    return tmp;
}

bool is_empty(int_dequeue *d) {
    return d->size == 0;
}

int size_of_dequeue(int_dequeue *d) {
    return d->size;
}

bool push_back(int_dequeue *d, int val) {
    if (d->size == MAX_CAPACITY) {
        return false;
    }
    d->buf[d->tail] = val;
    d->tail = (d->tail + 1) % MAX_CAPACITY;
    d->size++;
    return true;
}

bool push_front(int_dequeue *d, int val) {
    if (d->size == MAX_CAPACITY) {
        return false;
    }
    d->head = (d->head - 1 + MAX_CAPACITY) % MAX_CAPACITY;
    d->buf[d->head] = val;
    d->size++;
    return true;
}

int pop_back(int_dequeue *d) {
    d->tail = (d->tail - 1 + MAX_CAPACITY) % MAX_CAPACITY;
    int res = d->buf[d->tail];
    d->buf[d->tail] = 0;
    d->size--;
    return res;
}

int pop_front(int_dequeue *d) {
    int res = d->buf[d->head];
    d->buf[d->head] = 0;
    d->head = (d->head + 1) % MAX_CAPACITY;
    d->size--;
    return res;
}

void destroy(int_dequeue *d) {
    free(d);
}