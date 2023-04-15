#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define MIN_CAPACITY 10

typedef struct {
    int *buf;
    int cap;
    int size;
    int head;
    int tail;
} int_vector;

int_vector *create_vector();
int get_size(int_vector *v);
bool set_size(int_vector *v, int new_size); //
bool is_empty(int_vector *v); 
int get_elem(int_vector *v, int idx); 
void set_elem(int_vector *v, int idx, int val); 
bool push_back(int_vector *v, int val);
int pop_back(int_vector *v);
bool push_front(int_vector *v, int val);
int pop_front(int_vector *v);
void destroy(int_vector *v);
void print_vector(int_vector *v); //потом уберу