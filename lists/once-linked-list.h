#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;
struct node {
    int value;
    node* next; 
};

typedef struct {
    node* head;
    int size;
} int_list;

bool int_list_init(int_list* list);
void int_list_clean(int_list* list);
void int_list_destroy(int_list* list);

void int_list_push(int_list* list, int val);
void int_list_pushf(int_list* list, int val);
int int_list_pop(int_list* list);
int int_list_popf(int_list* list);
void int_list_insert(int_list* list, int val, int idx);
void int_list_remove(int_list* list, int idx);

node* get_node(int_list* list, int idx);
int int_list_at(int_list* list, int idx);

bool int_list_empty(int_list* list);