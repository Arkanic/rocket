#include <stdbool.h>

struct ll_list {
    struct ll_item *head;
    struct ll_item *current;
};

struct ll_item {
    void *item;
    unsigned long long key;
    struct ll_item *next;
};

struct ll_list *ll_create(void);

void ll_ifirst(struct ll_list *lp, unsigned long long key, void *data);

struct ll_item *ll_dfirst(struct ll_list *lp);

bool ll_empty(struct ll_list *lp);

int ll_length(struct ll_list *lp);

struct ll_item *ll_find(struct ll_list *lp, unsigned long long key);

struct ll_item *ll_delete(struct ll_list *lp, unsigned long long key);

void ll_sort(struct ll_list *lp);

int ll_getlist(struct ll_list *lp, struct ll_item ***list);

void ll_freeall(struct ll_list *lp);