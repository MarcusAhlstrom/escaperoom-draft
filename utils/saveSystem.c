#include <stdbool.h>
#include "../includeAll.h"


Save* createNewSave();
void saveGame(Save *save);
void loadGame(Save *save);
bool AllCompleted(Save *save);

void saveGame(Save *save) {
    FILE *file = fopen("savegame", "wb");
    if (file == NULL) {
        printf("Error opening save file\n");
        return;
    }
    fwrite(save, sizeof(Save), 1, file);
    fclose(file);
}

void loadGame(Save *save) {
    FILE *file = fopen("savegame", "rb");
    if (file == NULL) {
        printf("Error opening save file\n");
        return;
    }
    fread(save, sizeof(Save), 1, file);
    fclose(file);
}

Save* createNewSave() {
    Save *save = safeCalloc(1, sizeof(Save));
    save->completedPong = false;
    save->completedLabyrinth = false;
    save->completedSimonSays1 = false;
    save->completedSimonSays2 = false;
    save->completedSimonSays3 = false;
    save->completedMath = false;
    save->completedKod = false;
    save->completedWordsearch = false;
    save->completesSecurity = false;
    return save;
}

bool AllCompleted(Save *save) {
    if (save->completedPong && save->completedLabyrinth && save->completedSimonSays1 && save->completedSimonSays2 && save->completedSimonSays3 && save->completedMath && save->completedKod && save->completedWordsearch && save->completesSecurity) {
        return true;
    } else {
        return false;
    }
}