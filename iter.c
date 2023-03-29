#include <stdlib.h>
#include "iter.h"

void list_init(list *l) {
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

void list_destroy(list *l) {
    for (int _ = 0; _ < l->size; _++) {
        node *next = l->first->next;
        free(l->first);
        l->first = next;
    }
}

iter iter_begin(list *l) {
    iter it;
    it.prev = NULL;
    it.lst = l;
    return it;
}

iter iter_end(list *l) {
    iter it;
    it.prev = l->last;
    it.lst = l;
    return it;
}

void iter_inc(iter *it) {
    if (it->prev == NULL) {
        it->prev = it->lst->first;
    } else {
        it->prev = it->prev->next;
    }
}

double iter_get_val(iter *it) {
    if (it->prev == NULL) {
        return it->lst->first->val;
    }
    return it->prev->next->val;
}

void iter_set_val(iter *it, double val) {
    if (it->prev == NULL) {
        it->lst->first->val = val;
    }
    it->prev->next->val = val;
}

void iter_remove(iter *it) {
    node *elem;
    if (it->prev == NULL) { //если первый элемент
        elem = it->lst->first;
        it->lst->first = it->lst->first->next;
        if (it->lst->first == NULL) { //если список был пустой
            it->lst->last = NULL;
        }
    } else if (it->prev->next->next == NULL) { //последний элемент
        elem = it->prev->next;
        it->prev->next = NULL;
        it->lst->last = it->prev;
    } else {
        elem = it->prev->next;
        it->prev->next = it->prev->next->next;
    }
    free(elem);
    it->lst->size--;
}

void iter_add(iter *it, double val) {
    node *elem = malloc(sizeof(node));
    elem->val = val;
    if (it->prev == NULL) { //если первый элемент 
        elem->next = it->lst->first;
        it->lst->first = elem;
        if (it->lst->last == NULL) { //если список был пустой
            it->lst->last = elem;
        }
    } else if (it->prev->next == NULL) { //последний элемент
        elem->next = NULL;
        it->lst->last = elem;
        it->prev->next = elem;
    } else { 
        elem->next = it->prev->next;
        it->prev->next = elem;
    }
    it->prev = elem;
    it->lst->size++;
}