#include "list.h"

bool int_list_init(int_list* list) {
    if(list->size > 0 || list->head != NULL)
        return false;
    list->head = NULL;
    list->size = 0;
    return true;
}

void int_list_clean(int_list* list) {
    int len = list->size;
    for(int i = 0; i < len; ++i)
        int_list_popf(list);
}

void int_list_destroy(int_list* list) {
    int_list_clean(list);
    free(list);
}

void int_list_push(int_list* list, int val) {
    node* new = (node*)malloc(sizeof(node));
    new->next = NULL;
    new->value = val;

    if(list->size == 0) 
        list->head = new;
    else {
        node* last = get_node(list, list->size - 1);
        last->next = new;
    }
    list->size++;
}

void int_list_pushf(int_list* list, int val) {
    node* new = (node*)malloc(sizeof(node));
    new->next = list->head; 
    new->value = val;
    list->head = new;
    list->size++;
}

int int_list_pop(int_list* list) {
    int val;
    if(list->size > 1) {
        node* p = get_node(list, list->size - 2);
        node* last = p->next;
        val = last->value;
        free(last);
        p->next = NULL;
    }
    else {
        val = list->head->value;
        free(list->head);
        list->head = NULL;
    }
    list->size--;
    return val;
}

int int_list_popf(int_list* list) {
    node* new_head = list->head->next;
    int val = list->head->value;
    free(list->head);
    list->head = new_head;
    list->size--;
    return val;
}

void int_list_insert(int_list* list, int val, int idx) {
    if(idx == 0)
        int_list_pushf(list, val);
    else {
        node* p = get_node(list, idx - 1);
        node* new  = (node*)malloc(sizeof(node));
        new->next = p->next;
        new->value = val;
        p->next = new;
        list->size++;
    }
}

void int_list_remove(int_list* list, int idx) {
    if(idx == 0)
        int_list_popf(list);
    else {
        node *p = get_node(list, idx - 1);
        node *d = p->next;
        p->next = d->next;
        free(d);
        list->size--;
    }
}

node* get_node(int_list* list, int idx) {
    node* n = list->head;
    for(int i = 0; i < idx; ++i)
        n = n->next;
    return n;
}

int int_list_at(int_list* list, int idx) {
    return get_node(list, idx)->value;
}

bool int_list_empty(int_list* list) {
    return list->size == 0;
}