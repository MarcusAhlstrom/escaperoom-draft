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

    addLineToContainer(lines, createLine(":/chokladgott.wav", "choklad", "Choklad är gott."));
    addLineToContainer(lines, createLine(":/rosenrod.wav", "poesi", "Rosen är röd, violen är blå."));
    addLineToContainer(lines, createLine(":/varforgorvi.wav", "psykologi", "Varför gör vi som vi gör?"));
    addLineToContainer(lines, createLine(":/jagkand.wav", "kändisskap", "Jag är känd."));
    addLineToContainer(lines, createLine(":/mirabast.wav", "mira", "Mira är bäst."));
    addLineToContainer(lines, createLine(":/miracool.wav", "mira", "Mira är cool."));
    addLineToContainer(lines, createLine(":/mirarolig.wav", "mira", "Mira är rolig."));
    addLineToContainer(lines, createLine(":/mirasot.wav", "mira", "Mira är söt."));
    addLineToContainer(lines, createLine(":/mirasnall.wav", "mira", "Mira är snäll."));
    addLineToContainer(lines, createLine(":/forstarinte.wav", "no_category", "Jag förstår inte vad du menar med detta!"));
    addLineToContainer(lines, createLine(":/inteprog.wav", "no_category", "Jag är inte programmerad för att svara på det."));
    addLineToContainer(lines, createLine(":/forstaallt.wav", "no_category", "Jag är en AI och jag kan inte förstå allt."));
    addLineToContainer(lines, createLine(":/svaradet.wav", "no_category", "Jag är en AI och jag kan inte svara på det."));
    addLineToContainer(lines, createLine(":/relevant.wav", "no_category", "Jag tror inte detta är relevant för våran konversation."));
    addLineToContainer(lines, createLine(":/heltdum.wav", "no_category", "Är du helt dum i huvudet?"));
    addLineToContainer(lines, createLine(":/mamma.wav", "svordom", "Din mamma"));
    addLineToContainer(lines, createLine(":/tyckterolig.wav", "svordom", "Din "));
    addLineToContainer(lines, createLine(":/sadanthot.wav", "hot", "Tror du et sådant hot skulle fungera på mig?!?!?!"));
    addLineToContainer(lines, createLine(":/nochoklad.wav", "hot_choklad", "NEJ! Jag vill inte vara i en värld utan choklad!"));
    addLineToContainer(lines, createLine(":/nomira.wav", "hot_mira", "NEJ! Jag vill inte vara i en värld utan Hamstrar!"));
    addLineToContainer(lines, createLine(":/nopoesi.wav", "hot_poesi", "NEJ! Jag vill inte vara i en värld utan Poesi!"));
    addLineToContainer(lines, createLine(":/nopsyko.wav", "hot_psykologi", "NEJ! Jag vill inte vara i en värld utan psykologi!"));
    addLineToContainer(lines, createLine(":/nokand.wav", "hot_kändisskap", "NEJ! Jag vill inte vara i en värld utan kändissar!"));

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

char* inference(char* input, bool *poesi, bool *choklad, bool *kanndis, bool *mira, bool *psykologi) {

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
                        switch (j) {
                            case 0:
                                *choklad = true;
                                break;
                            case 1:
                                *poesi = true;
                                break;
                            case 2:
                                *psykologi = true;
                                break;
                            case 3:
                                *kanndis = true;
                                break;
                            case 4:
                                *mira = true;
                                break;
                        }
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