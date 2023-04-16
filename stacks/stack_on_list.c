#include "stack_on_list.h"
#include <stdlib.h>

int_stack *create_stack() {
    int_stack *tmp = (int_stack *) malloc(sizeof(int_stack));
    tmp->size = 0;
    tmp->head = NULL;
    return tmp;
}

node* get_node(int_stack *s, int idx) {
    node *n = s->head;
    for(int i = 0; i < idx; ++i)
        n = n->next;
    return n;
}

bool is_empty(int_stack *s) {
    return s->size == 0;
}

int size(int_stack *s) {
    return s->size;
}

void push(int_stack *s, int val) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = val;
    if (s->size == 0) {
        s->head = new_node;
        s->head->next = NULL;
    } else {
        node *next = s->head;
        s->head = new_node;
        s->head->next = next;
    }
    s->size++;
}

int pop(int_stack *s) {
    node *new_head = s->head->next;
    int res = s->head->value;
    free(s->head);
    s->head = new_head;
    s->size--;
    return res;
}

void destroy(int_stack *s) {
    int size = s->size;
    for (int i = 0; i < size; i++) {
        pop(s);
    }
    free(s);
}