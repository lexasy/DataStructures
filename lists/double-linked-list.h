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
} double_linked_list;

double_linked_list *create_list(); 
bool is_empty(double_linked_list *l); 
int size_of_list(double_linked_list *l); 
node *get_node(double_linked_list *l, int idx);
int del_elem(double_linked_list *l, int idx);
void insert_elem(double_linked_list *l, int idx, int val);
void push_front(double_linked_list *l, int val);
void push_back(double_linked_list *l, int val);
int pop_front(double_linked_list *l);
int pop_back(double_linked_list *l);
void destroy(double_linked_list *l);