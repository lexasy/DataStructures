#include "stack.h"

int_stack *create_stack() {
    int_stack *tmp = (int_stack *) malloc(sizeof(int_stack));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->buf = (int*)malloc(sizeof(int) * MAX_SIZE);
    if (tmp->buf == NULL) {
        exit(1);
    }
    tmp->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        *(tmp->buf + i) = 0;
    }
    return tmp;
}

bool is_empty(int_stack *s) {
    return s->size == 0;
}

bool push(int_stack *s, int val) {
    if (s->size == MAX_SIZE) {
        return false;
    }
    *(s->buf + s->size) = val;
    s->size++;
    return true;
}

int pop(int_stack *s) {
    if (s->size == 0) {
        return false;
    }
    s->size--;
    return *(s->buf + s->size);
}

void destroy(int_stack *s) {
    free(s->buf);
    s->buf = NULL;
    free(s);
}