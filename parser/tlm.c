#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

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

int checkimg(char *folder) {
    // assume that folder does indeed exist, check photos folder
    char *fn = strdup(folder);
    strcat(fn, "/frames");
    DIR *dir = opendir(fn);

    struct dirent *ep;
    int photos = 0;
    int highest = 0;
    while((ep = readdir(dir))) {
        if(!swith(ep->d_name, "frame")) continue;

        photos++;
        
        int frame = 0;
        sscanf(ep->d_name, "frame-%d.jpg", &frame);
        if(frame > highest) highest = frame;
    }

    if(photos != highest) {
        printf("\nFrames do not match up!\nFinal frame name is different to the total number of frames.\n");
        return 3;
    }

    closedir(dir);
    free(fn);

    return 0;
}

int checkffmpeg(void) {
    FILE *fp = popen("which ffmpeg", "r");
    if(!fp) {
        printf("\nFailed to run ffmpeg command!\n(this is a shell, not ffmpeg issue)\n");
        return 4;
    }

    char path[1036] = "\0";
    fgets(path, sizeof(path), fp);
    if(strlen(path) == 0) {
        printf("\nFFMPEG is not installed!\n");
        return 5;
    }

    return 0;
}

int check(char *folder) {
    printf("Beginning checks...\n");
    DIR *dir = opendir(folder);
    if(!dir) {
        if(errno == ENOENT) {
            printf("Directory provided does not exist!\n");
        } else {
            printf("Failed to open folder!\n");
        }
        return 2;
    }
    
    closedir(dir);

    printf("Checking images... ");
    int checkimgResult = checkimg(folder);
    if(checkimgResult != 0) return checkimgResult;
    printf("GOOD\n");

    printf("Checking ffmpeg... ");
    int checkffmpegResult = checkffmpeg();
    if(checkffmpegResult != 0) return checkffmpegResult;
    printf("GOOD\n");

    printf("Checks done.\n");
    return 0;
}

int processimg(char *folder) {
    char command[256];
    sprintf(command, "ffmpeg -i %s/frames/frame-%%d.jpg video.mp4", folder);
    printf("Starting ffmpeg...\n");
    system(command);
    printf("ffmpeg finished.\n");

    return 0;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: ./telemetry <FOLDER>\nWhere FOLDER is the copied data from the flight\n");
        return 1;
    }

    printf("---- TLM ----\nRocket Telemetry Parser\n\n");

    char *folder = argv[1];
    // if pathname ends with /
    if(folder[strlen(folder) - 1] == '/') folder[strlen(folder) - 1] = '\0';


    int checkfsResult = check(folder);
    if(checkfsResult != 0) return checkfsResult;

    // turn images into video
    printf("\nConverting video frames to video...\n");
    int processimgResult = processimg(folder);
    if(processimgResult != 0) return processimgResult;
    printf("Finished converting video.\n");
    
}