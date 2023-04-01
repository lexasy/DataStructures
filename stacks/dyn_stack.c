#include "dyn_stack.h"

#include <stdio.h>
#include <stdlib.h>


int_dyn_stack *create_stack() {
    int_dyn_stack *tmp = (int_dyn_stack *) malloc(sizeof(int_dyn_stack));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->buf = (int *) malloc(sizeof(int));
    if (tmp->buf == NULL) {
        exit(1);
    }
    tmp->size = 0;
    *tmp->buf = 0;
    return tmp;
}

bool is_empty(int_dyn_stack *s) {
    return s->size == 0;
}

bool push(int_dyn_stack *s, int val) {
    int *tmp;
    tmp = realloc(s->buf, sizeof(int) * (s->size + 1));
    if (tmp == NULL) {
        return false;
    }
    s->buf = tmp;
    *(s->buf + s->size) = val;
    s->size++;
    return true;
}

int pop(int_dyn_stack *s) {
    if (s->size == 0) {
        exit(2);
    }
    s->size--;
    return *(s->buf + s->size);
}

void destroy(int_dyn_stack *s) {
    free(s->buf);
    s->buf = NULL;
    free(s);
}