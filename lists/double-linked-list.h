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

double_linked_list *create_list(); //
bool is_empty(double_linked_list *l); //
int size_of_list(double_linked_list *l); //
int first_elem(double_linked_list *l); //
int last_elem(double_linked_list *l); //
node *get_node(double_linked_list *l, int idx); //
int next_elem(double_linked_list *l, int idx); //
int prev_elem(double_linked_list *l, int idx); //
double_linked_list *del_elem(double_linked_list *l, int idx); //
double_linked_list *insert_elem(double_linked_list *l, int idx, int val); //
double_linked_list *push_front(double_linked_list *l, int val); //
double_linked_list *push_back(double_linked_list *l, int val); //
double_linked_list *pop_front(double_linked_list *l);
double_linked_list *pop_back(double_linked_list *l);
void print_list(double_linked_list *l); //
void destroy(double_linked_list *l); //