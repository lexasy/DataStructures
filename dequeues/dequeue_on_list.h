#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;
struct node {
    int value;
    node *next;
    node *prev;
};

typedef struct {
    node *head;
    node *last;
    int size;
} int_dequeue;

int_dequeue *create_dequeue();
bool is_empty(int_dequeue *d);
int size(int_dequeue *d);
void push(int_dequeue *d, int val);
void pushf(int_dequeue *d, int val);
int pop(int_dequeue *d);
int popf(int_dequeue *d);
void destroy(int_dequeue *d);