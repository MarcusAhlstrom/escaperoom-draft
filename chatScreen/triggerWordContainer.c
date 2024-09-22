#include "../includeAll.h"
#include <stdio.h>
#include <string.h>

TriggerWord* createTriggerWord(const char* word, const char* category);
TriggerWordContainer* createTriggerWordContainer();
void addTriggerWord(TriggerWordContainer* container, TriggerWord* word);
char** findCategories(char* str, TriggerWordContainer* container);


// Function to create and return a new trigger word
TriggerWord* createTriggerWord(const char* word, const char* category) {
    TriggerWord *newWord = safeCalloc(1, sizeof(TriggerWord));
    strcpy(newWord->word, word);
    strcpy(newWord->category, category);
    return newWord;
}


// Function to create and return a new trigger word container
TriggerWordContainer* createTriggerWordContainer() {
    TriggerWordContainer* container = safeCalloc(1, sizeof(TriggerWordContainer));
    container->words = (TriggerWord*)safeCalloc(1, sizeof(TriggerWord));
    container->amount = 0;
    return container;
}


// Function to add a trigger word to the container
void addTriggerWord(TriggerWordContainer* container, TriggerWord* word) {
    // Reallocate memory for the words array
    container->words = (TriggerWord*)realloc(container->words, (container->amount + 1) * sizeof(TriggerWord));
    // Add the new word to the container
    container->words[container->amount] = *word;
    // Increment the amount of words in the container
    container->amount++;
}

// Function to find categories of trigger words in a string
char** findCategories(char* str, TriggerWordContainer* container) {
    // Array to store categories
    char** categories = (char**)malloc(container->amount * sizeof(char*));
    int numCategories = 0;

    // Tokenize the string into words
    char* token = strtok(str, " ");
    while (token != NULL) {
        // Compare each word with trigger words in the container
        for (int i = 0; i < container->amount; i++) {
            if (strcmp(token, container->words[i].word) == 0) {
                // Check if the category is already saved
                int categoryExists = 0;
                for (int j = 0; j < numCategories; j++) {
                    if (strcmp(container->words[i].category, categories[j]) == 0) {
                        categoryExists = 1;
                        break;
                    }
                }
                // Save the category if it doesn't exist
                if (!categoryExists) {
                    categories[numCategories] = strdup(container->words[i].category);
                    numCategories++;
                }
                break;
            }
        }
        token = strtok(NULL, " ");
    }

    if (numCategories == 0) {
        return NULL;
    }

    return categories;
}