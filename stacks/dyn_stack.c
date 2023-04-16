#include "dyn_stack.h"
#include <stdlib.h>

static bool increase(int_dyn_stack *s) {
    int new_cap = s->cap * 2;
    if (new_cap < MIN_CAP) {
        new_cap = MIN_CAP;
    }
    int *tmp = (int *) realloc(s->buf, sizeof(int) * new_cap);
    if (tmp == NULL) {
        return false;
    }
    s->cap = new_cap;
    s->buf = tmp;
    return true;
}

static void decrease_if_possible(int_dyn_stack *s) {
    if (s->count <= s->cap / 4) {
        int new_cap = s->cap / 2;
        if (new_cap < MIN_CAP) {
            new_cap = MIN_CAP;
        }
        if (new_cap < s->cap) {
            s->buf = (int *) realloc(s->buf, sizeof(int) * new_cap);
            s->cap = new_cap;
        }
    }
}

int_dyn_stack *create_stack() {
    int_dyn_stack *tmp = (int_dyn_stack *) malloc(sizeof(int_dyn_stack));
    tmp->cap = MIN_CAP;
    tmp->buf = (int *) malloc(sizeof(int) * tmp->cap);
    tmp->count = 0;
    return tmp;
}

bool is_empty(int_dyn_stack *s) {
    return s->count == 0;
}

bool push(int_dyn_stack *s, int val) {
    if (s->count == s->cap) {
        increase(s);
    }
    s->buf[s->count] = val;
    s->count++;
    return true;
}

int pop(int_dyn_stack *s) {
    int res = s->buf[s->count - 1];
    decrease_if_possible(s);
    s->count--;
    return res;
}

void destroy(int_dyn_stack *s) {
    free(s->buf);
    s->buf = NULL;
    s->cap = 0;
    s->count = 0;
}