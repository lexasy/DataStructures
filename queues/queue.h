#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct {
    int buf[MAX_SIZE];
    int size;
    int init_head;
} int_queue;

int_queue *create_queue();
bool is_empty(int_queue *q);
bool push(int_queue *q, int val);
int pop(int_queue *q);
int length(int_queue *q);
void destroy(int_queue *q);

