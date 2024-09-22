#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includeAll.h"


Line* createLine(const char* code, const char* category, const char* line) {
    Line *newLine = safeCalloc(1, sizeof(Line));
    strncpy(newLine->code, code, sizeof(newLine->code) - 1);
    strncpy(newLine->category, category, sizeof(newLine->category) - 1);
    strncpy(newLine->line, line, sizeof(newLine->line) - 1);
    return newLine;
}

LineContainer* createLineContainer() {
    LineContainer *container = safeCalloc(1, sizeof(LineContainer));
    container->lines = (Line*)safeCalloc(1, sizeof(Line));
    container->amount = 0;
    return container;
}

LineContainer* addLineToContainer(LineContainer* container, const Line* line) {
    container->lines = (Line*)safeRealloc(container->lines, (container->amount + 1) * sizeof(Line));
    container->lines[container->amount] = *line;
    container->amount++;
    return container;
}

LineContainer* getLinesByCategory(const LineContainer* container, const char* category) {
    LineContainer* result = createLineContainer();

    
    for (int i = 0; i < container->amount; i++) {
        if (strcmp(container->lines[i].category, category) == 0) {
            addLineToContainer(result, &container->lines[i]);
        }
    }
    return result;
}

Line* getRandomLine(const LineContainer* container) {
    if (container->amount == 0) {
        return NULL; // Return NULL if the container is empty
    }
    

    int randomIndex = rand() % container->amount; // Generate a random index within the range of the container
    playBoomboxSound(container->lines[randomIndex].code);
    return &container->lines[randomIndex]; // Return a pointer to the randomly selected line
}