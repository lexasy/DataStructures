#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define DEG 2
#define MIN_CAPACITY 10

typedef struct {
    int *buf;
    int size;
    int init_head;
    int cap;
} int_queue;

int_queue *create_queue();
bool is_empty(int_queue *q);
bool push(int_queue *q, int val);
int pop(int_queue *q);
int length(int_queue *q);
void destroy(int_queue *q);
// void printqueue(int_queue *q); //