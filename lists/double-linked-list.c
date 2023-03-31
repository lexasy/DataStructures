#include <stdio.h>
#include <stdlib.h>
#include "double-linked-list.h"

double_linked_list *create_list() {
    double_linked_list *tmp = (double_linked_list*) malloc(sizeof(double_linked_list));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->last = NULL;

    return tmp;
}

void destroy(double_linked_list *l) {
    node *next = NULL;
    while (l->head) {
        next = l->head->next;
        free(l->head);
        l->head = next;
    }
    free (l);
    l = NULL;
}

bool is_empty(double_linked_list *l) {
    return l->size == 0;
}

int size_of_list(double_linked_list *l) {
    return l->size;
}

int first_elem(double_linked_list *l) {
    return l->head->value;
}

int last_elem(double_linked_list *l) {
    return l->last->value;
}

node *get_node(double_linked_list *l, int idx) {
    node *tmp = NULL;
    int i;
    if (idx < l->size / 2) {
        i = 0;
        tmp = l->head;
        while (tmp && i < idx) {
            tmp = tmp->next;
            i++;
        }
    } else {
        i = l->size - 1;
        tmp = l->last;
        while (tmp && i > idx) {
            tmp = tmp->prev;
            i--;
        }
    }
    return tmp;
}

int next_elem(double_linked_list *l, int idx) {
    node *tmp = get_node(l, idx);
    return tmp->next->value;
}

int prev_elem(double_linked_list *l, int idx) {
    node *tmp = get_node(l, idx);
    return tmp->prev->value;
}

double_linked_list *insert_elem(double_linked_list *l, int idx, int val) { // вставка внутрь списка (не в нулевой и последний элемент)
    node *elm = NULL;
    node *new_node = NULL;
    elm = get_node(l, idx);
    if (elm == NULL) {
        exit(1);
    }
    new_node = (node *) malloc(sizeof(node));
    new_node->value = val;
    new_node->prev = elm;
    new_node->next = elm->next;
    if (elm->next) {
        elm->next->prev = new_node;
    }
    elm->next = new_node;
    if (!elm->prev) {
        l->head = elm;
    }
    if (!elm->next) {
        l->last = elm;
    }
    l->size++;
    return l;
}

double_linked_list *del_elem(double_linked_list *l, int idx) { // удаление изнутри списка (не из нулевого и последнего элемента)
    node *elm = NULL;
    elm = get_node(l, idx);
    if (elm == NULL) {
        exit(1);
    }
    if (elm->prev) {
        elm->next->prev = elm->prev;
    }
    if (elm->next) {
        elm->prev->next = elm->next;
    }
    if (!elm->prev) {
        l->head = elm->next;
    }
    if (!elm->next) {
        l->last = elm->prev;
    }
    free(elm);
    l->size--;
    return l;
}

double_linked_list *push_front(double_linked_list *l, int val) {
    node *new_node = (node *) malloc(sizeof(node));
    if (new_node == NULL) {
        exit(2);
    }
    new_node->value = val;
    new_node->next = l->head;
    new_node->prev = NULL;
    if (l->head) {
        l->head->prev = new_node;
    }
    l->head = new_node;
    if (l->last == NULL) {
        l->last = new_node;
    }
    l->size++;
    return l;
}

double_linked_list *push_back(double_linked_list *l, int val) {
    node *new_node = (node *) malloc(sizeof(node));
    if (new_node == NULL) {
        exit(2);
    }
    new_node->value = val;
    new_node->prev = l->last;
    new_node->next = NULL;
    if (l->last) {
        l->last->next = new_node;
    }
    l->last = new_node;
    if (l->head == NULL) {
        l->head = new_node;
    }
    l->size++;
    return l;
}

double_linked_list *pop_front(double_linked_list *l) {
    node *prev;
    if (l->head == NULL) {
        exit(3);
    }
    prev = l->head;
    l->head = l->head->next;
    if (l->head) {
        l->head->prev = NULL;
    }
    if (prev == l->last) {
        l->last = NULL;
    }
    free(prev);
    l->size--;
    return l;
}

double_linked_list *pop_back(double_linked_list *l) {
    node *next;
    if (l->last == NULL) {
        exit(3);
    }
    next = l->last;
    l->last = l->last->prev;
    if (l->last) {
        l->last->next = NULL;
    }
    if (next == l->head) {
        l->head = NULL;
    }
    free(next);
    l->size--;
    return l;
}

void print_list(double_linked_list *l) {
    node *tmp = l->head;
    while (tmp) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}