#pragma once

#include <stdio.h>
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
} int_queue;

int_queue *create_queue();
bool is_empty(int_queue *q);
int size(int_queue *q);
void push(int_queue *q, int val);
int pop(int_queue *q);
void destroy(int_queue *q);