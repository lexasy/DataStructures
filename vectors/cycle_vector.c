#include "cycle_vector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static bool increase(int_vector *v) {
    int new_cap = v->cap * 2;
    if (new_cap < MIN_CAPACITY) {
        new_cap = MIN_CAPACITY;
    }
    int *tmp = (int *) realloc(v->buf, sizeof(int) * new_cap);
    if (tmp == NULL) {
        return false;
    }
    for (int i = v->cap; i < new_cap; i++) {
        tmp[i] = 0;
    }
    v->buf = tmp;
    if (v->head + v->size > v->cap) {
        for (int i = 0; i < (v->head + v->size) - v->cap; i++) {
            v->buf[v->cap + i] = v->buf[i];
            v->buf[i] = 0;
        }
    }
    v->tail = v->head + v->size;
    v->cap = new_cap;
    return true;
}

static void decrease_if_possible(int_vector *v) {
    if (v->size < v->cap / 4) {
        int new_cap = v->cap / 2;
        if ((v->head > new_cap) && (v->head + v->size) > v->cap) {
            for (int i = 0; i <= (v->cap - v->head); i++) {
                v->buf[new_cap - i] = v->buf[v->cap - i];
            }
            v->head = new_cap - (v->cap - v->head);
            printf("[## | ##]");
        } else if ((v->head < new_cap - 1) && (v->head + v->size) > new_cap) {
            for (int i = new_cap; i < v->head + v->size; i++) {
                v->buf[i - new_cap] = v->buf[i];
            }
            v->tail = v->head + v->size - new_cap - 1;
            printf("[ ##|## ]");
        } else if ((v->head >= new_cap - 1) && (v->head + v->size) <= v->cap) {
            for (int i = 0; i <= v->size; i++) {
                v->buf[i] = v->buf[v->head + i];
            }
            v->head = 0;
            v->tail = v->head + v->size - 1;
            printf("[  | ## ]");
        } else {
            printf("[ ## |  ]");
        }
        v->buf = (int *) realloc(v->buf, sizeof(int) * new_cap);
        v->cap = new_cap;
    }
}

bool set_size(int_vector *v, int new_size) {
    if (new_size == v->size) {
        return true;
    } else if (new_size > v->cap) {
        int new_cap = v->cap * 2;
        while (new_cap < new_size) {
            new_cap *= 2;
        }
        int *tmp = (int *) realloc(v->buf, sizeof(int) * new_cap);
        if (tmp == NULL) {
            return false;
        }
        for (int i = v->cap; i < new_cap; i++) {
            tmp[i] = 0;
        }
        v->buf = tmp;
        if (v->head + v->size > v->cap) {
            for (int i = 0; i < (v->head + v->size) - v->cap; i++) {
                v->buf[v->cap + i] = v->buf[i];
                v->buf[i] = 0;
            }
        }
        v->size = new_size;
        v->tail = v->head + v->size;
        v->cap = new_cap;
        return true;
    } else if (new_size < v->size) {
        for (int i = new_size; i < v->size; i++) {
            v->buf[(v->head + i) % v->cap] = 0;
            v->tail = (v->tail - 1 + v->cap) % v->cap;
        }
        v->size = new_size;
        return true;
    } else {
        v->size = new_size;
        v->tail = v->head + v->size;
        return true;
    }
}

int_vector *create_vector() {
    int_vector *tmp = (int_vector *) malloc(sizeof(int_vector));
    tmp->buf = (int *) malloc(sizeof(int) * MIN_CAPACITY);
    tmp->cap = MIN_CAPACITY;
    tmp->head = 0;
    tmp->tail = 0;
    tmp->size = 0;
    return tmp;
}

int get_size(int_vector *v) {
    return v->size;
}

bool is_empty(int_vector *v) {
    return v->size == 0;
}

int get_elem(int_vector *v, int idx) {
    return v->buf[(v->head + idx) % v->cap];
}

void set_elem(int_vector *v, int idx, int val) {
    v->buf[(v->head + idx) % v->cap] = val;
}

bool push_back(int_vector *v, int val) {
    if ((v->size == v->cap) && (!increase(v))) {
        return false;
    }
    v->buf[v->tail] = val;
    v->tail = (v->tail + 1) % v->cap;
    v->size++;
    return true;
}

bool push_front(int_vector *v, int val) {
    if ((v->size == v->cap) && (!increase(v))) {
        return false;
    }
    v->head = (v->head - 1 + v->cap) % v->cap;
    v->buf[v->head] = val;
    v->size++;
    return true;
}

int pop_back(int_vector *v) {
    v->tail = (v->tail - 1 + v->cap) % v->cap;
    int res = v->buf[v->tail];
    v->buf[v->tail] = 0;
    decrease_if_possible(v);
    v->size--;
    return res;
}

int pop_front(int_vector *v) {
    int res = v->buf[v->head];
    v->buf[v->head] = 0;
    decrease_if_possible(v);
    v->head = (v->head + 1) % v->cap;
    v->size--;
    return res;
}

void destroy(int_vector *v) {
    free(v->buf);
    v->buf = NULL;
    v->cap = 0;
    v->head = 0;
    v->tail = 0;
    v->size = 0;
}

void print_vector(int_vector *v) {
    for (int i = 0; i < v->size; i++) {
        printf("%d ", v->buf[(v->head + i) % v->cap]);
    }
    printf("\n");
}