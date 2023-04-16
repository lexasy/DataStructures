#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;
struct node {
    int value;
    node *next;
};

typedef struct {
    node *head;
    int size;
} int_stack;

int_stack *create_stack();
bool is_empty(int_stack *s);
int size(int_stack *s);
void push(int_stack *s, int val);
int pop(int_stack *s);
void destroy(int_stack *s);