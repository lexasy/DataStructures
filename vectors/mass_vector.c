#include "mass_vector.h"

static bool increase(int_vector *v) {
    int new_cap = v->cap * 2;
    if (new_cap < MIN_CAPACITY) {
        new_cap = MIN_CAPACITY;
    }
    int *tmp = (int *) realloc(v->buf, sizeof(int) * new_cap);
    if (tmp == NULL) {
        return false;
    }
    v->buf = tmp;
    for (int i = v->cap; i < new_cap; i++) {
        v->buf[i] = 0;
    }
    v->cap = new_cap;
    return true;
}

static void decrease_if_possible(int_vector *v) {
    if (v->size <= v->cap / 4) {
        int new_cap = v->cap / 2;
        if (new_cap < MIN_CAPACITY) {
            new_cap = MIN_CAPACITY;
        }
        if ((v->head < new_cap) && (v->tail > new_cap)) {
            for (int i = v->head; i <= v->tail; i++) {
                v->buf[i - v->head] = v->buf[i];
                v->buf[i] = 0;
            }
            v->tail -= v->head;
            v->head = 0;
        } else if (v->head >= new_cap) {
            for (int i = v->head; i <= v->tail; i++) {
                v->buf[i - new_cap] = v->buf[i];
                v->buf[i] = 0;
            }
            v->head -= new_cap;
            v->tail -= new_cap;
        }
        v->buf = (int *) realloc(v->buf, sizeof(int) * new_cap);
        v->cap = new_cap;
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
        v->cap = new_cap;
        v->size = new_size;
        v->tail = v->head + v->size;
        return true;
    } else if (new_size < v->size) {
        for (int i = new_size; i < v->size; i++) {
            v->buf[v->head + i] = 0;
            v->tail--;
        }
        v->size = new_size;
        return true;
    } else {
        v->size = new_size;
        v->tail = v->head + v->size;
        return true;
    }
}

int get_size(int_vector *v) {
    return v->size;
}

bool is_empty(int_vector *v) {
    return v->size == 0;
}

int get_elem(int_vector *v, int idx) {
    return v->buf[v->head + idx];
}

void set_elem(int_vector *v, int idx, int val) {
    v->buf[v->head + idx] = val;
}

bool push_back(int_vector *v, int val) {
    v->tail = v->head + v->size;
    if ((v->tail == v->cap) && (!increase(v))) {
        return false;
    }
    v->buf[v->tail] = val;
    v->size++;
    return true;
}

bool push_front(int_vector *v, int val) {
    if ((v->head == 0) && (v->size != 0)) {
        if (!increase(v)) {
            return false;
        }
        for (int i = 0; i < v->cap / 2; i++) {
            v->buf[i + v->cap / 2] = v->buf[i];
            v->buf[i] = 0;
            v->head++;
            v->tail++;
        }
    }
    if ((v->size == v->cap) && (!increase(v))) {
        return false;
    }
    if ((v->head == 0) && (v->size == 0)) {
        v->head = v->cap - 1;
    } else {
        v->head--;
    }
    v->buf[v->head] = val;
    v->size++;
    return true;
}

int pop_back(int_vector *v) {
    int res = v->buf[v->tail];
    v->buf[v->tail] = 0;
    v->tail--;
    decrease_if_possible(v);
    v->size--;
    return res;
}

int pop_front(int_vector *v) {
    int res = v->buf[v->head];
    v->buf[v->head] = 0;
    decrease_if_possible(v);
    v->head++;
    v->size--;
    return res;
}

void destroy(int_vector *v) {
    free(v->buf);
    v->buf = NULL;
    v->cap = 0;
    v->head = 0;
    v->size = 0;
    v->tail = 0;
    free(v);
}