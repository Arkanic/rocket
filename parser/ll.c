// simple linked list implementation
// keys are in the format unsigned long long (so millis works as keys)

#include <stdlib.h>
#include <stdbool.h>
#include "ll.h"

struct ll_list *ll_create(void) {
    struct ll_list *ll = (struct ll_list *)malloc(sizeof(struct ll_list));
    ll->current = NULL;
    ll->head = NULL;

    return ll;
}

void ll_ifirst(struct ll_list *lp, unsigned long long key, void *data) {
    struct ll_item *link = (struct ll_item *)malloc(sizeof(struct ll_item));

    link->key = key;
    link->item = data;

    link->next = lp->head;
    lp->head = link;
}

struct ll_item *ll_dfirst(struct ll_list *lp) {
    struct ll_item *temp = lp->head;

    lp->head = lp->head->next;

    return temp;
}

bool ll_empty(struct ll_list *lp) {
    return lp->head == NULL;
}

int ll_length(struct ll_list *lp) {
    int len = 0;
    struct ll_item *current;

    for(current = lp->head; current != NULL; current = current->next) len++;

    return len;
}

//todo: proper search alog (require sort first)
struct ll_item *ll_find(struct ll_list *lp, unsigned long long key) {
    struct ll_item *current = lp->head;

    if(lp->head == NULL) return NULL;

    while(current->key != key) {
        if(current->next == NULL) return NULL;
        else current = current->next;
    }

    return current;
}

struct ll_item *ll_delete(struct ll_list *lp, unsigned long long key) {
    struct ll_item *current = lp->head;
    struct ll_item *previous = NULL;

    if(lp->head == NULL) return NULL;
    
    while(current->key != key) {
        if(current->next == NULL) return NULL;
        else {
            previous = current;
            current = current->next;
        }
    }

    if(current == lp->head) lp->head = lp->head->next;
    else previous->next = current->next;

    return current;
}

void ll_sort(struct ll_list *lp) {
    int i, j, k;
    unsigned long long tempkey;
    void *tempdata;

    struct ll_item *current, *next;

    int size = ll_length(lp);
    k = size;

    for(i = 0; i < size - 1; i++, k--) {
        current = lp->head;
        next = lp->head->next;

        for(j = 1; j < k; j++) {
            if(current->key > next->key) {
                tempdata = current->item;
                current->item = next->item;
                next->item = tempdata;

                tempkey = current->key;
                current->key = next->key;
                next->key = tempkey;
            }

            current = current->next;
            next = next->next;
        }
    }
}

int ll_getlist(struct ll_list *lp, struct ll_item ***list) {
    int length = ll_length(lp);
    *list = (struct ll_item **)malloc(sizeof(struct ll_item *) * length);

    struct ll_item *current = lp->head;
    for(int i = 0; i < length; i++) {
        (*list)[i] = current;
        current = current->next;
    }

    return length;
}

void ll_freeall(struct ll_list *lp) {
    struct ll_item *current = lp->head;
    while(current != NULL) {
        struct ll_item *temp = current->next;
        free(current->item);
        free(current);
        current = temp;
    }

    free(lp);
}
