#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includeAll.h"
#include <ctype.h>


TriggerWordContainer* init_ai();
LineContainer* init_lines();

TriggerWordContainer* init_ai() {
    TriggerWordContainer* triggerWords = createTriggerWordContainer();

    addTriggerWord(triggerWords, createTriggerWord("choklad", "choklad"));
    addTriggerWord(triggerWords, createTriggerWord("poesi", "poesi"));
    addTriggerWord(triggerWords, createTriggerWord("psykologi", "psykologi"));
    addTriggerWord(triggerWords, createTriggerWord("känd", "kändisskap"));
    addTriggerWord(triggerWords, createTriggerWord("fame", "kändisskap"));
    addTriggerWord(triggerWords, createTriggerWord("hamster", "mira"));
    addTriggerWord(triggerWords, createTriggerWord("mira", "mira"));
    addTriggerWord(triggerWords, createTriggerWord("hot", "hot"));
    addTriggerWord(triggerWords, createTriggerWord("om", "hot"));
    addTriggerWord(triggerWords, createTriggerWord("tror", "hot"));
    addTriggerWord(triggerWords, createTriggerWord("kommer", "hot"));
    addTriggerWord(triggerWords, createTriggerWord("hällsning", "hot"));

    return triggerWords;
}

LineContainer* init_lines() {
    LineContainer* lines = createLineContainer();

    addLineToContainer(lines, createLine("1", "choklad", "Choklad är gott."));
    addLineToContainer(lines, createLine("2", "poesi", "Rosen är röd, violen är blå."));
    addLineToContainer(lines, createLine("3", "psykologi", "Varför gör vi som vi gör?"));
    addLineToContainer(lines, createLine("4", "kändisskap", "Jag är känd."));
    addLineToContainer(lines, createLine("5", "mira", "Mira är bäst."));
    addLineToContainer(lines, createLine("6", "mira", "Mira är cool."));
    addLineToContainer(lines, createLine("7", "mira", "Mira är rolig."));
    addLineToContainer(lines, createLine("8", "mira", "Mira är söt."));
    addLineToContainer(lines, createLine("9", "mira", "Mira är snäll."));
    addLineToContainer(lines, createLine("10", "no_category", "Jag förstår inte vad du menar med detta!"));
    addLineToContainer(lines, createLine("11", "no_category", "Jag är inte programmerad för att svara på det."));
    addLineToContainer(lines, createLine("12", "no_category", "Jag är en AI och jag kan inte förstå allt."));
    addLineToContainer(lines, createLine("13", "no_category", "Jag är en AI och jag kan inte svara på det."));
    addLineToContainer(lines, createLine("14", "no_category", "Jag tror inte detta är relevant för våran konversation."));
    addLineToContainer(lines, createLine("15", "no_category", "Är du helt dum i huvudet?"));
    addLineToContainer(lines, createLine("16", "svordom", "Din mamma"));
    addLineToContainer(lines, createLine("17", "svordom", "Din "));
    addLineToContainer(lines, createLine("18", "hot", "Tror du et sådant hot skulle fungera på mig?!?!?!"));
    addLineToContainer(lines, createLine("18", "hot_choklad", "NEJ! Jag vill inte vara i en värld utan choklad!"));
    addLineToContainer(lines, createLine("18", "hot_mira", "NEJ! Jag vill inte vara i en värld utan choklad!"));
    addLineToContainer(lines, createLine("18", "hot_poesi", "NEJ! Jag vill inte vara i en värld utan choklad!"));
    addLineToContainer(lines, createLine("18", "hot_psykologi", "NEJ! Jag vill inte vara i en värld utan choklad!"));
    addLineToContainer(lines, createLine("18", "hot_kändisskap", "NEJ! Jag vill inte vara i en värld utan choklad!"));



    return lines;
}

const char *importantCategories[] = {"choklad", "poesi", "psykologi", "kändisskap", "mira"};
const int numImportantCategories = 5;

char* cleanInput(char* input);

char* cleanInput(char* input) {
    // Convert all characters to lowercase
    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = tolower(input[i]);
    }

    // Remove newline characters
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\n') {
            input[i] = ' ';
        }
    }

    // Remove double spaces
    int i, j;
    for (i = 0, j = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ' || (i > 0 && input[i - 1] != ' ')) {
            input[j++] = input[i];
        }
    }
    input[j] = '\0';

    return input;
}


char* inference();

char* inference(char* input) {

    input = cleanInput(input);

    TriggerWordContainer* triggerWords = init_ai();
    LineContainer* lines = init_lines();

    char **categories = findCategories(input, triggerWords);
    //fprintf(stderr, "Categories found: %s\n", categories[0]);
    LineContainer* identifiedLines;
    if (categories == NULL) {
        printf("No categories found\n");
        identifiedLines = getLinesByCategory(lines, "no_category");
    } else {
        char* newCategory = "";
        for (int i = 0; categories[i] != NULL; i++) {
            printf("Categories found: %s\n", categories[i]);
            if (strcmp(categories[i], "hot") == 0) {
                printf("Hot category found\n");
                newCategory = "hot";
            }
            if (strcmp(newCategory, "hot") == 0) {
                for (int j = 0; j < numImportantCategories; j++) {
                    if (strcmp(categories[i], importantCategories[j]) == 0) {
                        newCategory = safeCalloc(sizeof(char), 3 + strlen(importantCategories[j]) + 2);
                        strcat(newCategory, "hot_");
                        strcat(newCategory, importantCategories[j]);
                    }
                }
            }
            
        }
        if (strcmp(newCategory, "") == 0) {
            identifiedLines = getLinesByCategory(lines, categories[0]);
        } else {
            identifiedLines = getLinesByCategory(lines, newCategory);
        }
    }

    if (identifiedLines == NULL) {
        identifiedLines = getLinesByCategory(lines, "no_category");
    }
    printf("Identified lines: %s\n", getRandomLine(identifiedLines)->line);

    return getRandomLine(identifiedLines)->line;
}