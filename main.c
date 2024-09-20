#include "includeAll.h"

int main(int argc, const char *argv []){
        if(argc == 2){
                int level = atoi(argv[1]);
                switch(level){
                        case 1:
                                loginScreen();
                                break;
                        case 2:
                                twoFaScreen();
                                break;
                        case 3:
                                chatScreen();
                                break;
                        case 4:
                                stageFour();
                                break;
                        case 5:
                                stageFive();
                                break;
                        case 6:
                                stageSix();
                                break;
                        case 7:
                                stageSeven();
                                break;
                        case 8:
                                stageEight();
                                break;
                        case 9:
                                stageNine();
                                break;
                        case 10:
                                stageTen();
                                break;
                        default:
                                loginScreen();
                }
        }else if(argc == 1){
                loginScreen();
        }else{
                printf("Too many arguments");
        }
        //check_usb_sticks(); // Move this from usbChecker to here
        return 0;
}
