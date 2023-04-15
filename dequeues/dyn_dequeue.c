#include "dyn_dequeue.h"
#include <stdio.h>
#include <stdlib.h>


static bool increase(int_dequeue *d) {
    int new_cap = d->cap * 2;
    if (new_cap < MIN_CAPACITY) {
        new_cap = MIN_CAPACITY;
    }
    int *tmp = (int *) realloc(d->buf, sizeof(int) * new_cap);
    if (tmp == NULL) {
        return false;
    }
    for (int i = d->cap; i < new_cap; i++) {
        tmp[i] = 0;
    }
    d->buf = tmp;
    if (d->head + d->size > d->cap) {
        for (int i = 0; i < (d->head + d->size) - d->cap; i++) {
            d->buf[d->cap + i] = d->buf[i];
            d->buf[i] = 0;
        }
    }
    d->tail = d->head + d->size;
    d->cap = new_cap;
    return true;
}

static void decrease_if_possible(int_dequeue *d) {
    if (d->size < d->cap / 4) {
        int new_cap = d->cap / 2;
        if ((d->head > new_cap) && (d->head + d->size) > d->cap) {
            for (int i = 0; i <= (d->cap - d->head); i++) {
                d->buf[new_cap - i] = d->buf[d->cap - i];
            }
            d->head = new_cap - (d->cap - d->head);
            printf("[## | ##]");
        } else if ((d->head < new_cap - 1) && (d->head + d->size) > new_cap) {
            for (int i = new_cap; i < d->head + d->size; i++) {
                d->buf[i - new_cap] = d->buf[i];
            }
            d->tail = d->head + d->size - new_cap - 1;
            printf("[ ##|## ]");
        } else if ((d->head >= new_cap - 1) && (d->head + d->size) <= d->cap) {
            for (int i = 0; i <= d->size; i++) {
                d->buf[i] = d->buf[d->head + i];
            }
            d->head = 0;
            d->tail = d->head + d->size;
            printf("[  | ## ]");
        } else {
            printf("[ ## |  ]");
        }
        d->buf = (int *) realloc(d->buf, sizeof(int) * new_cap);
        d->cap = new_cap;
    }
}

int_dequeue *create_dequeue() {
    int_dequeue *tmp = (int_dequeue *) malloc(sizeof(int_dequeue));
    tmp->buf = (int *) malloc(sizeof(int) * MIN_CAPACITY);
    tmp->cap = MIN_CAPACITY;
    tmp->head = 0;
    tmp->tail = 0;
    tmp->size = 0;
    return tmp;
}

int size_of_dequeue(int_dequeue *d) {
    return d->size;
}

bool is_empty(int_dequeue *d) {
    return d->size == 0;
}

bool push_back(int_dequeue *d, int val) {
    if ((d->size == d->cap) && (!increase(d))) {
        return false;
    }
    d->buf[d->tail] = val;
    d->tail = (d->tail + 1) % d->cap;
    d->size++;
    return true;
}

bool push_front(int_dequeue *d, int val) {
    if ((d->size == d->cap) && (!increase(d))) {
        return false;
    }
    d->head = (d->head - 1 + d->cap) % d->cap;
    d->buf[d->head] = val;
    d->size++;
    return true;
}

int pop_back(int_dequeue *d) {
    d->tail = (d->tail - 1 + d->cap) % d->cap;
    int res = d->buf[d->tail];
    d->buf[d->tail] = 0;
    decrease_if_possible(d);
    d->size--;
    return res;
}

int pop_front(int_dequeue *d) {
    int res = d->buf[d->head];
    d->buf[d->head] = 0;
    decrease_if_possible(d);
    d->head = (d->head + 1) % d->cap;
    d->size--;
    return res;
}

void destroy(int_dequeue *d) {
    free(d->buf);
    d->buf = NULL;
    d->cap = 0;
    d->head = 0;
    d->tail = 0;
    d->size = 0;
    free(d);
}

