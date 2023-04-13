#include "dyn_queue.h"
#include <stdio.h>
#include <stdlib.h>

static bool increase(int_queue *q) {
    int new_cap = q->cap * DEG;
    if (new_cap < MIN_CAPACITY) {
        new_cap = MIN_CAPACITY;
    }
    int *tmp = (int *) realloc(q->buf, sizeof(int) * new_cap);
    if (tmp == NULL) {
        return false;
    }
    for (int i = q->cap; i < new_cap; i++) {
        tmp[i] = 0;
    }
    q->buf = tmp;
    if (q->init_head + q->size > q->cap) {
        for (int i = 0; i < (q->init_head + q->size) - q->cap; i++) {
            q->buf[q->cap + i] = q->buf[i];
            q->buf[i] = 0;
        }
    }
    q->cap = new_cap;
    return true;
}

static void decrease_if_possible(int_queue * q) {
    if (q->size < q->cap / (DEG * DEG)) {
        int new_cap = q->cap / DEG;
        if ((q->init_head > new_cap) && (q->init_head + q->size) > q->cap) {
            for (int i = 0; i < (q->cap - q->init_head); i++) {
                q->buf[new_cap - i] = q->buf[q->cap - i];
            }
            q->init_head = new_cap - (q->cap - q->init_head);
            printf("[## | ##]");
        } else if ((q->init_head < new_cap - 1) && (q->init_head + q->size) > new_cap) {
            for (int i = new_cap; i < q->init_head + q->size; i++) {
                q->buf[i - new_cap] = q->buf[i];
            }
            printf("[ ##|## ]");
        } else if ((q->init_head >= new_cap - 1) && (q->init_head + q->size) <= q->cap) {
            for (int i = 0; i <= q->size; i++) {
                q->buf[i] = q->buf[q->init_head + i];
            }
            q->init_head = 0;
            printf("[  | ## ]");
        } else {
            printf("[ ## |  ]");
        }
        q->buf = (int *) realloc(q->buf, sizeof(int) * new_cap);
        q->cap = new_cap;
    }
}

int_queue *create_queue() {
    int_queue *tmp = (int_queue *) malloc(sizeof(int_queue));
    tmp->buf = (int *) malloc(sizeof(int) * MIN_CAPACITY);
    tmp->cap = MIN_CAPACITY;
    tmp->size = 0;
    tmp->init_head = 0;
    return tmp;
}

bool is_empty(int_queue *q) {
    return q->size == 0;
}

int length(int_queue *q) {
    return q->size;
}

bool push(int_queue *q, int val) {
    if (q->size == q->cap) {
        if (!increase(q)) {
            return false;
        }
    }
    q->buf[(q->init_head + q->size) % q->cap] = val;
    q->size++;
    return true;
}

int pop(int_queue *q) {
    int res = q->buf[q->init_head];
    q->buf[q->init_head] = 0;
    decrease_if_possible(q);
    q->init_head = (q->init_head + 1) % q->cap;
    q->size--;
    return res;
}

void destroy(int_queue *q) {
    free(q->buf);
    q->buf = NULL;
    q->cap = 0;
    q->init_head = 0;
    q->size = 0;
    free(q);
    q = NULL;
}