#include "includeAll.h"

void stageEight(Save *save) {
    if (save == NULL) {
        printf("Error: Save is NULL\n");
        return;
    }
    while (1) {
        char userInput[100];
        printf("Enter user input: ");
        fgets(userInput, sizeof(userInput), stdin);
        printf("User: %s", userInput);
        char *aiGen = "alkdjhgas,hmdasgdjhkl,";
        printf("AI: %s\n", aiGen);
    }

    printf("STAGE EIGHT\n");
    stageNine();
}
