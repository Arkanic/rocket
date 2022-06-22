#define _GNU_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "ll.h"
#include "tlm.h"

void trimend(char *str) {
    str[strlen(str) - 1] = '\0';
}

bool swith(char *str, char *substr) {
    bool startsWith = false;
    for(int i = 0; substr[i] != '\0'; i++) {
        if(str[i] != substr[i]) {
            startsWith = false;
            break;
        }
        startsWith = true;
    }

    return startsWith;
}

int processdat(char *folder, struct ll_list *ll) {
    printf("Processing data...\n");
    char *foldern;
    asprintf(&foldern, "%s/dat", folder);

    DIR *dir = opendir(foldern);
    if(!dir) {
        printf("Failed to open dat directory!\n");
        return 1;
    }

    struct dirent *ep;
    while((ep = readdir(dir))) {
        if(!(swith(ep->d_name, "dat"))) continue;

        char *filen;
        asprintf(&filen, "%s/%s", foldern, ep->d_name);
        FILE *fp = fopen(filen, "r");
        if(!fp) return 1;

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while((read = getline(&line, &len, fp)) != -1) {
            char *token;

            char *rawparts[2];
            int i = 0;
            while((token = strsep(&line, " "))) {
                rawparts[i] = strdup(token);
                i++;
            }
            trimend(rawparts[0]);

            char *data[2];
            data[0] = strdup(rawparts[0]);
            data[1] = strdup(rawparts[1]);

            for(int i = 0; i < 2; i++) free(rawparts[i]);

            struct datframe *dat = (struct datframe *)malloc(sizeof(struct datframe));

            unsigned long long millis;
            sscanf(ep->d_name, "dat-%llu.txt", &millis);
            dat->millis = millis;

            if(strcmp(data[0], "framerate") == 0) {
                float framerate;
                sscanf(data[1], "%f", &framerate);

                dat->framerate = framerate;
            }

            ll_ifirst(ll, millis, dat);

            free(data[0]);
            free(data[1]);
        }

        fclose(fp);
        if(line) free(line);
        free(filen);
    }

    ll_sort(ll);

    free(foldern);

    return 0;
}

int processimg(char *folder, int framerate) {
    char command[256];
    sprintf(command, "ffmpeg -framerate %d -i %s/frames/frame-%%d.jpg %s/video.mp4", framerate, folder, folder);
    printf("Starting ffmpeg...\n");
    system(command);
    printf("ffmpeg finished.\n");

    return 0;
}

int savejson(char *folder, char *json) {
    printf("Saving JSON...\n");
    char *path;
    asprintf(&path, "%s/telemetry.json", folder);
    FILE *fp = fopen(path, "wb");
    if(fp == NULL) return 1;

    fprintf(fp, "%s", json);

    fclose(fp);
    free(path);

    return 0;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: ./tlm <FOLDER>\nWhere FOLDER is the copied data from the flight\n");
        return 1;
    }

    printf("---- TLM ----\nRocket Telemetry Parser\n\n");

    char *folder = argv[1];
    // if pathname ends with /
    if(folder[strlen(folder) - 1] == '/') trimend(folder);

    struct ll_list *ll = ll_create();
    processdat(folder, ll);

    char *json = datlltoa(ll);
    savejson(folder, json);
    free(json);

    ll_freeall(ll);

    processimg(folder, 12);
}