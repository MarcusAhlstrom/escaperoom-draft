#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* predefined_words[] = {"example", "test", "word", "check"};
const int predefined_words_count = sizeof(predefined_words) / sizeof(predefined_words[0]);

char* processString(const char* input) {
    // Allocate memory for the output string
    char* output = (char*)safeCalloc(sizeof(char), strlen(input) + 1);

    output[0] = '\0'; // Initialize the output string

    // Tokenize the input string
    char* input_copy = strdup(input);
    char* token = strtok(input_copy, " ");
    while (token != NULL) {
        // Check if the token is in the predefined list
        for (int i = 0; i < predefined_words_count; i++) {
            if (strcmp(token, predefined_words[i]) == 0) {
                // Append the word to the output string
                strcat(output, token);
                strcat(output, " ");
                break;
            }
        }
        token = strtok(NULL, " ");
    }

    // Remove the trailing space
    if (strlen(output) > 0) {
        output[strlen(output) - 1] = '\0';
    }

    free(input_copy);
    return output;
}

int main() {
    const char* input = "This is an example test string to check for predefined words.";
    char* result = processString(input);
    printf("Found words: %s\n", result);
    free(result);
    return 0;
}