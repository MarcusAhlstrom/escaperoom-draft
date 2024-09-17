#include "includeAll.h"

void playSound(char *soundFile){
        pid_t pid;
        pid = fork();

        if(pid < 0){
                fprintf(stderr, "Fork Problem");
        }

        if(pid == 0){
                //This is the child
                char *first[]={"aplay", soundFile, NULL};
                execvp(first[0], first);
        }else{
                free(soundFile);
        }
        int status;
        wait(&status);
        if(status != 0){
                exit(EXIT_FAILURE);
        }
}
