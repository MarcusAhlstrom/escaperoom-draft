#include "includeAll.h"

int main(int argc, const char *argv []){
        Save *save = createNewSave();
        if(argc == 2){
                int level = atoi(argv[1]);
                switch(level){
                        case 1:
                                loginScreen(save);
                                break;
                        case 2:
                                twoFaScreen(save);
                                break;
                        case 3:
                                chatScreen(save);
                                break;
                        case 4:
                                check_usb_sticks();
                                break;
                        case 5:
                                stageFive(save);
                                break;
                        case 6:
                                stageSix(save);
                                break;
                        case 7:
                                stageSeven(save);
                                break;
                        case 8:
                                stageEight(save);
                                break;
                        case 9:
                                stageNine(save);
                                break;
                        case 10:
                                stageTen(save);
                                break;
                        default:
                                loginScreen(save);
                }
        }else if(argc == 1){
                loginScreen(save);
        }else{
                printf("Too many arguments");
        }
        //check_usb_sticks(); // Move this from usbChecker to here
        return 0;
}
