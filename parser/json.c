#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"
#include "tlm.h"

char *astrcat(char *a, char *b) {
    char *str = malloc(strlen(a) + strlen(b) - 1);
    sprintf(str, "%s%s", a, b);

    return str;
}

char *dattoa(struct datframe *dat) {
    char *json;
    asprintf(&json, "{\"millis\": %llu, \"framerate\": %f}", dat->millis, dat->framerate);

    return json;
}

char *datlltoa(struct ll_list *ll) {
    printf("Generating json...\n");
    char *json;
    asprintf(&json, "{\"frames\": {");

    struct ll_item **list;
    int listlen = ll_getlist(ll, &list);
    for(int i = 0; i < listlen; i++) {
        struct datframe *dat = (struct datframe *)list[i]->item;
        char *datj = dattoa(dat);

        char *jline;
        if(i == 0) asprintf(&jline, "\"%llu\": %s", dat->millis, datj);
        else asprintf(&jline, ", \"%llu\": %s", dat->millis, datj);

        char *temp = json;
        json = astrcat(json, jline);
        free(jline);
        free(temp);
    }

    char *temp = json;
    json = astrcat(json, "}}");
    //free(temp);

    free(list);

    return json;
}