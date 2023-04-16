#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define MIN_CAP 10

typedef struct {
    int *buf;
    int cap;
    int count;
} int_dyn_stack;

int_dyn_stack *create_stack();
bool is_empty(int_dyn_stack *s);
bool push(int_dyn_stack *s, int val);
int pop(int_dyn_stack *s);
void destroy(int_dyn_stack *s);