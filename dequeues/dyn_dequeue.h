#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define MIN_CAPACITY 10

typedef struct {
    int *buf;
    int size;
    int head;
    int tail;
    int cap;
} int_dequeue;

int_dequeue *create_dequeue();
int size_of_dequeue(int_dequeue *d);
bool is_empty(int_dequeue *d);
bool push_back(int_dequeue *d, int val);
bool push_front(int_dequeue *d, int val);
int pop_back(int_dequeue *d);
int pop_front(int_dequeue *d);
void destroy(int_dequeue *d);