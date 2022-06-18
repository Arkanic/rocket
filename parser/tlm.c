#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int processimg(char *folder, int framerate) {
    char command[256];
    sprintf(command, "ffmpeg -framerate %d -i %s/frames/frame-%%d.jpg video.mp4", framerate, folder);
    printf("Starting ffmpeg...\n");
    system(command);
    printf("ffmpeg finished.\n");

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
    if(folder[strlen(folder) - 1] == '/') folder[strlen(folder) - 1] = '\0';

    processimg(folder, 12);
}