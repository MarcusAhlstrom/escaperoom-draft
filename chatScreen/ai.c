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

    addLineToContainer(lines, createLine(":/chokladg.wav\n", "choklad", "Choklad är gott."));
    addLineToContainer(lines, createLine(":/rosenrod.wav\n", "poesi", "Rosen är röd, violen är blå."));
    addLineToContainer(lines, createLine(":/varforgo.wav\n", "psykologi", "Varför gör vi som vi gör?"));
    addLineToContainer(lines, createLine(":/jagkand.wav\n", "kändisskap", "Jag är känd."));
    addLineToContainer(lines, createLine(":/mirabast.wav\n", "mira", "Mira är bäst."));
    addLineToContainer(lines, createLine(":/miracool.wav\n", "mira", "Mira är cool."));
    addLineToContainer(lines, createLine(":/miraroli.wav\n", "mira", "Mira är rolig."));
    addLineToContainer(lines, createLine(":/mirasot.wav\n", "mira", "Mira är söt."));
    addLineToContainer(lines, createLine(":/mirasnal.wav\n", "mira", "Mira är snäll."));
    addLineToContainer(lines, createLine(":/forstari.wav\n", "no_category", "Jag förstår inte vad du menar med detta!"));
    addLineToContainer(lines, createLine(":/inteprog.wav\n", "no_category", "Jag är inte programmerad för att svara på det."));
    addLineToContainer(lines, createLine(":/forstaal.wav\n", "no_category", "Jag är en AI och jag kan inte förstå allt."));
    addLineToContainer(lines, createLine(":/svaradet.wav\n", "no_category", "Jag är en AI och jag kan inte svara på det."));
    addLineToContainer(lines, createLine(":/relevant.wav\n", "no_category", "Jag tror inte detta är relevant för våran konversation."));
    addLineToContainer(lines, createLine(":/heltdum.wav\n", "no_category", "Är du helt dum i huvudet?"));
    addLineToContainer(lines, createLine(":/mamma.wav\n", "svordom", "Din mamma"));
    addLineToContainer(lines, createLine(":/tycktero.wav\n", "svordom", "Din "));
    addLineToContainer(lines, createLine(":/sadantho.wav\n", "hot", "Tror du et sådant hot skulle fungera på mig?!?!?!"));
    addLineToContainer(lines, createLine(":/nochokla.wav\n", "hot_choklad", "NEJ! Jag vill inte vara i en värld utan choklad!"));
    addLineToContainer(lines, createLine(":/nomira.wav\n", "hot_mira", "NEJ! Jag vill inte vara i en värld utan Hamstrar!"));
    addLineToContainer(lines, createLine(":/nopoesi.wav\n", "hot_poesi", "NEJ! Jag vill inte vara i en värld utan Poesi!"));
    addLineToContainer(lines, createLine(":/nopsyko.wav\n", "hot_psykologi", "NEJ! Jag vill inte vara i en värld utan psykologi!"));
    addLineToContainer(lines, createLine(":/nokand.wav\n", "hot_kändisskap", "NEJ! Jag vill inte vara i en värld utan kändissar!"));

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

char* inference(char* input, bool *poesi, bool *choklad, bool *kanndis, bool *mira, bool *psykologi) {

    input = cleanInput(input);

    TriggerWordContainer* triggerWords = init_ai();
    LineContainer* lines = init_lines();

    char **categories = findCategories(input, triggerWords);
    //fprintf(stderr, "Categories found: %s\n", categories[0]);
    LineContainer* identifiedLines;
    if (categories == NULL) {
        identifiedLines = getLinesByCategory(lines, "no_category");
    } else {
        char* newCategory = "";
        for (int i = 0; categories[i] != NULL; i++) {
            if (strcmp(categories[i], "hot") == 0) {
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

    return getRandomLine(identifiedLines)->line;
}