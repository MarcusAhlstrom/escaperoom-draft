#ifndef SAVE_SYSTEM
#define SAVE_SYSTEM

typedef struct {
    bool completedPong;
    bool completedLabyrinth;
    bool completedSimonSays1;
    bool completedSimonSays2;
    bool completedSimonSays3;
    bool completedMath;
    bool completedKod;
    bool completedWordsearch;
    bool completesSecurity;
} Save;

void saveGame(Save *save);
void loadGame(Save *save);
Save* createNewSave();
bool AllCompleted(Save *save);
void pong();

#endif
