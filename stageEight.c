#include "includeAll.h"

void stageEight(){
    while (1) {
        char userInput[100];
        printf("Enter user input: ");
        fgets(userInput, sizeof(userInput), stdin);
        printf("User: %s", userInput);
        char *aiGen = inference(userInput);
        printf("AI: %s\n", aiGen);
    }

    printf("STAGE EIGHT\n");
    stageNine();
}
