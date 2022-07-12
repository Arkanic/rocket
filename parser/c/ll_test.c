#include <stdlib.h>
#include <stdio.h>

#include "ll.h"

void printl(struct ll_item **list, int len) {
    printf("[");
    for(int i = 0; i < len; i++) {
        struct ll_item *item = list[i];
        printf("%d ", *(int *)(item->item));
    }
    printf("]\n");
}

int main(void) {
    struct ll_list *ll = ll_create();

    for(int i = 0; i < 100; i++) {
        int *item = (int *)malloc(sizeof(int));
        *item = i;
        ll_ifirst(ll, i, item);
    }

    struct ll_item **list = NULL;
    int listlen = ll_getlist(ll, &list);
    printf("static list len: %d\n", listlen);
    printl(list, listlen);
    free(list);

    ll_sort(ll);
    
    listlen = ll_getlist(ll, &list);
    printl(list, listlen);
    free(list);

    struct ll_item *fifty = ll_find(ll, 50);
    printf("found %llu\n", *(unsigned long long *)fifty->item);

    ll_freeall(ll);

    return 0;
}