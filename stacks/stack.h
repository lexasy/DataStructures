#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct {
    int *buf;
    int size;
} int_stack;

int_stack *create_stack();
bool is_empty(int_stack *s);
bool push(int_stack *s, int val);
int pop(int_stack *s);
void destroy(int_stack *s);

