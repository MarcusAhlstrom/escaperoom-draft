#include "includeAll.h"

void stageTwo(){
        char *soundfile = safeCalloc(40, sizeof(char));
        strcpy(soundfile, "/usr/share/sounds/alsa/Front_Right.wav");
        playSound(soundfile);
        stageThree();
}
