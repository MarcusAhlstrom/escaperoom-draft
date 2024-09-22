#ifndef TRIGGER_WORD_CONTAINER
#define TRIGGER_WORD_CONTAINER

typedef struct {
    char word[100];
    char category[50];
} TriggerWord;

typedef struct {
    TriggerWord* words;
    int amount;
} TriggerWordContainer;

TriggerWord* createTriggerWord(const char* word, const char* category);
TriggerWordContainer* createTriggerWordContainer();
void addTriggerWord(TriggerWordContainer* container, TriggerWord* word);
char** findCategories(char* str, TriggerWordContainer* container);
#endif
