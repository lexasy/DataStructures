#include <stdlib.h>
#include "dbl_vector_cycle.h"
#define MIN_CAPACITY 32

// static bool increase(dbl_vector *v) {
//     int new_capacity = 2 * v->cap;
//     if (new_capacity < MIN_CAPACITY) {
//         new_capacity = MIN_CAPACITY;
//     }
//     double *tmp = realloc(v->buf, new_capacity * sizeof(double));
//     if (tmp == NULL) {
//         return false;
//     }
//     v->cap = new_capacity;
//     v->buf = tmp;
//     return true;
// }

// static void decrease_if_possible(dbl_vector *v) {
//     if (v->size < v->cap / 4) {
//         int new_cap = v->cap / 2;
//         if (new_cap < MIN_CAPACITY) {
//             new_cap = MIN_CAPACITY;
//         }
//         if (new_cap < v->cap) {
//             v->buf = realloc(v->buf, new_cap * sizeof(double));
//             v->cap = new_cap;
//         }
//     }
// }(v->size + v->head) % v->cap(v->size + v->head) % v->cap(v->size + v->head) % v->cap

bool set_size(dbl_vector *v, int new_size) {
    if (new_size <= v->cap) {
        v->size = new_size;
        decrease_if_possible(v);
        return true;
    }
    if (new_size == v->size + 1) {
        if (!increase(v)) {
            return false;
        }
        v->size = new_size;
        return true;
    }
    int new_cap = new_size;
    double *tmp = realloc(v->buf, new_cap);
    if (tmp == NULL) {
        return false;
    }
    v->buf = tmp;
    if (v->head + v->size > v->cap) {
        int old_cap = v->cap;
        for (int i = old_cap - 1; i >= v->head; i--) {
            v->buf[i + new_cap - old_cap] = v->buf[i];
        }
        v->head += new_cap;
    }
    v->size = new_size;
    v->cap = new_cap;
    return true;
}

static void zero_range(dbl_vector *v, int from, int to) {
    for (int i = from; i < to; i++) {
        dv_set_elem(v, i, 0);
    }
}

void dv_set_elem(dbl_vector *v, int idx, double val) {
    v->buf[(v->head + idx) % v->cap] = val;
}

double dv_get_elem(dbl_vector *v, int idx) {
    return v->buf[(idx+v->head) % v->cap];
}

bool dv_is_empty(dbl_vector *v) {
    return v->size == 0;
}

int dv_get_size(dbl_vector *v) {
    return v->size;
}

void dv_init(dbl_vector *v) {
    v->size = 0;
    v->buf = NULL;
}

void dv_destroy(dbl_vector *v) {
    free(v->buf);
    v->buf = NULL;
    v->size = 0;
}

bool dv_push_back(dbl_vector *v, double val) {
    if (v->size == v->cap) {
        if (!increase(v)) {
            return false;
        }
    }
    v->buf[(v->size + v->head) % v->cap] = val;
    v->size++;
    return true;
}

bool dv_push_front(dbl_vector *v, double val) {

}

double dv_pop_back(dbl_vector *v) {

}

double dv_pop_front(dbl_vector *v) {

}

