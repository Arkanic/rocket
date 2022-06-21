#include <stdlib.h>
#include <stdio.h>

#include "ll.h"

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
    for(int i = 0; i < listlen; i++) {
        struct ll_item *item = list[i];
        printf("%d ", *(int *)(item->item));
    }
    printf("\n");

    return 0;
}