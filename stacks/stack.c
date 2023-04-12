#include "stack.h"

int_stack *create_stack() {
    int_stack *tmp = (int_stack *) malloc(sizeof(int_stack));
    tmp->size = 0;
    return tmp;
}

bool is_empty(int_stack *s) {
    return s->size == 0;
}

bool push(int_stack *s, int val) {
    if (s->size == MAX_SIZE) {
        return false;
    }
    s->buf[s->size] = val;
    s->size++;
    return true;
}

int pop(int_stack *s) {
    s->size--;
    int res = s->buf[s->size];
    return res;
}

void destroy(int_stack *s) {
    free(s);
}