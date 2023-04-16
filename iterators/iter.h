#pragma once
#include <stdlib.h>

typedef struct node node;
struct node {
    node *next;
    double val;
};

typedef struct {
    node *first;
    node *last;
    int size;
} list;

typedef struct {
    node *prev;
    list *lst;
} iter;

void list_init(list *l);
void list_destroy(list *l);
iter iter_begin(list *l);
iter iter_end(list *l);
void iter_inc(iter *it);
double iter_get_val(iter *it);
void iter_set_val(iter *it, double val);
void iter_remove(iter *it);
void iter_add(iter *it, double val);