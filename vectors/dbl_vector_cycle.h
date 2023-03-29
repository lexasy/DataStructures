#pragma once
#include <stdbool.h>

typedef struct {
    double *buf;
    int head;
    int size;
    int cap;
} dbl_vector;

void dv_init(dbl_vector *v); //done
void dv_destroy(dbl_vector *v); //done
bool dv_push_back(dbl_vector *v, double val);
bool dv_push_front(dbl_vector *v, double val);
double dv_pop_back(dbl_vector *v);
double dv_pop_front(dbl_vector *v);
bool dv_is_empty(dbl_vector *v); //done
int dv_get_size(dbl_vector *v); //done
bool dv_set_size(dbl_vector *v, int new_size); //done
double dv_get_elem(dbl_vector *v, int idx); //done
void dv_set_elem(dbl_vector *v, int idx, double val); //done

// void dv_init(dbl_vector *v);
// void dv_size(dbl_vector *v);
// int dv_size(dbl_vector *v);
// bool dv_resize(dbl_vector *v, int new_size);
// double dv_get(dbl_vector *v, int idx);
// void dv_put(dbl_vector *v, int idx, double val); static