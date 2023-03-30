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






